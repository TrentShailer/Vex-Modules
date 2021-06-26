#ifndef SmoothMotor_H
#define SmoothMotor_H

#include "vex.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include "util.h"

using namespace vex;

class SmoothMotor
{
private:
	motor _motor;
	float speed = 0;

public:
	SmoothMotor(motor m) : _motor(m)
	{
		_motor = m;
	}
	float maxSpeed = 100;
	float acceleration = 20;
	float stoppingThreshold = 5;

	void Drive(float target)
	{

		float increaseBy = (target - speed) / acceleration;
		speed += increaseBy;

		if (floatWithin(speed, -stoppingThreshold, stoppingThreshold) && floatWithin(target, -stoppingThreshold, stoppingThreshold))
		{
			return Stop();
		}

		_motor.setVelocity(speed * (acceleration / 100), percent);
		_motor.spin(forward);
	}

	void Stop()
	{
		_motor.stop();
	}
};

#endif