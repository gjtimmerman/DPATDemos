using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Facade
{
    public enum Direction { Left, Right };
    public class Car
    {
        public void CheckLeftMirror()
        {
            Console.WriteLine("Checking left mirror");
        }
        public void CheckRightMirror()
        {
            Console.WriteLine("Checking right mirror");
        }
        public void CheckLeftBlindSpot()
        {
            Console.WriteLine("Checking left blind spot");
        }
        public void CheckRightBlindSpot()
        {
            Console.WriteLine("Checking right blind spot");
        }
        public void SignalLeftDirectionIndicator()
        {
            Console.WriteLine("Signaling left direction indicator");
        }
        public void SignalRightDirectionIndicator()
        {
            Console.WriteLine("Signaling right direction indicator");
        }
        public void TurnSteeringWheel(Direction direct)
        {
            Console.WriteLine("Turning steering wheel to the " + direct.ToString());
        }

    }

    public class CarDriver
    {
        public CarDriver (Car car)
        {
            myCar = car;
        }
        private Car myCar;
        public void TurnLeft()
        {
            myCar.CheckLeftMirror();
            myCar.CheckLeftBlindSpot();
            myCar.SignalLeftDirectionIndicator();
            myCar.TurnSteeringWheel(Direction.Left);
        }
        public void TurnRight()
        {
            myCar.CheckRightMirror();
            myCar.CheckRightBlindSpot();
            myCar.SignalRightDirectionIndicator();
            myCar.TurnSteeringWheel(Direction.Right);

        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Car myCar = new Car();
            CarDriver driveCar = new CarDriver(myCar);
            driveCar.TurnLeft();
            driveCar.TurnRight();
        }
    }
}
