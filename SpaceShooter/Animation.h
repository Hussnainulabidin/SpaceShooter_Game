#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>


using namespace std;
using namespace sf;

class Animation
{
public:
    Sprite heart_sprite;
    Texture heart_tex;
    int x;
    int y;

    int lvl = 1;
    int invasion = 1;

    Animation()
    {
        heart_tex.loadFromFile("img/PNG/Power-ups/heart-icon-png-transparent-0.jpg");
        heart_sprite.setTexture(heart_tex);
        heart_sprite.setPosition(10, 10);
        heart_sprite.setScale(0.01, 0.01);
    }
    void show_live(int live, RenderWindow& window)
    {
        int x = 10;
        int y = 10;

        for (int i = 0; i < live; ++i)
        {
            window.draw(heart_sprite);
            x += 35;
            heart_sprite.setPosition(x, y);
        }
    }
    void collide_Invader(RenderWindow& window, Sprite& back_ground, Player*& p)
    {
        if (invasion > 3)
        {
            lvl += 1;
            invasion = 1;
        }
        Sprite sprite1;
        Sprite sprite2;

        Texture tex1;
        Texture tex2;
        Texture tex3;

        tex3.loadFromFile("img/explosion.png");
        tex1.loadFromFile("img/enemy_3.png");
        tex2.loadFromFile("img/enemy_3.png");

        sprite1.setTexture(tex1);
        sprite2.setTexture(tex2);

        IntRect rectexlosion(0, 0, 138, 138);
        Sprite explosion(tex3, rectexlosion);

        explosion.setPosition(320, 100);
        sprite1.setPosition(-70, 150);
        sprite2.setPosition(780, 150);
        sprite1.setScale(0.7, 0.7);
        sprite2.setScale(0.7, 0.7);
        explosion.setScale(1.3, 1.3);

        float speed = 0.3;
        int check_diag1 = 0;
        int check_diag2 = 0;

        Music exp;
        exp.openFromFile("sound/big-explosion.wav");
        exp.setVolume(100);

        int count = 0;

        Font font_text;
        font_text.loadFromFile("img/Fonts/PakenhamBl Italic.ttf");
        Text game_text;
        game_text.setFont(font_text);
        game_text.setFillColor(Color::White);
        game_text.setPosition(330, 150);
        game_text.setCharacterSize(30);

        string str = "    LEVEL : " + to_string(lvl) + "\n" + "INVASION : " + to_string(invasion);
        game_text.setString(str);

        invasion += 1;

        Clock clock;
        while (window.isOpen())
        {
            check_diag1 = check_diag2 = 0;
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                {
                    window.close(); // close the game
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Left)) // If left key is pressed
            {
                check_diag1 = 1;
                p->move("l"); // Player will move to left
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
            {
                check_diag1 = 2;
                p->move("r"); // player will move to right
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) // If up key is pressed
            {
                check_diag2 = 1;
                p->move("u"); // playet will move upwards
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
            {
                check_diag2 = 2;
                p->move("d"); // player will move downwards
            }

            p->wrap_around();
            p->diagonal_move(check_diag1, check_diag2);

            sprite1.move(+speed, 0);
            sprite2.move(-speed, 0);

            window.draw(back_ground);
            window.draw(p->sprite);
            window.draw(game_text);

            if (sprite1.getPosition().x + 150 > sprite2.getPosition().x)
            {
                count += 1;
                if (count == 1)
                    exp.play();
                window.draw(explosion);
                if (clock.getElapsedTime().asSeconds() > 0.3f)
                {
                    rectexlosion.left += 138;
                    explosion.setTextureRect(rectexlosion);
                    clock.restart();
                }
            }
            else
            {
                window.draw(sprite1);
                window.draw(sprite2);
                clock.restart();
            }

            if (sprite1.getPosition().x > sprite2.getPosition().x + 200)
            {
                break;
            }
            window.display();
        }
    }
    void SpaecShip_broke(Player*& p, RenderWindow& window)
    {
        Texture t1;
        Texture t2;
        Texture t3;
        Texture t4;
        Sprite s1;
        Sprite s2;
        Sprite s3;
        Sprite s4;

        t1.loadFromFile("img/PNG/Damage/playerShip3_damage3.png");
        t2.loadFromFile("img/PNG/Damage/playerShip3_damage2.png");
        t3.loadFromFile("img/PNG/Damage/playerShip3_damage1.png");
        t4.loadFromFile("img/PNG/Damage/playerShip1_damage1.png");

        s1.setTexture(t1);
        s2.setTexture(t2);
        s3.setTexture(t3);
        s4.setTexture(t4);

        s1.setPosition(p->x, p->y);
        s2.setPosition(p->x, p->y);
        s3.setPosition(p->x, p->y);
        s4.setPosition(p->x, p->y);
        Clock clock;
        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                {
                    window.close(); // close the game
                }
            }
            // cout << clock.getElapsedTime().asSeconds() << endl;
            if (clock.getElapsedTime().asSeconds() > 1)
                break;
            else if (clock.getElapsedTime().asSeconds() > 0.8)
            {
                cout << "in " << endl;
                window.draw(s4);
            }
            else if (clock.getElapsedTime().asSeconds() > 0.6)
            {
                window.draw(s3);
            }
            else if (clock.getElapsedTime().asSeconds() > 0.4)
            {
                window.draw(s2);
            }
            else if (clock.getElapsedTime().asSeconds() > 0.2)
            {
                window.draw(s1);
            }
            window.display();
        }
    }
    void start_game(RenderWindow& window, Sprite& background)
    {
        Sprite sprite;
        Texture tex;
        tex.loadFromFile("img/—Pngtree—new start game_6016764(1).png");
        sprite.setTexture(tex);
        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                {
                    window.close(); // close the game
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) // If left key is pressed
            {
                break;
            }
            window.draw(background);
            window.draw(sprite);
            window.display();
        }

    }
    void Game_Over(RenderWindow& window, Sprite& background)
    {
        Sprite sprite;
        Texture tex;
        tex.loadFromFile("img/gameover.png");
        sprite.setTexture(tex);
        sprite.setScale(1, 0.9);
        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed) // If cross/close is clicked/pressed
                {
                    window.close(); // close the game
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) // If left key is pressed
            {
                break;
            }
            window.draw(background);
            window.draw(sprite);
            window.display();
        }

    }
};

#endif
