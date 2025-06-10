#ifndef ENEMY_H
#define ENEMY_H

#include "Header.h"




class Enemy {

private:
	int MaxHealth;
	int Currenthealth = MaxHealth;

	
	float CurrentFrame = 0;
	int HeroDirection = 3;
	int damage = 15;
	//интервал 0.5 секунды
	Texture enemy_texture;
	//Texture damage_texture;
	Sprite damage_sprite;
	/*Clock damageClock;*/
	FloatRect enemyBounds;
	Image enemy_image;
	Clock DamageTakenAnimation;
	bool isTakingDamage = false;
	bool isDeath = false;
	int transparent = 255;
	float DeathScale = 1;
	Color baseColor = Color::White;
	int rotate = 1; // 1 - налево, 2 - направо
	int HeroDamageBoost = 0;
	int CountOfEXP = 20;

	//SoundBuffer damageBuffer;
	//Sound EnemyDamage;

public:
	enum EnemyType {basic, boss, entity};
	EnemyType Type = basic;

	bool isGray = false;
	Color originalColor;

	int enemy_speed = 2;
	float currentspeed = enemy_speed;
	Clock Damage3Cooldown;

	bool canPush = true;
	Sprite enemy_sprite;
	bool CanTakeDamage[6] = { true, true, true, true, true, true };
	Clock damageCooldown;
	float cooldownTime = 0.55f;
	int lastHitByProjectile3 = -1;
	int lastHitByProjectile2 = -1;
	Clock damageCooldown2;

	bool TimeStop = false;
	int GivenMoney = 1;
	
	float PushFactor = 1;

	//bool canTakeDamage = true;

	Enemy(const Texture& texture, const Texture& damage_texture, int x, int y, Hero& hero, int MAXHealth, int Damage, string type, float pushfactor)
	{
		PushFactor = pushfactor;

		if (type == "basic")
			Type = EnemyType::basic;
		else if (type == "boss")
			Type = EnemyType::boss;
		else if (type == "entity")
			Type = EnemyType::entity;

		MaxHealth = MAXHealth;
		Currenthealth = MaxHealth;
		damage = Damage;
		HeroDamageBoost = hero.damageBoost;



		//damage_texture.loadFromFile(way_path);
		/*damage_sprite.setTexture(damage_texture);
		damage_sprite.setScale(Vector2f(0.2f, 0.2f));
		damage_sprite.setColor(Color(255, 255, 255, 0));*/

		/*enemy_image.loadFromFile("data/images/car.png");*/
		//enemy_image.loadFromFile("data/images/enemy.psd");
		//enemy_texture.loadFromImage(enemy_image);
		enemy_sprite.setTexture(texture);
		enemy_sprite.setPosition(x, y);
		enemyBounds = enemy_sprite.getGlobalBounds();
		//damageBuffer.loadFromFile("data/music/EnemyDamage.mp3"); отказался от звука из-за ошибок. Фиксить сил нету. ОТЛОЖЕНО В ДОЛГИЙ ЯЩИК
		//EnemyDamage.setBuffer(damageBuffer);
		
		//EnemyDamage.setVolume(20);
		
		//enemy.setTextureRect(IntRect(45, 0, 48, 58));//выделяем из картинки отрезок. от координат (0,0) до (48,58)
		if (Type == EnemyType::basic)
		{
			enemy_sprite.setScale(Vector2f(0.2f, 0.2f));
			enemy_sprite.setTextureRect(IntRect(0, 0, 205, 360));
			damage_sprite.setTexture(damage_texture);
			damage_sprite.setScale(Vector2f(0.2f, 0.2f));
			damage_sprite.setColor(Color(255, 255, 255, 0));
		}
		else if (Type == EnemyType::boss)
		{
			enemy_sprite.setScale(Vector2f(0.6f, 0.6f));
			enemy_sprite.setTextureRect(IntRect(0, 0, 192, 192));
			damage_sprite.setTexture(damage_texture);
			damage_sprite.setScale(Vector2f(0.6f, 0.6f));
			damage_sprite.setColor(Color(255, 255, 255, 0));
			CountOfEXP *= 8;
		}
		else
		{
			enemy_sprite.setScale(Vector2f(0.2f, 0.2f));
			damage_sprite.setTexture(damage_texture);
			damage_sprite.setColor(Color(255, 255, 255, 0));
			damage_sprite.setScale(Vector2f(0.2f, 0.2f));
			MaxHealth = 30;
			Currenthealth = MaxHealth;
			damage = 0;
			canPush = false;
		}

	}
	/*FloatRect enemyBounds = enemy_sprite.getGlobalBounds();*/

	void Collision(vector<Enemy>& enemies, int moveDirectionX, int moveDirectionY)
	{
		FloatRect enemyBounds = enemy_sprite.getGlobalBounds();
		Vector2f centerThis(enemy_sprite.getPosition().x + enemyBounds.width / 2.f,
			enemy_sprite.getPosition().y + enemyBounds.height / 2.f);

		for (Enemy& other : enemies) {
			if (&other != this) { // Проверяем только других врагов
				FloatRect otherBounds = other.enemy_sprite.getGlobalBounds();
				Vector2f centerOther(other.enemy_sprite.getPosition().x + otherBounds.width / 2.f,
					other.enemy_sprite.getPosition().y + otherBounds.height / 2.f);

				if (enemyBounds.intersects(otherBounds)) {
					// Вектор между центрами
					Vector2f direction = centerThis - centerOther;
					float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

					// Защита от деления на 0
					if (distance == 0.f)
						direction = Vector2f(1.f, 0.f); // просто вправо
					else
						direction /= distance; // нормализация

					float overlap = 0.5f * (std::min(enemyBounds.width, otherBounds.width) - distance);
					if (overlap < 1.f) overlap = 1.f; // чтобы не "слипались"

					// Раздвигаем врагов в разные стороны
					enemy_sprite.move(direction * overlap);
					other.enemy_sprite.move(-direction * overlap);
				}
			}
		}
	}


	void HeroFollow(int gamePause, FloatRect& inheroBounds, Sprite& hero, float deltatime, vector<Enemy>& enemies)
	{
		if (TimeStop)
			currentspeed = 0;

		if (gamePause != true)
		{
			int enemydif_x = (hero.getPosition().x) - (enemy_sprite.getPosition().x);
			int enemydif_y = (hero.getPosition().y) - (enemy_sprite.getPosition().y);
			float supX = abs(enemydif_x);
			float supY = abs(enemydif_y);
			int Xmove = 15;
			if (hero.getPosition().x < enemy_sprite.getPosition().x)
			{
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				if(Type == EnemyType::basic)
				{
					if (CurrentFrame != 0) Xmove = 15 * int(CurrentFrame);
					else Xmove = 0;
					if (!TimeStop)
						enemy_sprite.setTextureRect(IntRect((int(CurrentFrame) * 195) + Xmove, 0, 205, 360));
				}
				else if (Type == EnemyType::boss)
				{
					if (CurrentFrame != 0) Xmove = 9 * int(CurrentFrame);
					else Xmove = 0;
					if (!TimeStop)
					{
						enemy_sprite.setTextureRect(IntRect((int(CurrentFrame) * 192) + Xmove, 197, 192, 192));
						damage_sprite.setTextureRect(IntRect((int(CurrentFrame) * 192) + Xmove, 197, 192, 192));
					}
				}
				rotate = 1;
			}
			else
			{
				CurrentFrame += 0.005 * deltatime;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				if (Type == EnemyType::basic)
				{
					if (CurrentFrame != 0) Xmove = 15 * int(CurrentFrame);
					else Xmove = 0;
					if (!TimeStop)
						enemy_sprite.setTextureRect(IntRect((int(CurrentFrame) * 195) + Xmove, 375, 205, 360));
				}
				else if (Type == EnemyType::boss)
				{
					if (CurrentFrame != 0) Xmove = 9 * int(CurrentFrame);
					else Xmove = 0;
					if (!TimeStop)
					{
						enemy_sprite.setTextureRect(IntRect((int(CurrentFrame) * 192) + Xmove, 0, 192, 192));
						damage_sprite.setTextureRect(IntRect((int(CurrentFrame) * 192) + Xmove, 0, 192, 192));
					}
				}
				rotate = 2;
				
			}
			if (Type != EnemyType::entity)
			{
				if (hero.getPosition().x != enemy_sprite.getPosition().x)
				{
					if (enemydif_x < 0)
					{
						enemy_sprite.move(-(currentspeed * (supX / sqrt(supX * supX + supY * supY))), 0);
						Collision(enemies, currentspeed * (supX / sqrt(supX * supX + supY * supY)), 0);
					}
					else
					{
						enemy_sprite.move(currentspeed * (supX / sqrt(supX * supX + supY * supY)), 0);
						Collision(enemies, -(currentspeed * (supX / sqrt(supX * supX + supY * supY))), 0);
					}

				}
				if (hero.getPosition().y != enemy_sprite.getPosition().y)
				{
					if (enemydif_y < 0)
					{
						enemy_sprite.move(0, -(currentspeed * (supY / sqrt(supX * supX + supY * supY))));
						Collision(enemies, 0, currentspeed * (supY / sqrt(supX * supX + supY * supY)));
					}
					else
						enemy_sprite.move(0, currentspeed * (supY / sqrt(supX * supX + supY * supY)));
					Collision(enemies, 0, -(currentspeed * (supY / sqrt(supX * supX + supY * supY))));

				}

				if (inheroBounds.intersects(enemyBounds))
				{
					if (enemydif_x < 0)
					{
						if (abs(enemydif_x) < abs(enemydif_y))
							enemy_sprite.move((currentspeed * (supX / sqrt(supX * supX + supY * supY))), 0);
						else
							enemy_sprite.move(currentspeed, 0);
					}
					else
						if (abs(enemydif_x) < abs(enemydif_y))
							enemy_sprite.move(-currentspeed * (supX / sqrt(supX * supX + supY * supY)), 0);
						else
							enemy_sprite.move(-currentspeed, 0);

					if (enemydif_y < 0)
					{
						if (abs(enemydif_x) > abs(enemydif_y))
							enemy_sprite.move(0, (currentspeed * (supX / sqrt(supX * supX + supY * supY))));
						else
							enemy_sprite.move(0, currentspeed);
					}
					else
						if (abs(enemydif_x) > abs(enemydif_y))
							enemy_sprite.move(0, -currentspeed * (supX / sqrt(supX * supX + supY * supY)));
						else
							enemy_sprite.move(0, -currentspeed);
				}
			}
			enemyBounds = enemy_sprite.getGlobalBounds();
		}
		damage_sprite.setPosition(enemy_sprite.getPosition());
	}
	void DamageDeal(int gamePause, Hero& Hero, const float damageInterval, Clock& damageClock)
	{
		if (Type != EnemyType::entity)
		{
			if (gamePause != true && TimeStop != true)
			{
				FloatRect heroBounds1 = Hero.heroBounds;
				if (heroBounds1.intersects(enemyBounds) && damageClock.getElapsedTime().asSeconds() >= damageInterval)
				{
					Hero.isTakingDamage = true;
					Hero.DamageTakenAnimation.restart();
					Hero.health -= damage * (1.f - float(Hero.armor) / 100); // Уменьшаем здоровье
					Hero.DamageSound();
					damageClock.restart(); // Сбрасываем таймер

				}
			}
		}
	}

	bool canTakeDamage()
	{
		return damageCooldown.getElapsedTime().asSeconds() >= cooldownTime;
	}

	void takeDamage(int damage, int WeaponIndex)
	{
		if (CanTakeDamage[WeaponIndex])
		{
			//EnemyDamage.setBuffer(damageBuffer); // этот звук говно собачье. ПОЧЕМУ КОГДА Я ЕГО ЗАПОЛНЯЮ В КОНСТРУКТОРЕ ОН ВСЁ РАВНО ПРОПАДАЕТ. ЧТО Я ДЕЛАЮ НЕ ТАК??
			//EnemyDamage.stop();
			//EnemyDamage.play();
			Currenthealth -= damage * (1.f + float(HeroDamageBoost)/100);
			// Запускаем анимацию
			DamageTakenAnimation.restart();
			isTakingDamage = true;

			// исходный цвет
			baseColor = enemy_sprite.getColor();

			CanTakeDamage[WeaponIndex] = false;
		}
	}
	EnemyType getType()
	{
		return Type;
	}
	void updateDamageAnimation()
	{
		if (!isTakingDamage) return;

		if (rotate == 1)
		{
			if(Type == EnemyType::basic)
				damage_sprite.setTextureRect(IntRect(0, 0, 195, 360));
		}
		else
		{
			if (Type == EnemyType::basic)
				damage_sprite.setTextureRect(IntRect(195, 0, 195, 360));
		}

		sf::Time elapsed = DamageTakenAnimation.getElapsedTime();
		const sf::Time duration = sf::milliseconds(100);

		float progress = elapsed.asSeconds() / duration.asSeconds();

		if (progress >= 1.f)
		{
			// Анимация завершена — делаем белый спрайт полностью прозрачным
			damage_sprite.setColor(sf::Color(255, 255, 255, 0));
			isTakingDamage = false;
		}
		else
		{
			// Плавная альфа: сначала возрастает до 255, потом убывает до 0
			float factor;

			if (progress <= 0.5f)
			{
				factor = progress * 2.f;  // от 0 до 1, когда progress идёт от 0 до 0.5
			}
			else
			{
				factor = (1.f - progress) * 2.f;  // от 1 до 0, когда progress идёт от 0.5 до 1
			}

			int alpha = int(factor * 255);

			// Устанавливаем цвет: белый с изменяемой прозрачностью
			damage_sprite.setColor(sf::Color(255, 255, 255, alpha));

		}
	}
	bool DeathAnimation()
	{
		if (!isDeath) return false;

		enemy_speed = 0;
		enemy_sprite.setOrigin(enemy_sprite.getGlobalBounds().width / 2.f, enemy_sprite.getGlobalBounds().height / 2.f);
		damage_sprite.setOrigin(enemy_sprite.getGlobalBounds().width / 2.f, enemy_sprite.getGlobalBounds().height / 2.f);
		enemy_sprite.setScale(0.2f * DeathScale, 0.2f * DeathScale);
		damage_sprite.setScale(0.2f * DeathScale, 0.2f * DeathScale);
		DeathScale += 0.01;
		enemy_sprite.setColor(Color(255, 255, 255, transparent));
		transparent -= 25;
		if (transparent <= 0)
			return true;
		else
			return false;

	}
	FloatRect getGlobalBounds()
	{
		return enemy_sprite.getGlobalBounds();
	}
	Vector2f getPosition()
	{
		return enemy_sprite.getPosition();
	}
	bool EnemyUpdate(RenderWindow& window)
	{
		//enemy_sprite.setTexture(enemy_texture);
		//damage_sprite.setTexture(damage_texture);
		window.draw(enemy_sprite);
		window.draw(damage_sprite);
		if (Currenthealth <= 0)
		{
			isDeath = true;
			return false;
		}
		else
			return true;
	}
	Sprite getSprite()
	{
		return enemy_sprite;
	}
	int getEXP()
	{
		return CountOfEXP;
	}
	~Enemy()
	{
	}
};



//ДУМАЮ ДОБАВЛЮ БОССА НА МИНУТУ 2-3. ПО ПРИКОЛУ

#endif // ENEMY_H