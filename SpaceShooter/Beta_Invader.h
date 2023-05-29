#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Invader.h"

using namespace std;
using namespace sf;

class Beta_Invader : public Invader
{
public:
    Beta_Invader()
    {
    }
    void display(RenderWindow& window, Enemy*& B_invaders)
    {
        if (no_B_invaders != 0)
        {
            Beta_Invader* temp = dynamic_cast<Beta_Invader*>(B_invaders);
            for (int i = 0; i < this->no_B_invaders; ++i)
            {
                window.draw(temp[i].sprite);
            }
        }
    }
    void form_Enemy(Enemy*& B_invaders, int size, string formation, float time, int lvl)
    {
        if (size != 0)
        {
            if (lvl == 1)
            {
                fire_speed = 0.2;
                fire_timer = 5;
            }
            else if (lvl == 2)
            {
                fire_speed = 0.4;
                fire_timer = 4;
            }
            else if (lvl == 3)
            {
                fire_speed = 0.5;
                fire_timer = 2;
            }
            this->no_B_invaders = size;
            this->formation = formation;
            int x = 60;
            int y = 200;
            B_invaders = new Beta_Invader[this->no_B_invaders];
            Beta_Invader* temp = dynamic_cast<Beta_Invader*>(B_invaders);
            if (this->formation == "triangle" || this->formation == "filledcircle")
            {
                x = 180;
                y = 30;
                for (int i = 0; i < size; ++i)
                {
                    temp[i].timer = time;
                    temp[i].health = 2;
                    temp[i].tex.loadFromFile("img/enemy_2.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 120;
                }
            }
            else if (formation == "cross")
            {
                y = 200;
                x = 180;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 4)
                    {
                        y = 20;
                        x = 360;
                    }
                    temp[i].timer = time;
                    temp[i].health = 2;
                    temp[i].tex.loadFromFile("img/enemy_2.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 120;
                }
            }
            else if (formation == "circle")
            {
                y = 230;
                x = 260;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        y = 90;
                        x = 260;
                    }
                    temp[i].timer = time;
                    temp[i].health = 2;
                    temp[i].tex.loadFromFile("img/enemy_2.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 200;
                }
            }
            else if (formation == "diamond" || formation == "filleddiamond")
            {
                y = 260;
                x = 180;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        y -= 180;
                        x = 180;
                    }
                    temp[i].timer = time;
                    temp[i].health = 2;
                    temp[i].tex.loadFromFile("img/enemy_2.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 380;
                }
            }
            else if (formation == "heart")
            {
                y = 100;
                x = 80;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        y = 180;
                        x = 170;
                    }
                    temp[i].timer = time;
                    temp[i].health = 2;
                    temp[i].tex.loadFromFile("img/enemy_2.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 550;
                    if (i == 2)
                    {
                        x = 540;
                    }
                }
            }
            else if (formation == "filledrectangle")
            {
                y = 180;
                x = 170;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        y = 350;
                        x = 350;
                    }
                    temp[i].timer = time;
                    temp[i].health = 2;
                    temp[i].tex.loadFromFile("img/enemy_2.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 360;
                }
            }
            else if (formation == "exit")
            {
                cout << no_B_invaders << endl;
                y = 110;
                x = 100;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        y = 180;
                        x = 170;
                    }
                    temp[i].timer = time;
                    temp[i].health = 2;
                    temp[i].tex.loadFromFile("img/enemy_2.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 90;

                    if (i == 0)
                    {
                        x = 600;
                    }
                }
            }
        }
    }
    int Check_laser_collision(Player*& p, Enemy*& B_invaders, int lvl, int& Score, Music& blast)
    {
        int hit_counter = 0;
        if (p->laser_count != 0 && no_B_invaders != 0)
        {

            Beta_Invader* temp = dynamic_cast<Beta_Invader*>(B_invaders);
            for (int i = 0; i < p->laser_count; ++i)
            {
                for (int j = 0; j < this->no_B_invaders; ++j)
                {
                    if (temp[j].y - 2 < p->All_Laser[i].y && temp[j].y > p->All_Laser[i].y && temp[j].x <= p->All_Laser[i].x && temp[j].x + 60 >= p->All_Laser[i].x)
                    {
                        if (p->add_on == nullptr)
                        {
                            p->remove_Laser(i);
                        }
                        else if (p->add_on != nullptr)
                        {
                            if (p->add_on->type != "firee")
                                p->remove_Laser(i);
                        }
                        temp[j].health -= 1;
                        if (temp[j].health <= 0)
                        {
                            hit_counter += 1;
                        }
                    }
                }
            }
            if (hit_counter != 0)
            {
                blast.stop();
                blast.play();
                int kill_counter = 0;
                for (int j = 0; j < this->no_B_invaders; ++j)
                {
                    if (temp[j].health <= 0)
                        kill_counter += 1;
                }
                Score += (lvl * 20) * kill_counter;
                Beta_Invader* temp_B_invaders = temp;
                temp = new Beta_Invader[no_B_invaders - kill_counter];
                int k = 0;
                for (int j = 0; j < this->no_B_invaders; ++j)
                {
                    if (temp_B_invaders[j].health <= 0)
                        continue;
                    temp[k] = temp_B_invaders[j];
                    k++;
                }
                this->no_B_invaders -= kill_counter;
                delete[] temp_B_invaders;
                if (this->no_B_invaders != 0)
                {
                    B_invaders = new Beta_Invader[no_B_invaders];
                    Beta_Invader* temp1 = dynamic_cast<Beta_Invader*>(B_invaders);
                    for (int i = 0; i < this->no_B_invaders; ++i)
                    {
                        temp1[i].health = temp[i].health;
                        temp1[i].tex.loadFromFile("img/enemy_2.png");
                        temp1[i].sprite.setTexture(temp1[i].tex);
                        int x = temp1[i].x = temp[i].x;
                        int y = temp1[i].y = temp[i].y;
                        temp1[i].sprite.setPosition(sf::Vector2f(x, y));
                        temp1[i].sprite.setScale(0.6, 0.6);
                    }
                }
                delete[] temp;
            }
        }
        return this->no_B_invaders;
    }
    void Invader_bomb(Enemy*& B_invaders, Bomb*& All_bomb, int& no_of_bomb, float current_time)
    {
        if (this->no_B_invaders != 0)
        {
            srand(time(NULL));
            Bomb b1;
            Beta_Invader* temp = dynamic_cast<Beta_Invader*>(B_invaders);
            for (int i = 0; i < this->no_B_invaders; ++i)
            {
                if (temp[i].timer + this->fire_timer < current_time)
                {
                    temp[i].timer = current_time;
                    int proablity = rand() % 2;
                    if (proablity == 0)
                        continue;
                    no_of_bomb += 1;
                    enemy_bomb = new Bomb("img/PNG/Lasers/laserGreen01.png", this->fire_speed, temp[i].x, temp[i].y, 1, 1);

                    Bomb* temp1 = All_bomb;
                    All_bomb = new Bomb[no_of_bomb];
                    for (int i = 0; i < no_of_bomb - 1; ++i)
                    {
                        All_bomb[i].bomb_speed = temp1[i].bomb_speed;
                        All_bomb[i].tex = temp1[i].tex;
                        All_bomb[i].sprite.setTexture(All_bomb[i].tex);
                        int x = All_bomb[i].x = temp1[i].x;
                        int y = All_bomb[i].y = temp1[i].y;
                        All_bomb[i].sprite.setPosition(sf::Vector2f(x, y));
                        All_bomb[i].sprite.setScale(1, 1);
                    }
                    All_bomb[no_of_bomb - 1] = *enemy_bomb;
                    delete[] temp1;
                }
            }
            b1.Remove_bomb_exceeding_window_limit(All_bomb, no_of_bomb);
        }
    }
    void check_enemy_player_collsion(Player*& p, Enemy*& enemy)
    {
        if (no_B_invaders != 0)
        {
            Beta_Invader* temp = dynamic_cast<Beta_Invader*>(enemy);
            for (int i = 0; i < no_B_invaders; ++i)
            {
                if (temp[i].x >= p->x - 20 && temp[i].x <= p->x + 20 && temp[i].y >= p->y - 40 && temp[i].y <= p->y + 40)
                {
                    p->lives -= 1;
                    p->x = 340;
                    p->y = 600;
                }
            }
        }
    }
};