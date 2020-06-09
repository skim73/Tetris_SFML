#include "InputManager.h"
#include <iostream>

volatile unsigned int InputManager::upHold = 0,
					  InputManager::downHold = 0, 
					  InputManager::leftHold = 0,
					  InputManager::rightHold = 0;

unsigned int InputManager::upPressed()
{
	if (++upHold == UINT32_MAX)
		upHold = 1;
	return upHold;
}

unsigned int InputManager::downPressed()
{
	if (++downHold == UINT32_MAX)
		downHold = 1;
	return downHold;
}

unsigned int InputManager::leftPressed()
{
	if (++leftHold == UINT32_MAX)
		leftHold = 1;
	return leftHold;
}

unsigned int InputManager::rightPressed()
{
	if (++rightHold == UINT32_MAX)
		rightHold = 1;
	return rightHold;
}

void InputManager::upReleased()
{
	upHold = 0;
}

void InputManager::downReleased()
{
	downHold = 0;
}

void InputManager::leftReleased()
{
	leftHold = 0;
}

void InputManager::rightReleased()
{
	rightHold = 0;
}


bool InputManager::activateInput(unsigned int val, unsigned int rate, bool delayBetweenFirstPress)
{
	if (delayBetweenFirstPress)
		return ((val < rate) || (val > rate*3)) && !(val % rate - 1);
	return !(val % rate - 1);
}