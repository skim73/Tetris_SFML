#pragma once
#include <vector>
#include "Mino.h"

class Tetromino : public sf::Drawable
{
	std::vector<Mino> minoes;
	char type;

public:
	Tetromino(char type);

	std::vector<Mino>& getMinoes()
	{
		return minoes;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
