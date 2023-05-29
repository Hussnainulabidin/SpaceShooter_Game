#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "laser.h"
#include "Power_Up.h"
#include "Add_On.h"

using namespace std;
using namespace sf;

class Player : public Laser
{
public:
	Texture tex;
	Sprite sprite;
	float speed = 0.8;
	float laser_speed = 0.7;
	float prev_fire_time;
	float delay_fire = 0.5;
	float x, y;
	int lives;
	Laser* All_Laser;
	int laser_count = 0;

	Add_On* add_on;

	Player(std::string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340;
		y = 600;
		sprite.setPosition(sf::Vector2f(x, y));
		sprite.setScale(0.75, 0.75);
		lives = 3;
		All_Laser = nullptr;
		this->add_on = nullptr;
	}
	void Set_position()
	{
		this->x = 340;
		this->y = 600;
		this->sprite.setPosition(340, 600);
	}
	int getPlayer_x_position()
	{
		return x;
	}
	int getPlayer_y_position()
	{
		return y;
	}
	bool fire(float timer, Music& fire_sound)
	{
		if (this->add_on != nullptr)
			if (this->add_on->timer < timer)
			{
				fire_sound.openFromFile("sound/blaster-2-81267.wav");
				this->laser_speed = 0.7;
				this->add_on = nullptr;
				this->delay_fire = 0.5;
			}

		Laser* laser;
		if (laser_count != 0)
		{
			if (this->prev_fire_time + this->delay_fire > timer)
				return false;
		}

		if (this->add_on != nullptr)
		{
			fire_sound.stop();
			if (add_on->type == "firee")
			{
				fire_sound.play();
				laser = new Laser("img/PNG/Lasers/laserGreen11.png", x, y, laser_speed);
				this->laser_count += 1;
				laser->set_All_Laser(this->All_Laser, laser, this->laser_count);

			}
			else if (add_on->type == "power_up")
			{
				fire_sound.play();
				Laser* l1, * l2, * l3, * l4;

				laser = new Laser("img/PNG/Lasers/laserRed06.png", x, y, laser_speed);
				this->laser_count += 1;
				laser->set_All_Laser(this->All_Laser, laser, this->laser_count);

				l1 = new Laser("img/PNG/Lasers/rotatedleftmax.png", x, y, laser_speed);
				laser_count += 1;
				l1->set_All_Laser(this->All_Laser, l1, this->laser_count);

				l2 = new Laser("img/PNG/Lasers/rotatedleftmin.png", x, y, laser_speed);
				laser_count += 1;
				l2->set_All_Laser(this->All_Laser, l2, this->laser_count);

				l3 = new Laser("img/PNG/Lasers/rotatedrightmin.png", x, y, laser_speed);
				laser_count += 1;
				l3->set_All_Laser(this->All_Laser, l3, this->laser_count);

				l4 = new Laser("img/PNG/Lasers/rotatedrightmax.png", x, y, laser_speed);
				laser_count += 1;
				l4->set_All_Laser(this->All_Laser, l4, this->laser_count);
				delete l1, l2, l3, l4;
			}
		}
		else
		{
			fire_sound.stop();
			fire_sound.play();
			laser = new Laser("img/PNG/Lasers/laserBlue15.png", x, y, laser_speed);
			this->laser_count += 1;
			laser->set_All_Laser(this->All_Laser, laser, this->laser_count);
			delete laser;
		}
		prev_fire_time = timer;
		return true;
	}
	void wrap_around()
	{
		Vector2f position = sprite.getPosition();
		if (position.x < 0)
		{
			sprite.setPosition(Vector2f(780, position.y));
			x = 780;
		}
		else if (position.x > 780)
		{
			sprite.setPosition(Vector2f(0, position.y));
			x = 0;
		}
		if (position.y < 0)
		{
			sprite.setPosition(Vector2f(position.x, 780));
			y = 780;
		}
		else if (position.y > 780)
		{
			sprite.setPosition(Vector2f(position.x, 0));
			y = 0;
		}
	}
	void diagonal_move(int check_diag1, int check_diag2)
	{
		// if(check_diag1 == 0 || check_diag2 == 0)
		// 	return;
		if (check_diag1 == 1 && check_diag2 == 1)
		{
			tex.loadFromFile("img/Diagonal ship/l.png");
			sprite.setTexture(tex);
			sprite.setPosition(sf::Vector2f(this->x, this->y));
			sprite.setScale(1, 0.75);
		}
		else if (check_diag1 == 2 && check_diag2 == 1)
		{
			tex.loadFromFile("img/Diagonal ship/r.png");
			sprite.setTexture(tex);
			sprite.setPosition(sf::Vector2f(this->x, this->y));
			sprite.setScale(0.75, 0.75);
		}
		else if (check_diag1 == 2 && check_diag2 == 2)
		{
			tex.loadFromFile("img/Diagonal ship/rb.png");
			sprite.setTexture(tex);
			sprite.setPosition(sf::Vector2f(this->x, this->y));
			sprite.setScale(0.75, 0.75);
		}
		else if (check_diag1 == 1 && check_diag2 == 2)
		{
			tex.loadFromFile("img/Diagonal ship/lb.png");
			sprite.setTexture(tex);
			sprite.setPosition(sf::Vector2f(this->x, this->y));
			sprite.setScale(0.75, 0.75);
		}
		else
		{
			tex.loadFromFile("img/player_ship.png");
			sprite.setTexture(tex);

			sprite.setPosition(sf::Vector2f(x, y));
			sprite.setScale(0.75, 0.75);
		}
	}
	void move(std::string s)
	{
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x = -1;
		else if (s == "r")
			delta_x = 1;
		if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;
		delta_x *= speed;
		delta_y *= speed;
		x += delta_x;
		y += delta_y;
		sprite.move(delta_x, delta_y);
	}
	void display_bullets(RenderWindow& window)
	{

		for (int i = 0; i < this->laser_count; ++i)
		{
			All_Laser[i].laser_move();
			window.draw(this->All_Laser[i].sprite);
		}
		Remove_Laser_Exceeding_Window_Limit();
	}
	void remove_Laser(int no)
	{
		Laser* temp_laser = this->All_Laser;
		this->All_Laser = new Laser[this->laser_count - 1];
		int j = 0;
		for (int i = 0; i < this->laser_count; ++i)
		{
			if (i == no)
				continue;
			All_Laser[j] = temp_laser[i];
			j++;
		}
		laser_count -= 1;
		delete[] temp_laser;
	}
	void Remove_Laser_Exceeding_Window_Limit()
	{
		int exceed_count = 0;
		for (int i = 0; i < this->laser_count; ++i)
		{
			if (this->All_Laser[i].y <= 0)
			{
				exceed_count += 1;
			}
		}
		if (exceed_count != 0)
		{
			Laser* temp_laser = this->All_Laser;
			this->All_Laser = new Laser[laser_count - exceed_count];
			int j = 0;
			for (int i = 0; i < this->laser_count; ++i)
			{
				if (temp_laser[i].y <= 0)
					continue;
				this->All_Laser[j] = temp_laser[i];
				j++;
			}
			this->laser_count -= exceed_count;
			delete[] temp_laser;
		}
	}
	void Collect_Add_On(Add_On* add, float current_time, Music& fire_sound, Music& power_sound)
	{
		if (add->x >= this->x - 60 && add->x <= this->x + 60 && add->y >= this->y - 20 && add->y <= this->y + 20)
		{
			if (add->type == "firee")
			{
				power_sound.stop();
				power_sound.openFromFile("sound/Video-Game-Power-Level-Up-A1-www.fesliyanstudios.com.wav");
				power_sound.play();
				fire_sound.openFromFile("sound/salamisound-3564437-sfx-laser-gun-5-games.wav");
			}
			else if (add->type == "power_up")
			{
				power_sound.stop();
				power_sound.openFromFile("sound/Video-Game-Power-Level-Up-A1-www.fesliyanstudios.com.wav");
				power_sound.play();
				fire_sound.openFromFile("sound/laser-zap-90575.wav");
			}
			if (add->type != "live" && add->type != "danger")
			{
				this->laser_speed = 1;
				this->add_on = add;
				this->add_on->timer = current_time + 5;
				if (add->type == "power_up")
				{
					delay_fire = 0.2;
				}
			}
			if (add->type == "live")
			{
				power_sound.stop();
				power_sound.openFromFile("sound/MARIO POWER UP - SOUND EFFECT-YoutubeConvert.cc.wav");
				power_sound.play();
				this->lives += 1;
				cout << "this> live " << this->lives << endl;
			}
			add->formation = false;
		}
		if (add->type == "danger")
		{
			if (add->x >= this->x - 60 && add->x <= this->x + 60 && add->y >= this->y - 50 && add->y <= this->y + 50)
			{
				power_sound.stop();
				power_sound.openFromFile("sound/ka8wt-uklpq.wav");
				power_sound.play();
				this->lives -= 1;
				cout << "this> live " << this->lives << endl;
				add->formation = false;
			}
		}
	}
};
