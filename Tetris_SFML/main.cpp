#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TitleScreen.h"
#include "Options.h"
#include "LoadingScreen.h"

#include <iostream>

enum class ProgramState
{
	MENU, LOAD, GAME, OPTIONS, HIGHSCORE
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Tetris_SFML");

	ProgramState state = ProgramState::MENU;

	GUI *currentGUI;

	TitleScreen title;
	currentGUI = &title;

	LoadingScreen loading;

	sf::Music music;
	music.openFromFile(title.getMusic());
	music.setLoopPoints(sf::Music::TimeSpan(sf::seconds(52.646f), sf::seconds(49.180f)));
	music.play();
	music.setLoop(true);

	sf::Sound sfx;
	sfx.setVolume(100.f);

	Options options(&music, &sfx);

	sf::Clock programClock;
	sf::Clock joyHold;

	volatile unsigned int holdIndex = 0;

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
					state = ProgramState::GAME;
				}
			}
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed && ++holdIndex % 2)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::Up:
						currentGUI->upPressed();
						break;
					case sf::Keyboard::Down:
						currentGUI->downPressed();
						break;
					case sf::Keyboard::Left:
						currentGUI->leftPressed();
						break;
					case sf::Keyboard::Right:
						currentGUI->rightPressed();
						break;
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
									currentGUI = &loading;
									programClock.restart();
									break;
								case 1:
									state = ProgramState::OPTIONS;
									currentGUI = &options;
									break;
								case 2:
									break;
							}
						}
						else if (state == ProgramState::OPTIONS && currentGUI->enterPressed())
						{
							currentGUI = &title;
							state = ProgramState::MENU;
						}
				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				holdIndex = 0;
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