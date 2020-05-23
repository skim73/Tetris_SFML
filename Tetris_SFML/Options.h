#pragma once
#include <SFML/Graphics.hpp>

class Options
{
	sf::RectangleShape rectangle;
	sf::Text musicVolText;
	sf::Text sfxVolText;
	sf::Text backText;

	sf::RectangleShape& getRectangle()
	{
		return rectangle;
	}
	sf::Text& getMusicVolText()
	{
		return musicVolText;
	}
	sf::Text& getSFXVolText()
	{
		return sfxVolText;
	}
	sf::Text& getBackText()
	{
		return backText;
	}
};