#include "Mino.h"

Mino::Mino(short x, short y, sf::Color color)
{
	texture.loadFromFile("img/mino.png");
	sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
	sprite.setTexture(texture);
	sprite.setPosition(300.f + x * 30.f, 300.f + y * 30.f);

	sprite.setColor(color);

	point = Point(x, y);
}

void Mino::setColor(sf::Color color)
{
	sprite.setColor(color);
}

void Mino::setPoint(short r, short c)
{
	point.row = r;
	point.col = c;
	sprite.setPosition(300.f + r * 30.f, 300.f + c * 30.f);	// definitely gonna change this
}

void Mino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}