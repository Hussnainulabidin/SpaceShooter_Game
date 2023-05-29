#ifndef Dragon_H
#define Dragon_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <string.h>
#include "Enemy.h"

using namespace std;
using namespace sf;

class Dragon : public Enemy
{
public:
    Sprite sprite1;
    Sprite sprite2;
    Texture tex1;
    Texture tex2;
    float x1, y1, x2, y2;

    bool is_formed = false;
    bool attack;
    float on_screen_time;

    float player_position = 0;
    float posi = 0;
    float player_posi_time = 0;

    Dragon()
    {
        this->is_formed = false;
        this->on_screen_time = 0;
        this->attack = false;
    }
    void display(RenderWindow& window, Enemy*& dragon)
    {
        if (dragon != nullptr)
        {
            Dragon* temp = dynamic_cast<Dragon*>(dragon);
            window.draw(temp->sprite);
            window.draw(temp->sprite1);
            window.draw(temp->sprite2);
        }
    }
    void form_Enemy(Enemy*& dragon, int formed, string formation, float current_time, int lvl)
    {
        if (this->is_formed == false)
        {
            dragon = new Dragon;
            Dragon* temp = dynamic_cast<Dragon*>(dragon);
            this->is_formed = formed;
            temp->on_screen_time = current_time;
            temp->timer = current_time;
            temp->player_posi_time = 0;
            temp->attack = false;
            temp->tex.loadFromFile("img/dragon2.png");
            temp->sprite.setTexture(temp->tex);
            temp->speed = 1;
            temp->x = 100;
            temp->y = 5;
            temp->sprite.setPosition(sf::Vector2f(temp->x, temp->y));
            temp->sprite.setScale(0.8, 0.5);

            temp->tex1.loadFromFile("img/dragonleft.png");
            temp->sprite1.setTexture(temp->tex1);
            temp->x1 = 530;
            temp->y1 = 150;
            temp->sprite1.setPosition(sf::Vector2f(530, 150));
            temp->sprite1.setScale(0.8, 0.8);

            temp->tex2.loadFromFile("img/dragon1right.png");
            temp->sprite2.setTexture(temp->tex2);
            temp->x2 = -10;
            temp->y2 = 150;
            temp->sprite2.setPosition(sf::Vector2f(-10, 150));
            temp->sprite2.setScale(0.8, 0.8);
        }
    }
    bool check_Enemy(Music& alert)
    {
        srand(time(NULL));
        int num1 = rand() % 101;
        if (num1 > 21 && num1 < 23 && this->is_formed == false)
        {
            alert.stop();
            alert.play();
            return true;
        }
        if (this->is_formed == true)
        {
            return true;
        }
        return false;
    }
    bool mosnter_attack(Enemy*& dragon, Bomb*& dragon_bomb, int& no_of_bomb, float current_time, float player_x, Music& laser)
    {
        Dragon* temp = dynamic_cast<Dragon*>(dragon);
        if (temp->player_position == 0)
        {
            temp->player_posi_time = current_time;
            temp->player_position = player_x;
        }
        if (temp->player_posi_time + 4 < current_time)
        {
            temp->player_position = player_x;
            temp->player_posi_time = current_time;
        }
        if (temp->timer + 4 < current_time)
        {
            laser.stop();
            temp->attack = false;
            temp->timer = current_time;
            dragon_bomb = nullptr;
        }
        else if (temp->timer + 2 < current_time && dragon_bomb == nullptr && temp->attack == false)
        {
            laser.play();
            temp->attack = true;
            if (temp->player_position >= 191 && temp->player_position <= 485)
                dragon_bomb = new Bomb("img/PNG/Effects/fire05.png", 0.3, temp->x + 140, temp->y + 50, 20, 25);
            else if (temp->player_position > 485)
                dragon_bomb = new Bomb("img/PNG/Effects/fire05(1)right.png", 0.3, temp->x2, temp->y2 + 60, 30, 16);
            else if (temp->player_position < 191)
                dragon_bomb = new Bomb("img/PNG/Effects/fire05left.png", 0.3, -200, temp->y1 + 60, 30, 16);
        }
        if (temp->on_screen_time + 10 < current_time)
        {
            delete dragon;
            dragon = nullptr;
            delete dragon_bomb;
            dragon_bomb = nullptr;
            this->is_formed = false;
            return true;
        }
        return false;
    }
    bool check_Dragon_Laser_Collision(Enemy*& dragon, Player*& p, Bomb*& dragon_Bomb, Music& hit)
    {
        if (p->add_on != nullptr)
            if (p->add_on->type == "power_up")
                return false;
        if (dragon_Bomb != nullptr && dragon != nullptr)
        {
            Dragon* temp = dynamic_cast<Dragon*>(dragon);
            if (dragon_Bomb->x == 240 && p->x >= 191 && p->x <= 485)
            {
                //--------------------------------------------------
                hit.stop();
                hit.openFromFile("sound/ka8wt-uklpq.wav");
                hit.play();
                //-------------------------------------------------
                delete dragon_Bomb;
                dragon_Bomb = nullptr;
                p->lives -= 1;
            }
            else if (dragon_Bomb->x == -10 && p->x > 485)
            {
                //-------------------------------------------------
                hit.stop();
                hit.openFromFile("sound/ka8wt-uklpq.wav");
                hit.play();
                //-------------------------------------------------
                delete dragon_Bomb;
                dragon_Bomb = nullptr;
                p->lives -= 1;
            }
            else if (dragon_Bomb->x == -200 && p->x < 191)
            {
                //-------------------------------------------------
                hit.stop();
                hit.openFromFile("sound/ka8wt-uklpq.wav");
                hit.play();
                //-------------------------------------------------
                delete dragon_Bomb;
                dragon_Bomb = nullptr;
                p->lives -= 1;
            }
            if (p->lives == 0)
                return true;
        }
        return false;
    }
    void check_enemy_player_collsion(Player*& p, Enemy*& enemy)
    {
        if (enemy != nullptr)
        {
            Dragon* temp = dynamic_cast<Dragon*>(enemy);

            //---Inrementing Dragon X and Y upto hit Box to check if any contact of Player with Dragon---

            if (temp->x <= p->x && temp->x + 450 >= p->x && temp->y - 200 <= p->y && temp->y + 250 >= p->y)
            {
                p->lives -= 1;
                p->x = 340;
                p->y = 600;
            }
            else if (temp->x1 <= p->x && temp->x1 + 200 >= p->x && temp->y1 - 200 <= p->y && temp->y1 + 200 >= p->y)
            {
                p->lives -= 1;
                p->x = 340;
                p->y = 600;
            }
            else if (temp->x2 <= p->x && temp->x2 + 200 >= p->x && temp->y2 - 200 <= p->y && temp->y2 + 200 >= p->y)
            {
                p->lives -= 1;
                p->x = 340;
                p->y = 600;
            }
        }
    }
};

#endif