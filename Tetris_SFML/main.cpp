#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TitleScreen.h"
#include "Options.h"
#include "LoadingScreen.h"
#include "TetrisGame.h"
#include "InputManager.h"

#include <iostream>

enum class ProgramState
{
	MENU, LOAD, STAND_BY, GAME, GAME_OVER, QUIT_GAME, OPTIONS, HIGHSCORE
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Tetris_SFML");

	ProgramState state = ProgramState::MENU;

	GUI *currentGUI;

	TitleScreen title;
	currentGUI = &title;

	TetrisGame *tetrisGameInstance = nullptr;

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

	unsigned int *results;

	bool downButtonHeld = false;

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
				state = ProgramState::MENU;
				delete tetrisGameInstance;
				tetrisGameInstance = nullptr;
				currentGUI = &title;

				music.setVolume(musicVolume);
				music.play();
			}
		}

		// CHECK FOR INPUTS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			if (InputManager::activateInput(InputManager::upPressed(), 40, true))
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
			unsigned int downButtonRate = state == ProgramState::GAME ? 20 : 40;

			if (!downButtonHeld && InputManager::activateInput(InputManager::downPressed(), downButtonRate, state != ProgramState::GAME))
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
			}
		}
		else
		{
			InputManager::downReleased();
			downButtonHeld = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			if (InputManager::activateInput(InputManager::leftPressed(), 40, true))
			{
				currentGUI->leftPressed();
			}
		}
		else
		{
			InputManager::leftReleased();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (InputManager::activateInput(InputManager::rightPressed(), 40, true))
			{
				currentGUI->rightPressed();
			}
		}
		else
		{
			InputManager::rightReleased();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						currentGUI->escPressed();
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