#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TitleScreen.h"
#include "Options.h"
#include "LoadingScreen.h"
#include "TetrisGame.h"
#include "InputManager.h"
#include "HighScores.h"

#include <iostream>

enum class ProgramState
{
	MENU, LOAD, STAND_BY, GAME, GAME_OVER, PAUSE, QUIT_GAME, ENTER_NAME, OPTIONS, HIGHSCORE
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Tetris_SFML");

	ProgramState state = ProgramState::MENU;

	GUI *currentGUI;

	TitleScreen title;
	currentGUI = &title;

	TetrisGame *tetrisGameInstance = nullptr;

	sf::Font square721bt;
	square721bt.loadFromFile("Square-721-BT.ttf");

	sf::Music music;
	music.openFromFile(title.getMusic());
	music.setLoopPoints(sf::Music::TimeSpan(sf::seconds(52.646f), sf::seconds(49.180f)));
	music.play();
	music.setLoop(true);
	float musicVolume = 100.f;

	sf::Sound sfx;
	sfx.setVolume(100.f);

	sf::Clock programClock;

	short startingLevel;

	unsigned int *results = nullptr;

	bool downButtonHeld = false;
	bool leftButtonHeld = false;
	bool rightButtonHeld = false;
	unsigned int inputRate = 40;

	HighScores hiScoreScreen;
	std::string playerName;

	while (window.isOpen())
	{
		window.clear();
		window.draw(*currentGUI);

		if (state == ProgramState::LOAD)
		{
			if (music.getVolume() > 1)
				music.setVolume(music.getVolume() - 1.f);
			else
				music.stop();
			if (programClock.getElapsedTime() > sf::seconds(3.f))
			{
				if (currentGUI->fadeAway())
				{
					programClock.restart();
					state = ProgramState::STAND_BY;
					delete currentGUI;
					currentGUI = new TetrisGame(startingLevel);
					tetrisGameInstance = dynamic_cast<TetrisGame*>(currentGUI);
				}
			}
		}
		else if (state == ProgramState::STAND_BY)
		{
			if (tetrisGameInstance != nullptr)
			{
				tetrisGameInstance->setBGMVolume(musicVolume);
				tetrisGameInstance->setSFXVolume(sfx.getVolume());
			}

			if (currentGUI->fadeIn())
			{
				tetrisGameInstance->spawnNextTetromino();
				state = ProgramState::GAME;
				programClock.restart();
			}
		}
		else if (state == ProgramState::GAME)
		{
			inputRate = 40 - (tetrisGameInstance->getMinoNum() / 38) * 4;

			if (programClock.getElapsedTime() >= sf::seconds(tetrisGameInstance->getCurrentSpeed() / 60.f))
			{
				downButtonHeld = false;
				if (tetrisGameInstance->downPressed() == -1)
				{
					state = ProgramState::GAME_OVER;
					results = tetrisGameInstance->gameOver();
				}
				programClock.restart();
			}
		}
		else if (state == ProgramState::QUIT_GAME)
		{
			if (currentGUI->fadeAway())
			{
				delete tetrisGameInstance;
				tetrisGameInstance = nullptr;
				currentGUI = nullptr;

				short rank = hiScoreScreen.determineRank(results[0]);
				if (rank < 6)
				{
					state = ProgramState::ENTER_NAME;
					std::cout << "\nYou ranked in the top 5 high scores! Enter your name below!" << std::endl;
					std::cout << "PLEASE: No spaces and at most 20 characters!" << std::endl;
					std::cin >> playerName;
					if (playerName.size() > 20)
						playerName = playerName.substr(0, 20);

					hiScoreScreen.updateHighScores(playerName, results[0], results[1], rank - 1);
				}

				state = ProgramState::MENU;
				currentGUI = &title;
				music.setVolume(musicVolume);
				music.play();
				delete results;
				results = nullptr;
			}
		}

		// CHECK FOR INPUTS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			if (InputManager::activateInput(InputManager::upPressed(), inputRate, true))
			{
				currentGUI->upPressed();
			}
		}
		else
		{
			InputManager::upReleased();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			unsigned int downButtonRate = state == ProgramState::GAME ? inputRate/2 : inputRate;

			if (!downButtonHeld && 
				InputManager::activateInput(InputManager::downPressed(), downButtonRate, state != ProgramState::GAME))
			{
				short status = currentGUI->downPressed();
				if (status == 1)
				{
					InputManager::downReleased();
					downButtonHeld = true;
					programClock.restart();
				}
				else if (status == -1 && state == ProgramState::GAME)
				{
					state = ProgramState::GAME_OVER;
					results = tetrisGameInstance->gameOver();
				}

				if (tetrisGameInstance && state == ProgramState::GAME)
					tetrisGameInstance->updateScore(1);
			}
		}
		else
		{
			InputManager::downReleased();
			downButtonHeld = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (!rightButtonHeld && InputManager::activateInput(InputManager::leftPressed(), inputRate, true))
			{
				leftButtonHeld = true;
				InputManager::rightReleased();
				currentGUI->leftPressed();
			}
		}
		else
		{
			InputManager::leftReleased();
			leftButtonHeld = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (!leftButtonHeld && InputManager::activateInput(InputManager::rightPressed(), inputRate, true))
			{
				rightButtonHeld = true;
				InputManager::leftReleased();
				currentGUI->rightPressed();
			}
		}
		else
		{
			InputManager::rightReleased();
			rightButtonHeld = false;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						if (state == ProgramState::GAME)
						{
							state = ProgramState::PAUSE;
							currentGUI = new PauseScreen();
						}
						else if (state == ProgramState::PAUSE)
						{
							state = ProgramState::GAME;
							delete currentGUI;
							currentGUI = tetrisGameInstance;
						}
						else if (state == ProgramState::HIGHSCORE)
						{
							state = ProgramState::MENU;
							currentGUI = &title;

							music.openFromFile(title.getMusic());
							music.setLoopPoints(sf::Music::TimeSpan(sf::seconds(52.646f), sf::seconds(49.180f)));
							music.play();
							music.setLoop(true);
						}
						break;
					case sf::Keyboard::Z:
						currentGUI->zPressed();
						break;
					case sf::Keyboard::X:
						currentGUI->xPressed();
						break;
					case sf::Keyboard::Enter:
						if (state == ProgramState::MENU)
						{
							switch (currentGUI->enterPressed())
							{
								case 0:
									state = ProgramState::LOAD;
									startingLevel = title.getLevelCursor();
									currentGUI = new LoadingScreen();
									musicVolume = music.getVolume();
									programClock.restart();
									break;
								case 1:
									state = ProgramState::OPTIONS;
									currentGUI = new Options(&music, &sfx);
									break;
								case 2:
									state = ProgramState::HIGHSCORE;
									currentGUI = &hiScoreScreen;
									music.stop();
									music.openFromFile("music/Tetris X BGM 12 (Title).ogg");
									music.setLoop(false);
									music.play();
									break;
							}
						}
						else if (state == ProgramState::GAME_OVER)
						{
							state = ProgramState::QUIT_GAME;
						}
						else if (state == ProgramState::OPTIONS && currentGUI->enterPressed())
						{
							delete currentGUI;
							currentGUI = &title;
							state = ProgramState::MENU;
						}
				}
			}
			else if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.display();
	}

	return 0;
}