package observer;

import java.util.ArrayList;

interface Observer
{
    void Update(EventArgs args);
}

abstract class EventArgs
{
	
}
class CarEventArgs extends EventArgs
{
    public int Speed;
}

class Car
{
    public void Accelerate(int delta)
    {
        speed += delta;
        if (speed > Speedlimit)
        {
            for (Observer obs : observers)
            {
            	CarEventArgs careventargs = new CarEventArgs();
            	careventargs.Speed = speed;
            	obs.Update(careventargs);
            }
        }
    }

    private int speed;
    public static int Speedlimit;
    public void Attach(Observer obs)
    {
        observers.add(obs);
    }
    private ArrayList<Observer> observers = new ArrayList<>();
}

class MyObserver implements Observer
{
    public void Update(EventArgs args)
    {
    	CarEventArgs cargs = null;
    	if (args instanceof CarEventArgs)
    	{
    		 cargs = (CarEventArgs)args;
    		 System.out.println("Speedlimit Exceeded: " + cargs.Speed);
    	}
    }
}



public class MainClass {

	public static void main(String[] args) {
        Car.Speedlimit = 130;
        Car myCar = new Car();
        MyObserver myObs = new MyObserver();
        MyObserver myObs2 = new MyObserver();
        myCar.Attach(myObs);
        myCar.Attach(myObs2);
        myCar.Accelerate(150);

	}

}
