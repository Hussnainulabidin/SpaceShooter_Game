#ifndef GAMMA_INVADER_H
#define GAMMA_INVADER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Invader.h"

using namespace std;
using namespace sf;

class Gamma_Invader : public Invader
{
public:
    Gamma_Invader() {}
    void display(RenderWindow& window, Enemy*& G_invaders)
    {
        if (this->no_G_invaders != 0)
        {
            Gamma_Invader* temp = dynamic_cast<Gamma_Invader*>(G_invaders);
            for (int i = 0; i < this->no_G_invaders; ++i)
            {
                window.draw(temp[i].sprite);
            }
        }
    }
    void form_Enemy(Enemy*& G_invaders, int size, string formation, float time, int lvl)
    {
        if (size != 0)
        {
            if (lvl == 1)
            {
                fire_speed = 0.4;
                fire_timer = 3;
            }
            else if (lvl == 2)
            {
                fire_speed = 0.5;
                fire_timer = 2;
            }
            else if (lvl == 3)
            {
                fire_speed = 0.6;
                fire_timer = 1;
            }
            this->no_G_invaders = size;
            this->formation = formation;
            int x = 60;
            int y = 200;
            G_invaders = new Gamma_Invader[this->no_G_invaders];
            Gamma_Invader* temp = dynamic_cast<Gamma_Invader*>(G_invaders);
            if (formation == "cross")
            {
                y = 120;
                x = 280;
                for (int i = 0; i < size; ++i)
                {
                    temp[i].timer = time;
                    temp[i].health = 3;
                    temp[i].tex.loadFromFile("img/enemy_3.png");
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
                y = 320;
                x = 160;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        x = 160;
                        y = 20;
                    }
                    temp[i].timer = time;
                    temp[i].health = 3;
                    temp[i].tex.loadFromFile("img/enemy_3.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 360;
                }
            }
            else if (formation == "diamond")
            {
                y = 320;
                x = 280;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        x = 280;
                        y = 20;
                    }
                    temp[i].timer = time;
                    temp[i].health = 3;
                    temp[i].tex.loadFromFile("img/enemy_3.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 160;
                }
            }
            else if (formation == "heart")
            {
                y = 20;
                x = 160;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 4)
                    {
                        y = 320;
                        x = 350;
                    }
                    temp[i].timer = time;
                    temp[i].health = 3;
                    temp[i].tex.loadFromFile("img/enemy_3.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 120;
                }
            }
            else if (formation == "filledrectangle")
            {
                y = 30;
                x = 160;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 2)
                    {
                        y = 100;
                        x = 30;
                    }
                    if (i == 5)
                    {
                        y = 250;
                        x = 260;
                    }
                    temp[i].timer = time;
                    temp[i].health = 3;
                    temp[i].tex.loadFromFile("img/enemy_3.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 300;
                    if (i == 0)
                        x = 500;
                    if (i == 5)
                    {
                        x = 420;
                    }
                }
            }
            else if (formation == "filleddiamond")
            {
                y = 340;
                x = 280;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 4)
                    {
                        x = 280;
                        y -= 160;
                    }
                    if (i == 6)
                    {
                        y = 20;
                        x = 280;
                    }
                    temp[i].timer = time;
                    temp[i].health = 3;
                    temp[i].tex.loadFromFile("img/enemy_3.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 160;
                    if (i == 1)
                    {
                        y = 260;
                        x = 280;
                    }
                }
            }
            else if (formation == "exit")
            {
                y = 20;
                x = 170;
                for (int i = 0; i < size; ++i)
                {
                    if (i == 4)
                    {
                        y = 110;
                        x = 170;
                    }
                    if (i == 8)
                    {
                        y = 320;
                        x = 350;
                    }
                    temp[i].timer = time;
                    temp[i].health = 3;
                    temp[i].tex.loadFromFile("img/enemy_3.png");
                    temp[i].sprite.setTexture(temp[i].tex);
                    temp[i].x = x;
                    temp[i].y = y;
                    temp[i].sprite.setPosition(sf::Vector2f(x, y));
                    temp[i].sprite.setScale(0.6, 0.6);
                    x += 110;
                }
            }

        }
    }
    int Check_laser_collision(Player*& p, Enemy*& G_invaders, int lvl, int& Score, Music& blast)
    {
        bool check = false;
        int hit_counter = 0;
        if (p->laser_count != 0 && no_G_invaders != 0)
        {
            Gamma_Invader* temp = dynamic_cast<Gamma_Invader*>(G_invaders);
            for (int i = 0; i < p->laser_count; ++i)
            {
                for (int j = 0; j < this->no_G_invaders; ++j)
                {
                    if (temp[j].y - 30 <= p->All_Laser[i].y && temp[j].y >= p->All_Laser[i].y && temp[j].x <= p->All_Laser[i].x && temp[j].x + 80 >= p->All_Laser[i].x)
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
                            check = true;
                        }
                    }
                }
            }
            if (hit_counter != 0)
            {
                blast.stop();
                blast.play();
                int kill_counter = 0;
                for (int j = 0; j < this->no_G_invaders; ++j)
                {
                    if (temp[j].health <= 0)
                        kill_counter += 1;
                }
                Score += (lvl * 30) * kill_counter;
                Gamma_Invader* temp_G_invaders = temp;
                temp = new Gamma_Invader[this->no_G_invaders - kill_counter];
                int k = 0;
                for (int j = 0; j < this->no_G_invaders; ++j)
                {
                    if (temp_G_invaders[j].health <= 0)
                        continue;
                    temp[k] = temp_G_invaders[j];
                    k++;
                }
                this->no_G_invaders -= kill_counter;
                delete[] temp_G_invaders;
                if (this->no_G_invaders != 0)
                {
                    G_invaders = new Gamma_Invader[this->no_G_invaders];
                    Gamma_Invader* temp1 = dynamic_cast<Gamma_Invader*>(G_invaders);
                    for (int i = 0; i < this->no_G_invaders; ++i)
                    {
                        temp1[i].health = temp[i].health;
                        temp1[i].tex.loadFromFile("img/enemy_3.png");
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
        return this->no_G_invaders;
    }
    void Invader_bomb(Enemy*& G_invaders, Bomb*& All_bomb, int& no_of_bomb, float current_time)
    {
        if (this->no_G_invaders != 0)
        {
            srand(time(NULL));
            Bomb b1;
            Gamma_Invader* temp = dynamic_cast<Gamma_Invader*>(G_invaders);
            int proablity = 0;
            for (int i = 0; i < this->no_G_invaders; ++i)
            {
                if (temp[i].timer + fire_timer < current_time)
                {
                    temp[i].timer = current_time;
                    proablity = rand() % 100;
                    if (proablity > 50)
                        continue;
                    no_of_bomb += 1;
                    enemy_bomb = new Bomb("img/PNG/Lasers/laserGreen14.png", fire_speed, temp[i].x, temp[i].y, 1, 1);

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
        if (no_G_invaders != 0)
        {
            Gamma_Invader* temp = dynamic_cast<Gamma_Invader*>(enemy);
            for (int i = 0; i < no_G_invaders; ++i)
            {
                if (temp[i].x >= p->x - 30 && temp[i].x <= p->x + 30 && temp[i].y >= p->y - 50 && temp[i].y <= p->y + 50)
                {
                    p->lives -= 1;
                    p->x = 340;
                    p->y = 600;
                }
            }
        }
    }
};

#endif