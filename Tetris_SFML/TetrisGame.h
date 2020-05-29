#pragma once
#include <cstdlib>
#include "Tetromino.h"
#include "Mino.h"
#include "GUI.h"

class TetrisGame : public GUI
{
	sf::RectangleShape matrixPicture;

	Tetromino *currentBlock;
	Tetromino *nextBlock;

	bool matrix[20][10];

	const unsigned short frameRate[31] = {
		48, 43, 38, 33, 28, 23, 18, 13, 8, 6,
		5, 5, 5, 4, 4, 4, 3, 3, 3, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1
	};
	const char tetrominoTypeArray[7] = {'I', 'O', 'T', 'L', 'J', 'Z', 'S'};

	short level;
	unsigned int score;
	unsigned int lines;

public:
	TetrisGame();

	char spawnNextTetromino();
	short checkLines();
	void levelUp();
	unsigned int* gameOver();

	void upPressed() override;
	void downPressed() override;
	void leftPressed() override;
	void rightPressed() override;
	short enterPressed() override;
	void escPressed() override;
	void zPressed() override;
	void xPressed() override;

	void setLevel(short level)
	{
		this->level = level;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};