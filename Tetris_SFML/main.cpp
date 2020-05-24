#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TitleScreen.h"
#include "Options.h"

#include <iostream>

enum class ProgramState
{
	MENU, LOAD, GAME, OPTIONS, HIGHSCORE
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Tetris_SFML");

	ProgramState state = ProgramState::MENU;

	TitleScreen title;
	Options options;

	sf::RectangleShape background(sf::Vector2f(1600, 900));
	background.setTexture(title.getBackground());

	sf::Music music;
	music.openFromFile(title.getMusic());
	music.setLoopPoints(sf::Music::TimeSpan(sf::seconds(52.646f), sf::seconds(49.180f)));
	music.play();
	music.setLoop(true);

	sf::Sound sfx;
	sfx.setVolume(100.f);

	sf::Clock programClock;
	sf::Clock joyHold;

	volatile unsigned int holdIndex = 0;

	while (window.isOpen())
	{
		window.clear();
		window.draw(background);

		sf::Event event;
		switch (state)
		{
			case ProgramState::MENU:
				window.draw(title.getMenuRect());
				for (sf::Text text : title.getMenuItems())
				{
					window.draw(text);
				}

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (++holdIndex % 2)
						{
							switch (event.key.code)
							{
								case sf::Keyboard::Key::Up:
									title.moveCursorUp();
									break;
								case sf::Keyboard::Key::Down:
									title.moveCursorDown();
									break;
								case sf::Keyboard::Key::Left:
									title.changeLevelDown();
									break;
								case sf::Keyboard::Key::Right:
									title.changeLevelUp();
									break;
								case sf::Keyboard::Key::Enter:
									switch (title.getMenuCursor())
									{
										case 0:
											state = ProgramState::LOAD;
											programClock.restart();
											break;

										case 1:
											state = ProgramState::OPTIONS;
											break;

										case 2:
											state = ProgramState::HIGHSCORE;
											break;
									}
							}
						}
					}
					else if (event.type == sf::Event::KeyReleased)
						holdIndex = 0;
				}

				break;

			case ProgramState::LOAD:
				window.draw(title.getLoadingRect());
				window.draw(title.getLoadingText());
				if (music.getVolume() > 1)
					music.setVolume(music.getVolume() - 1);
				else
					music.stop();
				if (programClock.getElapsedTime() >= sf::seconds(3.0f))
				{
					state = ProgramState::GAME;
				}
				break;

			case ProgramState::GAME:

				break;

			case ProgramState::OPTIONS:
				window.draw(options.getRectangle());
				window.draw(options.getMusicVolText());
				window.draw(options.getMusicSlider());
				window.draw(options.getSFXVolText());
				window.draw(options.getSFXSlider());
				window.draw(options.getBackText());

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (++holdIndex % 2)
						{
							switch (event.key.code)
							{
								case sf::Keyboard::Key::Up:
									options.moveCursorUp();
									break;
								case sf::Keyboard::Key::Down:
									options.moveCursorDown();
									break;
								case sf::Keyboard::Key::Left:
									options.moveSliderLeft(music, sfx);
									break;
								case sf::Keyboard::Key::Right:
									options.moveSliderRight(music, sfx);
									break;
								case sf::Keyboard::Key::Enter:
									if (options.getCursor() == 2)
										state = ProgramState::MENU;
							}
						}
					}
					else if (event.type == sf::Event::KeyReleased)
						holdIndex = 0;
					break;
				}
			case ProgramState::HIGHSCORE:
				break;
		}

		if (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					window.setSize(sf::Vector2u(1600, 900));
					std::cout << "This program produces painfully blurred images if resized. "
						<< "Hence, I am overriding all resizes of the application.\n"
						<< "You are running the version that is optimal for 1080p (Full HD) displays.\n\n"
						<< "****  Go to [github.com/johnscolidge/Tetris_SFML] to download the version of "
						<< "Tetris_SFML\n      that has the optimal resolution for your display.  ****\n\n\n\n";
					break;
			}
		}
		window.display();
	}

	return 0;
}