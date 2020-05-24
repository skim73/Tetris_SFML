#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Options
{
	sf::RectangleShape rectangle;
	sf::Font square721bt;

	sf::Text musicVolText;
	sf::RectangleShape musicSlider;
	sf::Text sfxVolText;
	sf::RectangleShape sfxSlider;
	sf::Text backText;

	short cursor;

public:
	Options();

	void moveCursorUp();
	void moveCursorDown();
	void moveSliderLeft(sf::Music& music, sf::Sound& sfx);
	void moveSliderRight(sf::Music& music, sf::Sound& sfx);

	sf::RectangleShape& getRectangle()
	{
		return rectangle;
	}
	sf::Text& getMusicVolText()
	{
		return musicVolText;
	}
	sf::RectangleShape& getMusicSlider()
	{
		return musicSlider;
	}
	sf::Text& getSFXVolText()
	{
		return sfxVolText;
	}
	sf::RectangleShape& getSFXSlider()
	{
		return sfxSlider;
	}
	sf::Text& getBackText()
	{
		return backText;
	}
	short getCursor()
	{
		return cursor;
	}
};