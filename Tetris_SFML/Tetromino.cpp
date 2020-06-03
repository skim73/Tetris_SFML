#include "Tetromino.h"

Tetromino::Tetromino()
{
	location = Point(0, 4);
}

Tetromino::Tetromino(char type)
{
	location = Point(0, 4);
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
			minoes.push_back(new Mino(0, 0, sf::Color(0, 100, 255)));
			minoes.push_back(new Mino(0, 1, sf::Color(0, 100, 255)));
			minoes.push_back(new Mino(1, 0, sf::Color(0, 100, 255)));
			minoes.push_back(new Mino(1, 1, sf::Color(0, 100, 255)));
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
	location = location - Point(0, x);
	for (Mino *mino : minoes)
	{
		mino->setPositionAt(mino->getPoint() + location);
	}
}

void Tetromino::moveRight(short x)
{
	location = location + Point(0, x);
	for (Mino *mino : minoes)
	{
		mino->setPositionAt(mino->getPoint() + location);
	}
}

void Tetromino::moveDown(short y)
{
	location = location + Point(y, 0);
	for (Mino *mino : minoes)
	{
		mino->setPositionAt(mino->getPoint() + location);
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
				minoes[i]->setPositionAt(minoes[i]->getPoint() + location);
			}
			break;
		case 'Z':
		case 'S':
		case 'I':
			for (int i = 1; i < 4; ++i)
			{
				short r = minoes[i]->getPoint().row, c = minoes[i]->getPoint().col;
				Point transform = rotation ? Point(-c, r) : Point(c, -r);
				minoes[i]->setPoint(transform.row, transform.col);
				minoes[i]->setPositionAt(transform + location);
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
				minoes[i]->setPositionAt(minoes[i]->getPoint() + location);
			}
			break;
		case 'Z':
		case 'S':
		case 'I':
			for (int i = 1; i < 4; ++i)
			{
				short r = minoes[i]->getPoint().row, c = minoes[i]->getPoint().col;
				Point transform = rotation ? Point(-c, r) : Point(c, -r);
				minoes[i]->setPoint(transform.row, transform.col);
				minoes[i]->setPositionAt(transform + location);
			}
			rotation = !rotation;
	}
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Mino *mino : minoes)
	{
		target.draw(*mino);
	}
}