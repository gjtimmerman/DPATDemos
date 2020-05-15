// Singleton.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>

using namespace std;

namespace Singleton
{
	class BicyclePart
	{
	public:
		virtual void Show() = 0;

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
		virtual Saddle* CreateSaddle() = 0;
		virtual Pedal* CreatePedal() = 0;
		virtual FrontWheel* CreateFrontWheel() = 0;
		virtual RearWheel* CreateRearWheel() = 0;
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
		Saddle* CreateSaddle() override
		{
			return new BatavusSaddle;
		}
		Pedal* CreatePedal() override
		{
			return new BatavusPedal;
		}
		FrontWheel* CreateFrontWheel() override
		{
			return new BatavusFrontWheel;
		}
		RearWheel* CreateRearWheel() override
		{
			return new BatavusRearWheel();
		}
	private:
		BatavusFactory()
		{}
		friend class BicycleFactory;
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
		Saddle* CreateSaddle() override
		{
			return new GazelleSaddle();
		}
		Pedal* CreatePedal() override
		{
			return new GazellePedal();
		}
		FrontWheel* CreateFrontWheel() override
		{
			return new GazelleFrontWheel();
		}
		RearWheel* CreateRearWheel() override
		{
			return new GazelleRearWheel();
		}
	private:
		GazelleFactory()
		{}
		friend class BicycleFactory;
	};

	class BicycleFactory
	{
	private:
		static BicyclePartsFactory* factoryInstance;
		BicycleFactory() = delete;
	public:
		template <typename T>
		static BicyclePartsFactory* GetBicycleFactory()
		{
			if (factoryInstance == nullptr)
				factoryInstance = new T();
			return factoryInstance;
		}
	};

	BicyclePartsFactory *BicycleFactory::factoryInstance = nullptr;

}

int main()
{
	using namespace Singleton;

	BicyclePartsFactory* myFactory = BicycleFactory::GetBicycleFactory<GazelleFactory>();

	array<BicyclePart*, 4> myBicyclePartSet;
	myBicyclePartSet[0] = myFactory->CreateSaddle();
	myBicyclePartSet[1] = myFactory->CreatePedal();
	myBicyclePartSet[2] = myFactory->CreateFrontWheel();
	myBicyclePartSet[3] = myFactory->CreateRearWheel();

	for (BicyclePart* bp : myBicyclePartSet)
		bp->Show();

	for (BicyclePart* bp : myBicyclePartSet)
		delete bp;
	delete myFactory;
	return 0;
}
