#ifndef HERO_H
#define HERO_H

#include "Header.h"


using namespace sf;


class Hero {

private:

	int char_speed = 4;
	float CurrentFrame = 0;
	int CurrentEXP = 0; // текущее кол-во опыта
	int RequireEXP = 100; // необходимое кол-во
	


public:
	int Level = 0;
	int UpgradePoint = 6; // ПОТОМ ПОМЕНЯТЬ НА 1
	int HaveAbilities[6] = { 0, 0, 0, 0, 0, 0 };
	int health;
	int damageBoost;
	int armor;
	int HeroDirection = 3;

	Image hero_image;
	Texture hero_texture;
	Sprite hero_sprite;

	Image hero_in_image;
	Texture hero_in_texture;
	Sprite heroCollision;

	FloatRect inheroBounds;
	FloatRect heroBounds;

	Hero(int x, int y, int Health = 100, int DamageBoost = 0, int Armor = 0/*, int WhichAbilityHave = 0*/)
	{
		health = Health;
		damageBoost = DamageBoost;
		armor = Armor;
		//HaveAbilities[WhichAbilityHave] += true;

		hero_image.loadFromFile("data/images/character1.png");
		hero_texture.loadFromImage(hero_image);
		hero_sprite.setTexture(hero_texture);
		hero_sprite.setPosition(x, y);
		hero_sprite.setTextureRect(IntRect(45, 0, 46, 56));//выделяем из картинки отрезок. от координат (0,0) до (48,58)

		hero_in_image.loadFromFile("data/images/character1.png");
		hero_in_texture.loadFromImage(hero_in_image);
		heroCollision.setTexture(hero_in_texture);
		heroCollision.setPosition(x + 24, y + 29);
		heroCollision.setTextureRect(IntRect(45, 0, 1, 1));

	}

	void handleInput(int gamePause, float deltatime) {
		if (gamePause != true)
		{
			if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
			{
				HeroDirection = 0;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
			{
				HeroDirection = 0;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
			{
				HeroDirection = 1;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
			{
				HeroDirection = 1;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A))
			{
				HeroDirection = 0;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				hero_sprite.move(-(char_speed), 0);//char_speed скорость героя
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				HeroDirection = 1;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				hero_sprite.move(+(char_speed), 0);
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::W))
			{
				HeroDirection = 2;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 183, 46, 58));
				hero_sprite.move(0, -(char_speed));
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				HeroDirection = 3;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 0, 46, 58));
				hero_sprite.move(0, +(char_speed));
				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else
			{
				switch (HeroDirection)
				{
				case 0:
					hero_sprite.setTextureRect(IntRect(0, 120, 46, 56));
					break;
				case 1:
					hero_sprite.setTextureRect(IntRect(45, 58, 46, 56));
					break;
				case 2:
					hero_sprite.setTextureRect(IntRect(45, 185, 46, 56));
					break;
				case 3:
					hero_sprite.setTextureRect(IntRect(45, 0, 46, 56));
					break;
				}

			}
		}
	}

	void HeroDraw(RenderWindow& window)
	{
		inheroBounds = heroCollision.getGlobalBounds();
		heroBounds = hero_sprite.getGlobalBounds();
		window.draw(heroCollision);
		window.draw(hero_sprite);
	}
	void addEXP(int countOfEXP)
	{
		CurrentEXP += countOfEXP;
		if (CurrentEXP >= RequireEXP)
		{
			CurrentEXP = 0;
			RequireEXP += 25;
			Level += 1;
			UpgradePoint += 1;
		}
	}
	int getEXP()
	{
		return CurrentEXP;
	}
	int getRequireEXP()
	{
		return RequireEXP;
	}
	~Hero()
	{
	}
};

#endif // HERO_H




//void handleInput(int gamePause, float deltatime) {
//	if (gamePause != true)
//	{
//		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::S))
//		{
//			HeroDirection = 0;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
//			hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
//		{
//			HeroDirection = 0;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
//			hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
//		{
//			HeroDirection = 1;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
//			hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
//		{
//			HeroDirection = 1;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
//			hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость героя
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::A))
//		{
//			HeroDirection = 0;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
//			hero_sprite.move(-(char_speed), 0);//char_speed скорость героя
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::D))
//		{
//			HeroDirection = 1;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
//			hero_sprite.move(+(char_speed), 0);
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::W))
//		{
//			HeroDirection = 2;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 183, 46, 58));
//			hero_sprite.move(0, -(char_speed));
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::S))
//		{
//			HeroDirection = 3;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 0, 46, 58));
//			hero_sprite.move(0, +(char_speed));
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else
//		{
//			switch (HeroDirection)
//			{
//			case 0:
//				hero_sprite.setTextureRect(IntRect(0, 120, 46, 56));
//				break;
//			case 1:
//				hero_sprite.setTextureRect(IntRect(45, 58, 46, 56));
//				break;
//			case 2:
//				hero_sprite.setTextureRect(IntRect(45, 185, 46, 56));
//				break;
//			case 3:
//				hero_sprite.setTextureRect(IntRect(45, 0, 46, 56));
//				break;
//			}
//
//		}
//	}
//}