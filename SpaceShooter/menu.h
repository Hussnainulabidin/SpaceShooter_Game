#include <SFML/Graphics.hpp>

class Menu
{
public:
    Texture menu_texture;
    Sprite menu_sprite;
    int choice;

    // add menu attributes here
    Menu(string png)
    {
        menu_texture.loadFromFile(png);
        menu_sprite.setTexture(menu_texture);
        menu_sprite.setScale(0.9, 1);
        choice = 0;
    }
    bool display_menu(RenderWindow& window, bool& exit)
    {
        while (window.isOpen())
        {
            Event n;
            while (window.pollEvent(n))
            {
                if (n.type == Event::Closed)
                    window.close();
                if (n.type == Event::KeyPressed)
                {
                    if (n.key.code == Keyboard::Num1)
                        choice = 1;
                    else if (n.key.code == Keyboard::Num2)
                        choice = 2;
                    else if (n.key.code == Keyboard::Num3)
                        choice = 3;
                    else if (n.key.code == Keyboard::Num4)
                        choice = 4;
                }
            }
            if (choice == 1)
            {
                cout << "test" << endl;
                choice = 0;
                return true;
            }
            else if (choice == 2)
            {
                this->Show_Instructions(window);
                choice = 0;
            }
            if (choice == 3)
            {
                this->show_high_scores(window);
                choice = 0;
            }
            if (choice == 4)
            {
                exit = true;
                return false;
            }
            window.draw(menu_sprite);
            window.display();
        }
        return false;
    }
    bool pause_menu(RenderWindow& window, bool& Continue, bool& exit)
    {
        Texture tex;
        tex.loadFromFile("img/pause_menu.jpg");
        Sprite sprite;
        sprite.setTexture(tex);
        sprite.setScale(1.1, 1.15);

        while (window.isOpen())
        {
            while (window.isOpen())
            {
                Event n;
                while (window.pollEvent(n))
                {
                    if (n.type == Event::Closed)
                        window.close();
                    if (n.type == Event::KeyPressed)
                    {
                        if (n.key.code == Keyboard::Num1)
                            choice = 1;
                        else if (n.key.code == Keyboard::Num2)
                            choice = 2;
                        else if (n.key.code == Keyboard::Num3)
                            choice = 3;
                        else if (n.key.code == Keyboard::Num4)
                            choice = 4;
                        else if (n.key.code == Keyboard::Num5)
                            choice = 5;
                    }
                }
                if (choice == 1)
                {
                    Continue = true;
                    choice = 0;
                    return false;
                }
                else if (choice == 2)
                {
                    Continue = false;
                    choice = 0;
                    return true;
                }
                if (choice == 3)
                {
                    this->Show_Instructions(window);
                    choice = 0;
                }
                if (choice == 4)
                {
                    this->show_high_scores(window);
                    choice = 0;
                }
                if (choice == 5)
                {
                    exit = true;
                    choice = 0;
                    return false;
                }
                window.draw(sprite);
                window.display();
            }
        }
        return false;
    }
    void Show_Instructions(RenderWindow& window)
    {
        Texture tex;
        tex.loadFromFile("img/ins.jpg");
        Sprite sprite;
        sprite.setTexture(tex);

        while (window.isOpen())
        {
            Event n;
            while (window.pollEvent(n))
            {
                if (n.type == Event::Closed)
                    window.close();
                if (n.type == Event::KeyPressed)
                {
                    if (n.key.code == Keyboard::Num1 || n.key.code == Keyboard::Escape)
                        return;
                }
            }
            window.draw(sprite);
            window.display();
        }
    }
    void show_high_scores(RenderWindow& window)
    {
        ifstream file_read; // opening file in read only mode
        file_read.open("HighScore.txt");

        Texture tex, tex1, tex2, tex3;
        tex.loadFromFile("img/high_score1.jpg");
        tex1.loadFromFile("img/PNG/Power-ups/star_gold.png");
        tex2.loadFromFile("img/PNG/Power-ups/star_silver.png");
        tex3.loadFromFile("img/PNG/Power-ups/star_bronze.png");
        Sprite sprite, sprite1, sprite2, sprite3;
        sprite.setTexture(tex);
        sprite1.setTexture(tex1);
        sprite2.setTexture(tex2);
        sprite3.setTexture(tex3);

        sprite1.setScale(2, 2);
        sprite1.setPosition(600, 240);
        sprite2.setScale(2, 2);
        sprite2.setPosition(600, 390);
        sprite3.setScale(2, 2);
        sprite3.setPosition(600, 570);
        sprite.setScale(1, 1.7);

        Font font_score;
        font_score.loadFromFile("img/Fonts/OpenSans-Bold.ttf");
        Text high_score; // Making the text obj to diplay the text on the screen
        high_score.setFont(font_score);
        high_score.setFillColor(Color::Blue);
        high_score.setPosition(350, 250);
        high_score.setCharacterSize(40);

        Font font_name;
        font_name.loadFromFile("img/Fonts/OpenSans-BoldItalic (copy).ttf");
        Text high_name; // Making the text obj to diplay the text on the screen
        high_name.setFont(font_name);
        high_name.setFillColor(Color::Cyan);
        high_name.setPosition(60, 250);
        high_name.setCharacterSize(40);

        Font font_title;
        font_title.loadFromFile("img/Fonts/OpenSans-ExtraBold.ttf");
        Text title; // Making the text obj to diplay the text on the screen
        title.setFont(font_title);
        title.setFillColor(Color::Black);
        title.setPosition(60, 140);
        title.setCharacterSize(50);

        string t = "NAME         SCORE      BADGE";

        string arr = "";
        string str;
        string names = "";
        string score;
        char a[20];
        int i = 0;
        int namelength;
        string name;
        while (getline(file_read, str) && i < 3) // Start taking input from the file untill the file ends
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
            arr += score + "\n\n\n";  // storing the score in a int array
            names += name + "\n\n\n"; // storing the names in the name array
            ++i;

        }
        file_read.close();
        bool check = false;
        while (window.isOpen()) // Displaying the score untill escape is pressed
        {
            Event m;
            while (window.pollEvent(m))
            {
                if (m.type == Event::Closed)
                    window.close();
                if (m.type == Event::KeyPressed)
                {
                    if (m.key.code == Keyboard::Num2 || m.key.code == Keyboard::Escape)
                    {
                        check = true;
                        break;
                    }
                }
            }
            if (check == true)
                break;
            high_score.setString(arr);
            high_name.setString(names);
            title.setString(t);


            window.draw(sprite);
            window.draw(sprite1);
            window.draw(sprite2);
            window.draw(sprite3);
            window.draw(title);
            window.draw(high_score);
            window.draw(high_name);
            window.display();
        }
    }
};
