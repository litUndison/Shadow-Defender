#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "Header.h"
class Button
{
private:
	RectangleShape rect;
	Font font;
	Text text;
	string legend;
	FloatRect Textrect;
	int textSize;
	Color rectcolor;
	Color textcolor;
	Clock appearClock;
	int currentAlpha = 0;
	int fadeSpeed = 2;
	bool canclick = false;
public:
	Button(int Recwidth, int Recheight, int PosX, int PosY, const Color& colorshape,
		const Font& Font, const String& Legend, int TextSize, const Color& colortext, int transparent, bool CanClick = false, int Thickness = 0)
	{
		canclick = CanClick;
		rect.setSize(Vector2f(Recwidth, Recheight));
		rectcolor = colorshape;
		rectcolor.a = transparent;
		rect.setFillColor(rectcolor);
		font = Font;
		legend = Legend;
		textSize = TextSize;
		rect.setPosition(PosX, PosY);

		text.setFont(font);
		text.setString(Legend);
		text.setCharacterSize(textSize);
		textcolor = colortext;
		text.setFillColor(textcolor);
		Textrect = text.getLocalBounds(); // нашёл коллизию текста, то есть прямоугольник в котором он находится
		text.setPosition(PosX + ((Recwidth / 2) - (Textrect.width / 2)), PosY + ((Recheight / 2) - (Textrect.height / 2)));
		text.setOutlineThickness(Thickness);                       // Толщина
		text.setOutlineColor(Color(50, 50, 50));

	}
	void ButtonUpdate(RenderWindow& window, Event event = Event())
	{
		window.draw(rect);
		window.draw(text);
		if (canclick)
		{
			Vector2i MousePos = Mouse::getPosition(window);
			ContainsCheck(window, MousePos, event); // вызываем только если передано
		}
	}
	void ContainsCheck(RenderWindow& window, Vector2i MousePos, Event event)
	{
		Vector2f worldPos = window.mapPixelToCoords(MousePos);
		if (text.getGlobalBounds().contains(worldPos))
		{
			// Мышка навелась на кнопку
			text.setOutlineColor(sf::Color(200, 200, 200));
		}
		else
		{
			text.setOutlineColor(Color(50, 50, 50));
		}
		//if (event.type == sf::Event::MouseButtonPressed &&
		//	event.mouseButton.button == sf::Mouse::Left)
		//{
		//	sf::Vector2i mousePos = sf::Mouse::getPosition(window); // позиция мыши в окне
		//	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos); // преобразование в координаты мира

		//	if (rect.getGlobalBounds().contains(worldPos)) {
		//		// Кнопка нажата
		//		cout << "Кнопка нажата!" << std::endl;
		//		// тут можно вызвать нужную функцию
		//	}
		//}
	}
	void setTextColor(const Color& colortext)
	{
		textcolor = colortext;
		text.setFillColor(textcolor);
	}
	void setOutlineColor(const Color& color)
	{
		text.setOutlineColor(color);
	}
	void setCoords(int X, int Y)
	{
		rect.setPosition(X, Y);
		text.setPosition(X + ((rect.getLocalBounds().width / 2) - (Textrect.width / 2)), Y + ((rect.getLocalBounds().height / 2) - (Textrect.height / 2)));
	}
	Text getText()
	{
		return text;
	}
	int getWidth()
	{
		return rect.getLocalBounds().width;
	}
	int getHeight()
	{
		return rect.getLocalBounds().height;
	}
	void setText(string Text)
	{
		text.setString(Text);

	}
	RectangleShape getRect()
	{
		return rect;
	}
	FloatRect getTextRect()
	{
		return Textrect;
	}
	void TextAppears(RenderWindow& window) // плавное появление текста можно сделать int, чтобы когда возвращало 1 значило что текст появился и можно отображать другие кнопки
	{
		if (currentAlpha < 255)
		{
			currentAlpha += fadeSpeed;
			if (currentAlpha > 255)
				currentAlpha = 255;
			text.setOutlineColor(sf::Color(0, 0, 0, currentAlpha));    // Белый контур
			sf::Color color = text.getFillColor();
			color.a = currentAlpha;
			text.setFillColor(color);
		}

		window.draw(rect);
		window.draw(text);
	}
	~Button()
	{
	}
};

class MainMenu
{
private:
	RectangleShape rect;
	Texture texture;
public:
	MainMenu(Texture Texture = Texture())
	{
		texture = Texture;
		rect.setSize(Vector2f(1920, 1080));
		rect.setTexture(&Texture);
		rect.setPosition(0, 0);
	}
	void setColor(Color color)
	{
		rect.setFillColor(color);
		return;
	}
	void setPos(int x, int y)
	{
		rect.setPosition(x, y);
		return;
	}
	void MenuDraw(RenderWindow& window)
	{
		rect.setTexture(&texture);
		window.draw(rect); // Рисуем меню
	}
	~MainMenu()
	{
	}
};
class MovingRectangleShape
{

};
class Intro
{
private:
	Font font;
	Text text;
	string legend;
	FloatRect Textrect;
	int textSize;
	Color rectcolor;
	Color textcolor;
	Clock appearClock;
	int currentAlpha = 255;
	int fadeSpeed = 1;
	bool canclick = false;
	float scale = 1.0f;
	float targetScale = 1.1f;
	float speed = 0.0005f; // скорость увеличения
public:
	RectangleShape rect;
	Intro(int Recwidth, int Recheight, int PosX, int PosY, const Color& colorshape,
		const Font& Font, const String& Legend, int TextSize, const Color& colortext, int transparent, bool CanClick = false, int Thickness = 0)
	{
		canclick = CanClick;
		rect.setSize(Vector2f(Recwidth, Recheight));
		rectcolor = colorshape;
		rectcolor.a = transparent;
		rect.setFillColor(rectcolor);
		font = Font;
		legend = Legend;
		textSize = TextSize;
		rect.setPosition(PosX, PosY);

		text.setFont(font);
		text.setString(Legend);
		text.setCharacterSize(textSize);
		textcolor = colortext;
		text.setFillColor(textcolor);
		Textrect = text.getLocalBounds(); // нашёл коллизию текста, то есть прямоугольник в котором он находится
		text.setPosition(PosX + ((Recwidth / 2) - (Textrect.width / 2)), 800);
		text.setOutlineThickness(Thickness);                       // Толщина
		text.setOutlineColor(Color(0, 0, 0));

	}
	void ButtonUpdate(RenderWindow& window, Event event = Event())
	{
		window.draw(rect);
		window.draw(text);
	}
	void TextAnimation(RenderWindow& window, bool& isIntro)
	{
		text.setOrigin(Textrect.left + (Textrect.width / 2.0f), Textrect.top + (Textrect.height / 2.0f));
		text.setPosition(960, 833);
		currentAlpha -= fadeSpeed;
		if (scale < targetScale)
		{
			text.setOutlineColor(sf::Color(0, 0, 0, currentAlpha));    // Белый контур
			sf::Color color = text.getFillColor();
			color.a = currentAlpha;
			text.setFillColor(color);
			if (currentAlpha <= 0)
			{
				currentAlpha = 0;
				isIntro = false;
				return;
			}
			scale += speed; // deltaTime = время между кадрами
			if (scale >= targetScale)
			{
				scale = targetScale;
				isIntro = false;
				return;
			}

			text.setScale(scale, scale);
		}
		window.draw(text);

	}
};
class PopUpMenu
{
private:
	RectangleShape rect;
	Texture texture;
	int moving = 1920;
	int speed = 30;
public:
	bool MovingLeft = true;
	PopUpMenu(int SizeX, int SizeY)
	{
		rect.setSize(Vector2f(SizeX, SizeY));
		rect.setPosition(1920, 0);
		rect.setFillColor(Color(100, 100, 100, 200));
	}
	void setColor(const Color& color)
	{
		rect.setFillColor(color);
		return;
	}
	void setPos(int x, int y)
	{
		rect.setPosition(x, y);
		return;
	}
	Vector2f getPos()
	{
		return rect.getPosition();
	}
	void MenuDraw(RenderWindow& window)
	{
		/*rect.setTexture(&texture);*/
		window.draw(rect); // Рисуем меню
	}
	void Animation(bool& isAnimation, Button& Any)
	{
		if (MovingLeft == true)
		{
			rect.move(-speed, 0);
			moving -= speed;
			Any.setTextColor(Color(150, 150, 150));
			if (rect.getPosition().x <= 330)
				MovingLeft = false;
		}
		else if (MovingLeft == false)
		{
			if (rect.getPosition().x != 330)
			{
				Any.setTextColor(Color(139, 0, 0));
			}
			rect.move(speed, 0);
			moving += speed;
			if (rect.getPosition().x >= 1920)
				MovingLeft = true;
		}
		if (moving >= 1920 || moving <= 330)
			isAnimation = false;
		return;
	}
	~PopUpMenu()
	{
	}
};

class PopUpButton
{
private:
	RectangleShape rect;
	Font font;
	Text text;
	string legend;
	FloatRect Textrect;
	int textSize;
	Color rectcolor;
	Color textcolor;
	Clock appearClock;
	Color OutlineColor = Color(50,50,50);
	int currentAlpha = 0;
	int fadeSpeed = 2;
	bool canclick = false;
public:
	PopUpButton(int Recwidth, int Recheight, int PosX, int PosY, const Color& colorshape,
		const Font& Font, const String& Legend, int TextSize, const Color& colortext, int transparent, bool CanClick = false, int Thickness = 0)
	{
		canclick = CanClick;
		rect.setSize(Vector2f(Recwidth, Recheight));
		rectcolor = colorshape;
		rectcolor.a = transparent;
		rect.setFillColor(rectcolor);
		font = Font;
		legend = Legend;
		textSize = TextSize;
		rect.setPosition(PosX, PosY);

		text.setFont(font);
		text.setString(Legend);
		text.setCharacterSize(textSize);
		textcolor = colortext;
		text.setFillColor(textcolor);
		Textrect = text.getLocalBounds(); // нашёл коллизию текста, то есть прямоугольник в котором он находится
		text.setPosition(PosX + ((Recwidth / 2) - (Textrect.width / 2)), PosY + ((Recheight / 2) - (Textrect.height / 2)));
		text.setOutlineThickness(Thickness);                       // Толщина
		text.setOutlineColor(Color(50, 50, 50));

	}
	void ButtonUpdate(RenderWindow& window, Event event = Event())
	{
		window.draw(rect);
		window.draw(text);
		if (canclick)
		{
			Vector2i MousePos = Mouse::getPosition(window);
			ContainsCheck(window, MousePos, event); // вызываем только если передано
		}
	}
	void ContainsCheck(RenderWindow& window, Vector2i MousePos, Event event)
	{
		Vector2f worldPos = window.mapPixelToCoords(MousePos);
		if (text.getGlobalBounds().contains(worldPos))
			// Мышка навелась на кнопку
			text.setOutlineColor(sf::Color(200, 200, 200));
		else
			text.setOutlineColor(OutlineColor);
		//if (event.type == sf::Event::MouseButtonPressed &&
		//	event.mouseButton.button == sf::Mouse::Left)
		//{
		//	Vector2i mousePos = sf::Mouse::getPosition(window); // позиция мыши в окне
		//	Vector2f worldPos = window.mapPixelToCoords(mousePos); // преобразование в координаты мира

		//	if (rect.getGlobalBounds().contains(worldPos)) {
		//		cout << "Кнопка нажата!" << std::endl;
		//		return 1;
		//	}
		//	else
		//		return 0;
		//}
	}
	Color getTextColor()
	{
		return text.getFillColor();
	}
	void setTextColor(const Color& colortext)
	{
		textcolor = colortext;
		text.setFillColor(textcolor);
	}
	void setOutlineColor(const Color& color)
	{
		OutlineColor = color;
		text.setOutlineColor(color);
	}
	void setCoords(int X, int Y)
	{
		rect.setPosition(X, Y);
		text.setPosition(X + ((rect.getLocalBounds().width / 2) - (Textrect.width / 2)), Y + ((rect.getLocalBounds().height / 2) - (Textrect.height / 2)));
	}
	Text getText()
	{
		return text;
	}
	void setText(const String& newtext)
	{
		legend = newtext;
		text.setString(newtext);
	}
	int getWidth()
	{
		return rect.getLocalBounds().width;
	}
	int getHeight()
	{
		return rect.getLocalBounds().height;
	}
	RectangleShape getRect()
	{
		return rect;
	}
	FloatRect getTextRect()
	{
		return Textrect;
	}
	void TextAppears(RenderWindow& window) // плавное появление текста можно сделать int, чтобы когда возвращало 1 значило что текст появился и можно отображать другие кнопки
	{
		if (currentAlpha < 255)
		{
			currentAlpha += fadeSpeed;
			if (currentAlpha > 255)
				currentAlpha = 255;
			text.setOutlineColor(sf::Color(0, 0, 0, currentAlpha));    // Белый контур
			sf::Color color = text.getFillColor();
			color.a = currentAlpha;
			text.setFillColor(color);
		}

		window.draw(rect);
		window.draw(text);
	}
	~PopUpButton()
	{
	}
};
class SoundSlider
{
private:
	RectangleShape BackGroundrect;
	RectangleShape Sliderect;
	int percent;
public:
	SoundSlider(int PosX, int PosY, int SizeX, int SizeY, int Percent = 100)
	{
		percent = Percent;
		BackGroundrect.setSize(Vector2f(SizeX, SizeY));
		Sliderect.setSize(Vector2f(Percent * (BackGroundrect.getSize().x - 10) / 100, SizeY - 10));
		BackGroundrect.setPosition(PosX, PosY);
		Sliderect.setPosition(PosX + 5, PosY + 5);
		BackGroundrect.setFillColor(Color(50, 50, 50, 255));
		Sliderect.setFillColor(Color(140, 30, 30, 255));
	}
	void ButtonUpdate(RenderWindow& window, Event& event, PopUpButton& TextPercent, int& percent)
	{
		window.draw(BackGroundrect);
		window.draw(Sliderect);
		Vector2i MousePos = Mouse::getPosition(window);
		ContainsCheck(window, MousePos, event, TextPercent, percent);
	}
	void ContainsCheck(RenderWindow& window, Vector2i& MousePos, Event event, PopUpButton& TextPercent, int& percent)
	{
		Vector2f worldPos = window.mapPixelToCoords(MousePos);
		if (BackGroundrect.getGlobalBounds().contains(worldPos))
		{
			// Мышка навелась на кнопку
			Sliderect.setFillColor(sf::Color(200, 200, 200));
		}
		else
		{
			Sliderect.setFillColor(Color(160, 100, 100));
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (BackGroundrect.getGlobalBounds().contains(worldPos))
			{
				if (worldPos.x <= (BackGroundrect.getPosition().x + 5))
					Sliderect.setSize(Vector2f(0, BackGroundrect.getSize().y - 10));
				else if (worldPos.x >= (BackGroundrect.getPosition().x + BackGroundrect.getSize().x - 5))
					Sliderect.setSize(Vector2f(BackGroundrect.getSize().x - 10, BackGroundrect.getSize().y - 10));
				else
				{
					Sliderect.setSize(Vector2f(worldPos.x - (BackGroundrect.getPosition().x + 5), BackGroundrect.getSize().y - 10));
				}
				Sliderect.setPosition(BackGroundrect.getPosition().x + 5, BackGroundrect.getPosition().y + 5);
				percent = Sliderect.getSize().x / (BackGroundrect.getSize().x - 10) * 100;
				string Percent = to_string(percent);
				//percent.append("%");
				String sfString(Percent.c_str());
				TextPercent.setText(sfString);
			}
		}
	}
	String getPercent()
	{
		return to_string(percent);
	}
	~SoundSlider()
	{

	}
};
class AbilityButton
{
private:

	RectangleShape rect;
	RectangleShape Iconrect;
	RectangleShape Iconrect2;

	RectangleShape levelBg;
	RectangleShape level1;
	RectangleShape level2;
	RectangleShape level3;

	Font font;
	Text AbilityNameText;
	Text text;

	int prise;
	Text PriseText;
	string legend;
	FloatRect Textrect;
	int textSize;
	Color rectcolor;
	Color textcolor;

	Image abilityImage;
	Texture abilityTexture;
	Sprite abilitySprite;

	Image FrameImage;
	Texture FrameTexture;
	Sprite FrameSprite;

	float delttime = 0;
	int upgradeLevel; //0, 1, 2. Степень прокачки будет показываться делениями

	bool canclick = false;
public:
	AbilityButton(int Recwidth, int Recheight, int PosX, int PosY, const Color& colorshape,
		const Font& Font, const String& Legend, int TextSize, const Color& colortext, Image& AbilityImg, Image& Frame/*РАмка*/, bool CanClick = true, int Thickness = 0, int UpgradeLevel = 0, int Prise = 25)
	{
		upgradeLevel = UpgradeLevel;
		if (Prise != 100)
		{
			prise = Prise;
			PriseText.setString(to_string(prise));
		}
		else
			PriseText.setString("MAX");
		PriseText.setFillColor(Color(150, 150, 0));
		PriseText.setFont(font);
		PriseText.setCharacterSize(50);
		PriseText.setOutlineThickness(2);

		abilityImage = AbilityImg;
		abilityTexture.loadFromImage(abilityImage);
		abilitySprite.setTexture(abilityTexture);
		abilitySprite.setScale(sf::Vector2f(150 / abilityTexture.getSize().x, 150 / abilityTexture.getSize().y));

		FrameImage = Frame;
		FrameTexture.loadFromImage(FrameImage);
		FrameSprite.setTexture(FrameTexture);

		text.setString(L"Улучшить");
		canclick = CanClick;
		rect.setSize(Vector2f(Recwidth, Recheight));
		FrameSprite.setScale(float(Recwidth) / FrameTexture.getSize().x, float(Recheight) / FrameTexture.getSize().y);

		Iconrect.setSize(Vector2f(600 * 0.2 + 40, 600 * 0.2 + 40));
		Iconrect2.setSize(Vector2f(600 * 0.2 + 30, 600 * 0.2 + 30));

		rectcolor = colorshape;
		//rectcolor.a = transparent;
		rect.setFillColor(rectcolor);
		Iconrect.setFillColor(Color(50, 50, 50));
		Iconrect2.setFillColor(Color(235, 210, 170));
		font = Font;
		legend = Legend;
		textSize = TextSize;
		rect.setPosition(PosX, PosY);
		FrameSprite.setPosition(PosX, PosY);

		text.setFont(font);
		AbilityNameText.setFont(font);
		AbilityNameText.setString(Legend);
		text.setCharacterSize(textSize);
		AbilityNameText.setCharacterSize(textSize);
		textcolor = colortext;
		text.setFillColor(Color(176, 139, 25));
		AbilityNameText.setFillColor(textcolor);
		Textrect = text.getLocalBounds(); // нашёл коллизию текста, то есть прямоугольник в котором он находится
		AbilityNameText.setPosition(PosX + ((Recwidth / 2) - (AbilityNameText.getLocalBounds().width / 2)), PosY + 30);
		Iconrect.setPosition(PosX + ((Recwidth / 2) - (Iconrect.getSize().x / 2)), PosY + ((Recheight / 2.5) - (Iconrect.getSize().y / 2)) + 25);
		Iconrect2.setPosition(PosX + ((Recwidth / 2) - (Iconrect2.getSize().x / 2)), PosY + ((Recheight / 2.5) - (Iconrect2.getSize().y / 2)) + 25);
		abilitySprite.setPosition(Iconrect2.getPosition().x + Iconrect2.getSize().x / 2 - abilityTexture.getSize().x / 2, Iconrect2.getPosition().y + Iconrect2.getSize().y / 2 - abilityTexture.getSize().y / 2);
		text.setPosition(PosX + ((Recwidth / 2) - (Textrect.width / 2)), PosY + Recheight - 110);
		text.setOutlineThickness(Thickness);                       // Толщина
		AbilityNameText.setOutlineThickness(Thickness);
		text.setOutlineColor(Color(50, 50, 50));
		AbilityNameText.setOutlineColor(Color(20, 20, 20));


		PriseText.setPosition(PosX + ((Recwidth / 2) - (PriseText.getLocalBounds().width / 2)), PosY - 50);


		levelBg.setFillColor(Color(30, 30, 30));
		levelBg.setSize(Vector2f(Iconrect.getSize().x, 30));
		levelBg.setPosition(Iconrect.getPosition().x, Iconrect.getPosition().y + Iconrect.getSize().y + 5);

		level1.setFillColor(Color(201, 173, 32));
		level1.setSize(Vector2f((levelBg.getSize().x - 20) / 3, 20));
		level1.setPosition(levelBg.getPosition().x + 5, levelBg.getPosition().y + 5);

		level2.setFillColor(Color(201, 173, 32));
		level2.setSize(Vector2f((levelBg.getSize().x - 20) / 3, 20));
		level2.setPosition(levelBg.getPosition().x + level1.getSize().x + 10, levelBg.getPosition().y + 5);

		level3.setFillColor(Color(201, 173, 32));
		level3.setSize(Vector2f((levelBg.getSize().x - 20) / 3, 20));
		level3.setPosition(levelBg.getPosition().x + level1.getSize().x + level2.getSize().x + 15, levelBg.getPosition().y + 5);
	}
	int ButtonUpdate(RenderWindow& window, Clock& UpgradeClock, Event event = Event(), int CountOfMoney = 0)
	{
		delttime = UpgradeClock.getElapsedTime().asMilliseconds();
		window.draw(rect);
		window.draw(Iconrect);
		window.draw(Iconrect2);
		window.draw(text);
		window.draw(AbilityNameText);
		window.draw(abilitySprite);
		window.draw(FrameSprite);
		window.draw(levelBg);
		window.draw(PriseText);

		switch (upgradeLevel)
		{
		case 0:
			break;
		case 1:
		{
			window.draw(level1);
			break;
		}
		case 2:
		{
			window.draw(level1);
			window.draw(level2);
			break;
		}
		case 3:
			window.draw(level1);
			window.draw(level2);
			window.draw(level3);
			break;
		}// в будущем сделать функцию возвращающую уровень навыка, чтобы персонажа усилить

		if (canclick)
		{
			Vector2i MousePos = Mouse::getPosition(window);
			return ContainsCheck(window, MousePos, event, UpgradeClock, CountOfMoney); // вызываем только если передано
		}
	}
	int ContainsCheck(RenderWindow& window, Vector2i MousePos, Event event, Clock& UpgradeClock, int CountOfMoney)
	{
		Vector2f worldPos = window.mapPixelToCoords(MousePos);
		if (text.getGlobalBounds().contains(worldPos))
			// Мышка навелась на кнопку
			text.setOutlineColor(sf::Color(200, 200, 200));
		else
			text.setOutlineColor(Color(50, 50, 50));
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			Vector2i mousePos = sf::Mouse::getPosition(window); // позиция мыши в окне
			Vector2f worldPos = window.mapPixelToCoords(mousePos); // преобразование в координаты мира

			if (rect.getGlobalBounds().contains(worldPos) && delttime > 200)
			{
				UpgradeClock.restart();
				if (CountOfMoney >= prise)
				{
					if (upgradeLevel < 3)
					{
						upgradeLevel++;
						prise = 25 + 25 * upgradeLevel;
						PriseText.setString(to_string(prise));
					}
					if (upgradeLevel == 3)
						PriseText.setString("MAX");

					return 1;
				}
				return 0;
			}
			else
			{
				return 0;
			}
		}
	}
	Color getTextColor()
	{
		return text.getFillColor();
	}
	void setTextColor(const Color& colortext)
	{
		textcolor = colortext;
		text.setFillColor(textcolor);
	}
	void setOutlineColor(const Color& color)
	{
		text.setOutlineColor(color);
	}
	void setCoords(int X, int Y)
	{
		rect.setPosition(X, Y);
		text.setPosition(X + ((rect.getLocalBounds().width / 2) - (Textrect.width / 2)), Y + ((rect.getLocalBounds().height / 2) - (Textrect.height / 2)));
	}
	Text getText()
	{
		return text;
	}
	void setText(const String& newtext)
	{
		legend = newtext;
		text.setString(newtext);
	}
	int getWidth()
	{
		return rect.getLocalBounds().width;
	}
	int getHeight()
	{
		return rect.getLocalBounds().height;
	}
	RectangleShape getRect()
	{
		return rect;
	}
	FloatRect getTextRect()
	{
		return Textrect;
	}
	~AbilityButton()
	{
	}
};
#endif //GAMEMENU_H