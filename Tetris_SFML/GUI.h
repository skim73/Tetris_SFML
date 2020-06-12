#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class GUI : public sf::Drawable
{
public:
	virtual void upPressed() { return; }
	virtual short downPressed() { return 0; }
	virtual void leftPressed() { return; }
	virtual void rightPressed() { return; }
	virtual short enterPressed() { return 0; }
	virtual void zPressed() { return; }
	virtual void xPressed() { return; }

	virtual bool fadeAway()
	{
		return 0;
	}

	virtual bool fadeIn()
	{
		return 0;
	}
};