#include "TitleScreen.h"
#include <cstdio>

TitleScreen::TitleScreen()
{
	background.loadFromFile("img/backgrounds/title.png");
	bgmFile = "music/Tetris X BGM 01 (Technotris).ogg";

	square721.loadFromFile("Square-721-BT.ttf");
	square721extended.loadFromFile("Square-721-Extended-BT.ttf");

	menuCursor = 0;
	levelCursor = 0;

	menuRect.setSize(sf::Vector2f(680.0f, 310.0f));
	menuRect.setFillColor(sf::Color(0, 0, 0, 155));
	menuRect.setPosition(440.0f, 380.0f);
	menuItems.push_back(sf::Text("START : at level 0", square721extended, 50));
	menuItems.push_back(sf::Text("OPTIONS", square721extended, 50));
	menuItems.push_back(sf::Text("HIGH SCORES", square721extended, 50));

	for (int i = 0; i < 3; ++i)
	{
		menuItems[i].setFillColor(i ? sf::Color::White : sf::Color::Cyan);
		menuItems[i].setStyle(sf::Text::Bold);
		menuItems[i].setOutlineThickness(2);
		menuItems[i].setOutlineColor(sf::Color::Black);
		menuItems[i].setPosition(450.0f, 400.0f + i*100);
	}

	loadingRect.setSize(sf::Vector2f(800.0f, 100.0f));
	loadingRect.setFillColor(sf::Color(0, 0, 0, 155));
	loadingRect.setPosition(400.0f, 450.0f);
	loadingText.setFont(square721extended);
	loadingText.setString("Loading le Tetris game");
	loadingText.setPosition(510.0f, 475.0f);
	loadingText.setCharacterSize(40.0f);
}

void TitleScreen::moveCursorUp()
{
	if (--menuCursor < 0) 
		menuCursor = 0;
	else
	{
		menuItems[menuCursor + 1].setFillColor(sf::Color::White);
		menuItems[menuCursor].setFillColor(sf::Color::Cyan);
	}
}

void TitleScreen::moveCursorDown()
{
	if (++menuCursor > 2)
		menuCursor = 2;
	else
	{
		menuItems[menuCursor - 1].setFillColor(sf::Color::White);
		menuItems[menuCursor].setFillColor(sf::Color::Cyan);
	}
}

void TitleScreen::changeLevelUp()
{
	if (menuCursor)
		return;
	if (++levelCursor > 30)
		levelCursor = 30;
	menuItems[0].setString("START : at level " + std::to_string(levelCursor));
}

void TitleScreen::changeLevelDown()
{
	if (menuCursor)
		return;
	if (--levelCursor < 0)
		levelCursor = 0;
	menuItems[0].setString("START : at level " + std::to_string(levelCursor));
}