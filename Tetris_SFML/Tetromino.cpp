#include "Tetromino.h"

void Tetromino::moveLeft()
{
	for (Mino mino : minoes)
	{
		Point p = mino.getPoint();
		mino.setPoint(p.row, p.col - 1);
	}
}

void Tetromino::moveRight()
{
	for (Mino mino : minoes)
	{
		Point p = mino.getPoint();
		mino.setPoint(p.row, p.col + 1);
	}
}

void Tetromino::moveDown()
{
	for (Mino mino : minoes)
	{
		Point p = mino.getPoint();
		mino.setPoint(p.row + 1, p.col);
	}
}

void Tetromino::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Mino mino : minoes)
	{
		target.draw(mino);
	}
}

void Tetromino::rotateLeft()
{
	for (int i = 1; i < 4; ++i)
	{
		short r = minoes[i].getPoint().row, c = minoes[i].getPoint().col;
		minoes[i].setPoint(-c, r);
	}
}

void Tetromino::rotateRight()
{
	for (int i = 1; i < 4; ++i)
	{
		short r = minoes[i].getPoint().row, c = minoes[i].getPoint().col;
		minoes[i].setPoint(c, -r);
	}
}

TetrominoL::TetrominoL()
{
	minoes.push_back(Mino(0, 0, sf::Color::Magenta));
	minoes.push_back(Mino(0, -1, sf::Color::Magenta));
	minoes.push_back(Mino(0, 1, sf::Color::Magenta));
	minoes.push_back(Mino(1, -1, sf::Color::Magenta));
}

TetrominoJ::TetrominoJ()
{
	minoes.push_back(Mino(0, 0, sf::Color::Yellow));
	minoes.push_back(Mino(0, -1, sf::Color::Yellow));
	minoes.push_back(Mino(0, 1, sf::Color::Yellow));
	minoes.push_back(Mino(1, 1, sf::Color::Yellow));
}

TetrominoT::TetrominoT()
{
	minoes.push_back(Mino(0, 0, sf::Color::Green));
	minoes.push_back(Mino(0, -1, sf::Color::Green));
	minoes.push_back(Mino(0, 1, sf::Color::Green));
	minoes.push_back(Mino(1, 0, sf::Color::Green));
}

TetrominoO::TetrominoO()
{
	minoes.push_back(Mino(0, 0, sf::Color::Blue));
	minoes.push_back(Mino(0, 1, sf::Color::Blue));
	minoes.push_back(Mino(1, 0, sf::Color::Blue));
	minoes.push_back(Mino(1, 1, sf::Color::Blue));
}

void TetrominoO::rotateLeft()
{
	return;
}

void TetrominoO::rotateRight()
{
	return;
}

TetrominoZ::TetrominoZ()
{
	rotated = 0;
	minoes.push_back(Mino(0, 0, sf::Color(255, 128, 0)));
	minoes.push_back(Mino(0, -1, sf::Color(255, 128, 0)));
	minoes.push_back(Mino(1, 0, sf::Color(255, 128, 0)));
	minoes.push_back(Mino(1, 1, sf::Color(255, 128, 0)));
}

void TetrominoZ::rotateLeft()
{
	if (rotated)
	{
		Tetromino::rotateLeft();
	}
	else
	{
		Tetromino::rotateRight();
	}
	rotated = !rotated;
}

void TetrominoZ::rotateRight()
{
	if (rotated)
	{
		Tetromino::rotateLeft();
	}
	else
	{
		Tetromino::rotateRight();
	}
	rotated = !rotated;
}

TetrominoS::TetrominoS()
{
	rotated = 0;
	minoes.push_back(Mino(0, 0, sf::Color::Cyan));
	minoes.push_back(Mino(0, 1, sf::Color::Cyan));
	minoes.push_back(Mino(1, 0, sf::Color::Cyan));
	minoes.push_back(Mino(1, -1, sf::Color::Cyan));
}

void TetrominoS::rotateLeft()
{
	if (rotated)
	{
		Tetromino::rotateLeft();
	}
	else
	{
		Tetromino::rotateRight();
	}
	rotated = !rotated;
}

void TetrominoS::rotateRight()
{
	if (rotated)
	{
		Tetromino::rotateLeft();
	}
	else
	{
		Tetromino::rotateRight();
	}
	rotated = !rotated;
}

TetrominoI::TetrominoI()
{
	rotated = 0;
	minoes.push_back(Mino(0, 0, sf::Color::Red));
	minoes.push_back(Mino(0, -1, sf::Color::Red));
	minoes.push_back(Mino(0, 1, sf::Color::Red));
	minoes.push_back(Mino(0, 2, sf::Color::Red));
}

void TetrominoI::rotateLeft()
{
	if (rotated)
	{
		Tetromino::rotateLeft();
	}
	else
	{
		Tetromino::rotateRight();
	}
	rotated = !rotated;
}

void TetrominoI::rotateRight()
{
	if (rotated)
	{
		Tetromino::rotateLeft();
	}
	else
	{
		Tetromino::rotateRight();
	}
	rotated = !rotated;
}