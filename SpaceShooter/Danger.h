#ifndef DANGER_H
#define DANGER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <ctime>
#include "Add_On.h"

using namespace std;
using namespace sf;

class Danger : public Add_On
{
public:
    Danger()
    {
        this->tex.loadFromFile("img/PNG/Meteors/meteorBrown_big1.png");
        this->sprite.setTexture(this->tex);
        this->sprite.setScale(0.9, 0.9);
        this->type = "danger";
        speed = 0.5;
    }
    bool check_proablity()
    {
        srand(time(NULL));
        if (this->formation)
            return false;
        int num1 = rand() % 101;
        if (num1 > 70 && num1 < 80)
        {
            this->formation = true;
            return true;
        }
        return false;
    }
    void Create_Add_On(int& Score)
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
            check = false;
            this->move();
            check = this->remove_AddOn_exceeding_window_limit();
            if (check == true)
                Score += 5;
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