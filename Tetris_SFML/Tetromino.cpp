#include "Tetromino.h"

Tetromino::Tetromino(char type)
{
	this->type = type;
	switch (type)
	{
		case 'I':
			minoes.push_back(Mino(0, 3, sf::Color::Red));
			minoes.push_back(Mino(0, 4, sf::Color::Red));
			minoes.push_back(Mino(0, 5, sf::Color::Red));
			minoes.push_back(Mino(0, 6, sf::Color::Red));
			break;

		case 'O':
			minoes.push_back(Mino(0, 4, sf::Color::Blue));
			minoes.push_back(Mino(0, 5, sf::Color::Blue));
			minoes.push_back(Mino(1, 4, sf::Color::Blue));
			minoes.push_back(Mino(1, 5, sf::Color::Blue));
			break;

		case 'T':
			minoes.push_back(Mino(0, 3, sf::Color::Green));
			minoes.push_back(Mino(0, 4, sf::Color::Green));
			minoes.push_back(Mino(0, 5, sf::Color::Green));
			minoes.push_back(Mino(1, 4, sf::Color::Green));
			break;

		case 'L':
			minoes.push_back(Mino(0, 3, sf::Color::Magenta));
			minoes.push_back(Mino(0, 4, sf::Color::Magenta));
			minoes.push_back(Mino(0, 5, sf::Color::Magenta));
			minoes.push_back(Mino(1, 3, sf::Color::Magenta));
			break;

		case 'J':
			minoes.push_back(Mino(0, 3, sf::Color::Yellow));
			minoes.push_back(Mino(0, 4, sf::Color::Yellow));
			minoes.push_back(Mino(0, 5, sf::Color::Yellow));
			minoes.push_back(Mino(1, 5, sf::Color::Yellow));
			break;

		case 'Z':
			minoes.push_back(Mino(0, 3, sf::Color(255, 128, 0)));
			minoes.push_back(Mino(0, 4, sf::Color(255, 128, 0)));
			minoes.push_back(Mino(1, 4, sf::Color(255, 128, 0)));
			minoes.push_back(Mino(1, 5, sf::Color(255, 128, 0)));
			break;

		case 'S':
			minoes.push_back(Mino(0, 4, sf::Color::Cyan));
			minoes.push_back(Mino(0, 5, sf::Color::Cyan));
			minoes.push_back(Mino(1, 3, sf::Color::Cyan));
			minoes.push_back(Mino(1, 4, sf::Color::Cyan));
			break;
	}
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Mino mino : minoes)
	{
		target.draw(mino);
	}
}