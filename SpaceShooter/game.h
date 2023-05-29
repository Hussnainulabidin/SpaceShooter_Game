#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <ctime>
#include "player.h"
#include "menu.h"
#include "Alpha_Invader.h"
#include "Beta_Invader.h"
#include "Gamma_Invader.h"
#include "Invader.h"
#include "Monster.h"
#include "Dragon.h"
#include "Enemy.h"
#include "Power_Up.h"
#include "Danger.h"
#include "Live.h"
#include "Firee.h"
#include "Add_On.h"
#include "Animation.h"

const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
    Sprite background; // Game background sprite
    Texture bg_texture;

    Menu* menu;
    int game_level = 1; // Game Level

    bool check_start_game = false; // Bool to check Start New Game
    bool exit = false;             // Bool to check game End
    bool exit_game = false;        // Bool to check Game Quit
    bool Continue = true;          // Bool to check Continue game

    Player* p;        // Player = Space Ship
    Enemy* A_invader; // Enemy = Alpha Inavder
    Enemy* B_invader; // Enemy = Beta Inavder
    Enemy* G_invader; // Enemy = Gamma Inavder
    Enemy* invader;   // Enemy = Inavder to get formation/number of invaders
    Enemy* dragon;    // Enemy = Dragon
    Enemy* monster;   // Enemy = Monster

    int Score = 0;

    Add_On* power_up;
    Add_On* live;
    Add_On* danger;
    Add_On* firee;
    string name = "";

    Animation* animation;

    Game()
    {
        menu = new Menu("img/menu.png");
        p = new Player("img/player_ship.png");
        bg_texture.loadFromFile("img/background.jpg");
        background.setTexture(bg_texture);
        background.setScale(1, 1.5);
        check_start_game = false;
    }
    void start_game()
    {
        Music menu_sound;
        menu_sound.openFromFile("sound/menusound.wav");
        menu_sound.setVolume(10);
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
        while (window.isOpen())
        {
            if (!check_start_game)
            {
                menu_sound.play();
                check_start_game = menu->display_menu(window, exit_game);
            }
            if (exit_game)
            {
                return;
            }
            if (check_start_game)
            {

                this->Enter_name(window);
                menu_sound.stop();
                bool badge = false;
                Texture tex_badge;
                Sprite badge_sprite;
                badge = check_Badge(badge_sprite, tex_badge);

                game_level = 1;

                Score = 0;
                check_start_game = false;
                exit = false;
                float timer = 0;

                p->lives = 3;
                p->Set_position();

                // Booleans to check Different Scenario
                bool fire = false;
                int check_diag1 = 0;
                int check_diag2 = 0;
                bool check = false;
                bool check_monster = false;
                bool check_dragon = false;
                bool state = false;

                // All Laser on the Screen
                Laser* All_Laser;
                int laser_count = 0;

                // Invader Information for the Game
                int* no_of_enemy = new int[3];
                string formation;
                int no_of_bomb = 0;

                // All Bombs on the Screen
                Bomb* b1 = new Bomb;
                Bomb* All_bomb = nullptr;
                Bomb* monster_bomb = nullptr;
                Bomb* dragon_bomb = nullptr;

                // All Add Ons on the Screen
                power_up = new Power_Up;
                danger = new Danger;
                live = new Live;
                firee = new Firee;

                invader = new Invader;
                Enemy* E[] = { new Alpha_Invader, new Beta_Invader, new Gamma_Invader, new Monster, new Dragon };

                A_invader = nullptr;
                B_invader = nullptr;
                G_invader = nullptr;

                animation = new Animation;

                // Setting Font for Score display in Window
                Font font_score;
                font_score.loadFromFile("img/Fonts/OpenSans-ExtraBold (copy).ttf");
                Text game_score;
                game_score.setFont(font_score);
                game_score.setFillColor(Color::Blue);
                game_score.setPosition(480, 5);
                game_score.setCharacterSize(25);

                // Setting sound effect/music for game
                Music fire_sound;
                fire_sound.openFromFile("sound/blaster-2-81267.wav");

                Music blast;
                blast.openFromFile("sound/EXPLOSION 2.wav");
                blast.setVolume(100);

                Music monster_laser;
                monster_laser.openFromFile("sound/laserrocket2-6284.wav");
                monster_laser.setVolume(100);

                Music power_sound;
                power_sound.openFromFile("sound/Video-Game-Power-Level-Up-A1-www.fesliyanstudios.com.wav");

                Music alert;
                alert.openFromFile("sound/alert.wav");

                Music combact_sound;
                combact_sound.openFromFile("sound/Space Shooter Template Music.wav");
                combact_sound.setVolume(20);
                combact_sound.play();
                combact_sound.setLoop(true);

                animation->start_game(window, background);

                while (window.isOpen())
                {

                    check_diag1 = check_diag2 = 0; // make diagonal check false so to rotate until the key is pressed
                    window.setFramerateLimit(500);
                    float time = clock.getElapsedTime().asSeconds();
                    clock.restart();
                    timer += time;
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
                    if (Keyboard::isKeyPressed(Keyboard::Space))
                    {
                        fire = true;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::P))
                    {
                        combact_sound.stop();
                        menu_sound.play();
                        check_start_game = menu->pause_menu(window, Continue, exit_game);
                        menu_sound.stop();
                        if (!Continue) // If game continue is false then break loop to start a new game
                        {
                            this->Save_Score();
                            Continue = true;
                            break;
                        }
                        else if (exit_game)
                        {
                            this->Save_Score();
                            return;
                        }
                        combact_sound.play();
                    }

                    /////  Call your functions here            ///
                    ////////////////////////////////////////////////
                    //cout << timer << endl;
                    p->diagonal_move(check_diag1, check_diag2);
                    if (check_monster == false && check_dragon == false)
                    {
                        check = invader->check_Enemy(alert); // Checking if any invader exist on screen
                        if (check == true)
                        {
                            All_Laser = nullptr;
                            if(game_level < 4)
                                animation->collide_Invader(window, background, p);
                            invader->set_Invaders(game_level);            // Setting no of inavders on the sceen for new invasion
                            no_of_enemy = invader->get_no_of_Invader();   // Getting number of invader of invasion
                            formation = invader->get_invader_formation(); // getting the Invasion type

                            E[0]->form_Enemy(A_invader, no_of_enemy[0], formation, timer, game_level);
                            E[1]->form_Enemy(B_invader, no_of_enemy[1], formation, timer, game_level);
                            E[2]->form_Enemy(G_invader, no_of_enemy[2], formation, timer, game_level);
                        }
                        no_of_enemy[0] = E[0]->Check_laser_collision(p, A_invader, game_level, Score, blast);
                        no_of_enemy[1] = E[1]->Check_laser_collision(p, B_invader, game_level, Score, blast);
                        no_of_enemy[2] = E[2]->Check_laser_collision(p, G_invader, game_level, Score, blast);

                        invader->Kill_Enemy_Invader(no_of_enemy);

                        E[0]->Invader_bomb(A_invader, All_bomb, no_of_bomb, timer);
                        E[1]->Invader_bomb(B_invader, All_bomb, no_of_bomb, timer);
                        E[2]->Invader_bomb(G_invader, All_bomb, no_of_bomb, timer);

                        E[0]->check_enemy_player_collsion(p, A_invader);
                        E[1]->check_enemy_player_collsion(p, B_invader);
                        E[2]->check_enemy_player_collsion(p, G_invader);

                        exit = b1->check_Bullet_Player_Collision(p, All_bomb, no_of_bomb, power_sound);
                    }
                    if (check_dragon == false)
                    {
                        check_monster = E[3]->check_Enemy(alert);
                        if (check_monster == true)
                        {
                            E[3]->form_Enemy(monster, 1, "noformation", timer, game_level);
                            E[3]->check_enemy_player_collsion(p, monster);
                            exit = b1->check_Laser_Player_Collision(p, monster_bomb, power_sound);
                            state = E[3]->mosnter_attack(monster, monster_bomb, no_of_bomb, timer, p->x, monster_laser);
                            if (state)
                            {
                                Score += 40;
                            }
                        }
                        state = false;
                    }
                    if (check_monster == false)
                    {
                        check_dragon = E[4]->check_Enemy(alert);
                        if (check_dragon == true && check_monster == false)
                        {
                            E[4]->form_Enemy(dragon, 1, "noformation", timer, game_level);
                            E[4]->check_enemy_player_collsion(p, dragon);
                            state = E[4]->mosnter_attack(dragon, dragon_bomb, no_of_bomb, timer, p->x, monster_laser);
                            exit = E[4]->check_Dragon_Laser_Collision(dragon, p, dragon_bomb, power_sound);
                            if (state)
                                Score += 50;
                        }
                        state = false;
                    }

                    // Checking if any of the Add on is formed
                    power_up->Create_Add_On(Score);
                    danger->Create_Add_On(Score);
                    live->Create_Add_On(Score);
                    firee->Create_Add_On(Score);

                    if (p->lives == 0 || game_level == 4)
                    {
                        animation->Game_Over(window, background);
                        this->Save_Score();
                        combact_sound.pause();
                        break;
                    }

                    if (fire)
                    {
                        bool check = p->fire(timer, fire_sound);
                        fire = false;
                    }
                    p->wrap_around();

                    string str = "Level : " + to_string(game_level) + "    SCORE : " + to_string(Score);
                    game_score.setString(str);

                    //////////////////////////////////////////////

                    window.clear(Color::Black); // clears the screen
                    window.draw(background);    // setting background
                    window.draw(p->sprite);     // setting player on screen
                    p->display_bullets(window);
                   
                    if (monster_bomb != nullptr)
                        window.draw(monster_bomb->sprite);
                    if (dragon_bomb != nullptr)
                        window.draw(dragon_bomb->sprite);

                    if (check_monster == false && check_dragon == false)
                    {
                        for (int i = 0; i < no_of_bomb; ++i)
                        {
                            All_bomb[i].bomb_move();
                            window.draw(All_bomb[i].sprite);
                        }
                        E[0]->display(window, A_invader);
                        E[1]->display(window, B_invader);
                        E[2]->display(window, G_invader);
                    }
                    else if (check_monster == true && check_dragon == false)
                    {
                        E[3]->display(window, monster);
                    }
                    else if (check_dragon == true)
                    {
                        E[4]->display(window, dragon);
                    }

                    if (power_up->formation)
                    {
                        p->Collect_Add_On(power_up, timer, fire_sound, power_sound);
                        window.draw(power_up->sprite);
                    }
                    if (danger->formation)
                    {
                        p->Collect_Add_On(danger, timer, fire_sound, power_sound);
                        window.draw(danger->sprite);
                    }
                    if (live->formation)
                    {
                        p->Collect_Add_On(live, timer, fire_sound, power_sound);
                        window.draw(live->sprite);
                    }
                    if (firee->formation)
                    {
                        p->Collect_Add_On(firee, timer, fire_sound, power_sound);
                        window.draw(firee->sprite);
                    }

                    animation->show_live(p->lives, window);
                    window.draw(game_score);
                    if (badge)
                        window.draw(badge_sprite);
                    window.display(); // Displying all the sprites
                }
            }
        }
    }
    void Enter_name(RenderWindow& window)
    {
        Texture tex;
        tex.loadFromFile("img/Name_Enter1.jpg");
        Sprite nameenter(tex);
        nameenter.setScale(0.8, 1);
        char a[20] = "\0";
        bool check = false;

        Font font_score;
        font_score.loadFromFile("img/Fonts/OpenSans-Bold.ttf");
        Text playername;
        playername.setFont(font_score);
        playername.setFillColor(Color::White);
        playername.setPosition(250, 390);
        playername.setCharacterSize(60);
        int i = 0;

        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                {
                    window.close();
                    break;
                }
                if (e.type == Event::TextEntered)
                {
                    if (e.text.unicode == 8)
                    {
                        --i;
                        a[i] = ' ';
                        ;
                        this->name = a;
                        playername.setString(a);
                    }
                    else if (e.TextEntered < 128)
                    {
                        a[i] = e.text.unicode;
                        ++i;
                        this->name = a;
                        playername.setString(a);
                    }
                }
                if (e.key.code == Keyboard::Enter)
                {
                    check = true;
                    break;
                }
            }
            window.draw(nameenter);
            window.draw(playername);
            window.display();
            if (check == true)
                break;
        }
    }
    void Save_Score()
    {
        ifstream file_read;
        ofstream file_write;
        string name;
        file_read.open("HighScore.txt"); // Opening the file
        int arr[100] = { 0 };
        string str;
        string names[100];
        string score;
        char a[20];
        int i = 0;
        int namelength;
        bool check = false;
        int lines = 0;
        bool already_exist = false;
        int existance_index = 0;
        int lines2 = 0;
        while (getline(file_read, str)) // Start taking input from the file untill the file ends
        {
            namelength = 0;
            name = "";
            for (int j = 0; str[j] != ' '; ++j) // Checking for the First space which seperate Name from scores
            {
                namelength += 1;
            }
            for (int j = 0; j < namelength; ++j) // Coping the name From str unitll name length
            {
                name += str[j];
            }
            int m = 0;
            for (int j = namelength + 1; str[j] != '\0'; ++j) // Then copying the name from the namelength to \0
            {
                a[m] = str[j];
                ++m;
            }
            a[m] = '\0';
            score = a;
            arr[i] = stoi(score); // storing the score in a int array
            if (name == this->name)
            {
                already_exist = true;
                existance_index = i;
                if (this->Score > arr[i])
                {
                    arr[i] = this->Score;
                }
            }
            names[i] = name; // storing the names in the name array
            ++i;
        }
        if (already_exist == true)
        {
            lines2 = i + 1;
            lines = i;
        }
        else
        {
            existance_index = i + 1;
            names[existance_index] = this->name;
            arr[existance_index] = this->Score;
            lines = i + 1;
            lines2 = lines;
        }
        string temp1;
        int temp;
        for (int j = 0; j < existance_index; ++j)
        {
            if (existance_index == 0)
                break;
            if (arr[existance_index] > arr[j])
            {
                temp = arr[j];
                arr[j] = arr[existance_index];
                temp1 = names[j];
                names[j] = this->name;
                for (int k = j + 1; k < lines2; ++k)
                {
                    this->Score = arr[k];
                    arr[k] = temp;
                    temp = this->Score;
                }
                for (int k = j + 1; k < lines2; ++k)
                {
                    this->name = names[k];
                    names[k] = temp1;
                    temp1 = this->name;
                }
                check = true;
            }
            if (check == true)
                break;
        }
        cout << endl;
        for (int i = 0; i < lines; ++i)
        {
            cout << names[i] << endl;
        }
        file_read.close(); // Closing the read mode of the file
        file_write.open("HighScore.txt");
        for (int i = 0; i < lines; ++i) // Wrting the updated data into the file
        {
            file_write << names[i] << " ";
            file_write << arr[i] << endl;
        }
        file_write.close();
    }
    bool check_Badge(Sprite& sprite, Texture& tex1)
    {
        ifstream file_read;
        file_read.open("HighScore.txt");
        int i = 0;
        bool badge = false;
        string str;
        string score;
        char a[20];
        int namelength;
        bool check = false;
        string name = "";
        while (getline(file_read, str)) // Start taking input from the file untill the file ends
        {
            namelength = 0;
            name = "";
            for (int j = 0; str[j] != ' '; ++j) // Checking for the First space which seperate Name from scores
            {
                namelength += 1;
            }
            for (int j = 0; j < namelength; ++j) // Coping the name From str unitll name length
            {
                name += str[j];
            }
            int m = 0;
            for (int j = namelength + 1; str[j] != '\0'; ++j) // Then copying the name from the namelength to \0
            {
                a[m] = str[j];
                ++m;
            }
            a[m] = '\0';
            score = a;
            if (name == this->name)
            {
                badge = true;
                break;
            }
            ++i;
        }
        if (badge)
        {
            if (i == 0)
            {
                tex1.loadFromFile("img/PNG/Power-ups/star_gold.png");
                sprite.setTexture(tex1);
                sprite.setScale(1, 1);
                sprite.setPosition(440, 5);
            }
            else if (i == 1)
            {
                tex1.loadFromFile("img/PNG/Power-ups/star_silver.png");
                sprite.setTexture(tex1);
                sprite.setScale(1, 1);
                sprite.setPosition(440, 5);
            }
            else if (i == 2)
            {
                tex1.loadFromFile("img/PNG/Power-ups/star_bronze.png");
                sprite.setTexture(tex1);
                sprite.setScale(1, 1);
                sprite.setPosition(440, 5);
            }
        }
        return badge;
    }
};
