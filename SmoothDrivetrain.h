#ifndef SmoothDrivetrain
#define SmoothDrivetrain

#include "vex.h"
#include "util.h"
#include <iostream>
#include <vex_task.h>

// Note:	robot-config.h must be modified to have
// extern motor_group LeftDriveSmart;
// extern motor_group RightDriveSmart;

using namespace vex;

class SmoothDrivetrain
{
private:
	Vector2 speed = Vector2(0, 0);
	void Stop() { Drivetrain.stop(); }

public:
	Vector2 maxSpeed = Vector2(100, 100);
	float acceleration = 20;

	float stoppingThreshold = 5;

	SmoothDrivetrain()
	{
	}

	void Drive(Vector2 target)
	{
		float xIncreaseBy = (target.x - speed.x) / acceleration;
		speed.x < target.x ? speed.x += xIncreaseBy : speed.x += xIncreaseBy;

		float yIncreaseBy = (target.y - speed.y) / acceleration;
		speed.y < target.y ? speed.y += yIncreaseBy : speed.y += yIncreaseBy;

		if (speed.within(stoppingThreshold) && target.within(stoppingThreshold))
		{
			return Stop();
		}

		LeftDriveSmart.setVelocity(speed.x * (maxSpeed.x / 100), percent);
		LeftDriveSmart.spin(forward);

		RightDriveSmart.setVelocity(speed.y * (maxSpeed.y / 100), percent);
		RightDriveSmart.spin(forward);
	};

	SpeedDisplay()
	{
		while (true)
		{

			Controller1.Screen.clearScreen();
			Controller1.Screen.newLine();
			std::ostringstream s;
			s << "Max Speed: " << maxSpeed.x;

			Controller1.Screen.print(s.str().c_str());

			this_thread::sleep_for(20);
		}
		return 0;
	}

	void ManageSpeed()
	{
		if (Controller1.ButtonUp.pressing() && maxSpeed.x + 10 < 105 && canToggle)
		{
			void *arg = &canToggle;
			vex::thread reset(ResetToggle, arg);

			maxSpeed.x += 10;
			maxSpeed.y += 10;
		}
		else if (Controller1.ButtonDown.pressing() && maxSpeed.x - 10 > 5 &&
				 canToggle)
		{
			void *arg = &canToggle;
			vex::thread reset(ResetToggle, arg);

			maxSpeed.x -= 10;
			maxSpeed.y -= 10;
		}
	}
}

#endif