using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Observer
{
    public interface IObserver
    {
        void Update(EventArgs args);
    }

    public class CarEventArgs : EventArgs
    {
        public int Speed;
    }
//    public delegate void OnSpeedLimitExceeded(object sender, CarEventArgs args);

    public class Car
    {
        public void Accelerate(int delta)
        {
            speed += delta;
            if (speed > Speedlimit)
            {
                //                SpeedLimitExceeded(this, new CarEventArgs { Speed = speed });
                foreach (IObserver obs in observers)
                    obs.Update(new CarEventArgs { Speed = speed });
            }
        }

        private int speed;
        public static int Speedlimit;
        //        public event OnSpeedLimitExceeded SpeedLimitExceeded;
        public void Attach(IObserver obs)
        {
            observers.Add(obs);
        }
        private List<IObserver> observers = new List<IObserver>();
    }
    class MyObserver : IObserver
    {
        public void Update(EventArgs args)
        {
            CarEventArgs ?cargs = args as CarEventArgs;
            Console.WriteLine($"Speedlimit Exceeded: {cargs?.Speed}");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Car.Speedlimit = 130;
            Car myCar = new Car();
            MyObserver myObs = new MyObserver();
            MyObserver myObs2 = new MyObserver();
            myCar.Attach(myObs);
            myCar.Attach(myObs2);
//            myCar.SpeedLimitExceeded += (car, sargs) => { Console.WriteLine($"Speedlimit Exceeded: {sargs.Speed}"); };
            myCar.Accelerate(150);
        }
    }
}
