#pragma once
#include <SFML/Graphics.hpp>
#include "GUI.h"

class LoadingScreen : public GUI
{
	sf::RectangleShape bgRect;
	sf::Texture bgTexture;

public:
	LoadingScreen();
	bool fadeAway();
	
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};