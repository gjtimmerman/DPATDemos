package proxypattern;

import java.math.BigDecimal;

class OutOfStockException extends Exception
{
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public OutOfStockException(String message)
    {
    	super(message);
    }
}
class AlcoholNotAllowedException extends Exception
{
    /**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public AlcoholNotAllowedException(String message)
    { 
    	super(message);
    }
}
enum Drinks { Lemonade, CocaCola, Beer, Wine}

interface Shopable
{
    BigDecimal Buy(Drinks drink, int liters) throws AlcoholNotAllowedException, OutOfStockException;
}
class Shop implements Shopable
{
    private Shop()
    { }
    private int[] stock = new int[] {100,200,300,400};
    public BigDecimal Buy(Drinks drink, int liters) throws OutOfStockException
    {
        if (stock[drink.ordinal()] >= liters)
        {
            stock[drink.ordinal()] -= liters;
            return new BigDecimal((drink.ordinal() + 1) * 1.5 * liters);
        }
        else
            throw new OutOfStockException(liters + " of " + drink + " is not in store anymore");
    }
    public static Shopable Create(UserToken theUser)
    {
        return new ShopProxy(new Shop(), theUser);
    }
}
class UserToken
{
	public UserToken(String userName, int age)
	{
		UserName = userName;
		Age = age;
	}
    public String UserName;
    public int Age;
}

class ShopProxy implements Shopable
{
    private Shop realShop;
    private UserToken myUser;
    ShopProxy(Shop shop, UserToken user)
    {
        realShop = shop;
        myUser = user;
    }
    public BigDecimal Buy (Drinks drink, int liters) throws AlcoholNotAllowedException, OutOfStockException
    {
        if ((drink == Drinks.Beer || drink == Drinks.Wine) && myUser.Age < 18)
            throw new AlcoholNotAllowedException("You are " + myUser.Age + " old. You are not allowed to order " + drink);
        else
            return realShop.Buy(drink, liters);
    }

}



public class MainClass {

	public static void main(String[] args) {
        Shopable myShop = Shop.Create(new UserToken ( "Gert Jan", 16 ));
        try {
			System.out.println(myShop.Buy(Drinks.Beer, 10));
		} catch (AlcoholNotAllowedException e) {
			System.err.println("Sorry, Alcohol not allowed!");
		} catch (OutOfStockException e) {
			System.err.println("Sorry, this drink is out of stock!");
		}

	}

}
