package decorator;

import java.math.BigDecimal;
import java.util.ArrayList;

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
    protected ArrayList<IngredientAddition> Ingredients = new ArrayList<>();
    public PreparationStep(PreparationStep inner)
    {
        innerStep = inner;
    }
    protected String Procedure;
    protected BigDecimal CostPrice;
    
    public String GetProcedure()
    {
        return (innerStep != null ? innerStep.GetProcedure() + "\n" : "") + Procedure;
    }
    public BigDecimal GetCostPrice()
    {
        return (innerStep != null ? innerStep.GetCostPrice() : new BigDecimal("0.0")).add(CostPrice);
    }
    public ArrayList<IngredientAddition> GetIngredients()
    {
        ArrayList<IngredientAddition> innerIngredients = innerStep != null ? innerStep.GetIngredients() : new ArrayList<>();
        ArrayList<IngredientAddition> res = new ArrayList<>();
        res.addAll(innerIngredients);
        res.addAll(Ingredients);
        return res;
    }

}
class IngredientAddition
{
	public IngredientAddition(IngredientType Ingredient, BigDecimal amount)
	{
		this.Ingredient = Ingredient;
		this.amount = amount;
	}
    public IngredientType Ingredient;
    public BigDecimal amount ;
}

class GrindCoffee extends PreparationStep
{
    public GrindCoffee(IngredientType CoffeeType, BigDecimal amount)
    {
    	super(null);
        Ingredients.add(new IngredientAddition(CoffeeType, amount));
        Procedure = String.format("Take %s amount of coffee of type %s and grind it.", amount.toPlainString(), CoffeeType.toString());
        CostPrice = new BigDecimal("0.25").multiply(amount);
    }
}
class PutMilk extends PreparationStep
{
    public PutMilk(PreparationStep inner, BigDecimal amount)
    {
    	super(inner);
        Ingredients.add( new IngredientAddition(IngredientType.Milk, amount ));
        Procedure = String.format("Take %s amount of Milk and put it in a cup", amount.toPlainString());
        CostPrice = new BigDecimal("0.05").multiply(amount);
    }
}
class MakeCoffee extends PreparationStep
{
    public MakeCoffee(PreparationStep inner, Size actualSize)
    {
    	super(inner);
        Procedure = String.format("Take the grinded coffee and make coffee with the machine. Press button for size %s", actualSize.toString());
        CostPrice = new BigDecimal("0.02").multiply(new BigDecimal(actualSize.ordinal() + 1));
    }
}
class CustomPreparationStep extends PreparationStep
{
    public CustomPreparationStep(PreparationStep inner, ArrayList<IngredientAddition> ingredients, BigDecimal costPrice, String procedure)
    {
    	super(inner);
        Ingredients = ingredients;
        CostPrice = costPrice;
        Procedure = procedure;
    }
   
}
class Product
{
    private PreparationStep productionLine;
    public Product(String Name, PreparationStep productionLine)
    {
        this.Name = Name;
        this.productionLine = productionLine;
    }
    public String Name;
    public BigDecimal Price()
    {
    	return productionLine.GetCostPrice().multiply(new BigDecimal(2));
    }
    public ArrayList<IngredientAddition> IngredientAdditions()
    {
    	return productionLine.GetIngredients();
    }
}


public class MainClass {

	public static void main(String[] args) {
        Product[] products = new Product[3];
        PreparationStep product = new GrindCoffee(IngredientType.Espresso, new BigDecimal(10));
        product = new MakeCoffee(product, Size.Small);
        products[0] = new Product("Black Espresso Small", product);

        product = new GrindCoffee(IngredientType.Normal, new BigDecimal(15));
        product = new PutMilk(product, new BigDecimal(10));
        product = new MakeCoffee(product, Size.Medium);
        products[1] = new Product("Normal Coffee with milk Medium", product);


        product = new GrindCoffee(IngredientType.Caffeinefree, new BigDecimal(15));
        product = new PutMilk(product, new BigDecimal(10));
        product = new MakeCoffee(product, Size.Medium);
        products[2] = new Product("Caffeinefree with milk Medium", product);

        for (Product pr : products)
        {
            System.out.printf("%s costs %s\n",pr.Name,pr.Price().toPlainString());
            for (IngredientAddition ia : pr.IngredientAdditions())
                System.out.printf("Ingredient: %s, %s\n",ia.Ingredient.toString(),ia.amount.toPlainString());
        }

	}

}
