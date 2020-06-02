#pragma once
#include <vector>
#include "Mino.h"

class Tetromino : public sf::Drawable
{
	std::vector<Mino*> minoes;
	char type;
	bool rotation;
	Point location;

public:
	Tetromino();
	Tetromino(char type);

	std::vector<Mino*>& getMinoes()
	{
		return minoes;
	}

	Point getLocation()
	{
		return location;
	}

	void moveLeft(short x);
	void moveRight(short x);
	void moveDown(short y);
	void rotateLeft();
	void rotateRight();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};