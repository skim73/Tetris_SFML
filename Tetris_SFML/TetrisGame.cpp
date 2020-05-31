#include "TetrisGame.h"

TetrisGame::TetrisGame()
{
	matrix = std::vector<Mino*>(220, nullptr);

	matrixPicture.setSize(sf::Vector2f(432.f, 792.f));
	matrixPicture.setFillColor(sf::Color(0, 0, 0, 155));
	matrixPicture.setPosition(584.f, 54.f);

	square721bt.loadFromFile("Square-721-BT.ttf");
	nextBlockRect.setSize(sf::Vector2f(100.f, 100.f));
	nextBlockRect.setPosition(1200.f, 54.f);
	nextText = sf::Text("NEXT", square721bt, 20);
	nextBlock.moveRight(18);

	sf::Texture frameMinoTexture;
	frameMinoTexture.loadFromFile("img/mino.png");
	for (int i = 0; i < 64; ++i)
	{
		frame.push_back(sf::Sprite(frameMinoTexture));
		frame[i].setTextureRect(sf::IntRect(0, 0, 36, 36));
	}
	for (int i = 0; i < 12; ++i)
	{
		frame[i].setPosition(584.f + 36.f*i, 54.f);
		frame[i + 12].setPosition(584.f + 36.f*i, 810.f);
	}
	for (int i = 0; i < 20; ++i)
	{
		frame[i + 24].setPosition(584.f, 90.f + 36.f*i);
		frame[i + 44].setPosition(980.f, 90.f + 36.f*i);
	}

	currentBlock.moveRight(4);
}

void TetrisGame::spawnNextTetromino()
{
	currentBlock = nextBlock;
	currentBlock.resetPosition();
	currentBlock.moveRight(4);
	nextBlock = Tetromino(rand() % 7);
}

short TetrisGame::checkLines(short row)
{
	short lines = 0;
	std::vector<short> lineRows;
	for (short r = row; r > row - 4; --r)
	{
		int i = 0;
		while (i < 10)
		{
			if (matrix[MATRIX(r, i)] == nullptr)
				break;
			++i;
		}
		if (i == 10)
		{
			lineRows.push_back(r);
			++lines;
		}
	}

	if (lines)
	{
		if (lines == 4)
		{
			tetrisSound.play();
		}
		else
		{
			lineClearSound.play();
		}

		while (!lineRows.empty())
		{
			short row = lineRows.back();
			lineRows.pop_back();
			for (int i = 4; i >= 0; --i)
			{
				delete matrix[MATRIX(row, i)];
				delete matrix[MATRIX(row, 9 - i)];
			}
			for (int j = row + 1; j >= 2; --j)
			{
				for (int k = 0; k < 5; ++k)
				{
					matrix[MATRIX(j, k)] = matrix[MATRIX(j - 1, k)];
					matrix[MATRIX(j, 9 - k)] = matrix[MATRIX(j - 1, 9 - k)];
				}
			}
		}
	}
	return lines;
}

void TetrisGame::levelUp()
{
	levelUpSound.play();

	++level;
	std::string levelNumber;
	if (level / 10)
		levelNumber.push_back('0' + level / 10);
	levelNumber.push_back('0' + level % 10);
	backgroundPicture.loadFromFile("img/backgrounds/level" + levelNumber + ".png");

	switch (level)
	{
		case 3:
			bgm.stop();
			bgm.openFromFile("music/Hi Rollers.ogg");
			break;
		case 6:
			bgm.stop();
			bgm.openFromFile("music/Groove Ride.ogg");
			break;
		case 9:
			bgm.stop();
			bgm.openFromFile("music/Born To Funk.ogg");
			break;
		case 12:
			bgm.stop();
			bgm.openFromFile("music/Wild One.ogg");
			break;
		case 15:
			bgm.stop();
			bgm.openFromFile("music/Balearic.ogg");
	}
}

unsigned int* TetrisGame::gameOver()
{
	unsigned int *scoreAndLines = new unsigned int[2] { score, lines };
	return scoreAndLines;
}