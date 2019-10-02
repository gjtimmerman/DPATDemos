using System;
using System.Collections.Generic;

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
    }
    enum Size
    {
        Small,
        Medium,
        Large
    }
    class PreparationStep
    {
        private PreparationStep innerStep;
        protected List<IngredientAddition> Ingredients = new List<IngredientAddition>();
        public PreparationStep(PreparationStep inner)
        {
            innerStep = inner;
        }
        protected string Procedure { get; set; }
        protected decimal CostPrice { get; set; }
        public string GetProcedure()
        {
            return (innerStep?.GetProcedure() + "\n" ?? "") + Procedure;
        }
        public decimal GetCostPrice()
        {
            return (innerStep?.GetCostPrice() ?? 0.0m) + CostPrice;
        }
        public List<IngredientAddition> GetIngredients()
        {
            List<IngredientAddition> innerIngredients = innerStep?.GetIngredients() ?? new List<IngredientAddition>();
            List<IngredientAddition> res = new List<IngredientAddition>();
            res.AddRange(innerIngredients);
            res.AddRange(Ingredients);
            return res;
        }

    }
    class IngredientAddition
    {
        public IngredientType Ingredient { get; set; }
        public decimal amount { get; set; }
    }

    class GrindCoffee : PreparationStep
    {
        public GrindCoffee(IngredientType CoffeeType, decimal amount) : base(null)
        {
            Ingredients.Add(new IngredientAddition { Ingredient = CoffeeType, amount = amount });
            Procedure = string.Format("Take {0} amount of coffee of type {1} and grind it.", amount, CoffeeType);
            CostPrice = 0.25m * amount;
        }
    }
    class PutMilk : PreparationStep
    {
        public PutMilk(PreparationStep inner, decimal amount) : base(inner)
        {
            Ingredients.Add( new IngredientAddition { Ingredient = IngredientType.Milk, amount = amount });
            Procedure = string.Format("Take {0} amount of Milk and put it in a cup", amount);
            CostPrice = 0.05m * amount;
        }
    }
    class MakeCoffee : PreparationStep
    {
        public MakeCoffee(PreparationStep inner, Size actualSize) : base (inner)
        {
            Procedure = string.Format("Take the grinded coffee and make coffee with the machine. Press button for size {0}", actualSize);
            CostPrice = 0.02m * ((int)actualSize + 1);
        }
    }
    class CustomPreparationStep : PreparationStep
    {
        public CustomPreparationStep(PreparationStep inner, List<IngredientAddition> ingredients, decimal costPrice, string procedure): base(inner)
        {
            Ingredients = ingredients;
            CostPrice = costPrice;
            Procedure = procedure;
        }
       
    }
    class Product
    {
        private PreparationStep productionLine;
        public Product(string Name, PreparationStep productionLine)
        {
            this.Name = Name;
            this.productionLine = productionLine;
        }
        public string Name { get; set; }
        public decimal Price() => productionLine.GetCostPrice() * 2;
        public List<IngredientAddition> IngredientAdditions => productionLine.GetIngredients();
    }
    class Program
    {
        static void Main(string[] args)
        {
            Product[] products = new Product[3];
            PreparationStep product = new GrindCoffee(IngredientType.Espresso, 10m);
            product = new MakeCoffee(product, Size.Small);
            products[0] = new Product("Black Espresso Small", product);

            product = new GrindCoffee(IngredientType.Normal, 15m);
            product = new PutMilk(product, 10m);
            product = new MakeCoffee(product, Size.Medium);
            products[1] = new Product("Normal Coffee with milk Medium", product);


            product = new GrindCoffee(IngredientType.Caffeinefree, 15);
            product = new PutMilk(product, 10m);
            product = new MakeCoffee(product, Size.Medium);
            products[2] = new Product("Caffeinefree with milk Medium", product);

            foreach (Product pr in products)
            {
                Console.WriteLine($"{pr.Name} costs {pr.Price()}");
                foreach (IngredientAddition ia in pr.IngredientAdditions)
                    Console.WriteLine($"Ingredient: {ia.Ingredient}, {ia.amount}");
            }

        }
    }
}
