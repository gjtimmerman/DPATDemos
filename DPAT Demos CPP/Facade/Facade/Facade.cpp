// Facade.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace Facade
{
	enum Direction { Left, Right };
	class Car
	{
	public:
		void CheckLeftMirror()
		{
			cout << "Checking left mirror" << endl;
		}
		void CheckRightMirror()
		{
			cout << "Checking right mirror" << endl;
		}
		void CheckLeftBlindSpot()
		{
			cout << "Checking left blind spot" << endl;
		}
		void CheckRightBlindSpot()
		{
			cout << "Checking right blind spot" << endl;
		}
		void SignalLeftDirectionIndicator()
		{
			cout << "Signaling left direction indicator" << endl;
		}
		void SignalRightDirectionIndicator()
		{
			cout << "Signaling right direction indicator" << endl;
		}
		void TurnSteeringWheel(Direction direct)
		{
			cout << "Turning steering wheel to the " << ((direct == Direction::Left) ? "left" : "right") << endl;
		}

	};

	class CarDriver
	{
	public:
		CarDriver(const Car &car)
		{
			myCar = car;
		}
		void TurnLeft()
		{
			myCar.CheckLeftMirror();
			myCar.CheckLeftBlindSpot();
			myCar.SignalLeftDirectionIndicator();
			myCar.TurnSteeringWheel(Direction::Left);
		}
		void TurnRight()
		{
			myCar.CheckRightMirror();
			myCar.CheckRightBlindSpot();
			myCar.SignalRightDirectionIndicator();
			myCar.TurnSteeringWheel(Direction::Right);

		}
	private:
		Car myCar;
	};

}


int main()
{
	using namespace Facade;

	Car myCar;
	CarDriver driveCar(myCar);
	driveCar.TurnLeft();
	driveCar.TurnRight();
	return 0;
}

