#ifndef AutonSelect_H
#define AutonSelect_H

#include "util.h"
#include "vex.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace vex;

side curSide = none;

int timeForSelection = 20;

static const char *EnumStrings[] = {"Left", "Right", "None"};

void InitAutonSelect(void *left(void), void *right(void))
{
	Brain.Screen.drawLine(240, 0, 240, 280);
	Brain.Screen.setCursor(2, 2);
	Brain.Screen.print("Left");
	Brain.Screen.setCursor(4, 2);
	Brain.Screen.print("Right");
	Brain.Screen.setCursor(0, 0);

	for (int i = 0; i < (timeForSelection * 1000) / 20; i++)
	{
		int xPos = Brain.Screen.xPosition();
		if (Brain.Screen.pressing())
		{
			curSide = (xPos > 240 ? side::right : side::left);
			break;
		}
		wait(20, msec);
	}

	Brain.Screen.clearScreen();
	Brain.Screen.print(EnumStrings[side::left]);
	wait(1000, msec);
	Brain.Screen.clearScreen();

	if (curSide == side::right)
	{
		right();
		return;
	}
	else if (curSide == side::left)
	{
		left();
		return;
	}
}

#endif