#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <string.h>
#include "Enemy.h"

using namespace std;
using namespace sf;

class Monster : public Enemy
{
public:
    bool is_formed = false;
    bool move_left_right;
    bool attack;
    float on_screen_time;

    Monster()
    {
        this->is_formed = false;
        this->on_screen_time = 0;
        this->attack = false;
    }
    void display(RenderWindow& window, Enemy*& monster)
    {
        if (monster != nullptr)
        {
            Monster* temp = dynamic_cast<Monster*>(monster);
            temp->move();
            window.draw(temp->sprite);
        }
    }
    void form_Enemy(Enemy*& monster, int formed, string formation, float current_time, int lvl)
    {
        if (this->is_formed == false)
        {
            monster = new Monster;
            Monster* temp = dynamic_cast<Monster*>(monster);
            this->is_formed = formed;
            temp->on_screen_time = current_time;
            temp->timer = current_time;
            temp->attack = false;
            temp->tex.loadFromFile("img/monster.png");
            temp->sprite.setTexture(temp->tex);
            temp->speed = 1;
            temp->x = 250;
            temp->y = 20;
            temp->sprite.setPosition(sf::Vector2f(temp->x, temp->y));
            temp->sprite.setScale(0.2, 0.2);
            cout << "1" << endl;
        }
    }
    bool check_Enemy(Music& alert)
    {
        srand(time(NULL));
        int num1 = rand() % 101;
        if (num1 >= 50 && num1 <= 53 && this->is_formed == false)
        {
            alert.stop();
            alert.play();
            cout << num1 << endl;
            return true;
        }
        if (this->is_formed == true)
        {
            return true;
        }
        return false;
    }
    bool mosnter_attack(Enemy*& monster, Bomb*& monster_bomb, int& no_of_bomb, float current_time, float player_x, Music& laser)
    {
        Monster* temp = dynamic_cast<Monster*>(monster);
        if (temp->timer + 4 < current_time)
        {
            laser.stop();
            temp->attack = false;
            temp->timer = current_time;
            monster_bomb = nullptr;
        }
        else if (temp->timer + 2 < current_time && monster_bomb == nullptr && temp->attack == false)
        {
            laser.play();
            temp->attack = true;
            monster_bomb = new Bomb("img/PNG/Effects/fire16.png", 0.3, temp->x + 150, temp->y, 10, 26);
        }
        if (monster_bomb != nullptr)
        {
            monster_bomb->laser_float(temp->x + 80, temp->y);
        }
        if (temp->on_screen_time + 10 < current_time)
        {
            delete monster;
            monster = nullptr;
            delete monster_bomb;
            monster_bomb = nullptr;
            this->is_formed = false;
            return true;
        }
        return false;
    }
    void move()
    {
        if (move_left_right)
        {
            this->x -= speed;
            this->sprite.move(-speed, 0);
            if (this->x < -140)
            {
                move_left_right = false;
            }
        }
        else
        {
            this->x += speed;
            this->sprite.move(+speed, 0);
            if (this->x > 620)
            {
                move_left_right = true;
            }
        }
    }
    void check_enemy_player_collsion(Player*& p, Enemy*& enemy)
    {
        if (enemy != nullptr)
        {
            Monster* temp = dynamic_cast<Monster*>(enemy);

            if (temp->x <= p->x && temp->x + 250 >= p->x && temp->y - 200 <= p->y && temp->y + 300 >= p->y)
            {
                p->lives -= 1;
                p->x = 340;
                p->y = 600;
            }
        }
    }
};

#endif
