#include "TetrisGame.h"
#include <algorithm>

TetrisGame::TetrisGame(short level)
{
	matrix = std::vector<Mino*>(220, nullptr);

	matrixPicture.setSize(sf::Vector2f(432.f, 792.f));
	matrixPicture.setFillColor(sf::Color(0, 0, 0, 0));
	matrixPicture.setPosition(584.f, 54.f);

	square721bt.loadFromFile("Square-721-BT.ttf");

	nextBlockRect.setSize(sf::Vector2f(200.f, 200.f));
	nextBlockRect.setPosition(1200.f, 54.f);
	nextBlockRect.setFillColor(sf::Color(0, 0, 0, 0));

	nextText = sf::Text("NEXT", square721bt, 20);
	nextText.setPosition(1220.f, 60.f);
	nextText.setFillColor(sf::Color(255, 255, 255, 0));

	nextBlock = Tetromino(tetrominoTypes[rand() % 7]);
	nextBlock.moveRight(13);

	sf::Texture frameMinoTexture;
	frameMinoTexture.loadFromFile("img/mino.png");
	for (int i = 0; i < 64; ++i)
	{
		frame.push_back(sf::Sprite(frameMinoTexture));
		frame[i].setTextureRect(sf::IntRect(0, 0, 36, 36));
		frame[i].setColor(sf::Color(255, 255, 255, 0));
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

	this->level = level;

	std::string levelNumber;
	if (level >= 15)
		levelNumber = "15";
	else
	{
		if (level / 10)
			levelNumber.push_back('1');
		levelNumber.push_back('0' + level % 10);
	}
	backgroundPicture.loadFromFile("img/backgrounds/level" + levelNumber + ".png");

	backgroundRect.setSize(sf::Vector2f(1600.f, 900.f));
	backgroundRect.setTexture(&backgroundPicture);
	sf::Color color = backgroundRect.getFillColor();
	backgroundRect.setFillColor(sf::Color(color.r, color.g, color.b, 0));

	if (level <= 2)
		bgmFile = "music/[Feel It].ogg";
	else if (level <= 5)
		bgmFile = "music/Hi Rollers.ogg";
	else if (level <= 8)
		bgmFile = "music/Groove Ride.ogg";
	else if (level <= 11)
		bgmFile = "music/Born To Funk.ogg";
	else if (level <= 14)
		bgmFile = "music/Wild One.ogg";
	else
		bgmFile = "music/Balearic.ogg";


}

void TetrisGame::spawnNextTetromino()
{
	currentBlock = nextBlock;
	currentBlock.moveLeft(13);
	nextBlock = Tetromino(tetrominoTypes[rand() % 7]);
	nextBlock.moveRight(13);
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
				matrix[MATRIX(row, i)] = nullptr;
				delete matrix[MATRIX(row, 9 - i)];
				matrix[MATRIX(row, 9 - i)] = nullptr;
			}
			for (int j = row - 1; j >= 2; --j)
			{
				for (int k = 0; k < 5; ++k)
				{
					matrix[MATRIX(j + 1, k)] = matrix[MATRIX(j, k)];
					matrix[MATRIX(j + 1, 9 - k)] = matrix[MATRIX(j, 9 - k)];

					if (matrix[MATRIX(j, k)] != nullptr)
					{
						matrix[MATRIX(j, k)]->setPoint(j + 1, k);
						matrix[MATRIX(j, k)]->setPositionAt(Point(j + 1, k));
					}
					if (matrix[MATRIX(j, 9 - k)] != nullptr)
					{
						matrix[MATRIX(j, 9 - k)]->setPoint(j + 1, 9 - k);
						matrix[MATRIX(j, 9 - k)]->setPositionAt(Point(j + 1, 9 - k));
					}
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
	if (level >= 15)
		levelNumber = "15";
	else
	{
		if (level / 10)
			levelNumber.push_back('1');
		levelNumber.push_back('0' + level % 10);
	}
	backgroundPicture.loadFromFile("img/backgrounds/level" + levelNumber + ".png");

	switch (level)
	{
		case 3:
			bgmFile = "music/Hi Rollers.ogg";
			break;
		case 6:
			bgmFile = "music/Groove Ride.ogg";
			break;
		case 9:
			bgmFile = "music/Born To Funk.ogg";
			break;
		case 12:
			bgmFile = "music/Wild One.ogg";
			break;
		case 15:
			bgmFile = "music/Balearic.ogg";
	}
}

unsigned int* TetrisGame::gameOver()
{
	unsigned int *scoreAndLines = new unsigned int[2] { score, lines };
	return scoreAndLines;
}

void TetrisGame::setSFXVolume(float volume)
{
	moveSound.setVolume(volume);
	rotateSound.setVolume(volume);
	lineClearSound.setVolume(volume);
	tetrisSound.setVolume(volume);
	levelUpSound.setVolume(volume);
	gameoverSound.setVolume(volume);
}

void TetrisGame::downPressed()
{
	bool lock = false;
	for (Mino *mino : currentBlock.getMinoes())
	{
		Point newPt = mino->getPoint() + currentBlock.getLocation() + Point(1, 0);
		if (newPt.row >= 20 || matrix[MATRIX(newPt.row, newPt.col)] != nullptr)
		{
			lock = true;
			break;
		}
	}

	if (lock)
	{
		short row = currentBlock.getLocation().row;
		for (Mino *mino : currentBlock.getMinoes())
		{
			row = std::max(row, static_cast<short>(mino->getPoint().row + currentBlock.getLocation().row));
			Point finalPt = mino->getPoint() + currentBlock.getLocation();
			matrix[MATRIX(finalPt.row, finalPt.col)] = mino;
		}

		lines += checkLines(row);
		if (lines % 10 > level)
		{
			levelUp();
		}

		spawnNextTetromino();
	}
	else
	{
		currentBlock.moveDown(1);
	}
}

void TetrisGame::leftPressed()
{
	for (Mino *mino : currentBlock.getMinoes())
	{
		Point newPt = mino->getPoint() + currentBlock.getLocation() - Point(0, 1);
		if (newPt.col < 0 || matrix[MATRIX(newPt.row, newPt.col)] != nullptr)
		{
			return;
		}
	}

	currentBlock.moveLeft(1);
}

void TetrisGame::rightPressed()
{
	for (Mino *mino : currentBlock.getMinoes())
	{
		Point newPt = mino->getPoint() + currentBlock.getLocation() + Point(0, 1);
		if (newPt.col > 9 || matrix[MATRIX(newPt.row, newPt.col)] != nullptr)
		{
			return;
		}
	}

	currentBlock.moveRight(1);
}

void TetrisGame::escPressed()
{

}

void TetrisGame::zPressed()
{
	currentBlock.rotateLeft();
	for (Mino *mino : currentBlock.getMinoes())
	{
		Point newPt = mino->getPoint() + currentBlock.getLocation();
		if (newPt.col < 0 || newPt.col > 9 || newPt.row < -2 || newPt.row > 19 ||
			matrix[MATRIX(newPt.row, newPt.col)] != nullptr)
		{
			currentBlock.rotateRight();
			return;
		}
	}
}

void TetrisGame::xPressed()
{
	currentBlock.rotateRight();
	for (Mino *mino : currentBlock.getMinoes())
	{
		Point newPt = mino->getPoint() + currentBlock.getLocation();
		if (newPt.col < 0 || newPt.col > 9 || newPt.row < -2 || newPt.row > 19 ||
			matrix[MATRIX(newPt.row, newPt.col)] != nullptr)
		{
			currentBlock.rotateLeft();
			return;
		}
	}
}

bool TetrisGame::fadeIn()
{
	sf::Color bgColor = backgroundRect.getFillColor();
	backgroundRect.setFillColor(sf::Color(bgColor.r, bgColor.g, bgColor.b, bgColor.a + 5));
	sf::Color matrixColor = matrixPicture.getFillColor();
	matrixPicture.setFillColor(sf::Color(matrixColor.r, matrixColor.g, matrixColor.b, matrixColor.a + 3));
	sf::Color nextBlockColor = nextBlockRect.getFillColor();
	nextBlockRect.setFillColor(sf::Color(nextBlockColor.r, nextBlockColor.g, nextBlockColor.b, nextBlockColor.a + 3));
	sf::Color nextTextColor = nextText.getFillColor();
	nextText.setFillColor(sf::Color(nextTextColor.r, nextTextColor.g, nextTextColor.b, nextTextColor.a + 5));
	for (sf::Sprite &frameMino : frame)
	{
		sf::Color minoColor = frameMino.getColor();
		frameMino.setColor(sf::Color(minoColor.r, minoColor.g, minoColor.b, minoColor.a + 5));
	}

	return bgColor.a >= 255;
}

void TetrisGame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(backgroundRect);
	target.draw(matrixPicture);
	target.draw(nextBlockRect);
	target.draw(nextText);
	for (sf::Sprite frameMino : frame)
	{
		target.draw(frameMino);
	}
	target.draw(currentBlock);
	target.draw(nextBlock);
	for (Mino *mino : matrix)
	{
		if (mino != nullptr)
			target.draw(*mino);
	}
}

std::string TetrisGame::getBGMFile()
{
	return bgmFile;
}