#include "LoadingScreen.h"

LoadingScreen::LoadingScreen()
{
	bgTexture.loadFromFile("img/backgrounds/loading.png");
	bgRect.setTexture(&bgTexture);
	bgRect.setSize(sf::Vector2f(1600.f, 900.f));
}

bool LoadingScreen::fadeAway()
{
	sf::Color bgColor = bgRect.getFillColor();
	bgRect.setFillColor(sf::Color(bgColor.r, bgColor.g, bgColor.b, bgColor.a - 5));

	return bgRect.getFillColor().a == 0;
}

void LoadingScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(bgRect);
}