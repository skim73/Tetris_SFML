#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GUI.h"

class Options : public GUI
{
	sf::RectangleShape background;
	sf::Texture bgTexture;

	sf::RectangleShape rectangle;
	sf::Font square721bt;

	sf::Text musicVolText;
	sf::RectangleShape musicSlider;
	sf::Text sfxVolText;
	sf::RectangleShape sfxSlider;
	sf::Text backText;

	sf::Music *bgm;
	sf::Sound *sfx;

	short cursor;

public:
	Options(sf::Music *music, sf::Sound *sound);

	void upPressed() override;
	short downPressed() override;
	void leftPressed() override;
	void rightPressed() override;
	short enterPressed() override;
	void zPressed() override;
	void xPressed() override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};