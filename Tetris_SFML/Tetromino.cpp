#include "Tetromino.h"

Tetromino::Tetromino(char type)
{
	rotation = 0;
	this->type = type;
	switch (type)
	{
		case 'L':
			minoes.push_back(new Mino(0, 0, sf::Color::Magenta));
			minoes.push_back(new Mino(0, -1, sf::Color::Magenta));
			minoes.push_back(new Mino(0, 1, sf::Color::Magenta));
			minoes.push_back(new Mino(1, -1, sf::Color::Magenta));
			break;
		case 'J':
			minoes.push_back(new Mino(0, 0, sf::Color::Yellow));
			minoes.push_back(new Mino(0, -1, sf::Color::Yellow));
			minoes.push_back(new Mino(0, 1, sf::Color::Yellow));
			minoes.push_back(new Mino(1, 1, sf::Color::Yellow));
			break;
		case 'T':
			minoes.push_back(new Mino(0, 0, sf::Color::Green));
			minoes.push_back(new Mino(0, -1, sf::Color::Green));
			minoes.push_back(new Mino(0, 1, sf::Color::Green));
			minoes.push_back(new Mino(1, 0, sf::Color::Green));
			break;
		case 'O':
			minoes.push_back(new Mino(0, 0, sf::Color::Blue));
			minoes.push_back(new Mino(0, 1, sf::Color::Blue));
			minoes.push_back(new Mino(1, 0, sf::Color::Blue));
			minoes.push_back(new Mino(1, 1, sf::Color::Blue));
			break;
		case 'Z':
			minoes.push_back(new Mino(0, 0, sf::Color(255, 128, 0)));
			minoes.push_back(new Mino(0, -1, sf::Color(255, 128, 0)));
			minoes.push_back(new Mino(1, 0, sf::Color(255, 128, 0)));
			minoes.push_back(new Mino(1, 1, sf::Color(255, 128, 0)));
			break;
		case 'S':
			minoes.push_back(new Mino(0, 0, sf::Color::Cyan));
			minoes.push_back(new Mino(0, 1, sf::Color::Cyan));
			minoes.push_back(new Mino(1, 0, sf::Color::Cyan));
			minoes.push_back(new Mino(1, -1, sf::Color::Cyan));
			break;
		case 'I':
			minoes.push_back(new Mino(0, 0, sf::Color::Red));
			minoes.push_back(new Mino(0, -1, sf::Color::Red));
			minoes.push_back(new Mino(0, 1, sf::Color::Red));
			minoes.push_back(new Mino(0, 2, sf::Color::Red));
	}
}

void Tetromino::moveLeft(short x)
{
	for (Mino *mino : minoes)
	{
		mino->setPoint(mino->getPoint() - Point(0, x));
	}
}

void Tetromino::moveRight(short x)
{
	for (Mino *mino : minoes)
	{
		mino->setPoint(mino->getPoint() + Point(0, x));
	}
}

void Tetromino::moveDown(short y)
{
	for (Mino *mino : minoes)
	{
		mino->setPoint(mino->getPoint() + Point(y, 0));
	}
}

void Tetromino::resetPosition()
{
	for (Mino *mino : minoes)
	{
		mino->setPoint(0, 0);
	}
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Mino *mino : minoes)
	{
		target.draw(*mino);
	}
}

void Tetromino::rotateLeft()
{
	switch (type)
	{
		case 'L':
		case 'J':
		case 'T':
			for (int i = 1; i < 4; ++i)
			{
				short r = minoes[i]->getPoint().row, c = minoes[i]->getPoint().col;
				minoes[i]->setPoint(-c, r);
			}
			break;
		case 'Z':
		case 'S':
		case 'I':
			for (int i = 1; i < 4; ++i)
			{
				short r = minoes[i]->getPoint().row, c = minoes[i]->getPoint().col;
				Point transform = rotation ? Point(-c, r) : Point(c, -r);
				minoes[i]->setPoint(-c, r);
			}
			rotation = !rotation;
	}
}

void Tetromino::rotateRight()
{
	switch (type)
	{
		case 'L':
		case 'J':
		case 'T':
			for (int i = 1; i < 4; ++i)
			{
				short r = minoes[i]->getPoint().row, c = minoes[i]->getPoint().col;
				minoes[i]->setPoint(c, -r);
			}
			break;
		case 'Z':
		case 'S':
		case 'I':
			for (int i = 1; i < 4; ++i)
			{
				short r = minoes[i]->getPoint().row, c = minoes[i]->getPoint().col;
				Point transform = rotation ? Point(-c, r) : Point(c, -r);
				minoes[i]->setPoint(-c, r);
			}
			rotation = !rotation;
	}
}