#ifndef BOMB_H
#define BOMB_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Invader.h"

class Bomb
{
public:
    Sprite sprite;
    Texture tex;
    float bomb_speed;
    float x, y;
    Bomb()
    {
        x = 0;
        y = 0;
    }
    Bomb(string png_path, float speed, int x, int y, float scalex, float scaley)
    {
        this->bomb_speed = speed;
        this->tex.loadFromFile(png_path);
        this->sprite.setTexture(tex);
        this->x = x;
        this->y = y;
        this->sprite.setPosition(Vector2f(this->x, this->y));
        this->sprite.setScale(scalex, scaley);
    }
    void operator=(Bomb& bomb)
    {
        this->bomb_speed = bomb.bomb_speed;
        this->tex = bomb.tex;
        this->sprite = bomb.sprite;
        this->x = bomb.x;
        this->y = bomb.y;
        this->sprite.setPosition(Vector2f(this->x, this->y));
        this->sprite.setScale(1, 1);
    }
    void Set_All_Bomb(Bomb*& All_bomb, Bomb*& new_bomb, int& bomb_count)
    {
        Bomb* temp_bomb = All_bomb;
        All_bomb = new Bomb[bomb_count];
        for (int i = 0; i < bomb_count - 1; ++i)
        {
            All_bomb[i] = temp_bomb[i];
        }
        All_bomb[bomb_count - 1] = *new_bomb;
    }
    void bomb_move()
    {
        y += bomb_speed;
        sprite.move(0, +bomb_speed);
    }
    void laser_float(float x, float y)
    {
        this->x = x;
        this->y = y;
        sprite.setPosition(x, y);
    }
    void Remove_bomb_exceeding_window_limit(Bomb*& All_bomb, int& no_of_bomb)
    {
        int exceed_count = 0;
        for (int i = 0; i < no_of_bomb; ++i)
        {
            if (All_bomb[i].y >= 780)
            {

                exceed_count += 1;
            }
        }
        if (exceed_count != 0)
        {
            Bomb* temp_bomb = All_bomb;
            All_bomb = new Bomb[no_of_bomb - exceed_count];
            int j = 0;
            for (int i = 0; i < no_of_bomb; ++i)
            {
                if (temp_bomb[i].y >= 780)
                    continue;
                // All_bomb[j] = temp_bomb[i];
                All_bomb[j].bomb_speed = temp_bomb[i].bomb_speed;
                All_bomb[j].tex = temp_bomb[i].tex;
                All_bomb[j].sprite.setTexture(All_bomb[j].tex);
                int x = All_bomb[j].x = temp_bomb[i].x;
                int y = All_bomb[j].y = temp_bomb[i].y;
                All_bomb[j].sprite.setPosition(sf::Vector2f(x, y));
                All_bomb[j].sprite.setScale(1, 1);
                j++;
            }
            no_of_bomb -= exceed_count;
            delete[] temp_bomb;
        }
    }
    bool check_Bullet_Player_Collision(Player*& p, Bomb*& All_Bomb, int& no_of_bomb, Music& hit)
    {
        if (p->add_on != nullptr)
            if (p->add_on->type == "power_up")
                return false;
        for (int i = 0; i < no_of_bomb; ++i)
        {
            if (All_Bomb[i].y >= p->y - 20 && All_Bomb[i].y <= p->y + 20 && All_Bomb[i].x >= p->x - 20 && All_Bomb[i].x <= p->x + 60)
            {
                hit.stop();
                hit.openFromFile("sound/ka8wt-uklpq.wav");
                hit.play();
                p->lives -= 1;
                Bomb* temp1 = All_Bomb;
                All_Bomb = new Bomb[no_of_bomb - 1];
                int k = 0;
                for (int j = 0; j < no_of_bomb; ++j)
                {
                    if (j == i)
                        continue;
                    All_Bomb[k].bomb_speed = temp1[j].bomb_speed;
                    All_Bomb[k].tex = temp1[j].tex;
                    All_Bomb[k].sprite.setTexture(All_Bomb[k].tex);
                    int x = All_Bomb[k].x = temp1[j].x;
                    int y = All_Bomb[k].y = temp1[j].y;
                    All_Bomb[k].sprite.setPosition(sf::Vector2f(x, y));
                    All_Bomb[k].sprite.setScale(1, 1);
                    k++;
                }
                no_of_bomb -= 1;
                delete[] temp1;
                return true;
            }
        }
        // if (p->lives == 0)
        //     return true;
        return false;
    }
    bool check_Laser_Player_Collision(Player*& p, Bomb*& monster_Bomb, Music& hit)
    {
        if (p->add_on != nullptr)
            if (p->add_on->type == "power_up")
                return false;
        if (monster_Bomb != nullptr)
        {

            if (p->x <= monster_Bomb->x + 20 && p->x >= monster_Bomb->x + 10)
            {
                hit.stop();
                hit.openFromFile("sound/ka8wt-uklpq.wav");
                hit.play();
                delete monster_Bomb;
                monster_Bomb = nullptr;
                p->lives -= 1;
            }
        }
        if (p->lives == 0)
        {
            return true;
        }
        return false;
    }

};

#endif