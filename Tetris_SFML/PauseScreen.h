#pragma once
#include "GUI.h"
#include <SFML/Graphics.hpp>

class PauseScreen : public GUI
{
	sf::RectangleShape pauseRect;
	sf::Texture image;
	sf::Text text;
	sf::Font square721bt;

public:
	PauseScreen();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};