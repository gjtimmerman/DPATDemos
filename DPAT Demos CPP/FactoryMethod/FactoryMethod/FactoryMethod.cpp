// FactoryMethod.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace FactoryMethod
{
	struct VehiclePrefs
	{
	public:
		bool Motorized;
		unsigned int MaxSpeed;
	};

	class Vehicle
	{
	public:
		virtual void Drive() = 0;
		virtual void SlowDown() = 0;
		virtual void Stop() = 0;
		static Vehicle *CreateVehicle(VehiclePrefs prefs);
	};


	class Car : public Vehicle
	{
	};

	class F1Car : public Car
	{
	public:
		void Drive() override
		{
			cout << "Driving Formula1 Car" << endl;
		}
		void SlowDown() override
		{
			cout << "Slowing down Formula1 Car" << endl;
		}
		void Stop() override
		{
			cout << "Stopping Formula1 Car" << endl;
		}
	};

	class CommodityCar : public Car
	{
	public:
		void Drive() override
		{
			cout << "Driving Commodity Car" << endl;
		}
		void SlowDown() override
		{
			cout << "Slowing down Commodity Car" << endl;
		}
		void Stop() override
		{
			cout << "Stopping Commodity Car" << endl;
		}
	};

	class Bicycle : public Vehicle
	{
	public:
		void Drive() override
		{
			cout << "Driving Bicycle" << endl;
		}
		void SlowDown() override
		{
			cout << "Slowing down Bicycle" << endl;
		}
		void Stop() override
		{
			cout << "Stopping Bicycle" << endl;
		}

	};

	Vehicle *Vehicle::CreateVehicle(VehiclePrefs prefs)
	{
		if (prefs.Motorized)
		{
			if (prefs.MaxSpeed > 200)
				return new F1Car();
			else
				return new CommodityCar();
		}
		else
			return new Bicycle();
	}

}

int main()
{
	using namespace FactoryMethod;
	array<Vehicle *,3>vehicleSet;

	vehicleSet[0] = Vehicle::CreateVehicle({ true,150 });

	vehicleSet[1] = Vehicle::CreateVehicle({ false,25 });

	vehicleSet[2] = Vehicle::CreateVehicle({ true,250 });

	for(Vehicle *v : vehicleSet)
		v->Drive();

	for(Vehicle *v : vehicleSet)
		v->SlowDown();

	for(Vehicle *v : vehicleSet)
		v->Stop();

	for (Vehicle *v : vehicleSet)
		delete v;
	return 0;
}

