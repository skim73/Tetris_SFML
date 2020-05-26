#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
	background.loadFromFile("img/backgrounds/title.png");
	backgroundRect.setSize(sf::Vector2f(1600.f, 900.f));
	backgroundRect.setTexture(&background);

	bgmFile = "music/Tetris X BGM 01 (Technotris).ogg";

	square721.loadFromFile("Square-721-BT.ttf");
	square721extended.loadFromFile("Square-721-Extended-BT.ttf");

	menuCursor = 0;
	levelCursor = 0;

	menuRect.setSize(sf::Vector2f(720.0f, 310.0f));
	menuRect.setFillColor(sf::Color(0, 0, 0, 155));
	menuRect.setPosition(440.0f, 380.0f);
	menuItems.push_back(sf::Text("START : at level 0", square721extended, 50));
	menuItems.push_back(sf::Text("OPTIONS", square721extended, 50));
	menuItems.push_back(sf::Text("HIGH SCORES", square721extended, 50));

	drawableComponents.push_back(&backgroundRect);
	drawableComponents.push_back(&menuRect);

	for (int i = 0; i < 3; ++i)
	{
		menuItems[i].setFillColor(i ? sf::Color::White : sf::Color::Cyan);
		menuItems[i].setStyle(sf::Text::Bold);
		menuItems[i].setOutlineThickness(2);
		menuItems[i].setOutlineColor(sf::Color::Black);
		menuItems[i].setPosition(450.0f, 400.0f + i*100);
		drawableComponents.push_back(&menuItems[i]);
	}
}

void TitleScreen::upPressed()
{
	if (--menuCursor < 0) 
		menuCursor = 0;
	else
	{
		menuItems[menuCursor + 1].setFillColor(sf::Color::White);
		menuItems[menuCursor].setFillColor(sf::Color::Cyan);
	}
}

void TitleScreen::downPressed()
{
	if (++menuCursor > 2)
		menuCursor = 2;
	else
	{
		menuItems[menuCursor - 1].setFillColor(sf::Color::White);
		menuItems[menuCursor].setFillColor(sf::Color::Cyan);
	}
}

void TitleScreen::rightPressed()
{
	if (menuCursor)
		return;
	if (++levelCursor > 30)
		levelCursor = 30;
	menuItems[0].setString("START : at level " + std::to_string(levelCursor));
}

void TitleScreen::leftPressed()
{
	if (menuCursor)
		return;
	if (--levelCursor < 0)
		levelCursor = 0;
	menuItems[0].setString("START : at level " + std::to_string(levelCursor));
}

short TitleScreen::enterPressed()
{
	return menuCursor;
}

void TitleScreen::escPressed()
{
	return;
}

void TitleScreen::zPressed()
{
	return;
}

void TitleScreen::xPressed()
{
	return;
}