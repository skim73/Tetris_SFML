#include "Mino.h"

Mino::Mino()
{
	texture.loadFromFile("img/mino.png");
	sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
	sprite.setTexture(texture);
	sprite.setPosition(100.0f, 100.0f);
}

void Mino::setColor(sf::Color color)
{
	sprite.setColor(color);
}