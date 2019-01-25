// AbstractFactory.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace AbstractFactory
{
		class BicyclePart
		{
		public:
			virtual void Show()=0;

		};
		class Saddle : public BicyclePart
		{
		};
		class Pedal : public BicyclePart
		{
		};
		class FrontWheel : public BicyclePart
		{
		};
		class RearWheel : public BicyclePart
		{
		};
		class BicyclePartsFactory
		{
		public:
			virtual Saddle *CreateSaddle()=0;
			virtual Pedal *CreatePedal()=0;
			virtual FrontWheel *CreateFrontWheel()=0;
			virtual RearWheel *CreateRearWheel()=0;
		};

		class BatavusSaddle : public Saddle
		{
		public:
			void Show() override
			{
				cout << "Batavus Saddle" << endl;
			}
		};
		class BatavusPedal : public Pedal
		{
		public:
			void Show() override
			{
				cout << "Batavus Pedal" << endl;
			}
		};
		class BatavusFrontWheel : public FrontWheel
		{
		public:
			void Show() override
			{
				cout << "Batavus FrontWheel" << endl;
			}
		};
		class BatavusRearWheel : public RearWheel
		{
		public:
			void Show() override
			{
				cout << "Batavus RearWheel" << endl;
			}

		};

		class BatavusFactory : public BicyclePartsFactory
		{
		public:
			Saddle *CreateSaddle() override
			{
				return new BatavusSaddle;
			}
			Pedal *CreatePedal() override
			{
				return new BatavusPedal;
			}
			FrontWheel *CreateFrontWheel() override
			{
				return new BatavusFrontWheel;
			}
			RearWheel *CreateRearWheel() override
			{
				return new BatavusRearWheel();
			}
		};

		class GazelleSaddle : public Saddle
		{
		public:
			void Show() override
			{
				cout << "Gazelle Saddle" << endl;
			}
		};
		class GazellePedal : public Pedal
		{
		public:
			void Show() override
			{
				cout << "Gazelle Pedal" << endl;
			}
		};
		class GazelleFrontWheel : public FrontWheel
		{
		public:
			void Show() override
			{
				cout << "Gazelle FrontWheel" << endl;
			}
		};

		class GazelleRearWheel : public RearWheel
		{
		public:
			void Show() override
			{
				cout << "Gazelle RearWheel" << endl;
			}

		};

		class GazelleFactory : public BicyclePartsFactory
		{
		public:
			Saddle *CreateSaddle() override
			{
				return new GazelleSaddle();
			}
			Pedal *CreatePedal() override
			{
				return new GazellePedal();
			}
			FrontWheel *CreateFrontWheel() override
			{
				return new GazelleFrontWheel();
			}
			RearWheel *CreateRearWheel() override
			{
				return new GazelleRearWheel();
			}
		};

}

int main()
{
	using namespace AbstractFactory;

	BicyclePartsFactory *myFactory = new GazelleFactory;

	array<BicyclePart*,4> myBicyclePartSet;
	myBicyclePartSet[0] = myFactory->CreateSaddle();
	myBicyclePartSet[1] = myFactory->CreatePedal();
	myBicyclePartSet[2] = myFactory->CreateFrontWheel();
	myBicyclePartSet[3] = myFactory->CreateRearWheel();

	for(BicyclePart *bp : myBicyclePartSet)
		bp->Show();

	for (BicyclePart *bp : myBicyclePartSet)
		delete bp;
	delete myFactory;
	return 0;
}

