#include "WPILib.h"

class Robot: public SampleRobot {
	Joystick stick;
	Joystick armStick;
	Talon mFL, mFR, mBL, mBR; //Classes to controll motor controllers
	VictorSP v; //Arm motor
	// update every 0.005 seconds/5 milliseconds.
	double kUpdatePeriod = 0.005;

public:
	Robot() :
			stick(1), armStick(0), mFL(0), mBL(2), mFR(3), mBR(1), v(4) // Initialize the Talon on channel 0,1,2,3 and victor on 4.
	{
	}

	//This function controls joystick
	void Run() {
		float m = .7;
		if(stick.GetRawButton(1)) m = 1; //Boost power
		else m = .7;
		float x = stick.GetX()*m; //How much  "X" to apply to motors
		float y = -stick.GetY()*m;	//How much "y"

		if (y > .1 || y <= -.1) { //If joystick is not at default state
			if (x > .005) {
				float m = 1 - x / 2;
				mFR.SetSpeed(-y * m);
				mBR.SetSpeed(-y * m);
				mFL.SetSpeed(y);
				mBL.SetSpeed(y);
			} else if (x < -.005) {
				x = -x;
				float m = 1 - x / 2;
				mFR.SetSpeed(-y);
				mBR.SetSpeed(-y);
				mFL.SetSpeed(y * m);
				mBL.SetSpeed(y * m);
			} else if (x < .005 && x > -.005) {
				mFR.SetSpeed(-y);
				mBR.SetSpeed(-y);
				mFL.SetSpeed(y);
				mBL.SetSpeed(y);
			} else {
				mFR.SetSpeed(0);
				mBR.SetSpeed(0);
				mFL.SetSpeed(0);
				mBL.SetSpeed(0);
			}
		}
//		else if (!y > .005 && !y <= -.005) {
//			if (x < 0) {
//				mFR.SetSpeed(x);
//				mBR.SetSpeed(x);
//			} else if (x > 0) {
//				mFL.SetSpeed(x);
//				mBL.SetSpeed(x);
//			}
//		}
		else {
			float z = stick.GetZ();
			mFR.SetSpeed(z);
			mBR.SetSpeed(z);
			mFL.SetSpeed(z);
			mBL.SetSpeed(z);
		}
	}
	void Arm(bool &arm) {
		float speed = armStick.GetRawAxis(2); //How much power to apply to arm
//		if (speed < 0.7) {
		speed = speed * (arm ? 1 : -1); //which direction
		if (armStick.GetRawButton(6)) {
			v.SetSpeed(.2 * (arm ? -1 : 1));
		} else
			v.SetSpeed(speed);
//		}
	}
	void Run2() {
		float y = stick.GetY();
		mFR.SetSpeed(-y);
		mBR.SetSpeed(-y);
		mFL.SetSpeed(y);
		mBL.SetSpeed(y);
	}
	void SlowArm() {
//		if (armStick.GetRawButton())
	}
	void OperatorControl() {
		bool arm = false;
		while (IsOperatorControl() && IsEnabled()) {
			// Set the motor controller's output.
			// This takes a number from -1 (100% speed in reverse) to +1 (100% speed forwards).
//			mFL.Set(stick.GetY());
//			Run();
			Run();
			if (armStick.GetRawButton(1)) //Check if we should activate arm and other stuff
				arm = true;
			if (armStick.GetRawButton(2))
				arm = false;
			Arm(arm);
			Wait(kUpdatePeriod);			// Wait 5ms for the next update.
		}
	}
	void Autonomous() { //What robot should do in autonmous
		v.SetSpeed(-.65);
		Wait(0.26);
		v.SetSpeed(.2);
//		Wait(0.3);
//		v.SetSpeed(0);
//		Wait(0.1);
//		v.SetSpeed(0);
		mFR.SetSpeed(-.5);
		mBR.SetSpeed(-.5);
		mFL.SetSpeed(.5);
		mBL.SetSpeed(.5);
		Wait(3.2);
		v.SetSpeed(0);
//		v.SetSpeed(-.7);
//		Wait(0.1);
//		v.SetSpeed(0);
//		Wait(1);
		mFR.SetSpeed(0);
		mBR.SetSpeed(0);
		mFL.SetSpeed(0);
		mBL.SetSpeed(0);
//		Wait(1);
//		mFR.SetSpeed(.5);
//		mBR.SetSpeed(.5);
//		mFL.SetSpeed(-.5);
//		mBL.SetSpeed(-.5);
//		Wait(2.8);
//		mFR.SetSpeed(0);
//		mBR.SetSpeed(0);
//		mFL.SetSpeed(0);
//		mBL.SetSpeed(0);
	}
	void Test() { //Test code
		v.Set(0.3);
	}
};

START_ROBOT_CLASS(Robot)

