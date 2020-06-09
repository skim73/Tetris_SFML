#include "PauseScreen.h"

PauseScreen::PauseScreen()
{
	image.loadFromFile("img/backgrounds/gummies.jpg");

	pauseRect.setSize(sf::Vector2f(1600.f, 900.f));
	pauseRect.setTexture(&image);

	square721bt.loadFromFile("Square-721-BT.ttf");
	text = sf::Text("We all need a break at\nsome point.\nPress ESC to un-pause", square721bt);
	text.setPosition(200.f, 100.f);
	text.setFillColor(sf::Color::Black);
}

void PauseScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pauseRect);
	target.draw(text);
}