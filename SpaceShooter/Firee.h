#ifndef FIREE_H
#define FIREE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <ctime>
#include "Add_On.h"

using namespace std;
using namespace sf;

class Firee : public Add_On
{
public:

    Firee()
    {
        this->tex.loadFromFile("img/PNG/Power-ups/powerupBlue_star.png");
        this->sprite.setTexture(this->tex);
        this->type = "firee";
        speed = 0.2;
    }
    bool check_proablity()
    {
        srand(time(NULL));
        if (this->formation)
            return false;
        int num1 = rand() % 101;
        if (num1 > 90 && num1 < 95)
        {
            this->formation = true;
            return true;
        }
        return false;
    }
    void Create_Add_On(int& score)
    {
        srand(time(NULL));
        bool check = false;
        check = this->check_proablity();
        if (check)
        {
            // fire_sound.openFromFile("sound/salamisound-3564437-sfx-laser-gun-5-games.wav");
            this->x = rand() % 650 + 50;
            this->y = 0;
            this->sprite.setPosition(x, y);
        }
        if (this->formation)
        {
            this->move();
            this->remove_AddOn_exceeding_window_limit();
        }
    }
    void move()
    {
        y += speed;
        sprite.move(0, +speed);
    }
    bool remove_AddOn_exceeding_window_limit()
    {
        if (this->y > 780)
        {
            this->formation = false;
            return true;
        }
        return false;
    }
};

#endif