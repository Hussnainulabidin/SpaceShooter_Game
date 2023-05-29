#ifndef INVADER_H
#define INVADER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Enemy.h"
#include "Alpha_Invader.h"

using namespace std;
using namespace sf;

class Invader : public Enemy
{
public:
    int no_A_invaders;
    int no_B_invaders;
    int no_G_invaders;
    string formation;

    Invader()
    {
        formation = "rectangle";
        no_A_invaders = 0;
        no_B_invaders = 0;
        no_G_invaders = 0;
    }
    bool check_Enemy(Music& alert)
    {
        if (this->no_A_invaders == 0 && this->no_B_invaders == 0 && this->no_G_invaders == 0)
        {
            return true;
        }
        return false;
    }
    void Kill_Enemy_Invader(int* no)
    {
        this->no_A_invaders = no[0];
        this->no_B_invaders = no[1];
        this->no_G_invaders = no[2];
    }
    void set_Invaders(int& game_level)
    {
        if (this->formation == "rectangle")
        {
            this->no_A_invaders = 12;
            this->no_B_invaders = 4;
            this->no_G_invaders = 0;
            formation = "triangle";
        }
        else if (this->formation == "triangle")
        {
            this->no_A_invaders = 6;
            this->no_B_invaders = 5;
            this->no_G_invaders = 2;
            formation = "cross";
        }
        else if (this->formation == "cross")
        {
            this->no_A_invaders = 9;
            this->no_B_invaders = 4;
            this->no_G_invaders = 4;
            formation = "circle";
        }
        else if (this->formation == "circle")
        {
            game_level += 1;
            this->no_A_invaders = 2;
            this->no_B_invaders = 4;
            this->no_G_invaders = 4;
            formation = "diamond";
        }
        else if (this->formation == "diamond")
        {
            this->no_A_invaders = 2;
            this->no_B_invaders = 4;
            this->no_G_invaders = 5;
            formation = "heart";
        }
        else if (this->formation == "heart")
        {

            this->no_A_invaders = 0;
            this->no_B_invaders = 3;
            this->no_G_invaders = 7;
            formation = "filledrectangle";
        }
        else if (this->formation == "filledrectangle")
        {
            game_level += 1;
            this->no_A_invaders = 20;
            this->no_B_invaders = 4;
            this->no_G_invaders = 0;
            formation = "filledcircle";
        }
        else if (this->formation == "filledcircle")
        {
            this->no_A_invaders = 6;
            this->no_B_invaders = 4;
            this->no_G_invaders = 8;
            formation = "filleddiamond";
        }
        else if (this->formation == "filleddiamond")
        {
            this->no_A_invaders = 3;
            this->no_B_invaders = 7;
            this->no_G_invaders = 9;
            formation = "exit";
        }
        else if (formation == "exit")
        {
            game_level = 4;
        }
    }
    int* get_no_of_Invader()
    {
        int* no = new int[3];
        no[0] = this->no_A_invaders;
        no[1] = this->no_B_invaders;
        no[2] = this->no_G_invaders;
        return no;
    }
    string get_invader_formation()
    {
        return formation;
    }
};

#endif