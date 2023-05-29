
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Add_On.h"
using namespace std;
using namespace sf;

class Laser
{
public:
    Texture tex;
    Sprite sprite;
    float bullet_speed = 0.7;
    float x, y;
    bool laser_destroyed;
    string path;

    Laser() {}
    Laser(string png_path, int xx, int yy, float bullet_speed)
    {
        this->path = png_path;
        this->tex.loadFromFile(png_path);
        this->sprite.setTexture(tex);
        this->bullet_speed = bullet_speed;
        this->x = xx + 35;
        this->y = yy - 30;
        this->sprite.setPosition(Vector2f(this->x, this->y));
        this->sprite.setScale(1, 1);
    }
    void operator=(Laser& laser)
    {
        this->path = laser.path;
        this->tex = laser.tex;
        this->sprite.setTexture(this->tex);
        this->bullet_speed = laser.bullet_speed;
        this->x = laser.x;
        this->y = laser.y;
        this->sprite.setPosition(Vector2f(this->x, this->y));
        this->sprite.setScale(1, 1);
    }
    void set_All_Laser(Laser*& All_lasers, Laser*& new_laser, int& laser_count)
    {
        Laser* temp_lasers = All_lasers;
        All_lasers = new Laser[laser_count];
        for (int i = 0; i < laser_count - 1; ++i)
        {
            All_lasers[i] = temp_lasers[i];
        }
        All_lasers[laser_count - 1] = *new_laser;
    }
    void laser_move()
    {
        if (this->path == "img/PNG/Lasers/rotatedleftmax.png")
        {
            x -= 0.4;
            y -= bullet_speed;
            sprite.move(-0.4, -bullet_speed);
        }
        else if (this->path == "img/PNG/Lasers/rotatedleftmin.png")
        {
            x -= 0.2;
            y -= bullet_speed;
            sprite.move(-0.2, -bullet_speed);
        }
        else if (this->path == "img/PNG/Lasers/rotatedrightmin.png")
        {
            x += 0.2;
            y -= bullet_speed;
            sprite.move(+0.2, -bullet_speed);
        }
        else if (this->path == "img/PNG/Lasers/rotatedrightmax.png")
        {
            x += 0.4;
            y -= bullet_speed;
            sprite.move(+0.4, -bullet_speed);
        }
        else
        {
            y -= bullet_speed;
            sprite.move(0, -bullet_speed);
        }
    }
};