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

    void Update(RenderWindow& window, int newPercent = 0) 
    {
        
            percent += newPercent;
            Sliderect.setSize(Vector2f(float(percent) * BackGroundrect.getSize().x / maxEXP, 15));
            if (percent >= maxEXP)
            {
                percent = 0;
                maxEXP += 25;
            }
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
        window.draw(BackGroundrect);
        //window.draw(Sliderect);
        if (percent > 0)
        {
            window.draw(Sliderect);
            //if (isDamaged)
            //    window.draw(DamageOverlay);  // Отображаем жёлтую полоску повреждений
        }
        //window.draw(HealthFrameSprite);
    }

    String getPercent() {
        return to_string(percent);
    }

    ~EXPSlider() {
    }
};
class Ability1 // удар перед собой
{
private:
    Texture ability_texture;
    Sprite ability_sprite;
    
    bool active = false;
    Vector2f direction;
    float speed = 15.f; // пикселей в секунду
    int damage = 25;
    //float deltaTime;
    Vector2f startPosition;

public:
    int Level = 1;
    Ability1(int Damage, string Directory)
    {

        damage = Damage;
        ability_texture.loadFromFile(Directory);
        ability_sprite.setTexture(ability_texture);
        ability_sprite.setOrigin(ability_texture.getSize().x / 2, ability_texture.getSize().y / 2);
        ability_sprite.setScale(0.5f, 0.5f);
    }

    void attack(const sf::Sprite& heroSprite, Hero& character)
    {
        if (active == true)
            return;

        switch (character.HeroDirection)
        {
        case 0: //влево
            ability_sprite.setPosition(heroSprite.getPosition().x, heroSprite.getPosition().y + 29);
            break;
        case 1: //вправо
            ability_sprite.setPosition(heroSprite.getPosition().x + 48, heroSprite.getPosition().y + 29);
            break;
        case 2:
            ability_sprite.setPosition(heroSprite.getPosition().x + 24, heroSprite.getPosition().y);
            break;
        case 3:
            ability_sprite.setPosition(heroSprite.getPosition().x + 24, heroSprite.getPosition().y + 58);
            break;
        }
        startPosition = ability_sprite.getPosition();

        // Направление в зависимости от направления героя
        switch (character.HeroDirection)
        {
        case 0: //влево
            direction = sf::Vector2f(-1.f, 0.f);
            ability_sprite.setRotation(180);
            //ability_sprite.setPosition(heroSprite.getPosition().x, heroSprite.getPosition().y + 20);
            break;
        case 1: //вправо
            direction = sf::Vector2f(1.f, 0.f);
            ability_sprite.setRotation(0);
            //ability_sprite.setPosition(heroSprite.getPosition().x, heroSprite.getPosition().y + 20);
            break;
        case 2: //вверх
            direction = sf::Vector2f(0.f, -1.f);
            ability_sprite.setRotation(-90);
            //ability_sprite.setPosition(heroSprite.getPosition().x+20, heroSprite.getPosition().y);
            break;
        case 3: //вниз
            direction = sf::Vector2f(0.f, 1.f);
            ability_sprite.setRotation(90);

            break;
        }
        active = true;
    }

    void update(sf::RenderWindow& window, /*Clock& Ability1clock*/ vector<Enemy>& enemies)
    {
        if (active == false)
            return;

        // deltaTime = Ability1clock.getElapsedTime().asMilliseconds();

        if (sqrt(pow(ability_sprite.getPosition().x - startPosition.x, 2) + pow(ability_sprite.getPosition().y - startPosition.y, 2)) > 250)
        {
            active = false;
            for (auto& enemy : enemies)
            {
                enemy.CanTakeDamage[0] = true;
                enemy.canPush = true;
                //enemy.canTakeDamage = false;
            }
            return;
        }

        // Движение снаряда
        ability_sprite.move(direction * speed);

        // Проверка попадания во врагов
        sf::FloatRect bounds = ability_sprite.getGlobalBounds();
        for (auto& enemy : enemies)
        {
            if (enemy.getGlobalBounds().intersects(bounds))
            {
                enemy.takeDamage(damage, 0);
                if (enemy.canPush)
                {
                    enemy.enemy_sprite.move(direction * 50.f);
                    enemy.canPush = false;
                }

                //enemy.canTakeDamage = false;
            }
        }
    }
    Sprite getSprite()
    {
        return ability_sprite;
    }
    bool isActive() const
    {
        return active;
    }

    ~Ability1() {}
};
class Ability2 // выстрел в ближайшего врага
{
private:
    Texture ability_texture;
    Sprite ability_sprite;
    Music AttackSound;
    Clock AttackClock;
    //Clock internalClock; // <--- Новый таймер

    float cooldown = 1.f; // кулдаун между выстрелами
    float speed = 25.f;   // пикселей в секунду

    bool active = false;
    Vector2f direction;
    int damage = 25;
    Vector2f startPosition;
    Vector2f endPosition;
    float range = 2000.f;

    bool targetAcquired = false;

public:
    int Level = 1;
    Ability2(int Damage, const string& Directory)
    {
        AttackSound.openFromFile("data/music/Attack2.mp3");
        damage = Damage;
        ability_texture.loadFromFile(Directory);
        ability_sprite.setTexture(ability_texture);
        ability_sprite.setOrigin(ability_texture.getSize().x / 2.f, ability_texture.getSize().y / 2.f);
    }

    void attack(const Sprite& heroSprite)
    {
        if (active) return;

        float timeSinceLastAttack = AttackClock.getElapsedTime().asSeconds();
        if (timeSinceLastAttack < cooldown)
            return;

        AttackSound.play();
        ability_sprite.setPosition(heroSprite.getPosition().x + 24, heroSprite.getPosition().y + 29);
        startPosition = ability_sprite.getPosition();

        active = true;
        targetAcquired = false;
        AttackClock.restart();
        //internalClock.restart(); // сброс таймера движения
    }

    void update(RenderWindow& window, vector<Enemy>& enemies)
    {
        if (!active) return;

        // Обновляем deltaTime

        // Определение цели
        if (!targetAcquired)
        {
            float minDistance = 2500.f;
            for (auto& enemy : enemies)
            {
                Vector2f enemyPos = enemy.getPosition();
                float dx = enemyPos.x - startPosition.x;
                float dy = enemyPos.y - startPosition.y;
                float distance = sqrt(dx * dx + dy * dy);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    endPosition = enemyPos;
                }
            }

            direction = endPosition - startPosition;
            float length = sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length != 0)
                direction /= length; // нормализация

            float angle = atan2(direction.y, direction.x) * 180.f / 3.14159265f;
            ability_sprite.setRotation(angle);
            targetAcquired = true;
        }

        // Движение с учетом времени
        ability_sprite.move(direction * speed);

        float traveled = sqrt(pow(ability_sprite.getPosition().x - startPosition.x, 2) +
            pow(ability_sprite.getPosition().y - startPosition.y, 2));

        if (traveled > range)
        {
            deactivate(enemies);
            return;
        }

        // Столкновение
        FloatRect bounds = ability_sprite.getGlobalBounds();
        for (auto& enemy : enemies)
        {
            if (enemy.getGlobalBounds().intersects(bounds))
            {
                enemy.takeDamage(damage, 1);
                enemy.CanTakeDamage[1] = true;
                enemy.enemy_sprite.move(direction * 50.f);
                deactivate(enemies);
                break;
            }
        }
    }

    void deactivate(vector<Enemy>& enemies)
    {
        active = false;
        targetAcquired = false;
        for (auto& enemy : enemies)
        {
            enemy.CanTakeDamage[1] = true;
        }
    }

    Sprite getSprite() const { return ability_sprite; }
    bool isActive() const { return active; }

    ~Ability2() {}
};

class Ability3
{
private:
    Texture ability_texture;
    Sprite ability_sprites[8];

    int damage = 25;

    bool active = false;
    float cooldown;
    float duration;

    int MAXnumProjectiles = 8;
    int numProjectiles = 1;

    float radius = 250.f;
    float rotationSpeed = 100.f; // градусов в секунду
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
        float deltaTime = 1.f / 60.f; // если ты не передаёшь его, иначе замени

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
                float angle = currentAngle + (360.f / numProjectiles) * i;
                float rad = angle * 3.1415f / 180.f;

                float offsetX = std::cos(rad) * radius;
                float offsetY = std::sin(rad) * radius;

                ability_sprites[i].setPosition(heroSprite.getPosition().x + 24 + offsetX,
                    heroSprite.getPosition().y + 29 + offsetY);
                ability_sprites[i].setRotation(angle + 90.f);
            }

            for (auto& enemy : enemies)
            {
                for (int i = 0; i < numProjectiles; i++)
                {
                    if (enemy.getGlobalBounds().intersects(ability_sprites[i].getGlobalBounds()))
                    {
                        // Только если урон не был от этого же снаряда
                        if (enemy.lastHitByProjectile != i || enemy.Damage3Cooldown.getElapsedTime().asMilliseconds() >= 300)
                        {
                            enemy.takeDamage(damage, 2);
                            enemy.CanTakeDamage[2] = false;

                            Vector2f pushDirection = enemy.getPosition() - heroSprite.getPosition();
                            float length = sqrt(pushDirection.x * pushDirection.x + pushDirection.y * pushDirection.y);
                            if (length != 0)
                                pushDirection /= length;

                            enemy.enemy_sprite.move(pushDirection * 50.f);

                            // Сохраняем индекс снаряда, от которого был урон
                            enemy.lastHitByProjectile = i;
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

    bool isActive() const { return active; }
    ~Ability3() {}
};

class Ability4
{
private:
    Texture ability_texture;
    Sprite ability_sprite;

    int damage = 10;

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


public:
    int Level = 1;
    Ability4(const string& texturePath, int Damage)
    {
        damage = Damage;
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
                if (enemy.canTakeDamage())
                {
                    enemy.CanTakeDamage[3] = true;
                    enemy.takeDamage(damage, 3);
                    enemy.damageCooldown.restart();
                }

            }
        }


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

    RectangleShape ColorAnim;

public:
    UpgradeAbility(int RectSize, int PosX, int PosY, const Texture& Texture)
    {
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
    void Update(RenderWindow& window, bool& CurrentAbility) //bool говно полное. Потом сделать массив int. Чтобы 0 - отсутствие навыка, а 6 - максимум
    {
        float deltaTime = deltaClock.restart().asSeconds();
        Vector2i MousePos = Mouse::getPosition(window);
        Vector2f worldPos = window.mapPixelToCoords(MousePos);

        if (Mouse::isButtonPressed(sf::Mouse::Left) && UpgradeSprite.getGlobalBounds().contains(worldPos))
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
            CurrentAbility = true;
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
    }
    ~UpgradeAbility() {}
};

class AbilitiesUI
{
private:
    RectangleShape AbilityRects[6];

    Texture AbilityTextures[6];

    Sprite AbilitySprites[6];
    Texture UpgradeTexture;

    vector <UpgradeAbility> Upgrades;

    Texture IconTexture;
    Sprite IconSprite;
    bool CanDrawed[6] = { false,false,false,false,false,false };
public:
    AbilitiesUI(int PosX, int PosY, int RectSize, int SpaceBetween, string way_path1, string way_path2, string way_path3, string way_path4, string way_path5, string way_path6, string way_path_icon)
    {
        UpgradeTexture.loadFromFile("data/images/UpgradeButton.png");
        AbilityTextures[0].loadFromFile(way_path1);
        AbilityTextures[1].loadFromFile(way_path2);
        AbilityTextures[2].loadFromFile(way_path3);
        AbilityTextures[3].loadFromFile(way_path4);
        AbilityTextures[4].loadFromFile(way_path5);
        AbilityTextures[5].loadFromFile(way_path6);
        IconTexture.loadFromFile(way_path_icon);


        AbilitySprites[0].setTexture(AbilityTextures[0]);
        AbilitySprites[1].setTexture(AbilityTextures[1]);
        AbilitySprites[2].setTexture(AbilityTextures[2]);
        AbilitySprites[3].setTexture(AbilityTextures[3]);
        AbilitySprites[4].setTexture(AbilityTextures[4]);
        AbilitySprites[5].setTexture(AbilityTextures[5]);
        IconSprite.setTexture(IconTexture);

        AbilityRects[0].setSize(Vector2f(RectSize, RectSize));
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
        AbilityRects[5].setFillColor(Color(70, 70, 70, 220));

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

        for (int i = 0; i < 6; ++i) {
            Upgrades.emplace_back(RectSize, AbilityRects[i].getPosition().x, PosY, UpgradeTexture); // вызывается конструктор с аргументами
        }

    }
    void UpdateAbilities(bool HaveAbilities[6])
    {
        for (int i = 0; i < 6; i++)
        {
            if (HaveAbilities[i] == true)
            {
                CanDrawed[i] = true;
            }
        }
    }

    void Update(RenderWindow& window/*, bool HaveAbilities[6]*/, Hero& hero) // спорная херня, надо переделать
    {
        bool test;
        if (hero.UpgradePoint > 0)
        {
            for (int i = 0; i < 6; ++i)
            {
                if (hero.HaveAbilities[i] != true)
                    test = hero.HaveAbilities[i];
                Upgrades[i].Update(window, test);
                if (test == true)
                {
                    hero.HaveAbilities[i] = test;
                    CanDrawed[i] == true;
                    hero.UpgradePoint -= 1;
                }
            }
        }

        for (int i = 0; i < 6; i++)
        {
            window.draw(AbilityRects[i]);
        }

        for (int i = 0; i < 6; i++)
        {
            if (CanDrawed[i] == true)
            {
                AbilitySprites[i].setColor(Color(255, 255, 255));
                window.draw(AbilitySprites[i]);
            }
            else 
            {
                AbilitySprites[i].setColor(Color(100, 100, 100));
                window.draw(AbilitySprites[i]);
            }
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