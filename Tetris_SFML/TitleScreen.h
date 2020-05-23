#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class TitleScreen
{
	sf::Texture background;
	std::string bgmFile;

	sf::Font square721, square721extended;

	sf::RectangleShape menuRect;
	std::vector<sf::Text> menuItems;

	short menuCursor;
	short levelCursor;

	sf::RectangleShape loadingRect;
	sf::Text loadingText;
	
public:
	TitleScreen();

	void moveCursorUp();
	void moveCursorDown();
	void changeLevelUp();
	void changeLevelDown();

	sf::Texture* getBackground()
	{
		return &background;
	}

	std::string& getMusic()
	{
		return bgmFile;
	}

	sf::RectangleShape& getMenuRect()
	{
		return menuRect;
	}

	std::vector<sf::Text> getMenuItems()
	{
		return menuItems;
	}

	short getMenuCursor()
	{
		return menuCursor;
	}

	sf::RectangleShape& getLoadingRect()
	{
		return loadingRect;
	}

	sf::Text& getLoadingText()
	{
		return loadingText;
	}
};