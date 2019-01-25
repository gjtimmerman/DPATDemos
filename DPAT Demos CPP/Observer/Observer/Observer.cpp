// Observer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace Observer
{
	struct EventArgs
	{

	};

	class IObserver
	{
	public:
		virtual void Update(const EventArgs &args) = 0;
	};

	struct CarEventArgs : public EventArgs
	{
	public:
		int newSpeed;
	};

	class Car
	{
	private:
		int speed;
		vector<IObserver *> observers;
	public:
		Car() : speed(0)
		{

		}
		void Accelerate(int delta)
		{
			speed += delta;
			if (speed > Speedlimit)
			{
				CarEventArgs cea;
				cea.newSpeed = speed;
				for(IObserver *obs : observers)
					obs->Update(cea);
			}
		}

		static int Speedlimit;
		void Attach(IObserver *obs)
		{
			observers.push_back(obs);
		}
	};

	class MyObserver : public IObserver
	{
	public:
		virtual void Update(const EventArgs &args) override
		{
			CarEventArgs cargs = static_cast<const CarEventArgs &>(args);
			cout << "Speedlimit Exceeded: " << cargs.newSpeed << endl;
		}
	};
}

using namespace Observer;

int Car::Speedlimit = 130;

int main()
{

	Car myCar;
	MyObserver *myObs = new MyObserver();
	MyObserver *myObs2 = new MyObserver();
	myCar.Attach(myObs);
	myCar.Attach(myObs2);
	myCar.Accelerate(150);
	return 0;
}

