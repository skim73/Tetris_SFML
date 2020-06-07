#pragma once
#include <SFML/System.hpp>

class InputManager
{
public:
	static volatile unsigned int upHold, downHold, leftHold, rightHold;
	static bool enterHold, escHold, zHold, xHold;

	static unsigned int upPressed();
	static unsigned int downPressed();
	static unsigned int leftPressed();
	static unsigned int rightPressed();

	static void upReleased();
	static void downReleased();
	static void leftReleased();
	static void rightReleased();

	static bool activateInput(unsigned int val, bool delayBetweenFirstPress);
};