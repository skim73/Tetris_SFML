#pragma once
#include <vector>
#include "Mino.h"

class Tetromino : public sf::Drawable
{
	std::vector<Mino*> minoes;
	char type;
	bool rotation;

public:
	Tetromino(char type);

	std::vector<Mino*>& getMinoes()
	{
		return minoes;
	}

	void moveLeft(short x);
	void moveRight(short x);
	void moveDown(short y);
	void resetPosition();
	void rotateLeft();
	void rotateRight();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};