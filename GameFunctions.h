#ifndef GAMEABILITIES_H
#define GAMEABILITIES_H

#include "Header.h"
#include "Hero.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Slider {
private:
    RectangleShape BackGroundrect;        // Фоновая полоска здоровья
    RectangleShape Sliderect;             // Полоска здоровья (отображение текущего здоровья)
    RectangleShape DamageOverlay;         // Полоска для анимации потери здоровья (жёлтая)
    Texture HealthFrameTexture;           // Текстура для рамки
    Sprite HealthFrameSprite;             // Рамка полоски здоровья
    int percent;                          // Процент здоровья
    int previousPercent;                  // Предыдущее значение процентов здоровья (для вычисления потери)
    Vector2f startPosition;               // Начальная позиция полоски
    Vector2f endPosition;                 // Конечная позиция полоски
    float damageAmount;                   // Сколько здоровья потеряно
    bool isDamaged;                       // Флаг, который указывает на то, что был нанесён урон
    Clock damageClock;                       // Часы для отслеживания времени анимации  
    int maxHealth;

public:
    Slider(int PosX, int PosY, string path, int Percent = 100, int MaxHealth = 100)
    {
        maxHealth = MaxHealth;
        DamageOverlay.setSize(Vector2f(0, 0));
        HealthFrameTexture.loadFromFile(path);
        HealthFrameSprite.setTexture(HealthFrameTexture);

        percent = Percent;
        previousPercent = Percent; // Изначально предыдущий процент равен текущему

        BackGroundrect.setSize(Vector2f(450, 20));
        Sliderect.setSize(Vector2f(float(percent) * BackGroundrect.getSize().x / maxHealth, 20));
        HealthFrameSprite.setPosition(PosX, PosY);
        BackGroundrect.setPosition(HealthFrameSprite.getPosition().x + 4, HealthFrameSprite.getPosition().y + HealthFrameTexture.getSize().y / 2 - 9);
        Sliderect.setPosition(HealthFrameSprite.getPosition().x + 4, HealthFrameSprite.getPosition().y + HealthFrameTexture.getSize().y / 2 - 9);
        BackGroundrect.setFillColor(Color(20, 20, 20, 255));
        Sliderect.setFillColor(Color(156, 16, 16, 255));

        DamageOverlay.setSize(Vector2f(0, 0));  // Начальный размер для анимации
        DamageOverlay.setFillColor(Color(255, 255, 0, 150));  // Жёлтый цвет для потери здоровья
    }

    void Update(RenderWindow& window, int newPercent) {
        if (newPercent != percent)
        {
            int damage = percent - newPercent;

            if (damage > 0)
            {
                damageAmount = float(damage) * BackGroundrect.getSize().x / maxHealth;
                isDamaged = true;
                damageClock.restart();
            }
            percent = newPercent;
        }
        else
            DamageOverlay.setSize(Vector2f(0, 0));
        if (percent != 0)
            Sliderect.setSize(Vector2f(float(percent) * BackGroundrect.getSize().x / maxHealth, 20));
        else
            Sliderect.setSize(Vector2f(0, 20));
        Sliderect.setPosition(HealthFrameSprite.getPosition().x + 4, HealthFrameSprite.getPosition().y + HealthFrameTexture.getSize().y / 2 - 9);

        if (isDamaged) {
            float elapsedTime = damageClock.getElapsedTime().asSeconds();
            if (elapsedTime < 0.5f)
            {
                float shrinkAmount = (0.5f - elapsedTime) * damageAmount;
                DamageOverlay.setSize(Vector2f(shrinkAmount, 20));
                DamageOverlay.setPosition(Sliderect.getPosition().x + Sliderect.getSize().x, Sliderect.getPosition().y);
            }
            else
            {
                isDamaged = false;
                DamageOverlay.setSize(Vector2f(0, 20));
            }
        }

        // Отображаем все элементы на экране
        window.draw(BackGroundrect);
        //window.draw(Sliderect);
        if (percent >= 0)
        {
            window.draw(Sliderect);
            if (isDamaged)
                window.draw(DamageOverlay);  // Отображаем жёлтую полоску повреждений
        }
        window.draw(HealthFrameSprite);
    }

    String getPercent() {
        return to_string(percent);
    }

    ~Slider() {
    }
};
class EXPSlider {
private:
    RectangleShape BackGroundrect;        // Фоновая полоска здоровья
    RectangleShape Sliderect;             // Полоска здоровья (отображение текущего здоровья)
    RectangleShape DamageOverlay;         // Полоска для анимации потери здоровья (жёлтая)
    Texture HealthFrameTexture;           // Текстура для рамки
    Sprite HealthFrameSprite;             // Рамка полоски здоровья
    int percent;                          // Процент здоровья
    int previousPercent;                  // Предыдущее значение процентов здоровья (для вычисления потери)
    Vector2f startPosition;               // Начальная позиция полоски
    Vector2f endPosition;                 // Конечная позиция полоски
    float damageAmount;                   // Сколько здоровья потеряно
    bool isDamaged;                       // Флаг, который указывает на то, что был нанесён урон
    Clock damageClock;                       // Часы для отслеживания времени анимации  
    int maxEXP;

public:
    EXPSlider(int PosX, int PosY, int Percent = 0, int MaxEXP = 100)
    {
        percent = Percent;
        maxEXP = MaxEXP;
        //DamageOverlay.setSize(Vector2f(0, 0));
        BackGroundrect.setPosition(PosX, PosY);
        BackGroundrect.setSize(Vector2f(1920, 15));

        Sliderect.setSize(Vector2f(float(percent) * BackGroundrect.getSize().x / maxEXP, 15));
        Sliderect.setPosition(PosX, PosY);

        BackGroundrect.setFillColor(Color(50, 50, 50));
        Sliderect.setFillColor(Color(214, 171, 51));

        //percent = Percent;
        //previousPercent = Percent; // Изначально предыдущий процент равен текущему

        //BackGroundrect.setSize(Vector2f(450, 20));
        //HealthFrameSprite.setPosition(PosX, PosY);
        //BackGroundrect.setPosition(HealthFrameSprite.getPosition().x + 4, HealthFrameSprite.getPosition().y + HealthFrameTexture.getSize().y / 2 - 9);
        //Sliderect.setPosition(HealthFrameSprite.getPosition().x + 4, HealthFrameSprite.getPosition().y + HealthFrameTexture.getSize().y / 2 - 9);
        //BackGroundrect.setFillColor(Color(20, 20, 20, 255));
        //Sliderect.setFillColor(Color(156, 16, 16, 255));

        //DamageOverlay.setSize(Vector2f(0, 0));  // Начальный размер для анимации
        //DamageOverlay.setFillColor(Color(255, 255, 0, 150));  // Жёлтый цвет для потери здоровья

    }

    void Update(RenderWindow& window, Hero& Hero) 
    {
        
            percent = Hero.getEXP();
            maxEXP = Hero.getRequireEXP();
            Sliderect.setSize(Vector2f(float(percent) * BackGroundrect.getSize().x / maxEXP, 15));
            /*if (percent >= maxEXP)
            {
                percent = 0;
                maxEXP += 25;
            }*/
            /*int damage = percent - newPercent;

            if (damage > 0)
            {
                damageAmount = float(damage) * BackGroundrect.getSize().x / maxEXP;
                isDamaged = true;
                damageClock.restart();
            }
            percent = newPercent;*/
        /*else
            DamageOverlay.setSize(Vector2f(0, 0));
        if (percent != 0)
            Sliderect.setSize(Vector2f(float(percent) * BackGroundrect.getSize().x / maxEXP, 20));
        else
            Sliderect.setSize(Vector2f(0, 20));
        Sliderect.setPosition(HealthFrameSprite.getPosition().x + 4, HealthFrameSprite.getPosition().y + HealthFrameTexture.getSize().y / 2 - 9);

        if (isDamaged) {
            float elapsedTime = damageClock.getElapsedTime().asSeconds();
            if (elapsedTime < 0.5f)
            {
                float shrinkAmount = (0.5f - elapsedTime) * damageAmount;
                DamageOverlay.setSize(Vector2f(shrinkAmount, 20));
                DamageOverlay.setPosition(Sliderect.getPosition().x + Sliderect.getSize().x, Sliderect.getPosition().y);
            }
            else
            {
                isDamaged = false;
                DamageOverlay.setSize(Vector2f(0, 20));
            }
        }*/

        // Отображаем все элементы на экране
        //window.draw(BackGroundrect);
        //window.draw(Sliderect);
        //if (percent > 0)
        //{
        //    window.draw(Sliderect);
        //    //if (isDamaged)
        //    //    window.draw(DamageOverlay);  // Отображаем жёлтую полоску повреждений
        //}
        //window.draw(HealthFrameSprite);
    }
    void justDraw(RenderWindow& window)
    {
        window.draw(BackGroundrect);
        //window.draw(Sliderect);
        if (percent > 0)
        {
            window.draw(Sliderect);
            //if (isDamaged)
            //    window.draw(DamageOverlay);  // Отображаем жёлтую полоску повреждений
        }
    }
    String getPercent() {
        return to_string(percent);
    }

    ~EXPSlider() {
    }
};
class Ability1
{
private:
    Texture ability_texture;
    Sprite ability_sprite_forward;
    Sprite ability_sprite_backward;

    bool active = false;
    Vector2f direction;
    float speed = 10.f;
    int damage = 10;
    Vector2f startPosition;
    bool useDoubleAttack = false;
    int maxDistance = 100;

public:
    int Level = 1;

    Ability1(int Damage, string Directory)
    {
        damage = Damage;
        ability_texture.loadFromFile(Directory);

        ability_sprite_forward.setTexture(ability_texture);
        ability_sprite_backward.setTexture(ability_texture);

        ability_sprite_forward.setOrigin(ability_texture.getSize().x / 2, ability_texture.getSize().y / 2);
        ability_sprite_backward.setOrigin(ability_texture.getSize().x / 2, ability_texture.getSize().y / 2);

        ability_sprite_forward.setScale(0.5f, 0.5f);
        ability_sprite_backward.setScale(0.5f, 0.5f);
    }

    void attack(const sf::Sprite& heroSprite, Hero& character)
    {
        if (active == true)
            return;

        switch (character.HeroDirection)
        {
        case 0:
            direction = Vector2f(-1.f, 0.f);
            ability_sprite_forward.setPosition(heroSprite.getPosition().x, heroSprite.getPosition().y + 29);
            ability_sprite_backward.setPosition(heroSprite.getPosition().x + 48, heroSprite.getPosition().y + 29);
            ability_sprite_forward.setRotation(180);
            ability_sprite_backward.setRotation(0);
            break;
        case 1:
            direction = Vector2f(1.f, 0.f);
            ability_sprite_forward.setPosition(heroSprite.getPosition().x + 48, heroSprite.getPosition().y + 29);
            ability_sprite_backward.setPosition(heroSprite.getPosition().x, heroSprite.getPosition().y + 29);
            ability_sprite_forward.setRotation(0);
            ability_sprite_backward.setRotation(180);
            break;
        case 2:
            direction = Vector2f(0.f, -1.f);
            ability_sprite_forward.setPosition(heroSprite.getPosition().x + 24, heroSprite.getPosition().y);
            ability_sprite_backward.setPosition(heroSprite.getPosition().x + 24, heroSprite.getPosition().y + 58);
            ability_sprite_forward.setRotation(-90);
            ability_sprite_backward.setRotation(90);
            break;
        case 3:
            direction = Vector2f(0.f, 1.f);
            ability_sprite_forward.setPosition(heroSprite.getPosition().x + 24, heroSprite.getPosition().y + 58);
            ability_sprite_backward.setPosition(heroSprite.getPosition().x + 24, heroSprite.getPosition().y);
            ability_sprite_forward.setRotation(90);
            ability_sprite_backward.setRotation(-90);
            break;
        }

        startPosition = heroSprite.getPosition();
        active = true;
    }

    void update(sf::RenderWindow& window, vector<Enemy>& enemies)
    {
        if (active == false)
            return;

        float dx = ability_sprite_forward.getPosition().x - startPosition.x;
        float dy = ability_sprite_forward.getPosition().y - startPosition.y;
        float distance = sqrt(dx * dx + dy * dy);

        if (distance > maxDistance)
        {
            active = false;
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].CanTakeDamage[0] = true;
                enemies[i].canPush = true;
            }
            return;
        }

        ability_sprite_forward.move(direction * speed);
        if (useDoubleAttack)
            ability_sprite_backward.move(-direction * speed);

        FloatRect bounds1 = ability_sprite_forward.getGlobalBounds();
        for (int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i].getGlobalBounds().intersects(bounds1))
            {
                enemies[i].takeDamage(damage, 0);
                if (enemies[i].canPush)
                {
                    enemies[i].enemy_sprite.move(direction * 50.f);
                    enemies[i].canPush = false;
                }
            }
        }

        if (useDoubleAttack)
        {
            FloatRect bounds2 = ability_sprite_backward.getGlobalBounds();
            for (int i = 0; i < enemies.size(); i++)
            {
                if (enemies[i].getGlobalBounds().intersects(bounds2))
                {
                    enemies[i].takeDamage(damage, 0);
                    if (enemies[i].canPush)
                    {
                        enemies[i].enemy_sprite.move(-direction * 50.f);
                        enemies[i].canPush = false;
                    }
                }
            }
        }
    }

    void draw(sf::RenderWindow& window)
    {
        if (active == true)
        {
            window.draw(ability_sprite_forward);
            if (useDoubleAttack)
                window.draw(ability_sprite_backward);
        }
    }

    void setUpgradeLevel(int level)
    {
        if (level > 6)
            level = 6;

        Level = level;

        switch (Level)
        {
        case 2:
            damage += 5;
            speed += 5;
            break;
        case 3:
            ability_sprite_forward.setScale(0.5f, 0.6f);
            ability_sprite_backward.setScale(0.5f, 0.6f);
            maxDistance += 150;
            break;
        case 4:
            ability_sprite_forward.setScale(0.5f, 0.7f);
            ability_sprite_backward.setScale(0.5f, 0.7f);
            maxDistance += 100;
            damage += 5;
            speed += 5;
            break;
        case 5:
            damage += 5;
            speed += 5;
            break;
        case 6:
            useDoubleAttack = true;
            maxDistance += 100;
            break;
        }
    }

    Sprite getSprite1()
    {
        return ability_sprite_forward;
    }
    Sprite getSprite2()
    {
        return ability_sprite_backward;
    }
    bool isActive() const
    {
        return active;
    }

    ~Ability1() {}
};

class Ability2
{
private:
    const int MAX_PROJECTILES = 15;

    Texture ability_texture;
    Music AttackSound[15];

    float cooldown = 1.f; // интервал между выстрелами
    float speed = 10.f;
    int damage = 10;
    float range = 1200.f;

    Sprite projectiles[15];
    Clock projectileTimers[15];     // таймеры каждого снаряда
    bool isActive[15] = { false };
    bool canDamage[15] = { true };
    Vector2f directions[15];
    Vector2f startPositions[15];
    Vector2f endPositions[15];

    Clock globalTimer; // используется для атаки

public:
    int numProjectiles = 1; // можно менять во время игры
    int Level = 1;
    int DamageLimit = 1;

    Ability2(int Damage, const string& Directory, float Cooldown = 1.f)
    {
        damage = Damage;
        cooldown = Cooldown;
        ability_texture.loadFromFile(Directory);
        

        for (int i = 0; i < MAX_PROJECTILES; i++)
        {
            projectiles[i].setTexture(ability_texture);
            projectiles[i].setOrigin(ability_texture.getSize().x / 2, ability_texture.getSize().y / 2);
            AttackSound[i].openFromFile("data/music/Attack2.mp3");
            AttackSound[i].setVolume(50);
        }
    }

    void update(const Sprite& heroSprite, vector<Enemy>& enemies)
    {
        float currentTime = globalTimer.getElapsedTime().asSeconds();

        for (int i = 0; i < numProjectiles; ++i)
        {
            int DamageCounts = 0;
            int CurrentAttack = -1;
            // Если не активен — запускаем, если пришло время
            if (!isActive[i] && projectileTimers[i].getElapsedTime().asSeconds() >= cooldown)
            {
                if (enemies.empty()) return;

                // Запуск
                AttackSound[i].play();
                isActive[i] = true;
                canDamage[i] = true;
                projectileTimers[i].restart();

                startPositions[i] = heroSprite.getPosition() + Vector2f(24, 29);
                projectiles[i].setPosition(startPositions[i]);

                int targetIndex = rand() % enemies.size();
                endPositions[i] = enemies[targetIndex].getPosition();

                Vector2f dir = endPositions[i] - startPositions[i];
                float len = sqrt(dir.x * dir.x + dir.y * dir.y);
                if (len != 0) dir /= len;

                // Добавим случайную погрешность в направлении (+-1–2 градуса)
                float angleOffset = ((rand() % 5) - 2) * (3.14159265f / 180.f); // от -2 до +2 градуса в радианах

                float baseAngle = atan2(dir.y, dir.x);
                float finalAngle = baseAngle + angleOffset;

                // Пересчитаем направление с учетом погрешности
                dir = Vector2f(cos(finalAngle), sin(finalAngle));

                directions[i] = dir;

                float angle = finalAngle * 180.f / 3.14159265f;
                projectiles[i].setRotation(angle);
            }

            // Если активен — движется
            if (isActive[i])
            {
                projectiles[i].move(directions[i] * speed);

                float traveled = sqrt(pow(projectiles[i].getPosition().x - startPositions[i].x, 2) +
                    pow(projectiles[i].getPosition().y - startPositions[i].y, 2));

                // Проверка столкновений
                for (auto& enemy : enemies)
                {
                    if (canDamage[i] && enemy.getGlobalBounds().intersects(projectiles[i].getGlobalBounds()))
                    {
                        if (enemy.CanTakeDamage[1] && (enemy.lastHitByProjectile2 != i || enemy.damageCooldown2.getElapsedTime().asMilliseconds() >= 200))
                        {
                            enemy.takeDamage(damage, 1);
                            enemy.enemy_sprite.move(directions[i] * 50.f);
                            DamageCounts += 1;
                            enemy.lastHitByProjectile2 = i;
                            enemy.damageCooldown2.restart();
                        }
                        //canDamage[i] = false;
                        
                    }
                    if (DamageCounts == DamageLimit || traveled >= range)
                    {
                        isActive[i] = false;
                        break;
                    }
                }

                if (traveled >= range)
                {
                    isActive[i] = false;
                }

            }
        }
        for (auto& enemy : enemies)
        {
            enemy.CanTakeDamage[1] = true;
        }
    }

    void draw(RenderWindow& window)
    {
        for (int i = 0; i < numProjectiles; ++i)
        {
            if (isActive[i])
                window.draw(projectiles[i]);
        }
    }

    void addProjectileCount(int count)
    {
        numProjectiles += count;
        if (numProjectiles > 15) // пожалуй 15 лучше не использовать. Глухота обеспечена
            numProjectiles = 15;
    }

    void setUpgradeLevel(int level)
    {
        if (level > 6) level = 6;
        Level = level;

        switch (Level)
        {
        case 2:
            damage += 5;
            speed += 5;
            addProjectileCount(1);
            break;
        case 3:
            addProjectileCount(2);
            break;
        case 4:
            damage += 5;
            speed += 5;
            break;
        case 5:
            addProjectileCount(10);
            break;
        case 6:
            //damage += 10;
            DamageLimit += 2;
            break;
        }
    }

    ~Ability2() {}
};



class Ability3
{
private:
    Texture ability_texture;
    Sprite ability_sprites[8];

    int damage = 15;

    bool active = false;
    float cooldown;
    float duration;

    int MAXnumProjectiles = 8;
    int numProjectiles = 1;

    float radius = 170.f;
    float rotationSpeed = 80.f; // градусов в секунду
    float currentAngle = 0.f;

    Clock clock;
    float lastActivationTime = 0.f;
    Clock DamageCooldown;
    float DamageTime = DamageCooldown.getElapsedTime().asMilliseconds();

    bool fadingIn = false;
    bool fadingOut = false;
    int alpha = 0; // от 0 до 255
    float fadeSpeed = 300.f; // скорость появления/исчезновения в альфа-единицах в секунду

public:
    int Level = 1;
    Ability3(float cooldownSeconds, float durationSeconds, const string& texturePath, int NumProjectiles = 1)
    {
        cooldown = cooldownSeconds;
        duration = durationSeconds;
        numProjectiles = NumProjectiles;

        ability_texture.loadFromFile(texturePath);
        for (int i = 0; i < MAXnumProjectiles; ++i)
        {
            ability_sprites[i].setTexture(ability_texture);
            ability_sprites[i].setOrigin(ability_texture.getSize().x / 2, ability_texture.getSize().y / 2);
            ability_sprites[i].setScale(50.f / ability_texture.getSize().x, 50.f / ability_texture.getSize().y);
        }
    }
    void update(const Sprite& heroSprite, vector<Enemy>& enemies)
    {
        float deltaTime = 1.f / 60.f;

        if (fadingIn)
        {
            alpha += fadeSpeed * deltaTime;
            if (alpha >= 255) {
                alpha = 255;
                fadingIn = false;
            }
            for (int i = 0; i < numProjectiles; ++i)
                ability_sprites[i].setColor(Color(255, 255, 255, alpha));
        }
        if (fadingOut)
        {
            alpha -= fadeSpeed * deltaTime;
            if (alpha <= 0) {
                alpha = 0;
                fadingOut = false;
            }
            for (int i = 0; i < numProjectiles; ++i)
                ability_sprites[i].setColor(Color(255, 255, 255, alpha));
        }

        float currentTime = clock.getElapsedTime().asSeconds();

        if (!active && currentTime - lastActivationTime >= cooldown)
        {
            active = true;
            lastActivationTime = currentTime;
            alpha = 0;
            fadingIn = true;
            fadingOut = false;
        }

        if (active || fadingOut)
        {
            if (currentTime - lastActivationTime >= duration)
            {
                fadingOut = true;
                fadingIn = false;
                active = false;
            }

            currentAngle += rotationSpeed * (1.f / 60.f); // приблизительно как 60 FPS
            if (currentAngle >= 360.f)
                currentAngle -= 360.f;

            for (int i = 0; i < numProjectiles; i++)
            {
                float angle = 1;
                if (numProjectiles <= 4)
                {
                    angle = currentAngle + (360.f / numProjectiles) * i;
                }
                else
                {
                    // 0..3 — внешний круг, равномерно
                    // 4..7 — внутренний круг со смещением на 45°
                    int outerCount = 4;
                    int innerCount = numProjectiles - outerCount;
                    if (i < outerCount)
                    {
                        angle = currentAngle + (360.f / outerCount) * i;
                    }
                    else
                    {
                        angle = currentAngle + 45.f + (360.f / innerCount) * (i - outerCount);
                    }
                }

                float rad = angle * 3.1415f / 180.f;

                float offsetX = cos(rad) * radius;
                float offsetY = sin(rad) * radius;

                if (i > 3)
                {
                    ability_sprites[i].setPosition(heroSprite.getPosition().x + 24 + offsetX/1.5, heroSprite.getPosition().y + 29 + offsetY/1.5);
                    ability_sprites[i].setRotation(angle + 90.f);
                }
                else
                {
                    ability_sprites[i].setPosition(heroSprite.getPosition().x + 24 + offsetX, heroSprite.getPosition().y + 29 + offsetY);
                    ability_sprites[i].setRotation(angle + 90.f);
                }
            }

            for (auto& enemy : enemies)
            {
                for (int i = 0; i < numProjectiles; i++)
                {
                    if (enemy.getGlobalBounds().intersects(ability_sprites[i].getGlobalBounds()))
                    {
                        // Только если урон не был от этого же снаряда
                        if (enemy.lastHitByProjectile3 != i || enemy.Damage3Cooldown.getElapsedTime().asMilliseconds() >= 300)
                        {
                            enemy.takeDamage(damage, 2);
                            enemy.CanTakeDamage[2] = false;

                            Vector2f pushDirection = enemy.getPosition() - heroSprite.getPosition();
                            float length = sqrt(pushDirection.x * pushDirection.x + pushDirection.y * pushDirection.y);
                            if (length != 0)
                                pushDirection /= length;

                            enemy.enemy_sprite.move(pushDirection * 50.f);

                            // Сохраняем индекс снаряда, от которого был урон
                            enemy.lastHitByProjectile3 = i;
                            enemy.Damage3Cooldown.restart();
                        }
                    }
                    else
                    {
                        // Разрешаем снова получать урон, как только враг выйдет из зоны снаряда
                        /*if (enemy.lastHitByProjectile == i)
                            enemy.lastHitByProjectile = -1;*/

                        enemy.CanTakeDamage[2] = true;
                    }
                }
            }

        }
    }

    void draw(RenderWindow& window)
    {
        //if (alpha <= 0) return;
        //if (!active) return;
        for (int i = 0; i < numProjectiles; ++i)
        {
            window.draw(ability_sprites[i]);
        }
    }
    void setUpgradeLevel(int level)
    {
        if (level > 6)
            level = 6;

        Level = level;

        switch (Level)
        {
        case 2:
            rotationSpeed += 20;
            radius += 25;
            damage += 5;
            numProjectiles += 1;
            duration += 1;
            break;
        case 3:
            rotationSpeed += 20;
            radius += 25;
            damage += 5;
            numProjectiles += 1;
            cooldown -= 1;
            break;
        case 4:
            rotationSpeed += 20;
            //damage += 5;
            numProjectiles += 1;
            cooldown -= 1;
            break;
        case 5:
            for (int i = 0; i < MAXnumProjectiles; ++i)
            {
                ability_sprites[i].setScale(70.f / ability_texture.getSize().x, 70.f / ability_texture.getSize().y);
            }
            break;
        case 6:
            numProjectiles = 8;
            duration += 1;
            break;
        }
    }
    bool isActive() const { return active; }
    ~Ability3() {}
};

class Ability4
{
private:
    Texture ability_texture;
    Sprite ability_sprite;

    int damage = 0;

    bool active = true;
    float cooldown;
    float duration;

    int MAXnumProjectiles = 8;
    int numProjectiles = 1;

    float radius = 100.f;
    float rotationSpeed = 30.f; // градусов в секунду
    float currentAngle = 0.f;

    Clock DamageCooldown;
    float DamageTime = DamageCooldown.getElapsedTime().asMilliseconds();
    int SlowFactor = 1.5;

public:
    int Level = 1;
    Ability4(const string& texturePath, int Damage)
    {
        //damage = Damage;
        ability_texture.loadFromFile(texturePath);
        ability_sprite.setTexture(ability_texture);
        ability_sprite.setOrigin(ability_texture.getSize().x / 2, ability_texture.getSize().y / 2);
        ability_sprite.setScale(radius * 2 / ability_texture.getSize().x, radius * 2 / ability_texture.getSize().y);
    }
    void update(const Sprite& heroSprite, vector<Enemy>& enemies)
    {
        float deltaTime = 1.f / 60.f; // если ты не передаёшь его, иначе замени

        if (active)
        {

            currentAngle += rotationSpeed * (1.f / 60.f); // приблизительно как 60 FPS
            if (currentAngle >= 360.f)
                currentAngle -= 360.f;
            float angle = currentAngle;
            float rad = angle * 3.1415f / 180.f;

            ability_sprite.setPosition(heroSprite.getPosition().x + 24,
                heroSprite.getPosition().y + 29);
            ability_sprite.setRotation(angle + 90.f);
        }

        for (auto& enemy : enemies)
        {
            if (enemy.getGlobalBounds().intersects(ability_sprite.getGlobalBounds()))
            {
                if (enemy.canTakeDamage() && Level == 6)
                {
                    enemy.CanTakeDamage[3] = true;
                    enemy.takeDamage(damage, 3);
                    enemy.damageCooldown.restart();


                }
                enemy.currentspeed = float(enemy.enemy_speed) / SlowFactor; // на первом лвле уменьшение в полтора раза

            }
            else
                enemy.currentspeed = enemy.enemy_speed;
        }


    }
    void setUpgradeLevel(int level)
    {
        if (level > 6)
            level = 6;

        Level = level;

        switch (Level)
        {
        case 2:
            radius += 50;
            break;
        case 3:
            radius += 50;
            SlowFactor = 2;
            break;
        case 4:
            radius += 50;
            break;
        case 5:
            radius += 50;
            break;
        case 6:
            damage = 10;
            SlowFactor = 2.5;
            break;
        }
        ability_sprite.setScale(radius * 2 / ability_texture.getSize().x, radius * 2 / ability_texture.getSize().y);
    }

    void draw(RenderWindow& window)
    {
        //if (alpha <= 0) return;
        //if (!active) return;
        window.draw(ability_sprite);
    }

    bool isActive() const { return active; }
    ~Ability4() {}
};
class Ability5
{
private:
    
    int CountOfHP = 2; // количество получаемого хп
    int CountOfEnemies = 0; // количество убитых врагов
    int RequireEnemies = 10; // кол-во необходимых

public:
    int Level = 1;
    Ability5(int CountOfhp, int requireEnemies)
    {
        CountOfHP = CountOfhp;
        RequireEnemies = requireEnemies;
    }
    void update(int KillingEnemy, Hero& hero)
    {
        CountOfEnemies += KillingEnemy;
        if (CountOfEnemies >= RequireEnemies)
        {
            if (hero.health < hero.MAXhealth)
                hero.health += CountOfHP;
            if (hero.health >= hero.MAXhealth)
                hero.health = hero.MAXhealth;
            CountOfEnemies = 0;
        }
    }
    void setUpgradeLevel(int level)
    {
        if (level > 6)
            level = 6;

        Level = level;

        switch (Level)
        {
        case 2:
            RequireEnemies -= 2;
            break;
        case 3:
            CountOfHP += 1;
            break;
        case 4:
            CountOfHP += 1;
            break;
        case 5:
            RequireEnemies -= 2;
            break;
        case 6:
            RequireEnemies = 5;
            CountOfHP = 5;
            break;
        }
    }


    ~Ability5() {}
};

//class Ability6
//{
//private:
//
//    int cooldown;
//    int duration;
//    RectangleShape BGrect;
//    Clock Cooldown;
//    Clock Duration;
//
//    Color targetColor = Color(100, 100, 100, 100);
//    Color startColor = Color(100,100,100,0);
//
//    Texture clockTexture;
//    Sprite ClockSprite;
//    RectangleShape MinutesClockRect;
//    RectangleShape HourClockRect;
//
//    bool Active = false;
//
//public:
//    int Level = 1;
//    Ability6(int cooldown, int duration)
//    {
//        BGrect.setSize(Vector2f(1920, 1080));
//        BGrect.setPosition(0, 0);
//        BGrect.setFillColor(startColor);
//
//        MinutesClockRect.setSize(Vector2f(100,10));
//        MinutesClockRect.setFillColor(Color(50, 50, 50));
//        HourClockRect.setSize(Vector2f(50, 10));
//        HourClockRect.setFillColor(Color(150, 10, 10));
//
//        HourClockRect.setOrigin(0, 5);
//        HourClockRect.setRotation(-90);
//        MinutesClockRect.setOrigin(0, 5);
//        MinutesClockRect.setRotation(-90);
//    }
//    void update(vector<Enemy>& enemies)
//    {
//        if (!Active) return
//
//    }
//    void setUpgradeLevel(int level)
//    {
//        if (level > 6)
//            level = 6;
//
//        Level = level;
//
//        switch (Level)
//        {
//        case 2:
//            break;
//        case 3:
//            break;
//        case 4:
//            break;
//        case 5:
//            break;
//        case 6:
//            break;
//        }
//    }
//
//
//    ~Ability6() {}
//};

class Ability6
{
private:
    int cooldown;
    int duration;

    RectangleShape BGrect;
    Clock CooldownTimer;
    Clock PhaseTimer;

    Color targetColor = Color(100, 100, 120, 70);
    Color startColor = Color(100, 100, 100, 0);

    enum Phase { Idle, FadingIn, Active, FadingOut };
    Phase currentPhase = Idle;

    RectangleShape MinuteRect;
    RectangleShape HourRect;

    Texture ClockTexture;
    Sprite ClockSprite;

public:
    int Level = 1;

    Ability6(int Cooldown, int Duration)
    {
        cooldown = Cooldown;
        duration = Duration;

        BGrect.setSize(Vector2f(1920, 1080));
        BGrect.setPosition(0, 0);
        BGrect.setFillColor(startColor);

        MinuteRect.setFillColor(Color(200,200,0));
        MinuteRect.setOutlineThickness(1);
        MinuteRect.setOutlineColor(Color::Black);
        MinuteRect.setSize(Vector2f(38, 4));
        MinuteRect.setOrigin(0, 2);
        MinuteRect.setRotation(-90);

        HourRect.setFillColor(Color(100, 20, 20));
        HourRect.setSize(Vector2f(30, 4));
        HourRect.setOrigin(0, 2);
        

        ClockTexture.loadFromFile("data/images/Weapon6Clock.png");
        ClockSprite.setTexture(ClockTexture);

        ClockSprite.setScale(100.f/ ClockTexture.getSize().x, 100.f / ClockTexture.getSize().x);
        ClockSprite.setPosition(1750, 910);
        MinuteRect.setPosition(ClockSprite.getGlobalBounds().width/2 + ClockSprite.getPosition().x, ClockSprite.getGlobalBounds().height / 2 + ClockSprite.getPosition().y);
        HourRect.setPosition(ClockSprite.getGlobalBounds().width/2 + ClockSprite.getPosition().x, ClockSprite.getGlobalBounds().height / 2 + ClockSprite.getPosition().y);
    }

    void update(vector<Enemy>& enemies)
    {
        float elapsedSinceCooldown = CooldownTimer.getElapsedTime().asSeconds();
        float phaseTime = PhaseTimer.getElapsedTime().asSeconds();

        switch (currentPhase)
        {
        case Idle:
            if (elapsedSinceCooldown >= cooldown)
            {
                currentPhase = FadingIn;
                PhaseTimer.restart();
            }
            break;

        case FadingIn:
        {
            float alphaRatio = std::min(1.f, phaseTime / 2.f);
            Color currentColor = startColor;
            currentColor.r = static_cast<int>(startColor.r + (targetColor.r - startColor.r) * alphaRatio);
            currentColor.g = static_cast<int>(startColor.g + (targetColor.g - startColor.g) * alphaRatio);
            currentColor.b = static_cast<int>(startColor.b + (targetColor.b - startColor.b) * alphaRatio);
            currentColor.a = static_cast<int>(startColor.a + (targetColor.a - startColor.a) * alphaRatio);
            BGrect.setFillColor(currentColor);
            for (auto& enemy : enemies)
                enemy.currentspeed = enemy.enemy_speed * (1.f - alphaRatio);

            if (phaseTime >= 2.f)
            {
                for (auto& enemy : enemies)
                    enemy.TimeStop = true;

                currentPhase = Active;
                PhaseTimer.restart();
            }
            break;
        }

        case Active:
            BGrect.setFillColor(targetColor); // полный серый эффект
            if (phaseTime >= duration)
            {
                currentPhase = FadingOut;
                PhaseTimer.restart();
            }
            break;

        case FadingOut:
        {
            float alphaRatio = std::min(1.f, phaseTime / 2.f);
            Color currentColor = targetColor;
            currentColor.r = static_cast<int>(targetColor.r - (targetColor.r - startColor.r) * alphaRatio);
            currentColor.g = static_cast<int>(targetColor.g - (targetColor.g - startColor.g) * alphaRatio);
            currentColor.b = static_cast<int>(targetColor.b - (targetColor.b - startColor.b) * alphaRatio);
            currentColor.a = static_cast<int>(targetColor.a - (targetColor.a - startColor.a) * alphaRatio);
            BGrect.setFillColor(currentColor);
            for (auto& enemy : enemies)
            {
                enemy.currentspeed = enemy.enemy_speed * alphaRatio;
                enemy.TimeStop = false;
            }

            if (phaseTime >= 2.f)
            {

                BGrect.setFillColor(startColor);
                currentPhase = Idle;
                CooldownTimer.restart();
            }
            break;
        }
        }
    }

    void draw(RenderWindow& window)
    {
        if (currentPhase != Idle)
            window.draw(BGrect);
        window.draw(ClockSprite);
        window.draw(MinuteRect);
        window.draw(HourRect);
    }
    bool isActive()
    {
        if (currentPhase == Active)
            return true;
        return false;
    }
    void setUpgradeLevel(int level)
    {
        if (level > 6)
            level = 6;

        Level = level;

        
    }

    ~Ability6() {}

};


class UpgradeAbility // будет как в доте, то есть плюсики над навыками
{
private:
    Sprite UpgradeSprite;
    Color currentColor; // начальный серый
    Color targetColor;
    float AnimSpeed = 20.0f;
    Clock deltaClock;
    bool isPressed = false;
    float ScaleX;
    float ScaleY;
    float X;
    float Y;
    float width;
    float height;
    Keyboard::Key bindKey;

    RectangleShape ColorAnim;

public:
    UpgradeAbility(int RectSize, int PosX, int PosY, const Texture& Texture, Keyboard::Key BindKeyboard)
    {
        bindKey = BindKeyboard;
        UpgradeSprite.setTexture(Texture);
        ScaleX = float(RectSize) / Texture.getSize().x;
        ScaleY = float(RectSize) / Texture.getSize().y / 2;
        UpgradeSprite.setScale(ScaleX, ScaleY);
        UpgradeSprite.setPosition(PosX, PosY - Texture.getSize().y * float(RectSize) / Texture.getSize().y / 2 /*- (float(RectSize) / Texture.getSize().y/2)*/);
        X = PosX;
        Y = PosY - Texture.getSize().y * float(RectSize) / Texture.getSize().y / 2;
        ColorAnim.setSize(Vector2f(Texture.getSize().x * float(RectSize) / Texture.getSize().x / 2, Texture.getSize().y * float(RectSize) / Texture.getSize().y / 2));
        ColorAnim.setPosition(UpgradeSprite.getPosition().x + ColorAnim.getSize().x/2, UpgradeSprite.getPosition().y);
        ColorAnim.setFillColor(Color(50, 50, 50));
        width = UpgradeSprite.getGlobalBounds().width;
        height = UpgradeSprite.getGlobalBounds().height;
    }
    bool Update(RenderWindow& window, int& CurrentAbility) //bool говно полное. Потом сделать массив int. Чтобы 0 - отсутствие навыка, а 6 - максимум
    {
        static bool wasPressed = false;
        float deltaTime = deltaClock.restart().asSeconds();
        Vector2i MousePos = Mouse::getPosition(window);
        Vector2f worldPos = window.mapPixelToCoords(MousePos);

        if ((Mouse::isButtonPressed(sf::Mouse::Left) && UpgradeSprite.getGlobalBounds().contains(worldPos)) || Keyboard::isKeyPressed(bindKey))
            isPressed = true;
        else
            isPressed = false;
        if (UpgradeSprite.getGlobalBounds().contains(worldPos)) {
            targetColor = sf::Color(240, 186, 26); // оранжевый
        }
        else {
            targetColor = sf::Color(70, 70, 70); // серый
        }

        if (isPressed) 
        {
            UpgradeSprite.setOrigin(UpgradeSprite.getGlobalBounds().width / 2, UpgradeSprite.getGlobalBounds().height / 2);
            UpgradeSprite.setScale(ScaleX-0.01f, ScaleY-0.01f);  // чуть уменьшаем
            UpgradeSprite.setOrigin(0, 0);
            UpgradeSprite.setPosition(X + (width - UpgradeSprite.getGlobalBounds().width)/2, Y + (height - UpgradeSprite.getGlobalBounds().height)/2);

            ColorAnim.setOrigin(ColorAnim.getSize().x / 2, ColorAnim.getSize().y / 2);
            ColorAnim.setScale(UpgradeSprite.getGlobalBounds().width/2/ ColorAnim.getSize().x, 0.8f);
            ColorAnim.setOrigin(0, 0);
            ColorAnim.setPosition(X + (width - UpgradeSprite.getGlobalBounds().width) / 2 + UpgradeSprite.getGlobalBounds().width / 2 - ColorAnim.getSize().x/2, Y + (height - UpgradeSprite.getGlobalBounds().height));
            
        }
        else 
        {
            UpgradeSprite.setOrigin(0, 0);
            UpgradeSprite.setScale(ScaleX, ScaleY);  // чуть уменьшаем
            UpgradeSprite.setPosition(X, Y);

            ColorAnim.setOrigin(0, 0);
            ColorAnim.setScale(1, 1);
            ColorAnim.setPosition(UpgradeSprite.getPosition().x + UpgradeSprite.getGlobalBounds().width / 2 - ColorAnim.getSize().x/2, UpgradeSprite.getPosition().y);
        }

        float t = deltaTime * AnimSpeed;

        // Просто приближаем каждый канал по чуть-чуть

        if (currentColor.r != targetColor.r)
            currentColor.r += static_cast<int>((targetColor.r - currentColor.r) * t);

        if (currentColor.g != targetColor.g)
            currentColor.g += static_cast<int>((targetColor.g - currentColor.g) * t);

        if (currentColor.b != targetColor.b)
            currentColor.b += static_cast<int>((targetColor.b - currentColor.b) * t);

        ColorAnim.setFillColor(currentColor);

        window.draw(ColorAnim);
        window.draw(UpgradeSprite);
        

        if (isPressed)
        {
            // Кнопку отпустили
            CurrentAbility += 1;
            //wasPressed = false; // Обновляем состояние
            return true;
        }
        else
        {
            //wasPressed = MousePressed; // Обновляем состояние
            return false;
        }
    }
    void justDraw(RenderWindow& window)
    {
        window.draw(ColorAnim);
        window.draw(UpgradeSprite);
    }
    void setColor(Color color)
    {
        ColorAnim.setFillColor(color);
    }
    ~UpgradeAbility() {}
};

class AbilitiesUI
{
private:
    RectangleShape AbilityRects[6];

    Texture AbilityTextures[6];

    Sprite AbilitySprites[6];

    RectangleShape UpgradeLevel[6][6]; // первое число - номер навыка, второе - уровень
    RectangleShape UpgradeBG[6];

    Texture UpgradeTexture;

    vector <UpgradeAbility> Upgrades;

    Texture IconTexture;
    Sprite IconSprite;
    bool CanDrawed[6] = { false,false,false,false,false,false };
    Clock UpgradeClock;
    float UpgradeTime;
public:
    AbilitiesUI(int PosX, int PosY, int RectSize, int SpaceBetween, string AbilitiesWayPath[6], string way_path_icon)
    {
        UpgradeTexture.loadFromFile("data/images/UpgradeButton.png");

        for (int i = 0; i < 6; i++)
        {
            AbilityTextures[i].loadFromFile(AbilitiesWayPath[i]);
        }

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                UpgradeLevel[i][j].setFillColor(Color(100, 100, 100, 200));
                UpgradeLevel[i][j].setSize(Vector2f(18, 18));
            }

        }
        for (int i = 0; i < 6; i++)
        {
            UpgradeBG[i].setFillColor(Color(50, 50, 50, 200));
            UpgradeBG[i].setSize(Vector2f(70, 48));
        }
        /*AbilityTextures[0].loadFromFile(way_path1);
        AbilityTextures[1].loadFromFile(way_path2);
        AbilityTextures[2].loadFromFile(way_path3);
        AbilityTextures[3].loadFromFile(way_path4);
        AbilityTextures[4].loadFromFile(way_path5);
        AbilityTextures[5].loadFromFile(way_path6);*/
        IconTexture.loadFromFile(way_path_icon);

        for (int i = 0; i < 6; i++)
        {
            AbilitySprites[i].setTexture(AbilityTextures[i]);
        }
        
        /*AbilitySprites[0].setTexture(AbilityTextures[0]);
        AbilitySprites[1].setTexture(AbilityTextures[1]);
        AbilitySprites[2].setTexture(AbilityTextures[2]);
        AbilitySprites[3].setTexture(AbilityTextures[3]);
        AbilitySprites[4].setTexture(AbilityTextures[4]);
        AbilitySprites[5].setTexture(AbilityTextures[5]);*/
        IconSprite.setTexture(IconTexture);

        for (int i = 0; i < 6; i++)
        {
            AbilityRects[i].setSize(Vector2f(RectSize, RectSize));
            AbilityRects[i].setFillColor(Color(70, 70, 70, 220));
        }

        /*AbilityRects[0].setSize(Vector2f(RectSize, RectSize));
        AbilityRects[0].setFillColor(Color(70, 70, 70, 220));

        AbilityRects[1].setSize(Vector2f(RectSize, RectSize));
        AbilityRects[1].setFillColor(Color(70, 70, 70, 220));

        AbilityRects[2].setSize(Vector2f(RectSize, RectSize));
        AbilityRects[2].setFillColor(Color(70, 70, 70, 220));

        AbilityRects[3].setSize(Vector2f(RectSize, RectSize));
        AbilityRects[3].setFillColor(Color(70, 70, 70, 220));

        AbilityRects[4].setSize(Vector2f(RectSize, RectSize));
        AbilityRects[4].setFillColor(Color(70, 70, 70, 220));

        AbilityRects[5].setSize(Vector2f(RectSize, RectSize));
        AbilityRects[5].setFillColor(Color(70, 70, 70, 220));*/

        IconSprite.setScale(float(RectSize) / IconTexture.getSize().x, float(RectSize) / IconTexture.getSize().y);

        AbilityRects[0].setPosition(PosX, PosY);
        AbilitySprites[0].setScale(float(RectSize - 10) / AbilityTextures[0].getSize().x, float(RectSize - 10) / AbilityTextures[0].getSize().y);
        AbilitySprites[0].setPosition(AbilityRects[0].getPosition().x + 5, AbilityRects[0].getPosition().y + 5);

        AbilityRects[1].setPosition(PosX + (RectSize + SpaceBetween) * 1, PosY);
        AbilitySprites[1].setScale(float(RectSize - 10) / AbilityTextures[1].getSize().x, float(RectSize - 10) / AbilityTextures[1].getSize().y);
        AbilitySprites[1].setPosition(AbilityRects[1].getPosition().x + 5, AbilityRects[1].getPosition().y + 5);

        AbilityRects[2].setPosition(PosX + (RectSize + SpaceBetween) * 2, PosY);
        AbilitySprites[2].setScale(float(RectSize - 10) / AbilityTextures[2].getSize().x, float(RectSize - 10) / AbilityTextures[2].getSize().y);
        AbilitySprites[2].setPosition(AbilityRects[2].getPosition().x + 5, AbilityRects[2].getPosition().y + 5);

        AbilityRects[3].setPosition(PosX + (RectSize + SpaceBetween) * 3, PosY);
        AbilitySprites[3].setScale(float(RectSize - 10) / AbilityTextures[3].getSize().x, float(RectSize - 10) / AbilityTextures[3].getSize().y);
        AbilitySprites[3].setPosition(AbilityRects[3].getPosition().x + 5, AbilityRects[3].getPosition().y + 5);

        AbilityRects[4].setPosition(PosX + (RectSize + SpaceBetween) * 4, PosY);
        AbilitySprites[4].setScale(float(RectSize - 10) / AbilityTextures[4].getSize().x, float(RectSize - 10) / AbilityTextures[4].getSize().y);
        AbilitySprites[4].setPosition(AbilityRects[4].getPosition().x + 5, AbilityRects[4].getPosition().y + 5);

        AbilityRects[5].setPosition(PosX + (RectSize + SpaceBetween) * 5, PosY);
        AbilitySprites[5].setScale(float(RectSize - 10) / AbilityTextures[5].getSize().x, float(RectSize - 10) / AbilityTextures[5].getSize().y);
        AbilitySprites[5].setPosition(AbilityRects[5].getPosition().x + 5, AbilityRects[5].getPosition().y + 5);

        

        for (int i = 0; i < 6; i++)
        {
            int pos = 0;
            UpgradeBG[i].setPosition(AbilityRects[i].getPosition().x, AbilityRects[i].getPosition().y + RectSize);
            for (int j = 0; j < 6; j++)
            {
                if (pos < 3)
                    UpgradeLevel[i][j].setPosition(AbilityRects[i].getPosition().x + UpgradeLevel[i][j].getSize().x * pos + 4 * (pos+1), AbilityRects[i].getPosition().y + RectSize + 4);// это рамочка))
                else
                    UpgradeLevel[i][j].setPosition(AbilityRects[i].getPosition().x + UpgradeLevel[i][j].getSize().x * (pos - 3) + 4 * (pos - 2), AbilityRects[i].getPosition().y + RectSize + 4 + UpgradeLevel[i][j].getSize().y + 4);
                pos += 1;
            }

        }
        

        for (int i = 0; i < 6; ++i) {
            sf::Keyboard::Key bindKey = static_cast<sf::Keyboard::Key>(sf::Keyboard::Num1 + i);
            Upgrades.emplace_back(RectSize, AbilityRects[i].getPosition().x, PosY, UpgradeTexture, bindKey); // вызывается конструктор с аргументами
        }

    }
    void UpdateAbilities(int HaveAbilities[6])
    {
        for (int i = 0; i < 6; i++)
        {
            if (HaveAbilities[i] > 0)
            {
                CanDrawed[i] = true;
            }
        }
    }

    void Update(RenderWindow& window/*, bool HaveAbilities[6]*/, Hero& hero, Ability1& ability1, Ability2& ability2, Ability3& ability3, Ability4& ability4, Ability5& ability5) // спорная херня, надо переделать
    {
        if (hero.UpgradePoint > 0)
        {
            for (int i = 0; i < 6; ++i)
            {
                if (hero.HaveAbilities[i] < 6)
                {
                    Upgrades[i].setColor(Color(50, 50, 50));
                    Upgrades[i].justDraw(window);
                    UpgradeTime = UpgradeClock.getElapsedTime().asMilliseconds();
                    if (UpgradeTime >= 200)
                    {
                        if (Upgrades[i].Update(window, hero.HaveAbilities[i]))
                            //hero.HaveAbilities[i] = test;
                        {
                            //hero.HaveAbilities[i] += 1;
                            for (int j = 0; j < hero.HaveAbilities[i]; j++)
                                UpgradeLevel[i][j].setFillColor(Color(235, 192, 52));
                            if (!CanDrawed[i])
                                CanDrawed[i] = true;
                            hero.UpgradePoint -= 1;
                            UpgradeClock.restart();
                            switch (i) // да я обосрался и сделал так. А всё потому что тупень и решил не делать массивы и наследование. Теперь придётся мучаться с шедеврокодом
                            {
                            case 0:
                            {
                                ability1.setUpgradeLevel(hero.HaveAbilities[i]);
                                break;
                            }
                            case 1:
                            {
                                ability2.setUpgradeLevel(hero.HaveAbilities[i]);
                                break;
                            }
                            case 2:
                            {
                                ability3.setUpgradeLevel(hero.HaveAbilities[i]);
                                break;
                            }
                            case 3:
                            {
                                ability4.setUpgradeLevel(hero.HaveAbilities[i]);
                                break;
                            }
                            case 4:
                            {
                                ability5.setUpgradeLevel(hero.HaveAbilities[i]);
                                break;
                            }
                            case 5:
                            {
                                //ability6.setUpgradeLevel(hero.HaveAbilities[i]);
                                break;
                            }
                            }
                        }

                    }
                    
                }
            }
        }

        for (int i = 0; i < 6; i++)
        {
            window.draw(AbilityRects[i]);
        }

        for (int i = 0; i < 6; i++)
        {
            window.draw(UpgradeBG[i]);
            for (int j = 0; j < 6; j++)
            {
                window.draw(UpgradeLevel[i][j]);
            }

        }

        for (int i = 0; i < 6; i++)
        {
            if (CanDrawed[i] == true)
            {
                AbilitySprites[i].setColor(Color(255, 255, 255));
            }
            else 
            {
                AbilitySprites[i].setColor(Color(100, 100, 100));
            }
            window.draw(AbilitySprites[i]);
        }

        for (int i = 0; i < 6; i++)
        {
            IconSprite.setPosition(AbilityRects[i].getPosition().x, AbilityRects[i].getPosition().y);
            window.draw(IconSprite);
        }
    }
    ~AbilitiesUI()
    {

    }
};
#endif