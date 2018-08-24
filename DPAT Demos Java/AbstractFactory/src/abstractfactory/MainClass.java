package abstractfactory;

abstract class BicyclePart

{
    public abstract void Show();
}

abstract class Saddle extends BicyclePart
{
}

abstract class Pedal extends BicyclePart
{
}

abstract class FrontWheel extends BicyclePart
{
}

abstract class RearWheel extends BicyclePart
{
}

abstract class BicyclePartsFactory
{

    public abstract Saddle CreateSaddle();

    public abstract Pedal CreatePedal();

    public abstract FrontWheel CreateFrontWheel();

    public abstract RearWheel CreateRearWheel();

}



class BatavusSaddle extends Saddle

{
	@Override
    public void Show()
    {
        System.out.println("Batavus Saddle");
    }
}

class BatavusPedal extends Pedal
{
	@Override
    public void Show()
    {
		System.out.println("Batavus Pedal");
    }
}

class BatavusFrontWheel extends FrontWheel
{
	@Override
    public void Show()
    {
		System.out.println("Batavus FrontWheel");
    }

}

class BatavusRearWheel extends RearWheel
{
	@Override
    public void Show()
    {
		System.out.println("Batavus RearWheel");
    }
}



class BatavusFactory extends BicyclePartsFactory
{
	@Override
    public Saddle CreateSaddle()
    {
        return new BatavusSaddle();
    }
	@Override
    public Pedal CreatePedal()
    {
        return new BatavusPedal();
    }
	@Override
    public FrontWheel CreateFrontWheel()
    {
        return new BatavusFrontWheel();
    }
	@Override
    public RearWheel CreateRearWheel()
    {
        return new BatavusRearWheel();
    }

}



class GazelleSaddle extends Saddle
{
	@Override
    public void Show()
    {
		System.out.println("Gazelle Saddle");
    }
}

class GazellePedal extends Pedal
{
	@Override
    public void Show()
    {
    	System.out.println("Gazelle Pedal");
    }
}

class GazelleFrontWheel extends FrontWheel
{
	@Override
    public void Show()
    {
		System.out.println("Gazelle FrontWheel");
    }

}

class GazelleRearWheel extends RearWheel
{
	@Override
    public void Show()
    {
		System.out.println("Gazelle RearWheel");
    }
}



class GazelleFactory extends BicyclePartsFactory
{
	@Override
    public Saddle CreateSaddle()
    {
        return new GazelleSaddle();
    }
	
	@Override
    public Pedal CreatePedal()
    {
        return new GazellePedal();
    }
	@Override
    public FrontWheel CreateFrontWheel()
    {
        return new GazelleFrontWheel();
    }
	@Override
    public RearWheel CreateRearWheel()
    {
        return new GazelleRearWheel();
    }

}


public class MainClass {

	public static void main(String[] args) {
	    BicyclePartsFactory myFactory = new GazelleFactory();



	    BicyclePart[] myBicyclePartSet = new BicyclePart[4];

	    myBicyclePartSet[0] = myFactory.CreateSaddle();

	    myBicyclePartSet[1] = myFactory.CreatePedal();

	    myBicyclePartSet[2] = myFactory.CreateFrontWheel();

	    myBicyclePartSet[3] = myFactory.CreateRearWheel();

	    for (BicyclePart bp : myBicyclePartSet)
	        bp.Show();


	}

}
