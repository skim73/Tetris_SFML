#pragma once
#include "GUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class TitleScreen : public GUI
{
	sf::Texture background;
	sf::RectangleShape backgroundRect;

	std::string bgmFile;

	sf::Font square721, square721extended;

	sf::RectangleShape menuRect;
	std::vector<sf::Text> menuItems;

	short menuCursor;
	short levelCursor;
	
public:
	TitleScreen();

	void upPressed() override;
	short downPressed() override;
	void leftPressed() override;
	void rightPressed() override;
	short enterPressed() override;

	std::string& getMusic()
	{
		return bgmFile;
	}

	short getLevelCursor()
	{
		return levelCursor;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};