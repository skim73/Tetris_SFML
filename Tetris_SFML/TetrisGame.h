#pragma once
#include <cstdlib>
#include "Tetromino.h"
#include "Mino.h"
#include "GUI.h"
#include <SFML/Audio.hpp>

#define MATRIX(row, col) ((row+2)*10 + (col))

class TetrisGame : public GUI
{
	sf::RectangleShape matrixPicture;
	std::vector<sf::Sprite> frame;

	sf::Font square721bt;
	sf::RectangleShape nextBlockRect;
	sf::Text nextText;

	Tetromino currentBlock = Tetromino(rand() % 7);
	Tetromino nextBlock = Tetromino(rand() % 7);

	std::vector<Mino*> matrix;

	const unsigned short frameRate[31] = {
		48, 43, 38, 33, 28, 23, 18, 13, 8, 6,
		5, 5, 5, 4, 4, 4, 3, 3, 3, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1
	};
	const char tetrominoTypes[7] = { 'L', 'J', 'T', 'O', 'Z', 'S', 'I' };

	sf::RectangleShape backgroundRect;
	sf::Texture backgroundPicture;
	sf::Music bgm;
	sf::Sound moveSound, rotateSound, lineClearSound, tetrisSound, levelUpSound, gameoverSound;

	short level;
	unsigned int score;
	unsigned int lines;

public:
	TetrisGame();

	void spawnNextTetromino();
	short checkLines(short row);
	void levelUp();
	unsigned int* gameOver();

	void downPressed() override;
	void leftPressed() override;
	void rightPressed() override;
	short enterPressed() override;
	void escPressed() override;
	void zPressed() override;
	void xPressed() override;

	void setLevel(short level);

	unsigned short getFrameRate(short level)
	{
		return frameRate[level];
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};