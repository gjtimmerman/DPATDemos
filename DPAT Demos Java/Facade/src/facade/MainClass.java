package facade;

enum Direction { Left, Right };

class Car
{
    public void CheckLeftMirror()
    {
        System.out.println("Checking left mirror");
    }
    public void CheckRightMirror()
    {
    	System.out.println("Checking right mirror");
    }
    public void CheckLeftBlindSpot()
    {
    	System.out.println("Checking left blind spot");
    }
    public void CheckRightBlindSpot()
    {
    	System.out.println("Checking right blind spot");
    }
    public void SignalLeftDirectionIndicator()
    {
    	System.out.println("Signaling left direction indicator");
    }
    public void SignalRightDirectionIndicator()
    {
    	System.out.println("Signaling right direction indicator");
    }
    public void TurnSteeringWheel(Direction direct)
    {
    	System.out.println("Turning steering wheel to the " + direct.toString());
    }

}

class CarDriver
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


public class MainClass {
	public static void main(String [] args)
	{
        Car myCar = new Car();
        CarDriver driveCar = new CarDriver(myCar);
        driveCar.TurnLeft();
        driveCar.TurnRight();
	}
}
