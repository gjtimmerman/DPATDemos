// Proxy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

namespace Proxy
{
	struct ApplicationException
	{
	public:
		ApplicationException(string message) : message(message)
		{ }
		string getMessage()
		{
			return message;
		}
	private:
		string message;

	};
	struct OutOfStockException : public ApplicationException
	{
	public:
		OutOfStockException(string message) : ApplicationException(message)
		{ }
	};
	struct AlcoholNotAllowedException : public ApplicationException
	{
	public:
		AlcoholNotAllowedException(string message) : ApplicationException(message)
		{ }
	};
	enum Drinks { Lemonade, CocaCola, Beer, Wine };
	string drinkStrings[] = { "Lemonade", "Coca Cola", "Beer", "Wine" };

	class IShop
	{
	public:
		virtual long Buy(Drinks drink, int liters) = 0;
	};

	struct UserToken
	{
	public:
		UserToken(string UserName, int Age) : UserName(UserName), Age(Age)
		{

		}
		string UserName;
		int Age;
	};

	class Shop;

	class ShopProxy : public IShop
	{
	private:
		Shop *realShop;
		const UserToken *myUser;
	public:
		ShopProxy(Shop *shop, const UserToken *user)
		{
			realShop = shop;
			myUser = user;
		}
		virtual long Buy(Drinks drink, int liters) override;
		virtual ~ShopProxy();
	};

	class Shop : public IShop
	{
	private:
		Shop()
		{
		}
		int stock[4] = {100, 200, 300, 400};
	public:
		virtual long Buy(Drinks drink, int liters) override
		{
			if (stock[(int)drink] >= liters)
			{
				stock[(int)drink] -= liters;
				return ((int)drink + 1) * 150L * liters;
			}
			else
				throw OutOfStockException(to_string(liters) + "liters of " + drinkStrings[(int)drink] + " is not in store anymore");
		}
		static IShop *Create(const UserToken *theUser)
		{
			return new ShopProxy(new Shop(), theUser);
		}
	};
}

using namespace Proxy;

long ShopProxy::Buy(Drinks drink, int liters)
{
	if ((drink == Drinks::Beer || drink == Drinks::Wine) && myUser->Age < 18)
		throw AlcoholNotAllowedException("You are " + to_string(myUser->Age) + " old. You are not allowed to order " + drinkStrings[(int)drink]);
	else
		return realShop->Buy(drink, liters);
}

ShopProxy:: ~ShopProxy()
{
	delete realShop;
	delete myUser;
}


int main()
{
	using namespace Proxy;
	IShop *myShop = Shop::Create(new UserToken("Gert Jan", 17 ));
	try
	{
		long price = myShop->Buy(Drinks::CocaCola, 10);
		cout << price / 100 << "." << price % 100 << endl;
	}
	catch (ApplicationException ae)
	{
		cout << ae.getMessage() << endl;
	}
	delete myShop;
    return 0;
}

