#ifndef ADD_ON_H
#define ADD_ON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <ctime>

using namespace std;
using namespace sf;

class Add_On
{
public:
    Sprite sprite;
    Texture tex;
    float x, y;
    string type;
    bool formation = false;
    float speed;
    float timer;

    // Music fire_sound;

    virtual void Create_Add_On(int& score) = 0;
    virtual void move() = 0;
    virtual bool remove_AddOn_exceeding_window_limit() = 0;
};

#endif