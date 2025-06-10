#include "Header.h"
#include "Hero.h"
#include "Enemy.h"
#include "GameMenu.h"
#include "Engine.h"

//Texture grassTexture;
//
//Clock damageClock;
//////////////////
//
//int gamePause = -1; //-1 это отсутствие паузы. 1 - пауза есть
//
//////////////////
//CircleShape circle1(25, 30);
//Vector2f positionScreen(0, 0);
//
//int dimensionScreenX = 1920;
//int dimensionScreenY = 1080;
//int HeroDimensionX = 64;
//int HeroDimensionY = 96;
//const float damageInterval = 0.5f;
//
////------НАЧАЛО ЖОПНОЙ БОЛИ С МЕНЮ--------
//void InitText(Text& mtext, float xpos, float ypos, String str, int size_font = 60,
//	Color menu_text_color = Color::White, int bord = 0, Color border_color = Color::Black);




//---------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	GameStart();
	//setlocale(LC_ALL, "rus");
	//RenderWindow window(VideoMode(1920, 1080), "Shadow Defender");
	//window.setFramerateLimit(60);

	//Image icon;
	//icon.loadFromFile("data/images/icon.png");
	//window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	//RectangleShape background(Vector2f(1920, 1080));
	//Texture texture_window;
	///*if (!texture_window.loadFromFile("data/images/mainmenu.jfif")) return 4;
	//background.setTexture(&texture_window);

	//Font font;
	//if (!font.loadFromFile("data/font/PixelizerBold.ttf")) return 5;

	//Text GameName;
	//GameName.setFont(font);
	//InitText(GameName, 480, 50, L"Shadow Defender", 150, Color(237, 147, 0), 3);*/
	////Завтра продолжу











	//Font font;
	//font.loadFromFile("data/font/AmazDooMLeft2.ttf");

	//Button Button(200, 100, 500, 300, font, "Play", 70, Color::Red);

	///*enemy_image.loadFromFile("data/images/car.png");
	//enemy_image1.loadFromFile("data/images/car.png");
	//enemy_texture1.loadFromImage(enemy_image1);
	//enemy_sprite1.setTexture(enemy_texture1);
	//enemy_sprite1.setPosition(200, 200);*/

	////ХОТЬ ГДЕ-ТО Я МОГУ ПОЩУПАТЬ ТРАВКУ
	////(ЕСЛИ Я САМ НЕ ПОНИМАЮ СВОИ РОФЛЫ СПУСТЯ ВРЕМЯ, ТО ОБЪЯСНЯЮ: СНИЗУ ТЕКСТУРА ТРАВЫ)

	//grassTexture.loadFromFile("data/images/grass1.png");

	//const int tileWidth = grassTexture.getSize().x;
	//const int tileHeight = grassTexture.getSize().y;

	//vector<Sprite> tiles;
	//grassTexture.setSmooth(true);
	//// Заполняем мир плитками
	//for (int x = 0; x < 10000; x += tileWidth) {
	//	for (int y = 0; y < 10000; y += tileHeight) {
	//		Sprite tile(grassTexture);
	//		tile.setPosition(x, y);
	//		tiles.push_back(tile);
	//	}
	//}
	////ВОТ ТРАВКА И КОНЧИЛАСЬ((

	//circle1.setFillColor(Color::White);
	//circle1.setPosition(300, 300);

	//View view(FloatRect(0, 0, dimensionScreenX, dimensionScreenY));//экран прокрутки
	//HWND consoleWindow = GetConsoleWindow();
	//ShowWindow(consoleWindow, SW_SHOW);
	//SoundBuffer buffer;
	//buffer.loadFromFile("data/music/walk1.mp3");
	//Sound walking;
	//walking.setBuffer(buffer);

	//SoundBuffer buffer1;
	//buffer1.loadFromFile("data/music/damagetaken.mp3");
	//Sound damagetaken;
	//damagetaken.setBuffer(buffer1);

	//Clock clock;
	//Clock clock1;
	//Clock clock2;
	////Clock damageClock;
	////const float damageInterval = 0.5f; //интервал 0.5 секунды

	//Hero Hero(200, 200);
	//vector<Enemy> enemies;
	//vector<Enemy>::iterator iter;

	//while (window.isOpen())
	//{
	//	float delttime = clock2.getElapsedTime().asMilliseconds();
	//	if (delttime > 200 && Keyboard::isKeyPressed(Keyboard::Escape))
	//	{
	//		gamePause *= -1;
	//		clock2.restart();
	//	}
	//	float deltatime = clock.getElapsedTime().asMicroseconds();
	//	clock.restart();
	//	deltatime = deltatime / 800;
	//	Event close;//событие закрытие
	//	bool isMoving = false;
	//	bool walkSound = false;
	//	while (window.pollEvent(close))//окно запрашивает какое событие
	//	{
	//		if (close.type == Event::Closed)//если событие "закрытие", окно закрывается
	//		{
	//			window.close();
	//		}
	//	}
	//	Image enemy_image;
	//	enemy_image.loadFromFile("data/images/enemy.psd");
	//	if (gamePause != 1 && Keyboard::isKeyPressed(Keyboard::M))
	//	{
	//		Enemy enemy(enemy_image, 500, 500);
	//		enemies.emplace_back(enemy);
	//		cout << "Number of enemies: " << enemies.size() << endl; // Добавьте это для отладки
	//		clock1.restart();
	//	}
	//	Hero.handleInput(gamePause, deltatime);
	//	if (enemies.size() != 0)
	//	{
	//		for (iter = enemies.begin(); iter != enemies.end(); iter++)
	//		{
	//			iter->HeroFollow(gamePause, Hero.inheroBounds, Hero.hero_sprite, deltatime, enemies);
	//			iter->DamageDeal(gamePause, Hero, damageInterval, damageClock);
	//			/*iter->EnemyUpdate(window);*/
	//		}
	//	}
	//	/*if (enemies.size() != 0)
	//	{
	//		while (int i = 1 < enemies.size())
	//		{
	//			enemies[i].HeroFollow(Hero.inheroBounds, Hero.hero_sprite);
	//			enemies[i].DamageDeal(Hero, Hero.heroBounds);
	//			enemies[i].EnemyUpdate(window);
	//			i++;
	//		}
	//	}*/
	//	/*Enemy.HeroFollow(inheroBounds, enemyBounds, Hero.hero_sprite);
	//	Enemy.DamageDeal(Hero, heroBounds, enemyBounds);*/
	//	//ВЫВОД ГЛАВНОГО МЕНЮ

	//	/*window.clear();
	//	window.draw(background);
	//	window.draw(GameName);*/

	//	cout << Hero.hero_sprite.getPosition().x << "    ";
	//	cout << Hero.hero_sprite.getPosition().y << endl;





	//	FloatRect circleBounds = circle1.getGlobalBounds();
	//	if (Hero.heroBounds.intersects(circleBounds))
	//		cout << "collision" << endl;

	//	//УПРАВЛЕНИЕ  ВРАГОВ(НАВЕРНОЕ)
	//	//ПОПЫТКА ХОДЬБЫ ВРАГА
	//	/*float enemydif_x = (hero.getPosition().x) - (enemy.getPosition().x);
	//	float enemydif_y = (hero.getPosition().y) - (enemy.getPosition().y);
	//	float supX = abs(enemydif_x);
	//	float supY = abs(enemydif_y);
	//	float enemy_speed = 1;

	//	if (hero.getPosition().x != enemy.getPosition().x)
	//	{
	//		if (enemydif_x < 0)
	//		{
	//			if (abs(enemydif_x) < abs(enemydif_y))
	//				enemy.move(-(enemy_speed * (supX / sqrt(supX * supX + supY * supY))), 0);
	//			else
	//				enemy.move(-enemy_speed * (supX / sqrt(supX * supX + supY * supY)), 0);
	//		}
	//		else
	//			if (abs(enemydif_x) < abs(enemydif_y))
	//				enemy.move(enemy_speed * (supX / sqrt(supX * supX + supY * supY)), 0);
	//			else
	//				enemy.move(enemy_speed * (supX / sqrt(supX * supX + supY * supY)), 0);

	//	}
	//	if (hero.getPosition().y != enemy.getPosition().y)
	//	{
	//		if (enemydif_y < 0)
	//		{
	//			if (abs(enemydif_x) > abs(enemydif_y))
	//				enemy.move(0, -(enemy_speed * (supY / sqrt(supX * supX + supY * supY))));
	//			else
	//				enemy.move(0, -enemy_speed * (supY / sqrt(supX * supX + supY * supY)));
	//		}
	//		else
	//			if (abs(enemydif_x) > abs(enemydif_y))
	//				enemy.move(0, enemy_speed * (supY / sqrt(supX * supX + supY * supY)));
	//			else
	//				enemy.move(0, enemy_speed * (supY / sqrt(supX * supX + supY * supY)));

	//	}*/

	//	/*																				 |
	//	НАЧИНАЕТСЯ РУБРИКА ЭКСКРЕМЕНТЫ С МОИМ КОДОМ (эксперимент удался.Вот и результат \|/ )
	//	*/

	//	/*FloatRect enemyBounds = enemy.getGlobalBounds();*/
	//	/*if (inheroBounds.intersects(enemyBounds))
	//	{
	//		if (enemydif_x < 0)
	//		{
	//			if (abs(enemydif_x) < abs(enemydif_y))
	//				enemy.move((enemy_speed * (supX / sqrt(supX * supX + supY * supY))), 0);
	//			else
	//				enemy.move(enemy_speed, 0);
	//		}
	//		else
	//			if (abs(enemydif_x) < abs(enemydif_y))
	//				enemy.move(-enemy_speed * (supX / sqrt(supX * supX + supY * supY)), 0);
	//			else
	//				enemy.move(-enemy_speed, 0);

	//		if (enemydif_y < 0)
	//		{
	//			if (abs(enemydif_x) > abs(enemydif_y))
	//				enemy.move(0, (enemy_speed * (supX / sqrt(supX * supX + supY * supY))));
	//			else
	//				enemy.move(0, enemy_speed);
	//		}
	//		else
	//			if (abs(enemydif_x) > abs(enemydif_y))
	//				enemy.move(0, -enemy_speed * (supX / sqrt(supX * supX + supY * supY)));
	//			else
	//				enemy.move(0, -enemy_speed);
	//	}*/

	//	//if (heroBounds.intersects(enemyBounds))
	//	//	EnemyInHero = true;
	//	//else
	//	//	EnemyInHero = false;

	//	//if (EnemyInHero == true && damageClock.getElapsedTime().asSeconds() >= damageInterval)
	//	//{
	//	//		playerHealth--; // Уменьшаем здоровье на 1
	//	//		damageClock.restart(); // Сбрасываем таймер
	//	//		damagetaken.play();
	//	//		cout << "Health: " << playerHealth << endl; // Вывод текущего здоровья
	//	//}

	//	//СМЕЩЕНИЕ ЭКРАНА ПРИ ХОДЬБЕ

	//	const float worldWidth = 10000;  // мир 10000 пикселей
	//	const float worldHeight = 10000;  // мир 10000 пикселей


	//	positionScreen.x = Hero.hero_sprite.getPosition().x + HeroDimensionX - (dimensionScreenX / 2);
	//	positionScreen.y = Hero.hero_sprite.getPosition().y + HeroDimensionY - (dimensionScreenY / 2);

	//	// Ограничиваем движение камеры по оси X
	//	if (positionScreen.x < 0) {
	//		positionScreen.x = 0; // Камера не может выходить за пределы левой границы
	//	}
	//	else if (positionScreen.x > worldWidth - dimensionScreenX) {
	//		positionScreen.x = worldWidth - dimensionScreenX; // Камера не может выходить за пределы правой границы
	//	}

	//	// Ограничиваем движение камеры по оси Y
	//	if (positionScreen.y < 0) {
	//		positionScreen.y = 0; // Камера не может выходить за пределы верхней границы
	//	}
	//	else if (positionScreen.y > worldHeight - dimensionScreenY) {
	//		positionScreen.y = worldHeight - dimensionScreenY; // Камера не может выходить за пределы нижней границы
	//	}



	//	if (Hero.hero_sprite.getPosition().x- <= 0 && Hero.hero_sprite.getPosition().y <= 0) //ограничения, чтобы герой не вышел в отрицательные x и y
	//		Hero.hero_sprite.setPosition(0, 0);
	//	if (Hero.hero_sprite.getPosition().x <= 0)
	//		Hero.hero_sprite.setPosition(0, Hero.hero_sprite.getPosition().y);
	//	if (Hero.hero_sprite.getPosition().y <= 0)
	//		Hero.hero_sprite.setPosition(Hero.hero_sprite.getPosition().x, 0);
	//	if (Hero.hero_sprite.getPosition().x >= worldWidth - 35)
	//		Hero.hero_sprite.setPosition(worldWidth - 35, Hero.hero_sprite.getPosition().y);
	//	if (Hero.hero_sprite.getPosition().y >= worldHeight - 50)
	//		Hero.hero_sprite.setPosition(Hero.hero_sprite.getPosition().x, worldHeight - 50);


	//	view.reset(FloatRect(positionScreen.x, positionScreen.y, dimensionScreenX, dimensionScreenY));






	//	window.clear();
	//	window.setView(view);
	//	for (unsigned long int i = 0; i < tiles.size(); ++i) {
	//		window.draw(tiles[i]); // Рисуем каждый спрайт по индексу
	//	}
	//	//for (iter = enemies.begin(); iter < enemies.end(); ++iter) {
	//	//	iter->EnemyUpdate(window); // Рисуем каждого вражину по индексу
	//	//}
	//	for (unsigned long int i = 0; i < enemies.size(); ++i) {
	//		enemies[i].EnemyUpdate(window); // Рисуем каждого врага по индексу
	//	}
	//	window.draw(circle1);
	//	Button.ButtonDraw(window);
	//	Hero.HeroDraw(window);
	//	window.display();

	//}
	//window.close();
	return 0;
}
