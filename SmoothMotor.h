#ifndef SmoothMotor
#define SmoothMotor

#include "vex.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include "util.h"

using namespace vex;

class SmoothMotor
{

private:
	motor : _motor;
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

		float increaseBy = (target - speed) / modSpeed;
		speed += increaseBy;

		if (floatWithin(speed, -stoppingThreshold, stoppingThreshold) && floatWithin(target, -stoppingThreshold, stoppingThreshold))
		{
			return Stop();
		}

		_motor.setVelocity(speed * (maxSpeed / 100), percent);
		_motor.spin(forward);
	}

	void Stop()
	{
		_motor.stop();
	}
}

#endif