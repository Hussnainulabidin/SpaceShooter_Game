#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "Bomb.h"
using namespace std;
using namespace sf;

class Enemy
{
public:
    Sprite sprite;
    Texture tex;
    float speed;
    float fire_speed;
    float fire_timer;
    float x, y;
    float timer;

    // Music music;

    int health;
    Bomb* enemy_bomb;


    virtual void form_Enemy(Enemy*& A_Invader, int size, string formation, float time, int lvl) { return; }
    virtual void display(RenderWindow& window, Enemy*& A_invaders) { return; }
    virtual int Check_laser_collision(Player*& p, Enemy*& A_invaders, int lvl, int& Score, Music& blast) { return false; };
    virtual void Invader_bomb(Enemy*& A_invaders, Bomb*& All_bomb, int& no_of_bomb, float current_time) { return; }
    virtual void check_enemy_player_collsion(Player*& p, Enemy*& enemy) { return; }

    virtual bool check_Dragon_Laser_Collision(Enemy*& dragon, Player*& p, Bomb*& dragon_Bomb, Music& hit) { return false; }
    virtual bool mosnter_attack(Enemy*& A_invaders, Bomb*& All_bomb, int& no_of_bomb, float current_time, float player_x, Music& laser) { return false; }
    virtual bool check_Enemy(Music& alert) { return true; }
    virtual void set_Invaders(int& game_level) { return; }
    virtual void Kill_Enemy_Invader(int* no) { return; }
    virtual void show_Invader(Enemy*& Alpha_Invader) { return; }
    virtual int* get_no_of_Invader() { return nullptr; }
    virtual string get_invader_formation() { return "\0"; }
};

#endif