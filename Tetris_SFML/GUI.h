#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GUI
{
protected:
	std::vector<sf::Drawable*> drawableComponents;

public:
	virtual void upPressed() = 0;
	virtual void downPressed() = 0;
	virtual void leftPressed() = 0;
	virtual void rightPressed() = 0;
	virtual short enterPressed() = 0;
	virtual void escPressed() = 0;
	virtual void zPressed() = 0;
	virtual void xPressed() = 0;

	std::vector<sf::Drawable*> getDrawableComponents()
	{
		return drawableComponents;
	}
};