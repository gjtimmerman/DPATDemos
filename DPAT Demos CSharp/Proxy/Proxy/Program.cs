using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Proxy
{
    public class OutOfStockException : ApplicationException
    {
        public OutOfStockException(string message) : base(message)
        { }
    }
    public class AlcoholNotAllowedException : ApplicationException
    {
        public AlcoholNotAllowedException(string message) : base (message)
        { }
    }
    public enum Drinks { Lemonade, CocaCola, Beer, Wine}
    public interface IShop
    {
        decimal Buy(Drinks drink, int liters);
    }
    class Shop : IShop
    {
        private Shop()
        { }
        private int[] stock = new int[] {100,200,300,400};
        public decimal Buy(Drinks drink, int liters)
        {
            if (stock[(int)drink] >= liters)
            {
                stock[(int)drink] -= liters;
                return ((int)drink + 1) * 1.5M * liters;
            }
            else
                throw new OutOfStockException(liters + " of " + drink + " is not in store anymore");
        }
        public static IShop Create(UserToken theUser)
        {
            return new ShopProxy(new Shop(), theUser);
        }
    }
    public struct UserToken
    {
        public string UserName;
        public int Age;
    }

    internal class ShopProxy : IShop
    {
        private Shop realShop;
        private UserToken myUser;
        internal ShopProxy(Shop shop, UserToken user)
        {
            realShop = shop;
            myUser = user;
        }
        public decimal Buy (Drinks drink, int liters)
        {
            if ((drink == Drinks.Beer || drink == Drinks.Wine) && myUser.Age < 18)
                throw new AlcoholNotAllowedException("You are " + myUser.Age + " old. You are not allowed to order " + drink);
            else
                return realShop.Buy(drink, liters);
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            IShop myShop = Shop.Create(new UserToken { UserName = "Gert Jan", Age = 18 });
            Console.WriteLine(myShop.Buy(Drinks.Beer, 10));
        }
    }
}
