#pragma once
#include <SFML/Graphics.hpp>

struct Point
{
	short row, col;
	Point() : row(0), col(0) {}
	Point(short r, short c) : row(r), col(c) {}

	Point operator+ (Point other)
	{
		return Point(this->row + other.row, this->col + other.col);
	}
	Point operator- (Point other)
	{
		return Point(this->row - other.row, this->col - other.col);
	}
};

class Mino : public sf::Drawable
{
	sf::Texture texture;
	sf::Sprite sprite;

	Point point;

public:
	Mino(short r, short c, sf::Color color);
	~Mino();

	void setColor(sf::Color color);
	void setPoint(short r, short c);
	void setPositionAt(Point p);

	Point getPoint()
	{
		return point;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};