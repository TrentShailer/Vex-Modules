#ifndef AutonSelect
#define AutonSelect

#include "util.h"
#include "vex.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace vex;

util::side curSide = none;

int timeForSelection = 20;

static const char *EnumStrings[] = {"Left", "Right", "None"};

void InitAutonSelect(void *left, void *right)
{
	Brain.Screen.DrawLine(240, 0, 240, 280);
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
			curSide = (xPos > 240 ? util::side::right : util::side::left);
			break;
		}
		wait(20, msec)
	}

	Brain.Screen.clearScreen();
	Brain.Screen.print(EnumStrings[util::side::left]);
	wait(1000, msec);
	Brain.Screen.clearScreen();

	if (curSide == util::side::right)
	{
		right();
		return
	}
	else if (curSide == util::side::left)
	{
		left();
		return
	}
}

#endif