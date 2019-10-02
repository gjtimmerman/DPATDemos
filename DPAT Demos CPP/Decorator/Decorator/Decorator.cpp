// Decorator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace Decorator
{
	enum IngredientType
	{
		Normal,
		Espresso,
		Caffeinefree,
		Milk,
		Sugar,
		Honey,
	};
	string IngredientTypeStrings[] = { "Normal","Espresso","Caffeinefree","Milk","Sugar","Honey" };

	enum Size
	{
		Small,
		Medium,
		Large
	};
	string SizeStrings[] = { "Small", "Medium", "Large" };

	struct IngredientAddition
	{
	public:
		IngredientAddition(IngredientType ingredient, double amount) : Ingredient(ingredient), amount(amount)
		{
		}
		IngredientType Ingredient;
		double amount;
	};

	class PreparationStep
	{
	private:
		PreparationStep* innerStep;
	protected:
		vector<IngredientAddition> Ingredients;
		string Procedure;
		double CostPrice = 0;
	public:
		PreparationStep(PreparationStep* inner)
		{
			innerStep = inner;
		}
		string GetProcedure()
		{
			return (innerStep != 0 ? innerStep->GetProcedure() + "\n" : "") + Procedure;
		}
		double GetCostPrice()
		{
			return (innerStep != 0 ? innerStep->GetCostPrice() : 0.0) + CostPrice;
		}
		vector<IngredientAddition> GetIngredients()
		{
			vector<IngredientAddition> res = Ingredients;
			if (innerStep == 0)
				return res;
			for (IngredientAddition ingr : innerStep->GetIngredients())
				res.push_back(ingr);
			return res;
		}

	};

	class GrindCoffee : public PreparationStep
	{
	public:
		GrindCoffee(IngredientType CoffeeType, double amount) : PreparationStep(0)
		{
			Ingredients.push_back(IngredientAddition(CoffeeType, amount));
			char buf[80];
			snprintf(buf, 80, "Take %f amount of coffee of type %s and grind it.", amount, IngredientTypeStrings[CoffeeType].c_str());
			Procedure = string(buf);
			CostPrice = 0.25 * amount;
		}
	};

	class PutMilk : public PreparationStep
	{
	public:
		PutMilk(PreparationStep inner, double amount) : PreparationStep(inner)
		{
			Ingredients.push_back(IngredientAddition(Milk, amount));
			char buf[80];
			snprintf(buf, 80, "Take %f amount of Milk and put it in a cup", amount);
			Procedure = string(buf);
			CostPrice = 0.05 * amount;
		}
	};

	class MakeCoffee : public PreparationStep
	{
	public:
		MakeCoffee(PreparationStep inner, Size actualSize) : PreparationStep(inner)
		{
			char buf[80];
			snprintf(buf, 80, "Take the grinded coffee and make coffee with the machine. Press button for size %s", SizeStrings[actualSize].c_str());
			Procedure = string(buf);
			CostPrice = 0.02 * (actualSize + 1);
		}
	};

	class CustomPreparationStep : public PreparationStep
	{
	public:
		CustomPreparationStep(PreparationStep inner, vector<IngredientAddition> ingredients, double costPrice, string procedure) : PreparationStep(inner)
		{
			Ingredients = ingredients;
			CostPrice = costPrice;
			Procedure = procedure;
		}

	};

	class Product
	{
	private:
		PreparationStep* productionLine;
	public:
		Product(string Name, PreparationStep *productionLine) : Name(Name), productionLine(productionLine)
		{
		}
		string Name;
		double Price()
		{
			return productionLine->GetCostPrice() * 2;
		}
		vector<IngredientAddition> IngredientAdditions()
		{
			return productionLine->GetIngredients();
		}
	};
};

using namespace Decorator;

int main()
{
	Product *products[3];
	PreparationStep *product = new GrindCoffee(Espresso, 10);
	product = new MakeCoffee(product, Small);
	products[0] = new Product("Black Espresso Small", product);

	product = new GrindCoffee(Normal, 15);
	product = new PutMilk(product, 10);
	product = new MakeCoffee(product, Medium);
	products[1] = new Product("Normal Coffee with milk Medium", product);


	product = new GrindCoffee(Caffeinefree, 15);
	product = new PutMilk(product, 10);
	product = new MakeCoffee(product, Medium);
	products[2] = new Product("Caffeinefree with milk Medium", product);

	for(Product *pr : products)
	{
		cout << pr->Name << " costs " << pr->Price() << endl;
		for(IngredientAddition ia : pr->IngredientAdditions())
			cout << "Ingredient: " << IngredientTypeStrings[ia.Ingredient] << ", " << ia.amount << endl;
	}
}

