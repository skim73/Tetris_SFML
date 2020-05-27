#pragma once
#include <SFML/Graphics.hpp>

struct Point
{
	short row, col;

	Point() : row(0), col(4) {}
	Point(short r, short c) : row(r), col(c) {}
};

class Mino : public sf::Drawable
{
	sf::Texture texture;
	sf::Sprite sprite;

	Point point;

public:
	Mino(short x, short y, sf::Color color);

	void setColor(sf::Color color);
	void setPoint(short r, short c);

	Point getPoint()
	{
		return point;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};