#include "Header.h"
#include "ThreadPool.hpp"
#include "Hero.h"
#include "Enemy.h"
#include "GameMenu.h"
#include "GameFunctions.h"


Vector2f getRandomSpawnPosition(float screenPosX, float screenPosY) {
	int side = rand() % 4; // 0 = слева, 1 = справа, 2 = сверху, 3 = снизу
	float x, y;

	switch (side)
	{
	case 0: // слева
		x = -60.f; // за левым краем
		y = (rand() % 1080);
		return Vector2f(x + screenPosX, y + screenPosY);
	case 1: // справа
		x = 60.f; // за правым краем
		y = (rand() % 1080);
		return Vector2f(x + screenPosX + 1920, y + screenPosY);
	case 2: // сверху
		x = (rand() % 1920);
		y = -60.f; // выше экрана
		return Vector2f(x + screenPosX, y + screenPosY);
	case 3: // снизу
		x = (rand() % 1920);
		y = 60.f; // ниже экрана
		return Vector2f(x + screenPosX, y + screenPosY + 1080);
	}

};
void updateEnemies(
	std::vector<Enemy>& enemies,
	ThreadPool& pool,
	int gamePause,
	FloatRect& heroBounds,
	Sprite& heroSprite,
	float deltaTime,
	Hero& hero,
	const float damageInterval,
	Clock& damageClock
)
{
	std::vector<std::future<void>> futures;

	for (Enemy& enemy : enemies)
	{
		futures.push_back(pool.enqueue([&enemy, gamePause, &heroBounds, &heroSprite, deltaTime, &enemies, &hero, damageInterval, &damageClock]()
			{
				enemy.HeroFollow(gamePause, heroBounds, heroSprite, deltaTime, enemies);
				enemy.DamageDeal(gamePause, hero, damageInterval, damageClock);
			}));
	}

	for (auto& f : futures) {
		f.get(); // ждём выполнения всех врагов
	}
};
void save(int& MusicVolume, int& SoundVolume, int& BestScore, int& CountOfMoney, int& Upgrade1Level, int& Upgrade2Level, int& Upgrade3Level)
{
	ofstream save;
	save.open("save.txt");
	if (save.is_open())
	{
		save << MusicVolume << " " << SoundVolume << " " << BestScore << " " << CountOfMoney << " " << Upgrade1Level << " " << Upgrade2Level << " " << Upgrade3Level << " "; // потом прикрутить сюда все характеристики в цифрах, баланс и лучший счёт
	}
	save.close();
};
void load(int& MusicVolume, int& SoundVolume, int& BestScore, int& CountOfMoney, int& Upgrade1Level, int& Upgrade2Level, int& Upgrade3Level)
{
	ifstream load;
	load.open("save.txt");
	if (load.is_open())
	{
		int x;

		if (load >> x)
			MusicVolume = x;
		else
			MusicVolume = 50;

		if (load >> x)
			SoundVolume = x;
		else
			SoundVolume = 50;

		if (load >> x)
			BestScore = x;
		else
			BestScore = 0;

		if (load >> x)
			CountOfMoney = x;
		else
			CountOfMoney = 0;

		if (load >> x)
		{
			if (x > 3)
				x = 3;
			Upgrade1Level = x;
		}
		else
			Upgrade1Level = 0;
		if (load >> x)
		{
			if (x > 3)
				x = 3;
			Upgrade2Level = x;
		}
		else
			Upgrade2Level = 0;
		if (load >> x)
		{
			if (x > 3)
				x = 3;
			Upgrade3Level = x;
		}
		else
			Upgrade3Level = 0;
	}
	else
		return;
};
//int Menu(RenderWindow& window)
//{
//	setlocale(LC_ALL, "rus");
//	Texture texture;
//	texture.loadFromFile("data/images/MainMenu.png");
//	RectangleShape rect;
//		rect.setSize(Vector2f(1920, 1080));
//		rect.setTexture(&texture);
//		rect.setPosition(0, 0);
//	while (window.isOpen())
//	{
//		Event event_menu;
//		while (window.pollEvent(event_menu))
//		{
//			if (event_menu.type == Event::Closed) window.close();
//			if (event_menu.type == Event::KeyPressed)
//			{
//				if (event_menu.key.code == Keyboard::Escape) return 1;
//			}
//		}
//		window.clear();
//		window.draw(rect);
//		window.display();
//	}
//	return 1;
//}

int GameStart()
{
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_SHOW);
	setlocale(LC_ALL, "rus");
	RenderWindow window(VideoMode(1920, 1080), "Shadow Defender", Style::Default);
	window.setFramerateLimit(60);

	Cursor cursor;
	Image cursorImage;
	cursorImage.loadFromFile("data/images/Cursor.png");
	cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), Vector2u(0, 0));
	window.setMouseCursor(cursor);

	while (true)
	{

		Texture grassTexture;

		Clock damageClock;
		////////////////
		/*Sprite rect;
		Texture texture;
		texture.loadFromFile("data/images/Pause.png");*/

		int gamePause = false; //false это отсутствие паузы. true - пауза есть
		int UpgradePause = false; //false это отсутствие паузы. true - пауза есть
		ThreadPool pool(std::thread::hardware_concurrency());
		////////////////
		Vector2f positionScreen(0, 0);

		int dimensionScreenX = 1920;
		int dimensionScreenY = 1080;
		int HeroDimensionX = 64;
		int HeroDimensionY = 96;
		const float damageInterval = 0.5f;

		Image icon;
		icon.loadFromFile("data/images/icon.png");
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());


		//параметры которые будут передаваться из загрузки(иначе - по умолчанию)

		int SoundVolume = 100;
		int MusicVolume = 100;
		int BestScore = 0;
		int CountOfMoney = 0;

		int Upgrade1Level = 0;
		int Upgrade2Level = 0;
		int Upgrade3Level = 0;


		int UpgradeLevels[3];
		int UpgradeMoneyCount[3] = { 25,25,25 };


		int Difficulty = 2; // 1 - easy, 2 - normal, 3 - hard    ))))
		/*RectangleShape background(Vector2f(1920, 1080));
		Texture texture_window;*/
		/*if (!texture_window.loadFromFile("data/images/mainmenu.jfif")) return 4;
		background.setTexture(&texture_window);

		Font font;
		if (!font.loadFromFile("data/font/PixelizerBold.ttf")) return 5;

		Text GameName;
		GameName.setFont(font);
		InitText(GameName, 480, 50, L"Shadow Defender", 150, Color(237, 147, 0), 3);*/

		load(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);

		UpgradeLevels[0] = Upgrade1Level;
		UpgradeLevels[1] = Upgrade2Level;
		UpgradeLevels[2] = Upgrade3Level;

		for (int i = 0; i < 3; i++)
		{
			UpgradeMoneyCount[i] = 25 + UpgradeLevels[i] * 25;
		}
		//--------------------------------ГЛАВНОЕ МЕНЮ----------------------------
		Texture Main_texture;
		Texture Intro_texture;
		Font font;
		font.loadFromFile("data/font/AmazDooMLeft2.ttf");
		//Button(int Recwidth, int Recheight, int PosX, int PosY, const Color & colorshape, const Font & Font, const string & Legend, int TextSize, const Color & colortext, int transparent)
		//---------------------------------КНОПКИ МЕНЮ---------------------------
		Button ButtonBackground(330, 1080, 0, 0, Color(70, 70, 70), font, "", 120, Color(200, 0, 0), 220, false, 0);
		Button GameName(1000, 100, 460, 50, Color(100, 100, 100), font, "Shadow Defender", 150, Color(200, 0, 0), 0, false, 6);

		Button Money(280, 60, 50, 5, Color(100, 100, 100), font, to_string(CountOfMoney), 50, Color(200, 200, 0), 0, false, 2);
		RectangleShape MoneyRect, MoneyRectBG;
		MoneyRect.setSize(Vector2f(320, 60));
		MoneyRectBG.setSize(Vector2f(330, 70));
		MoneyRect.setPosition(5, 5);
		MoneyRectBG.setPosition(0, 0);
		MoneyRect.setFillColor(Color(70, 70, 70));
		MoneyRectBG.setFillColor(Color(120, 120, 120));
		Texture MoneyTexture;
		MoneyTexture.loadFromFile("data/images/gold.png");
		Sprite MoneySprite;
		MoneySprite.setTexture(MoneyTexture);
		MoneySprite.setScale(60.f / MoneyTexture.getSize().x, 60.f / MoneyTexture.getSize().y);
		MoneySprite.setPosition(5, 5);
		Button BestScoreText(400, 70, 1550, 900, Color(150, 150, 150), font, L"Лучший счёт:", 50, Color(200, 200, 0), 0, false, 5);
		Button BestScoreNumber(400, 70, 1550, 950, Color(190, 190, 190), font, to_string(BestScore), 50, Color(200, 200, 0), 0, false, 5);
		Button Play(130, 70, 100, 350, Color(100, 100, 100), font, L"Играть", 100, Color(139, 0, 0), 0, true, 5);
		Button Settings(130, 70, 100, 500, Color(100, 100, 100), font, L"Настройки", 100, Color(139, 0, 0), 0, true, 5);
		Button Upgrade(130, 70, 100, 620, Color(100, 100, 100), font, L"Улучшения", 100, Color(139, 0, 0), 0, true, 5);
		Button Info(130, 70, 100, 760, Color(100, 100, 100), font, L"Бестиарий", 100, Color(139, 0, 0), 0, true, 5);
		Button Exit(130, 70, 100, 960, Color(100, 100, 100), font, L"Выход", 100, Color(139, 0, 0), 0, true, 5);
		//---------------------------------------------------------------------
		Main_texture.loadFromFile("data/images/Intro.png");
		Intro_texture.loadFromFile("data/images/MainMenu.png");
		SoundBuffer buffer;
		Music music;
		//Я НЕ ОПРЕДЕЛИЛСЯ ЧТО СТАВИТЬ В НАЧАЛО
		srand(time(nullptr));
		int introIndex = rand() % 2; // от 0 до 2
		string filename = "data/music/Intro";
		if (introIndex != 0)
			filename += to_string(introIndex);
		filename += ".mp3";
		music.openFromFile(filename);
		music.setLoop(true);
		music.play();
		music.setVolume(30.f * (float(MusicVolume) / 100));
		//int moving = 1920;
		//-----------------------------КНОПКИ "PLAY"---------------------------
		PopUpMenu Play_Menu(1650, 1080);
		Button ChooseDf(1000, 70, 600, 100, Color(100, 100, 100), font, L"Выберите сложность", 100, Color(180, 0, 0), 0, false, 5);
		//
		Texture Df;
		Sprite DfEasy;
		Df.loadFromFile("data/images/Difficulty.psd");
		DfEasy.setTexture(Df);
		DfEasy.setTextureRect(IntRect(0, 0, 98, 130));
		DfEasy.setPosition(705, 400);
		DfEasy.setScale(Vector2f(1.5f, 1.5f));
		RectangleShape DfEasyRect(Vector2f(162, 210));
		DfEasyRect.setFillColor(Color(100, 100, 100, 200));
		DfEasyRect.setPosition(700, 395);
		DfEasyRect.setOutlineThickness(4);
		DfEasyRect.setOutlineColor(Color(60, 60, 60, 200));
		PopUpButton DifficultyEasy(210, 100, 675, 650, Color(100, 100, 100), font, L"Изи", 85, Color(200, 0, 0), 0, true, 6);
		//
		Sprite DfNormal;
		DfNormal.setTexture(Df);
		DfNormal.setTextureRect(IntRect(0, 130, 98, 130));
		DfNormal.setPosition(1002, 400);
		DfNormal.setScale(Vector2f(1.5f, 1.5f));
		RectangleShape DfNormalRect(Vector2f(162, 210));
		DfNormalRect.setFillColor(Color(100, 100, 100, 200));
		DfNormalRect.setPosition(997, 395);
		DfNormalRect.setOutlineThickness(4);
		DfNormalRect.setOutlineColor(Color(60, 60, 60, 200));
		PopUpButton DifficultyNormal(210, 100, 975, 650, Color(100, 100, 100), font, L"Нормас", 85, Color(200, 0, 0), 0, true, 6);
		//
		Sprite DfHard;
		DfHard.setTexture(Df);
		DfHard.setTextureRect(IntRect(98, 130, 94, 130));
		DfHard.setPosition(1300, 400);
		DfHard.setScale(Vector2f(1.5f, 1.5f));
		RectangleShape DfHardRect(Vector2f(162, 210));
		DfHardRect.setFillColor(Color(100, 100, 100, 200));
		DfHardRect.setPosition(1295, 395);
		DfHardRect.setOutlineThickness(4);
		DfHardRect.setOutlineColor(Color(60, 60, 60, 200));
		PopUpButton DifficultyHard(210, 100, 1275, 650, Color(100, 100, 100), font, L"Кошмар", 85, Color(200, 0, 0), 0, true, 6);
		//
		PopUpButton Start(210, 100, 975, 850, Color(100, 100, 100), font, L"Начать", 130, Color(65, 65, 65), 0, true, 6);
		//---------------------------------------------------------------------
		//----------------------------КНОПКИ "SETTINGS"------------------------
		PopUpMenu Settings_Menu(1650, 1080);
		PopUpButton MusicButton(210, 100, 600, 350, Color(100, 100, 100), font, L"Музыка", 85, Color(200, 0, 0), 0, false, 6);
		PopUpButton SoundButton(210, 100, 600, 500, Color(100, 100, 100), font, L"Звук", 85, Color(200, 0, 0), 0, false, 6);
		SoundSlider MusicSlide(850, 365, 380, 70, MusicVolume);
		SoundSlider SoundSlide(850, 515, 380, 70, SoundVolume);
		PopUpButton MusicPercent(210, 100, 1200, 350, Color(100, 100, 100), font, MusicSlide.getPercent(), 85, Color(200, 0, 0), 0, false, 6);
		PopUpButton SoundPercent(210, 100, 1200, 500, Color(100, 100, 100), font, SoundSlide.getPercent(), 85, Color(200, 0, 0), 0, false, 6);
		//---------------------------------------------------------------------
		//---------------------------КНОПКИ "UPGRADE"--------------------------
		PopUpMenu Upgrade_Menu(1650, 1080);
		Clock AbilityUpgrade;
		Image Frame;
		Frame.loadFromFile("data/images/AbilityIcon.png");
		Image ability_1;
		Image ability_2;
		Image ability_3;
		ability_1.loadFromFile("data/images/Ability1.png");
		ability_2.loadFromFile("data/images/Ability2.png");
		ability_3.loadFromFile("data/images/Ability3.png");
		/*(int Recwidth, int Recheight, int PosX, int PosY, const Color& colorshape,
			const Font& Font, const String& Legend, int TextSize, const Color& colortext, Image& AbilityImg, bool CanClick = true, int Thickness = 0)*/
		AbilityButton Ability_1(400, 450, 400, 70, Color(80, 80, 80), font, L"Здоровье", 85, Color(200, 0, 0), ability_1, Frame, true, 6, Upgrade1Level, UpgradeMoneyCount[0]);
		AbilityButton Ability_2(400, 450, 900, 70, Color(80, 80, 80), font, L"Броня", 85, Color(200, 0, 0), ability_2, Frame, true, 6, Upgrade2Level, UpgradeMoneyCount[1]);
		AbilityButton Ability_3(400, 450, 1400, 70, Color(80, 80, 80), font, L"Атака", 85, Color(200, 0, 0), ability_3, Frame, true, 6, Upgrade3Level, UpgradeMoneyCount[2]);
		//---------------------------------------------------------------------
		//-----------------------------КНОПКИ "INFO"---------------------------
		PopUpMenu Info_Menu(1650, 1080);
		Texture AbilityIc;
		AbilityIc.loadFromFile("data/images/AbilityIcon.png");
		Sprite AbilityIcon1;
		Sprite AbilityIcon2;
		Sprite AbilityIcon3;
		AbilityIcon1.setTexture(AbilityIc);
		AbilityIcon1.setScale(150.f / AbilityIc.getSize().x, 150.f / AbilityIc.getSize().y);
		AbilityIcon2 = AbilityIcon1;
		AbilityIcon3 = AbilityIcon1;

		Texture abilityTexture_1;
		Texture abilityTexture_2;
		Texture abilityTexture_3;

		abilityTexture_1.loadFromFile("data/images/Ability1.png");
		abilityTexture_2.loadFromFile("data/images/Ability2.png");
		abilityTexture_3.loadFromFile("data/images/Ability3.png");

		Sprite AbilitySprite1;
		Sprite AbilitySprite2;
		Sprite AbilitySprite3;

		AbilitySprite1.setTexture(abilityTexture_1);
		AbilitySprite2.setTexture(abilityTexture_2);
		AbilitySprite3.setTexture(abilityTexture_3);

		AbilitySprite1.setScale(sf::Vector2f(150 / abilityTexture_1.getSize().x, 150 / abilityTexture_1.getSize().y));
		RectangleShape Ability1Rect(Vector2f(150, 150));
		Ability1Rect.setFillColor(Color(70, 70, 70, 255));
		Ability1Rect.setPosition(400, 150);
		AbilityIcon1.setPosition(400, 150);
		AbilitySprite1.setPosition(415, 175);
		PopUpButton AboutAbility1(1200, 100, 575, 175, Color(100, 100, 100), font, L"Очки здоровья: \nувеличение количества здоровья на 25 за уровень (максимум 75)", 60, Color(165, 0, 0), 0, false, 6);

		AbilitySprite2.setScale(sf::Vector2f(150 / abilityTexture_2.getSize().x, 150 / abilityTexture_2.getSize().y));
		RectangleShape Ability2Rect(Vector2f(150, 150));
		Ability2Rect.setFillColor(Color(70, 70, 70, 255));
		Ability2Rect.setPosition(400, 350);
		AbilityIcon2.setPosition(400, 350);
		AbilitySprite2.setPosition(420, 375);
		PopUpButton AboutAbility2(1200, 100, 650, 375, Color(100, 100, 100), font, L"Броня: \nувеличение сопротивление урону на 5 процентов за уровень (максимум 15)", 60, Color(165, 0, 0), 0, false, 6);

		AbilitySprite3.setScale(sf::Vector2f(150 / abilityTexture_2.getSize().x, 150 / abilityTexture_2.getSize().y));
		RectangleShape Ability3Rect(Vector2f(150, 150));
		Ability3Rect.setFillColor(Color(70, 70, 70, 255));
		Ability3Rect.setPosition(400, 550);
		AbilityIcon3.setPosition(400, 550);
		AbilitySprite3.setPosition(420, 575);
		PopUpButton AboutAbility3(1200, 100, 625, 575, Color(100, 100, 100), font, L"Урон: \nувеличение наносимого урона на 5 процентов за уровень (максимум 15)", 60, Color(165, 0, 0), 0, false, 6);
		//---------------------------------------------------------------------

		/*buffer.loadFromFile();*/
		bool isMenu = false; // огромный цикл который позволяет зациклить меню-игру, чтобы работало нужно два true))
		bool isIntro = false; // потом вернуть true
		bool isAnimation[4] = { false, false, false, false }; //mas[0] - анимация "Играть", 1 - анимация "Настройки" и т.д.
		MainMenu Menu(Main_texture);
		MainMenu intro(Intro_texture);
		/*MainMenu SettingMenu();
		SettingMenu.setColor(Color(100, 100, 100));*/

		while (isMenu)
		{
			GameName.TextAppears(window);
			Event event;
			window.clear();
			if (isIntro)
			{
				// Отображаем сообщение "Нажмите любую кнопку для продолжения"
				Intro menu(1920, 1080, 0, 0, Color(50, 50, 50), font, L"Нажмите любую кнопку, чтобы продолжить", 60, Color(200, 0, 0), 0, false, 6);
				intro.MenuDraw(window);
				menu.ButtonUpdate(window); // Выводим текстовое сообщение
				// Обработка событий
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						music.stop();
						window.close();
					}
					SoundBuffer buffer;
					buffer.loadFromFile("data/music/introStart.mp3");
					Sound sound(buffer);
					sound.setVolume(7.f);
					//sound.setPlayingOffset(sf::seconds(5.f));
					if (event.type == Event::KeyPressed || (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left))
					{

						sound.play();
						while (isIntro)
						{
							window.clear();
							intro.MenuDraw(window);
							GameName.TextAppears(window);
							window.draw(menu.rect);
							GameName.ButtonUpdate(window);
							menu.TextAnimation(window, isIntro);
							window.display();
						}
						//sound.stop();
						break; // Выход из этого цикла, чтобы начать показывать основное меню
					}
				}
				GameName.ButtonUpdate(window);
				window.display();
			}
			if (!isIntro)
			{
				window.clear(); // Очистка окна
				Event event;
				while (window.pollEvent(event))//окно запрашивает какое событие
				{
					if (event.type == Event::Closed)
					{
						music.stop();
						save(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);
						window.close();
					}
					if (event.type == Event::KeyPressed)
					{
						if (event.key.code == Keyboard::Escape) // это потом удалить, сделал чтобы выйти в игру вцелом
							isMenu = false;
					}
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
					{
						Vector2f worldPos = window.mapPixelToCoords(Mouse::getPosition(window));
						if (isAnimation[0] == false && isAnimation[1] == false && isAnimation[2] == false && isAnimation[3] == false)
						{
							if (Play.getText().getGlobalBounds().contains(worldPos))
							{
								isAnimation[0] = true;
								if (Settings_Menu.getPos().x <= 330)
									isAnimation[1] = !isAnimation[1];
								if (Upgrade_Menu.getPos().x <= 330)
									isAnimation[2] = !isAnimation[2];
								if (Info_Menu.getPos().x <= 330)
									isAnimation[3] = !isAnimation[3];
								//std::cout << "Play нажата\n";
								/*if (play.getPosition().x == 1920)
								{
									while (play.getPosition().x > 330)
									{
										play.move(Vector2f(-10, 0));
										moving -= 10;
										window.draw(play);
										cout << moving << "     " << play.getPosition().x << endl;
									}
								}
								else if (play.getPosition().x == 330)
								{
									while (play.getPosition().x < 1920)
									{
										play.move(10, 0);
										moving += 10;
									}
								}*/
								//isMenu = false; // например, выйти из меню
							}
							if (Settings.getText().getGlobalBounds().contains(worldPos))
							{
								isAnimation[1] = true;
								if (Play_Menu.getPos().x <= 330)
									isAnimation[0] = !isAnimation[0];
								if (Upgrade_Menu.getPos().x <= 330)
									isAnimation[2] = !isAnimation[2];
								if (Info_Menu.getPos().x <= 330)
									isAnimation[3] = !isAnimation[3];
								//std::cout << "Settings нажата\n";

							}
							if (Upgrade.getText().getGlobalBounds().contains(worldPos))
							{
								isAnimation[2] = true;
								if (Play_Menu.getPos().x <= 330)
									isAnimation[0] = !isAnimation[0];
								if (Settings_Menu.getPos().x <= 330)
									isAnimation[1] = !isAnimation[1];
								if (Info_Menu.getPos().x <= 330)
									isAnimation[3] = !isAnimation[3];
								//std::cout << "Upgrade нажата\n";

							}
							if (Info.getText().getGlobalBounds().contains(worldPos))
							{
								isAnimation[3] = true;
								if (Play_Menu.getPos().x <= 330)
									isAnimation[0] = !isAnimation[0];
								if (Settings_Menu.getPos().x <= 330)
									isAnimation[1] = !isAnimation[1];
								if (Upgrade_Menu.getPos().x <= 330)
									isAnimation[2] = !isAnimation[2];
								//std::cout << "Info нажата\n";

							}
							if (Exit.getText().getGlobalBounds().contains(worldPos))
							{
								//std::cout << "Exit нажата\n";
								music.stop();
								save(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);
								window.close();
								/*isMenu = false;*/ // например, выйти из меню
							}
						}
						/*Settings.ButtonUpdate(window, event);
						Upgrade.ButtonUpdate(window, event);
						Info.ButtonUpdate(window, event);
						Exit.ButtonUpdate(window, event);
						Play_Menu.MenuDraw(window);

						Settings_Menu.MenuDraw(window);
						Upgrade_Menu.MenuDraw(window);
						Info_Menu.MenuDraw(window);*/
					}

				}
				Menu.MenuDraw(window);
				ButtonBackground.ButtonUpdate(window);
				if (isAnimation[0])
				{
					Play_Menu.Animation(isAnimation[0], Play);
				}
				if (isAnimation[1])
				{
					Settings_Menu.Animation(isAnimation[1], Settings);
				}
				if (isAnimation[2])
				{
					Upgrade_Menu.Animation(isAnimation[2], Upgrade);
				}
				if (isAnimation[3])
				{
					Info_Menu.Animation(isAnimation[3], Info);
				}
				GameName.ButtonUpdate(window);
				BestScoreText.ButtonUpdate(window);
				BestScoreNumber.ButtonUpdate(window);
				Play_Menu.MenuDraw(window);
				Settings_Menu.MenuDraw(window);
				Upgrade_Menu.MenuDraw(window);
				Info_Menu.MenuDraw(window);
				if (!Play_Menu.MovingLeft && Play_Menu.getPos().x <= 330)
				{
					/*MusicButton.ButtonUpdate(window);
					SoundButton.ButtonUpdate(window);
					MusicSlide.ButtonUpdate(window, event, MusicPercent);
					SoundSlide.ButtonUpdate(window, event, SoundPercent);
					MusicPercent.ButtonUpdate(window);
					SoundPercent.ButtonUpdate(window);*/
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
					{
						Vector2f worldPos = window.mapPixelToCoords(Mouse::getPosition(window));
						if (DifficultyEasy.getText().getGlobalBounds().contains(worldPos))
						{
							DifficultyEasy.setTextColor(Color(200, 0, 0));
							Difficulty = 1;
							Start.setTextColor(Color(200, 20, 20));
							DifficultyNormal.setTextColor(Color(100, 100, 100));
							DifficultyHard.setTextColor(Color(100, 100, 100));
						}
						else if (DifficultyNormal.getText().getGlobalBounds().contains(worldPos))
						{
							DifficultyNormal.setTextColor(Color(200, 0, 0));
							Difficulty = 2;
							Start.setTextColor(Color(200, 20, 20));
							DifficultyEasy.setTextColor(Color(100, 100, 100));
							DifficultyHard.setTextColor(Color(100, 100, 100));
						}
						else if (DifficultyHard.getText().getGlobalBounds().contains(worldPos))
						{
							DifficultyHard.setTextColor(Color(200, 0, 0));
							Difficulty = 3;
							Start.setTextColor(Color(200, 20, 20));
							DifficultyEasy.setTextColor(Color(100, 100, 100));
							DifficultyNormal.setTextColor(Color(100, 100, 100));
						}
						else if (Start.getText().getGlobalBounds().contains(worldPos))
						{
							if (Start.getTextColor() == Color(200, 20, 20))
							{
								isMenu = false;
								save(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);
							}
						}
					}
					GameName.setTextColor(Color(200, 0, 0, 0));
					GameName.setOutlineColor(Color(200, 0, 0, 0));
					BestScoreText.setTextColor(Color(150, 150, 150, 0));
					BestScoreNumber.setTextColor(Color(190, 190, 190, 0));
					BestScoreText.setOutlineColor(Color(0, 0, 0, 0));
					BestScoreNumber.setOutlineColor(Color(0, 0, 0, 0));
					ChooseDf.ButtonUpdate(window);
					DifficultyEasy.ButtonUpdate(window);
					DifficultyNormal.ButtonUpdate(window);
					DifficultyHard.ButtonUpdate(window);
					window.draw(DfEasyRect);
					window.draw(DfEasy);
					window.draw(DfNormalRect);
					window.draw(DfNormal);
					window.draw(DfHardRect);
					window.draw(DfHard);
					Start.ButtonUpdate(window);
				}
				if (!Settings_Menu.MovingLeft && Settings_Menu.getPos().x <= 330)
				{
					MusicButton.ButtonUpdate(window);
					SoundButton.ButtonUpdate(window);
					MusicSlide.ButtonUpdate(window, event, MusicPercent, MusicVolume);
					music.setVolume((30.f * (float(MusicVolume) / 100)));
					SoundSlide.ButtonUpdate(window, event, SoundPercent, SoundVolume);
					MusicPercent.ButtonUpdate(window);
					SoundPercent.ButtonUpdate(window);
				}
				if (!Upgrade_Menu.MovingLeft && Upgrade_Menu.getPos().x <= 330)
				{
					GameName.setTextColor(Color(200, 0, 0, 0));
					GameName.setOutlineColor(Color(200, 0, 0, 0));
					BestScoreText.setTextColor(Color(150, 150, 150, 0));
					BestScoreNumber.setTextColor(Color(190, 190, 190, 0));
					BestScoreText.setOutlineColor(Color(0, 0, 0, 0));
					BestScoreNumber.setOutlineColor(Color(0, 0, 0, 0));
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
					{
						Vector2f worldPos = window.mapPixelToCoords(Mouse::getPosition(window));
						if (Upgrade1Level < 3 && UpgradeMoneyCount[0] <= CountOfMoney)
						{
							if (Ability_1.getText().getGlobalBounds().contains(worldPos))
							{
								if (Ability_1.ButtonUpdate(window, AbilityUpgrade, event, CountOfMoney))
								{
									CountOfMoney -= UpgradeMoneyCount[0];
									UpgradeMoneyCount[0] += 25;
									Upgrade1Level++;
								}
							}
						}

						// Ability 2
						if (Upgrade2Level < 3 && UpgradeMoneyCount[1] <= CountOfMoney)
						{
							if (Ability_2.getText().getGlobalBounds().contains(worldPos))
							{
								if (Ability_2.ButtonUpdate(window, AbilityUpgrade, event, CountOfMoney))
								{
									CountOfMoney -= UpgradeMoneyCount[1];
									UpgradeMoneyCount[1] += 25;
									Upgrade2Level++;
								}
							}
						}

						// Ability 3
						if (Upgrade3Level < 3 && UpgradeMoneyCount[2] <= CountOfMoney)
						{
							if (Ability_3.getText().getGlobalBounds().contains(worldPos))
							{
								if (Ability_3.ButtonUpdate(window, AbilityUpgrade, event, CountOfMoney))
								{
									CountOfMoney -= UpgradeMoneyCount[2];
									UpgradeMoneyCount[2] += 25;
									Upgrade3Level++;
								}
							}
						}
					}
					Ability_1.ButtonUpdate(window, AbilityUpgrade, event);
					Ability_2.ButtonUpdate(window, AbilityUpgrade, event);
					Ability_3.ButtonUpdate(window, AbilityUpgrade, event);
					window.draw(MoneyRectBG);
					window.draw(MoneyRect);
					Money.setText(to_string(CountOfMoney));
					Money.ButtonUpdate(window);
					window.draw(MoneySprite);
				}
				if (!Info_Menu.MovingLeft && Info_Menu.getPos().x <= 330)
				{
					GameName.setTextColor(Color(200, 0, 0, 0));
					GameName.setOutlineColor(Color(200, 0, 0, 0));
					BestScoreText.setTextColor(Color(150, 150, 150, 0));
					BestScoreNumber.setTextColor(Color(190, 190, 190, 0));
					BestScoreText.setOutlineColor(Color(0, 0, 0, 0));
					BestScoreNumber.setOutlineColor(Color(0, 0, 0, 0));

					AboutAbility1.ButtonUpdate(window);
					AboutAbility2.ButtonUpdate(window);
					AboutAbility3.ButtonUpdate(window);

					window.draw(Ability1Rect);
					window.draw(AbilityIcon1);
					window.draw(AbilitySprite1);

					window.draw(Ability2Rect);
					window.draw(AbilityIcon2);
					window.draw(AbilitySprite2);

					window.draw(Ability3Rect);
					window.draw(AbilityIcon3);
					window.draw(AbilitySprite3);
				}
				if (Play_Menu.MovingLeft && Play_Menu.getPos().x >= 1920 && Settings_Menu.MovingLeft && Settings_Menu.getPos().x >= 1920 && Upgrade_Menu.MovingLeft && Upgrade_Menu.getPos().x >= 1920 && Info_Menu.MovingLeft && Info_Menu.getPos().x >= 1920)
				{
					GameName.setTextColor(Color(200, 0, 0, 255));
					GameName.setOutlineColor(Color(0, 0, 0, 255));
					BestScoreText.setTextColor(Color(150, 150, 150, 255));
					BestScoreNumber.setTextColor(Color(190, 190, 190, 255));
					BestScoreText.setOutlineColor(Color(0, 0, 0, 255));
					BestScoreNumber.setOutlineColor(Color(0, 0, 0, 255));
				}
				Play.ButtonUpdate(window);
				Settings.ButtonUpdate(window);
				Upgrade.ButtonUpdate(window);
				Info.ButtonUpdate(window);
				Exit.ButtonUpdate(window);
				window.display(); // Отображаем изменения
			}
		}
		music.stop();

		//--------------------------------ГЛАВНОЕ МЕНЮ (КОНЕЦ)----------------------------

		Hero Hero(200, 200, 150, 0, 0, 0);

		Music GameMusic1;
		GameMusic1.openFromFile("data/music/Game1.mp3");
		GameMusic1.setVolume(30.f * (float(MusicVolume) / 100));

		View uiView;
		//-----------------------ЧУТЬ-ЧУТЬ ИНТЕРФЕЙСА ИГРЫ--------------------------------
		//таймер вверху экрана
		Text timerText;
		Font TimerFont;
		TimerFont.loadFromFile("data/font/PixelizerBold.ttf");
		timerText.setFont(TimerFont);
		timerText.setCharacterSize(60);
		timerText.setFillColor(Color::White);
		timerText.setPosition(900, 20);

		const float totalTime = 600.0f; // 10 минут
		float gameTime = 0.f;          // Прошедшее время


		Button Pause(210, 130, (1920 / 2) - 105, 100, Color(100, 100, 100), font, L"Пауза", 150, Color(200, 0, 0), 0, false, 6);
		bool QuitWarning = false;
		RectangleShape PauseRect;
		PauseRect.setSize(Vector2f(1920, 1080));
		PauseRect.setPosition(0, 0);
		PauseRect.setFillColor(Color(100, 100, 100, 150));
		PopUpButton MusicPauseText(210, 100, 600, 350, Color(100, 100, 100), font, L"Музыка", 85, Color(158, 44, 44), 0, false, 6);
		PopUpButton SoundPauseText(210, 100, 600, 500, Color(100, 100, 100), font, L"Звук", 85, Color(158, 44, 44), 0, false, 6);
		SoundSlider MusicPauseSlide(850, 365, 380, 70, MusicVolume);
		SoundSlider SoundPauseSlide(850, 515, 380, 70, SoundVolume);
		PopUpButton MusicPausePercent(210, 100, 1200, 350, Color(100, 100, 100), font, MusicSlide.getPercent(), 85, Color(158, 44, 44), 0, false, 6);
		PopUpButton SoundPausePercent(210, 100, 1200, 500, Color(100, 100, 100), font, SoundSlide.getPercent(), 85, Color(158, 44, 44), 0, false, 6);

		PopUpButton QuitToMenu(210, 100, (1920 / 2) - 105, 900, Color(100, 100, 100), font, L"Выйти в меню", 85, Color(115, 112, 112), 0, true, 6);

		PopUpButton WarningText(500, 100, (1920 / 2) - 250, 300, Color(100, 100, 100), font, L"Уверены что хотите выйти?", 80, Color(200, 0, 0), 0, false, 6);
		PopUpButton WarningText1(500, 100, (1920 / 2) - 250, 400, Color(100, 100, 100), font, L"Весь прогресс этого сеанса будет утерян", 50, Color(150, 0, 0), 0, false, 6);

		PopUpButton QuitYes(350, 100, (1920 / 2) - 350, 575, Color(100, 100, 100), font, L"ДА!", 90, Color(180, 0, 0), 0, true, 6);
		PopUpButton QuitNo(350, 100, (1920 / 2), 575, Color(100, 100, 100), font, L"НЕ", 90, Color(180, 0, 0), 0, true, 6);

		RectangleShape QuitRect;
		QuitRect.setSize(Vector2f(700, 400));
		QuitRect.setPosition((1920 / 2) - 350, 300);
		QuitRect.setFillColor(Color(100, 100, 100, 255));



		Slider HealthBar(25, 25, "data/images/HealthBar.psd", 100, 150);
		EXPSlider EXPBar(0, 1065, 0, 100);
		//
		uiView.setSize(dimensionScreenX, dimensionScreenY);
		uiView.setCenter(dimensionScreenX / 2.f, dimensionScreenY / 2.f);
		RectangleShape LoadingRect;
		LoadingRect.setSize(Vector2f(1920, 1080));
		LoadingRect.setPosition(0, 0);
		LoadingRect.setFillColor(Color(47, 47, 47, 255));

		Text LoadingText;
		String loadText[3] = { L"Загрузка.", L"Загрузка..", L"Загрузка..." };
		LoadingText.setString(loadText[0]);
		LoadingText.setFont(TimerFont);
		LoadingText.setCharacterSize(70);
		LoadingText.setPosition((1920 / 2) - (LoadingText.getGlobalBounds().width / 2), (1080 / 2) - (LoadingText.getGlobalBounds().height / 2));
		int TextAnim = 0;

		Texture LoadingTexture;
		LoadingTexture.loadFromFile("data/images/Weapon2Icon.psd");
		Sprite LoadingSprite;
		LoadingSprite.setTexture(LoadingTexture);
		LoadingSprite.setOrigin(LoadingTexture.getSize().x / 2, LoadingTexture.getSize().y / 2);
		LoadingSprite.setPosition(1850, 1000);
		int RotateScale = 0;
		//
		/*AbilitiesUI(int PosX, int PosY, int RectSize, int SpaceBetween, string way_path1, string way_path2, string way_path3, string way_path4, string way_path5, string way_path6)*/
		AbilitiesUI Abilities(70, 950, 70, 5, "data/images/Weapon1Icon.png", "data/images/Weapon2Icon.psd", "data/images/Attack3.png", "data/images/Weapon4Icon.psd", "data/images/Attack1.png", "data/images/Attack1.png", "data/images/WeaponIcon.png");
		//-----------------------ЧУТЬ-ЧУТЬ ИНТЕРФЕЙСА ИГРЫ(КОНЕЦ)--------------------------
		// 
		//СПОСОБНОСТИ
		Ability1 ability1(25, "data/images/Attack1.png");
		Abilities.UpdateAbilities(Hero.HaveAbilities);
		Ability2 ability2(25, "data/images/Attack2.png");
		Ability3 ability3(6, 4, "data/images/Attack3.png", 7);
		Ability4 ability4("data/images/Attack4.psd", 10);
		//
		//МЕНЮ ПРОКАЧКИ НАВЫКОВ
		//
		//UpgradeAbility Ability1Update(400, 450, 400, 400, Color(80, 80, 80), font, L"Способ 1", 85, Color(200, 0, 0), "data/images/Weapon4Icon.psd", "data/images/WeaponIcon.png", true, 6);
		//
		/*enemy_image.loadFromFile("data/images/car.png");
		enemy_image1.loadFromFile("data/images/car.png");
		enemy_texture1.loadFromImage(enemy_image1);
		enemy_sprite1.setTexture(enemy_texture1);
		enemy_sprite1.setPosition(200, 200);*/

		//ХОТЬ ГДЕ-ТО Я МОГУ ПОЩУПАТЬ ТРАВКУ
		//(ЕСЛИ Я САМ НЕ ПОНИМАЮ СВОИ РОФЛЫ СПУСТЯ ВРЕМЯ, ТО ОБЪЯСНЯЮ: СНИЗУ ТЕКСТУРА ТРАВЫ)

		grassTexture.loadFromFile("data/images/grass1.png");

		const int tileWidth = grassTexture.getSize().x;
		const int tileHeight = grassTexture.getSize().y;

		vector<Sprite> tiles;
		grassTexture.setSmooth(true);
		// Заполняем мир плитками
		for (int x = 0; x < 10000; x += tileWidth) {
			for (int y = 0; y < 10000; y += tileHeight) {
				Sprite tile(grassTexture);
				tile.setPosition(x, y);
				tiles.push_back(tile);
			}
		}
		//ВОТ ТРАВКА И КОНЧИЛАСЬ((


		View view(FloatRect(0, 0, dimensionScreenX, dimensionScreenY));//экран прокрутки

		/*buffer.loadFromFile("data/music/walk1.mp3");*/

	/*	SoundBuffer buffer1;
		buffer1.loadFromFile("data/music/damagetaken.mp3");
		Sound damagetaken;
		damagetaken.setBuffer(buffer1);*/
		//Clock Ability1clock;
		Clock AbilitiesClock[6];
		//Clock Ability1clockCooldown;
		Clock AbilitiesCooldown[6];
		Clock clock;
		Clock TimerClock;
		Clock clock1;
		Clock clock2;
		float AbilitiesTime[6];
		for (int i = 0; i < 6; i++)
		{
			AbilitiesTime[i] = AbilitiesCooldown[i].getElapsedTime().asMilliseconds();
		}
		//float Ability1Time = AbilitiesCooldown[0].getElapsedTime().asMilliseconds();
		//Clock damageClock;
		//const float damageInterval = 0.5f; //интервал 0.5 секунды



		vector<Enemy> enemies;
		vector<Enemy>::iterator iter;
		Image enemy_image;
		float deltatime;
		Event close;
		Event event;
		enemy_image.loadFromFile("data/images/enemy.psd");
		bool StartGame = false;
		Clock LoadingClock;
		float LoadingTime = LoadingClock.getElapsedTime().asSeconds();
		Clock LoadAnimation;
		float AnimationLoad = LoadAnimation.getElapsedTime().asSeconds();



		const int worldWidth = 10000;  // мир 10000 пикселей
		const int worldHeight = 10000;  // мир 10000 пикселей


		//музычка
		bool MusicNotStarted = true;
		//GameMusic1.play();
		//музычка


		while (window.isOpen())
		{
			window.clear();

			float delttime = clock2.getElapsedTime().asMilliseconds();
			float deltaTimer = TimerClock.restart().asSeconds();

			deltatime = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			deltatime = deltatime / 800;

			//Event close;//событие закрытие
			/*bool isMoving = false;
			bool walkSound = false;*/
			while (window.pollEvent(event))//окно запрашивает какое событие
			{
				if (event.type == Event::Closed)//если событие "закрытие", окно закрывается
				{
					save(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);
					GameMusic1.stop();
					window.close();
					music.stop();
				}
			}

			for (int i = 0; i < 6; i++)
			{
				AbilitiesTime[i] = AbilitiesCooldown[i].getElapsedTime().asMilliseconds();
			}


			if (StartGame)
			{


				if (delttime > 200 && Keyboard::isKeyPressed(Keyboard::Escape))
				{
					gamePause = !gamePause;
					/*isMenu = true;
					isIntro = true;
					break;*/
					clock2.restart();
				}
				if (!gamePause && enemies.size() != 0)
				{
					gameTime += deltaTimer;
					if (gameTime > totalTime) {
						gameTime = totalTime;
						// в случае когда таймер достиг 10 минут он не меняется
					}
					int minutes = int(gameTime) / 60;
					int seconds = int(gameTime) % 60;


					string timeStr;

					if (minutes < 10) timeStr += "0";
					timeStr += std::to_string(minutes);
					timeStr += ":";
					if (seconds < 10) timeStr += "0";
					timeStr += std::to_string(seconds);

					timerText.setString(timeStr);
					//таймер
				}
				/*if (gameTime >= totalTime)
				{
					//сюда потом можно поместить разные триггеры. Например, появленение неизбежной смерти, кхм...
				}*/
				if (gamePause != 1 && Keyboard::isKeyPressed(Keyboard::M))
				{
					Vector2f spawnPos = getRandomSpawnPosition(positionScreen.x, positionScreen.y);
					Enemy enemy(enemy_image, "data/images/DamageAnim.psd", spawnPos.x, spawnPos.y);
					enemies.emplace_back(enemy);
					//cout << "Number of enemies: " << enemies.size() << endl;
					clock1.restart();
				}
				if (gamePause != 1 && Keyboard::isKeyPressed(Keyboard::N))
				{
					if (enemies.size() != 0)
					{
						enemies.erase(enemies.begin());
						//cout << "Number of enemies: " << enemies.size() << endl;
						clock1.restart();
					}
				}
				if (gamePause != 1)
				{
					for (int i = 0; i < enemies.size();)
					{
						if (!enemies[i].EnemyUpdate(window))
						{
							if (enemies[i].DeathAnimation())
							{
								Hero.addEXP(enemies[i].getEXP());
								EXPBar.Update(window, enemies[i].getEXP());
								enemies.erase(enemies.begin() + i);
								cout << "EXP: " << Hero.getEXP() << endl;
								cout << "Level: " << Hero.Level << " Points: " << Hero.UpgradePoint << endl;
							}
							continue;
						}
						enemies[i].updateDamageAnimation();
						i++;
					}
				}

				if (gamePause != 1)
				{
					if (enemies.size() != 0)
					{
					if (Hero.HaveAbilities[0] && AbilitiesTime[0] >= 1000)
					{
						ability1.attack(Hero.hero_sprite, Hero);
						AbilitiesCooldown[0].restart();
					}
					if (Hero.HaveAbilities[1])
					{
						ability2.attack(Hero.hero_sprite);
						//AbilitiesCooldown[1].restart();
					}
					if (Hero.HaveAbilities[2])
					{
						ability3.update(Hero.hero_sprite, enemies);
					}
					if (Hero.HaveAbilities[3])
					{
						ability4.update(Hero.hero_sprite, enemies);
					}
					}
				}
				else
				{
					for (int i = 0; i < 6; i++)
					{
						AbilitiesCooldown[i].restart();
					}	//может можно сделать как-то иначе, но это будет уловка для пауз-спаммеров))))
				}

				Hero.handleInput(gamePause, deltatime);
				//if (enemies.size() != 0)
				//{
				//	for (iter = enemies.begin(); iter != enemies.end(); iter++)
				//	{
				//		iter->HeroFollow(gamePause, Hero.inheroBounds, Hero.hero_sprite, deltatime, enemies);
				//		iter->DamageDeal(gamePause, Hero, damageInterval, damageClock);
				//		/*iter->EnemyUpdate(window);*/
				//	}
				//}
				updateEnemies(enemies, pool, gamePause, Hero.heroBounds, Hero.hero_sprite, deltatime, Hero, 0.8f, damageClock);
			}
			else
			{
				LoadingTime = LoadingClock.getElapsedTime().asSeconds();
				AnimationLoad = LoadAnimation.getElapsedTime().asMilliseconds();
				if (AnimationLoad >= 250)
				{
					LoadingText.setString(loadText[TextAnim]);
					LoadingSprite.setRotation(RotateScale += 90);
					LoadAnimation.restart();
					TextAnim++;
					if (TextAnim > 2)
						TextAnim = 0;
				}
				//тут будет анимация загрузачки

				if (LoadingTime >= 3)
				{
					LoadingRect.setFillColor(Color(47, 47, 47, LoadingRect.getFillColor().a - 5));
					LoadingSprite.setColor(Color(255, 255, 255, LoadingSprite.getColor().a - 5));
					LoadingText.setFillColor(Color(255, 255, 255, LoadingSprite.getColor().a - 5));
				}
			}
			/*window.clear();
			window.draw(background);
			window.draw(GameName);*/

			//cout << Hero.hero_sprite.getPosition().x << "    ";
			//cout << Hero.hero_sprite.getPosition().y << endl;





			//FloatRect circleBounds = circle1.getGlobalBounds();
			//if (Hero.heroBounds.intersects(circleBounds))
			//	cout << "collision" << endl;

			//СМЕЩЕНИЕ ЭКРАНА ПРИ ХОДЬБЕ



			positionScreen.x = Hero.hero_sprite.getPosition().x + HeroDimensionX - (dimensionScreenX / 2);
			positionScreen.y = Hero.hero_sprite.getPosition().y + HeroDimensionY - (dimensionScreenY / 2);

			// Ограничиваем движение камеры по оси X
			if (positionScreen.x < 0) {
				positionScreen.x = 0; // Камера не может выходить за пределы левой границы
			}
			else if (positionScreen.x > worldWidth - dimensionScreenX) {
				positionScreen.x = worldWidth - dimensionScreenX; // Камера не может выходить за пределы правой границы
			}
			// Ограничиваем движение камеры по оси Y
			if (positionScreen.y < 0) {
				positionScreen.y = 0; // Камера не может выходить за пределы верхней границы
			}
			else if (positionScreen.y > worldHeight - dimensionScreenY) {
				positionScreen.y = worldHeight - dimensionScreenY; // Камера не может выходить за пределы нижней границы
			}



			if (Hero.hero_sprite.getPosition().x <= 0 && Hero.hero_sprite.getPosition().y <= 0) //ограничения, чтобы герой не вышел в отрицательные x и y
				Hero.hero_sprite.setPosition(0, 0);
			if (Hero.hero_sprite.getPosition().x <= 0)
				Hero.hero_sprite.setPosition(0, Hero.hero_sprite.getPosition().y);
			if (Hero.hero_sprite.getPosition().y <= 0)
				Hero.hero_sprite.setPosition(Hero.hero_sprite.getPosition().x, 0);
			if (Hero.hero_sprite.getPosition().x >= worldWidth - 35)
				Hero.hero_sprite.setPosition(worldWidth - 35, Hero.hero_sprite.getPosition().y);
			if (Hero.hero_sprite.getPosition().y >= worldHeight - 50)
				Hero.hero_sprite.setPosition(Hero.hero_sprite.getPosition().x, worldHeight - 50);


			view.reset(FloatRect(positionScreen.x, positionScreen.y, dimensionScreenX, dimensionScreenY));

			if (!gamePause || !UpgradePause)
			{
				ability1.update(window, /*Ability1clock*/ enemies);
				ability2.update(window, /*Ability1clock*/ enemies);
			}

			//window.clear();
			window.setView(view);
			for (unsigned int i = 0; i < tiles.size(); ++i) {
				window.draw(tiles[i]); // Рисуем каждый спрайт по индексу
			}
			//for (iter = enemies.begin(); iter < enemies.end(); ++iter) {
			//	iter->EnemyUpdate(window); // Рисуем каждого вражину по индексу
			//}
			//for (unsigned long int i = 0; i < enemies.size(); ++i) {
			//	enemies[i].EnemyUpdate(window); // Рисуем каждого врага по индексу
			//}
			if (ability1.isActive() && Hero.HaveAbilities[0])
				window.draw(ability1.getSprite());
			if (ability2.isActive() && Hero.HaveAbilities[1])
				window.draw(ability2.getSprite());
			if (enemies.size() != 0 && Hero.HaveAbilities[2])
				ability3.draw(window);
			if (enemies.size() != 0 && Hero.HaveAbilities[3])
				ability4.draw(window);
			for (auto& enemy : enemies)
			{
				enemy.EnemyUpdate(window);
			}
			Hero.HeroDraw(window);
			//----------------ОТОБРАЖЕНИЕ ИНТЕРФЕЙСА-------------------

			window.setView(uiView); // неподвижная камера для UI
			window.draw(timerText);
			//HealthBar.setPosition(50, 50); // позиция фиксированная на экране
			HealthBar.Update(window, Hero.health);
			Abilities.Update(window/*, Hero.HaveAbilities*/, Hero);
			EXPBar.Update(window);
			//HealthBar.setPosition(50, 50);
			if (LoadingRect.getFillColor().a > 0)
			{
				window.draw(LoadingRect);
				window.draw(LoadingSprite);
				window.draw(LoadingText);
			}
			else
			{
				StartGame = true;
				if (MusicNotStarted)
				{
					GameMusic1.play();
					MusicNotStarted = false;
				}
			}
			
			//if (Hero.Upgrade == true)
			//{
			//	gamePause = true;
			//	if (gamePause)
			//	{
			//		while (window.pollEvent(event))
			//		{
			//			if (event.type == Event::Closed)//если событие "закрытие", окно закрывается
			//			{
			//				save(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);
			//				GameMusic1.stop();
			//				window.close();
			//				music.stop();
			//			}

			//			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			//			{
			//				Vector2f worldPos = window.mapPixelToCoords(Mouse::getPosition(window));
			//				if (Ability1Update.getText().getGlobalBounds().contains(worldPos))
			//				{
			//					if (Ability1Update.ButtonUpdate(window, AbilityUpgrade, event))
			//					{
			//						gamePause = false;
			//						Hero.Upgrade = false;
			//					}
			//				}
			//			}

			//		}
			//		Ability1Update.ButtonUpdate(window, AbilityUpgrade, event);
			//	}
			//}
			if (gamePause == true && Hero.UpgradePoint != 0)
			{

			}
			if (gamePause == true && Hero.UpgradePoint == 0)
			{
				/*rect.setTexture(texture);*/
				//Pause.setCoords((dimensionScreenX / 2) - (Pause.getWidth() / 2), (dimensionScreenY / 2) - (Pause.getHeight() / 2));
				window.draw(PauseRect);
				Pause.ButtonUpdate(window);
				MusicPauseText.ButtonUpdate(window);
				MusicPauseText.ButtonUpdate(window);
				SoundPauseText.ButtonUpdate(window);
				MusicPauseSlide.ButtonUpdate(window, event, MusicPausePercent, MusicVolume);
				SoundPauseSlide.ButtonUpdate(window, event, SoundPausePercent, SoundVolume);
				MusicPausePercent.ButtonUpdate(window);
				SoundPausePercent.ButtonUpdate(window);
				QuitToMenu.ButtonUpdate(window);
				while (window.pollEvent(event))
				{
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
					{
						Vector2f worldPos = window.mapPixelToCoords(Mouse::getPosition(window));
						if (QuitToMenu.getText().getGlobalBounds().contains(worldPos))
						{
							QuitWarning = true;
						}
					}
					if (event.type == Event::Closed)//если событие "закрытие", окно закрывается
					{
						save(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);
						window.close();
					}
				}
				if (QuitWarning)
				{
					window.draw(QuitRect);
					WarningText.ButtonUpdate(window);
					WarningText1.ButtonUpdate(window);
					QuitYes.ButtonUpdate(window);
					QuitNo.ButtonUpdate(window);
					if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
					{
						Vector2f worldPos = window.mapPixelToCoords(Mouse::getPosition(window));
						if (QuitYes.getText().getGlobalBounds().contains(worldPos))
						{
							save(MusicVolume, SoundVolume, BestScore, CountOfMoney, Upgrade1Level, Upgrade2Level, Upgrade3Level);
							// сохраняются только базовые значения. 
							// Значения полученной валюты и счёта будут добавляться в другие переменные и после завершения игры нормальным путём 
							// (т.е. смерть/победа) оно будет суммироваться со значением для сохранения
							isMenu = true;
							isIntro = true;
							break;
						}
						if (QuitNo.getText().getGlobalBounds().contains(worldPos))
						{
							QuitWarning = false;
						}
					}
				}
				//MusicSlide.ButtonUpdate(window, event, MusicPercent, MusicVolume);
				music.setVolume((30.f * (float(MusicVolume) / 100)));
				GameMusic1.setVolume((30.f * (float(MusicVolume) / 100)));
				//SoundSlide.ButtonUpdate(window, event, SoundPercent, SoundVolume);
				/*rect.setTextureRect(IntRect(0, 0, texture.getSize().x, texture.getSize().y));
				rect.setPosition((positionScreen.x + dimensionScreenX / 2) - (Pause.getWidth() / 2), (positionScreen.y + dimensionScreenY / 2) - (Pause.getHeight() / 2));
				window.draw(rect);*/
			}
			window.display();

		}
	}
	window.close();
	return 0;
}