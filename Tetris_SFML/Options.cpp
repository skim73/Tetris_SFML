#include "Options.h"
#include <algorithm>

Options::Options()
{
	rectangle.setFillColor(sf::Color::Black);
	rectangle.setSize(sf::Vector2f(880.0f, 500.0f));
	rectangle.setPosition(360.0f, 200.0f);

	square721bt.loadFromFile("Square-721-BT.ttf");

	musicVolText = sf::Text("Music Volume:", square721bt);
	musicVolText.setOutlineThickness(1.0f);
	musicVolText.setOutlineColor(sf::Color::Black);
	musicVolText.setPosition(400.f, 220.f);
	musicVolText.setFillColor(sf::Color::Cyan);

	musicSlider.setFillColor(sf::Color::Green);
	musicSlider.setSize(sf::Vector2f(800.f, 40.f));
	musicSlider.setPosition(400.f, 270.f);

	sfxVolText = sf::Text("SFX Volume:", square721bt);
	sfxVolText.setOutlineThickness(1.0f);
	sfxVolText.setOutlineColor(sf::Color::Black);
	sfxVolText.setPosition(400.f, 370.f);
	sfxVolText.setFillColor(sf::Color::White);

	sfxSlider.setFillColor(sf::Color::Green);
	sfxSlider.setSize(sf::Vector2f(800.f, 40.f));
	sfxSlider.setPosition(400.f, 420.f);

	backText = sf::Text("BACK", square721bt);
	backText.setOutlineThickness(2.0f);
	backText.setOutlineColor(sf::Color::Black);
	backText.setPosition(750.f, 650.f);
	backText.setFillColor(sf::Color::White);

	cursor = 0;
}

void Options::moveCursorUp()
{
	if (--cursor < 0)
		cursor = 0;
	else
	{
		switch (cursor)
		{
			case 0:
				musicVolText.setFillColor(sf::Color::Cyan);
				sfxVolText.setFillColor(sf::Color::White);
				break;
			case 1:
				sfxVolText.setFillColor(sf::Color::Cyan);
				backText.setFillColor(sf::Color::White);
		}
	}
}

void Options::moveCursorDown()
{
	if (++cursor > 2)
		cursor = 2;
	else
	{
		switch (cursor)
		{
			case 1:
				musicVolText.setFillColor(sf::Color::White);
				sfxVolText.setFillColor(sf::Color::Cyan);
				break;
			case 2:
				sfxVolText.setFillColor(sf::Color::White);
				backText.setFillColor(sf::Color::Cyan);
		}
	}
}

void Options::moveSliderLeft(sf::Music& music, sf::Sound& sfx)
{
	if (!cursor)
	{
		if (music.getVolume() > 0.f)
		{
			sf::Vector2f size = musicSlider.getSize();
			music.setVolume(std::max(music.getVolume() - 5.0f, 0.0f));
			musicSlider.setSize(sf::Vector2f(music.getVolume() * 8, size.y));
		}
	}
	else if (cursor == 1)
	{
		if (sfx.getVolume() > 0.f)
		{
			sf::Vector2f size = sfxSlider.getSize();
			sfx.setVolume(std::max(sfx.getVolume() - 5.0f, 0.0f));
			sfxSlider.setSize(sf::Vector2f(sfx.getVolume() * 8, size.y));
		}
	}
}

void Options::moveSliderRight(sf::Music& music, sf::Sound& sfx)
{
	if (!cursor)
	{
		if (music.getVolume() < 100.f)
		{
			sf::Vector2f size = musicSlider.getSize();
			music.setVolume(std::min(music.getVolume() + 5.0f, 100.0f));
			musicSlider.setSize(sf::Vector2f(music.getVolume() * 8, size.y));
		}
	}
	else if (cursor == 1)
	{
		if (sfx.getVolume() < 100.f)
		{
			sf::Vector2f size = sfxSlider.getSize();
			sfx.setVolume(std::min(sfx.getVolume() + 5.0f, 100.0f));
			sfxSlider.setSize(sf::Vector2f(sfx.getVolume() * 8, size.y));
		}
	}
}