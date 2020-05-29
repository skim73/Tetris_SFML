#include "Mino.h"

Mino::Mino(short r, short c, sf::Color color)
{
	texture.loadFromFile("img/mino.png");
	sprite.setTextureRect(sf::IntRect(0, 0, 36, 36));
	sprite.setTexture(texture);
	sprite.setPosition(620.f + r * 36.f, 90.f + c * 36.f);

	sprite.setColor(color);

	point = Point(r, c);
}

void Mino::setColor(sf::Color color)
{
	sprite.setColor(color);
}

void Mino::setPoint(short r, short c)
{
	point.row = r;
	point.col = c;
	sprite.setPosition(584.f + r * 36.f, 54.f + c * 36.f);	// definitely gonna change this
}

void Mino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}