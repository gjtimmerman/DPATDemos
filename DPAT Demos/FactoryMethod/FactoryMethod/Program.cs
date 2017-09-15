using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FactoryMethod
{
    public abstract class Vehicle
    {
        public abstract void Drive();
        public abstract void SlowDown();
        public abstract void Stop();

        public static Vehicle CreateVehicle(VehiclePrefs prefs)
        {
            if (prefs.Motorized)
            {
                if (prefs.MaxSpeed > 200)
                    return new F1Car();
                else
                    return new CommodityCar();
            }
            else
                return new Bicycle();
        }
    }

    public struct VehiclePrefs
    {
        public bool Motorized;
        public uint MaxSpeed;
    }

    public abstract class Car : Vehicle
    {

    }
    public class F1Car: Car
    {
        public override void Drive()
        {
            Console.WriteLine("Driving Formula1 Car");
        }
        public override void SlowDown()
        {
            Console.WriteLine("Slowing down Formula1 Car");
        }
        public override void Stop()
        {
            Console.WriteLine("Stopping Formula1 Car");
        }
    }
    public class CommodityCar : Car
    {
        public override void Drive()
        {
            Console.WriteLine("Driving Commodity Car");
        }
        public override void SlowDown()
        {
            Console.WriteLine("Slowing down Commodity Car");
        }
        public override void Stop()
        {
            Console.WriteLine("Stopping Commodity Car");
        }
    }
    public class Bicycle : Vehicle
    {
        public override void Drive()
        {
            Console.WriteLine("Driving Bicycle");
        }
        public override void SlowDown()
        {
            Console.WriteLine("Slowing down Bicycle");
        }
        public override void Stop()
        {
            Console.WriteLine("Stopping Bicycle");
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            Vehicle[] vehicleSet = new Vehicle[3];
            vehicleSet[0] = Vehicle.CreateVehicle(new VehiclePrefs {Motorized = true, MaxSpeed = 150 });
            vehicleSet[1] = Vehicle.CreateVehicle(new VehiclePrefs { Motorized = false, MaxSpeed = 25 });
            vehicleSet[2] = Vehicle.CreateVehicle(new VehiclePrefs { Motorized = true, MaxSpeed = 250 });

            foreach (Vehicle v in vehicleSet)
                v.Drive();

            foreach (Vehicle v in vehicleSet)
                v.SlowDown();

            foreach (Vehicle v in vehicleSet)
                v.Stop();


        }
    }
}
