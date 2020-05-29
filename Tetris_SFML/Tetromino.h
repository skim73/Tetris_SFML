#pragma once
#include <vector>
#include "Mino.h"

class Tetromino : public sf::Drawable
{
protected:
	std::vector<Mino> minoes;

public:
	std::vector<Mino>& getMinoes()
	{
		return minoes;
	}

	void moveLeft();
	void moveRight();
	void moveDown();
	virtual void rotateLeft();
	virtual void rotateRight();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class TetrominoL : public Tetromino
{
public:
	TetrominoL();
};

class TetrominoJ : public Tetromino
{
public:
	TetrominoJ();
};

class TetrominoT : public Tetromino
{
public:
	TetrominoT();
};

class TetrominoO : public Tetromino
{
public:
	TetrominoO();

	void rotateLeft() override;
	void rotateRight() override;
};

class TetrominoZ : public Tetromino
{
	bool rotated;

public:
	TetrominoZ();

	void rotateLeft() override;
	void rotateRight() override;
};

class TetrominoS : public Tetromino
{
	bool rotated;

public:
	TetrominoS();

	void rotateLeft() override;
	void rotateRight() override;
};

class TetrominoI : public Tetromino
{
	bool rotated;

public:
	TetrominoI();

	void rotateLeft() override;
	void rotateRight() override;
};