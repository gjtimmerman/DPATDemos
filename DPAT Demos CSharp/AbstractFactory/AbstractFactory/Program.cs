using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AbstractFactory
{
    class Program
    {
        public abstract class BicyclePart
        {
            public abstract void Show();

        }
        public abstract class Saddle : BicyclePart
        {
        }
        public abstract class Pedal : BicyclePart
        {

        }
        public abstract class FrontWheel : BicyclePart
        {

        }
        public abstract class RearWheel : BicyclePart
        {

        }
        public abstract class BicyclePartsFactory
        {
            public abstract Saddle CreateSaddle();
            public abstract Pedal CreatePedal();
            public abstract FrontWheel CreateFrontWheel();
            public abstract RearWheel CreateRearWheel();
        }

        public class BatavusSaddle : Saddle
        {
            public override void Show()
            {
                Console.WriteLine("Batavus Saddle");
            }
        }
        public class BatavusPedal : Pedal
        {
            public override void Show()
            {
                Console.WriteLine("Batavus Pedal");
            }
        }
        public class BatavusFrontWheel : FrontWheel
        {
            public override void Show()
            {
                Console.WriteLine("Batavus FrontWheel");
            }
        }
        public class BatavusRearWheel: RearWheel
        {
            public override void Show()
            {
                Console.WriteLine("Batavus RearWheel");
            }

        }

        public class BatavusFactory : BicyclePartsFactory
        {
            public override Saddle CreateSaddle()
            {
                return new BatavusSaddle();
            }
            public override Pedal CreatePedal()
            {
                return new BatavusPedal();
            }
            public override FrontWheel CreateFrontWheel()
            {
                return new BatavusFrontWheel();
            }
            public override RearWheel CreateRearWheel()
            {
                return new BatavusRearWheel();
            }
        }

        public class GazelleSaddle : Saddle
        {
            public override void Show()
            {
                Console.WriteLine("Gazelle Saddle");
            }
        }
        public class GazellePedal : Pedal
        {
            public override void Show()
            {
                Console.WriteLine("Gazelle Pedal");
            }
        }
        public class GazelleFrontWheel : FrontWheel
        {
            public override void Show()
            {
                Console.WriteLine("Gazelle FrontWheel");
            }
        }
        public class GazelleRearWheel : RearWheel
        {
            public override void Show()
            {
                Console.WriteLine("Gazelle RearWheel");
            }

        }

        public class GazelleFactory : BicyclePartsFactory
        {
            public override Saddle CreateSaddle()
            {
                return new GazelleSaddle();
            }
            public override Pedal CreatePedal()
            {
                return new GazellePedal();
            }
            public override FrontWheel CreateFrontWheel()
            {
                return new GazelleFrontWheel();
            }
            public override RearWheel CreateRearWheel()
            {
                return new GazelleRearWheel();
            }
        }

        static void Main(string[] args)
        {
            BicyclePartsFactory myFactory = new GazelleFactory();

            BicyclePart[] myBicyclePartSet = new BicyclePart[4];
            myBicyclePartSet[0] = myFactory.CreateSaddle();
            myBicyclePartSet[1] = myFactory.CreatePedal();
            myBicyclePartSet[2] = myFactory.CreateFrontWheel();
            myBicyclePartSet[3] = myFactory.CreateRearWheel();

            foreach (BicyclePart bp in myBicyclePartSet)
                bp.Show();
        }
    }
}
