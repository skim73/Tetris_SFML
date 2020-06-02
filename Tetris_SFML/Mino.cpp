#include "Mino.h"

Mino::Mino(short r, short c, sf::Color color)
{
	texture.loadFromFile("img/mino.png");
	sprite.setTextureRect(sf::IntRect(0, 0, 36, 36));
	sprite.setTexture(texture);
	sprite.setPosition(620.f + c * 36.f, 90.f + r * 36.f);

	sprite.setColor(color);

	point = Point(r, c);
}

Mino::~Mino()
{
	sprite.setColor(sf::Color::Transparent);
}

void Mino::setColor(sf::Color color)
{
	sprite.setColor(color);
}

void Mino::setPoint(short r, short c)
{
	point.row = r;
	point.col = c;
}

void Mino::setPositionAt(Point p)
{
	sprite.setPosition(620.f + p.col * 36.f, 90.f + p.row * 36.f);
}

void Mino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}