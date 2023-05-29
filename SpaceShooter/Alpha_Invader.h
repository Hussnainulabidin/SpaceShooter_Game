#ifndef ALPHA_INVADER_H
#define ALPHA_INVADER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include <string.h>
#include "Invader.h"

using namespace std;
using namespace sf;

class Alpha_Invader : public Invader
{
public:
    Alpha_Invader() {}

    void display(RenderWindow& window, Enemy*& A_invaders)
    {
        if (this->no_A_invaders != 0)
        {
            Alpha_Invader* temp = dynamic_cast<Alpha_Invader*>(A_invaders);
            for (int i = 0; i < this->no_A_invaders; ++i)
            {
                window.draw(temp[i].sprite);
            }
        }
    }
    void form_Enemy(Enemy*& A_invaders, int size, string formation, float time, int lvl)
    {
        if (size != 0)
        {
            if (lvl == 1)
            {
                fire_speed = 0.2;
                fire_timer = 6;
            }
            else if (lvl == 2)
            {
                fire_speed = 0.3;
                fire_timer = 5;
            }
            else if (lvl == 3)
            {
                fire_speed = 0.4;
                fire_timer = 4;
            }
            this->no_A_invaders = size;
            this->formation = formation;
            int x = 60;
            int y = 200;
            A_invaders = new Alpha_Invader[this->no_A_invaders];
            Alpha_Invader* temp = dynamic_cast<Alpha_Invader*>(A_invaders);
            for (int i = 0; i < size; ++i)
            {
                temp[i].timer = time;
                temp[i].health = 1;
                temp[i].tex.loadFromFile("img/enemy_1.png");
                temp[i].sprite.setTexture(temp[i].tex);
                if (this->formation == "triangle")
                {
                    if (i == 0)
                    {
                        y = 300;
                    }
                    if (i == 6 || i == 10 || i == 8)
                    {
                        y -= 85;
                        x = 60;
                    }
                    temp[i].x = x;
                    temp[i].y = y;
                    x += 120;
                    if (i == 6 || i == 10 || i == 8)
                        x = 660;
                }
                else if (this->formation == "cross")
                {
                    y = 300;
                    temp[i].x = x;
                    temp[i].y = y;
                    x += 120;
                }
                else if (this->formation == "circle")
                {
                    if (i == 0)
                    {
                        y = 430;
                    }
                    if (i == 0 || i == 2 || i == 4 || i == 5 || i == 7)
                    {
                        y -= 90;
                        x = 60;
                        if (i == 4)
                        {
                            y += 15;
                            x = 350;
                        }
                        if (i == 5)
                            y += 25;
                    }
                    temp[i].x = x;
                    temp[i].y = y;
                    x += 120;
                    if (i == 0 || i == 2 || i == 4 || i == 5 || i == 7)
                        x = 660;
                }
                else if (this->formation == "diamond")
                {
                    if (i == 0)
                    {
                        y = 180;
                        x = 80;
                    }
                    temp[i].x = x;
                    temp[i].y = y;
                    x += 120;
                    if (i == 0)
                        x = 640;
                }
                else if (this->formation == "heart")
                {
                    if (i == 0)
                    {
                        y = 270;
                        x = 260;
                    }
                    temp[i].x = x;
                    temp[i].y = y;
                    if (i == 0)
                        x = 450;
                }
                if (this->formation == "filledcircle")
                {
                    if (i == 0)
                    {
                        y = 300;
                    }
                    if (i == 6 || i == 12 || i == 18)
                    {
                        y -= 85;
                        x = 60;
                    }
                    temp[i].x = x;
                    temp[i].y = y;
                    x += 120;
                    if (i == 18)
                        x = 660;
                }
                else if (this->formation == "filleddiamond")
                {
                    if (i == 0)
                    {
                        y = 180;
                        x = 80;
                    }
                    temp[i].x = x;
                    temp[i].y = y;
                    x += 122;

                }
                else if (this->formation == "exit")
                {
                    if (i == 0)
                    {
                        y = 270;
                        x = 260;
                    }
                    temp[i].x = x;
                    temp[i].y = y;
                    x += 90;
                }
                temp[i].sprite.setPosition(sf::Vector2f(temp[i].x, temp[i].y));
                temp[i].sprite.setScale(0.6, 0.6);
            }
        }
    }
    int Check_laser_collision(Player*& p, Enemy*& A_invaders, int lvl, int& Score, Music& blast)
    {
        bool check = false;
        int hit_counter = 0;
        if (p->laser_count != 0 && no_A_invaders != 0)
        {
            Alpha_Invader* temp = dynamic_cast<Alpha_Invader*>(A_invaders);
            for (int i = 0; i < p->laser_count; ++i)
            {
                for (int j = 0; j < this->no_A_invaders; ++j)
                {
                    if (temp[j].y - 30 <= p->All_Laser[i].y && temp[j].y >= p->All_Laser[i].y && temp[j].x <= p->All_Laser[i].x && temp[j].x + 60 >= p->All_Laser[i].x)
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
                for (int j = 0; j < this->no_A_invaders; ++j)
                {
                    if (temp[j].health <= 0)
                        kill_counter += 1;
                }
                Score += (lvl * 10) * kill_counter;
                Alpha_Invader* temp_A_invaders = temp;
                temp = new Alpha_Invader[no_A_invaders - kill_counter];
                int k = 0;
                for (int j = 0; j < this->no_A_invaders; ++j)
                {
                    if (temp_A_invaders[j].health <= 0)
                        continue;
                    temp[k] = temp_A_invaders[j];
                    k++;
                }
                this->no_A_invaders -= kill_counter;
                delete[] temp_A_invaders;
                if (this->no_A_invaders != 0)
                {
                    A_invaders = new Alpha_Invader[no_A_invaders];
                    Alpha_Invader* temp1 = dynamic_cast<Alpha_Invader*>(A_invaders);
                    for (int i = 0; i < this->no_A_invaders; ++i)
                    {
                        temp1[i].health = temp[i].health;
                        temp1[i].tex.loadFromFile("img/enemy_1.png");
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
        return this->no_A_invaders;
    }
    void Invader_bomb(Enemy*& A_invaders, Bomb*& All_bomb, int& no_of_bomb, float current_time)
    {
        if (this->no_A_invaders != 0)
        {
            srand(time(NULL));
            Bomb b1;
            Alpha_Invader* temp = dynamic_cast<Alpha_Invader*>(A_invaders);
            for (int i = 0; i < this->no_A_invaders; ++i)
            {
                if (temp[i].timer + fire_timer < current_time)
                {
                    temp[i].timer = current_time;
                    int proablity = rand() % 2;
                    if (proablity == 0)
                        continue;
                    no_of_bomb += 1;
                    enemy_bomb = new Bomb("img/enemy_laser.png", fire_speed, temp[i].x, temp[i].y, 1, 1);

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
        if (no_A_invaders != 0)
        {
            Alpha_Invader* temp = dynamic_cast<Alpha_Invader*>(enemy);
            for (int i = 0; i < no_A_invaders; ++i)
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

#endif