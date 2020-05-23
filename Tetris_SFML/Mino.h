#pragma once
#include <SFML/Graphics.hpp>

class Mino
{
	sf::Texture texture;
	sf::Sprite sprite;

public:
	Mino();
	void setColor(sf::Color color);

	sf::Sprite& getSprite()
	{
		return sprite;
	}
};