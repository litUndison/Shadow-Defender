#ifndef HERO_H
#define HERO_H

#include "Header.h"


using namespace sf;


class Hero {

private:

	int char_speed = 4;
	float CurrentFrame = 0;
	int CurrentEXP = 0; // текущее кол-во опыта
	int RequireEXP = 150; // необходимое кол-во
	float DeathScale = 1;
	int transparent = 255;
	Music LevelUpSound;
	SoundBuffer Buffer;
	Sound HeroDamage;

public:
	int Level = 0;
	int UpgradePoint = 1; // ѕќ“ќћ ѕќћ≈Ќя“№ Ќј 1
	int HaveAbilities[6] = { 0, 0, 0, 0, 0, 0 };
	int health;
	int MAXhealth;
	int damageBoost;
	int armor;
	int HeroDirection = 3;
	bool isTakingDamage = false;

	Image hero_image;
	Texture hero_texture;
	Sprite hero_sprite;

	Texture DamageTexture;
	Sprite DamageSprite;
	Clock DamageTakenAnimation;

	Image hero_in_image; // думаю это можно удалить
	Texture hero_in_texture;
	Sprite heroCollision;

	FloatRect inheroBounds; // эт тоже
	FloatRect heroBounds;
	

	Hero(int x, int y, int Health = 100, int DamageBoost = 0, int Armor = 0/*, int WhichAbilityHave = 0*/)
	{
		LevelUpSound.openFromFile("data/music/LevelUp.mp3");
		LevelUpSound.setVolume(10.f);
		Buffer.loadFromFile("data/music/HeroDamage.mp3");
		HeroDamage.setBuffer(Buffer);
		HeroDamage.setVolume(200.f);

		MAXhealth = Health;
		health = Health;
		damageBoost = DamageBoost;
		armor = Armor;
		//HaveAbilities[WhichAbilityHave] += true;

		hero_image.loadFromFile("data/images/character1.png");
		hero_texture.loadFromImage(hero_image);
		hero_sprite.setTexture(hero_texture);
		hero_sprite.setPosition(x, y);
		DamageSprite.setPosition(x, y);
		hero_sprite.setTextureRect(IntRect(45, 0, 46, 56));//выдел€ем из картинки отрезок. от координат (0,0) до (48,58)

		hero_in_image.loadFromFile("data/images/character1.png");
		hero_in_texture.loadFromImage(hero_in_image);
		heroCollision.setTexture(hero_in_texture);
		heroCollision.setPosition(x + 24, y + 29);
		heroCollision.setTextureRect(IntRect(45, 0, 1, 1));

		DamageTexture.loadFromFile("data/images/characterDamage.png");
		DamageSprite.setTexture(DamageTexture);
		DamageSprite.setTextureRect(IntRect(45, 0, 46, 56));
		DamageSprite.setColor(sf::Color(255, 255, 255, 0));
		
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
				hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
			{
				HeroDirection = 0;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
			{
				HeroDirection = 1;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
			{
				HeroDirection = 1;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::A))
			{
				HeroDirection = 0;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				hero_sprite.move(-(char_speed), 0);//char_speed скорость геро€

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::D))
			{
				HeroDirection = 1;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				hero_sprite.move(+(char_speed), 0);

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::W))
			{
				HeroDirection = 2;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 183, 46, 58));
				hero_sprite.move(0, -(char_speed));

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 183, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else if (Keyboard::isKeyPressed(Keyboard::S))
			{
				HeroDirection = 3;
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 0, 46, 58));
				hero_sprite.move(0, +(char_speed));

				DamageSprite.setTextureRect(IntRect(int(CurrentFrame) * 46, 0, 46, 58));
				DamageSprite.setPosition(hero_sprite.getPosition());

				heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
			}
			else
			{
				switch (HeroDirection)
				{
				case 0:
					hero_sprite.setTextureRect(IntRect(0, 120, 46, 56));
					DamageSprite.setTextureRect(IntRect(0, 120, 46, 56));
					break;
				case 1:
					hero_sprite.setTextureRect(IntRect(45, 58, 46, 56));
					DamageSprite.setTextureRect(IntRect(45, 58, 46, 56));
					break;
				case 2:
					hero_sprite.setTextureRect(IntRect(45, 185, 46, 56));
					DamageSprite.setTextureRect(IntRect(45, 185, 46, 56));
					break;
				case 3:
					hero_sprite.setTextureRect(IntRect(45, 0, 46, 56));
					DamageSprite.setTextureRect(IntRect(45, 0, 46, 56));
					break;
				}

			}
		}
	}
	void DamageSound()
	{
		HeroDamage.stop();
		HeroDamage.play();
	}
	void updateDamageAnimation()
	{
		if (!isTakingDamage) return;

		sf::Time elapsed = DamageTakenAnimation.getElapsedTime();
		const sf::Time duration = sf::milliseconds(200);

		float progress = elapsed.asSeconds() / duration.asSeconds();

		if (progress >= 1.f)
		{
			// јнимаци€ завершена Ч делаем белый спрайт полностью прозрачным
			DamageSprite.setColor(sf::Color(255, 255, 255, 0));
			isTakingDamage = false;
		}
		else
		{
			// ѕлавна€ альфа: сначала возрастает до 255, потом убывает до 0
			float factor;

			if (progress <= 0.5f)
			{
				factor = progress * 2.f;  // от 0 до 1, когда progress идЄт от 0 до 0.5
			}
			else
			{
				factor = (1.f - progress) * 2.f;  // от 1 до 0, когда progress идЄт от 0.5 до 1
			}

			int alpha = int(factor * 255);

			// ”станавливаем цвет: белый с измен€емой прозрачностью
			DamageSprite.setColor(sf::Color(255, 255, 255, alpha));

		}
	}
	void DeathAnimation()
	{
		
		if (health > 0) return;
		if (transparent <= 0) return;
		char_speed = 0;
		hero_sprite.setOrigin(hero_sprite.getGlobalBounds().width / 2.f, hero_sprite.getGlobalBounds().height / 2.f);
		hero_sprite.setOrigin(hero_sprite.getGlobalBounds().width / 2.f, hero_sprite.getGlobalBounds().height / 2.f);
		hero_sprite.setScale(0.2f * DeathScale, 0.2f * DeathScale);
		hero_sprite.setScale(0.2f * DeathScale, 0.2f * DeathScale);
		DeathScale += 0.01;
		hero_sprite.setColor(Color(255, 255, 255, transparent));
		transparent -= 25;
	}
	void setVolume(int Volume)
	{
		LevelUpSound.setVolume(10.f * float(Volume) / 100.f);
		HeroDamage.setVolume(200.f * float(Volume) / 100.f);
	}
	void HeroDraw(RenderWindow& window)
	{
		inheroBounds = heroCollision.getGlobalBounds();
		heroBounds = hero_sprite.getGlobalBounds();
		window.draw(heroCollision);
		window.draw(hero_sprite);
		window.draw(DamageSprite);
	}
	void addEXP(int countOfEXP)
	{
		CurrentEXP += countOfEXP;
		if (CurrentEXP >= RequireEXP)
		{
			CurrentEXP = 0;
			RequireEXP += 50;
			Level += 1;
			UpgradePoint += 1;
			LevelUpSound.play();
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
//			hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W))
//		{
//			HeroDirection = 0;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
//			hero_sprite.move(-(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
//		{
//			HeroDirection = 1;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
//			hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), +(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::W))
//		{
//			HeroDirection = 1;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 58, 46, 58));
//			hero_sprite.move(+(sqrt(pow(char_speed, 2) / 2)), -(sqrt(pow(char_speed, 2) / 2)));//char_speed скорость геро€
//			heroCollision.setPosition(hero_sprite.getPosition().x + 24, hero_sprite.getPosition().y + 29);
//		}
//		else if (Keyboard::isKeyPressed(Keyboard::A))
//		{
//			HeroDirection = 0;
//			CurrentFrame += 0.005 * deltatime;
//			if (CurrentFrame > 4) CurrentFrame -= 4;
//			hero_sprite.setTextureRect(IntRect(int(CurrentFrame) * 45, 120, 46, 58));
//			hero_sprite.move(-(char_speed), 0);//char_speed скорость геро€
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