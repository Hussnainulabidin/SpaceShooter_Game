#ifndef LIVE_H
#define LIVE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <ctime>
#include "Add_On.h"

using namespace std;
using namespace sf;

class Live : public Add_On
{
public:
    Live()
    {
        this->tex.loadFromFile("img/PNG/Power-ups/powerupBlue(1).png");
        this->sprite.setTexture(this->tex);
        this->sprite.setScale(1, 1);
        this->type = "live";
        speed = 0.3;
    }
    bool check_proablity()
    {
        srand(time(NULL));
        if (this->formation)
            return false;
        int num1 = rand() % 101;
        if (num1 > 33 && num1 < 35)
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
        this->y += this->speed;
        this->sprite.move(0, +speed);
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