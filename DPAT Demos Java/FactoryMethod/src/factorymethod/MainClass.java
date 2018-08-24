package factorymethod;

abstract class Vehicle
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

class VehiclePrefs
{
    public boolean Motorized;
    public int MaxSpeed;
}

abstract class Car extends Vehicle
{

}
class F1Car extends Car
{
	@Override
    public void Drive()
    {
        System.out.println("Driving Formula1 Car");
    }
	@Override
    public void SlowDown()
    {
		System.out.println("Slowing down Formula1 Car");
    }
	@Override
    public void Stop()
    {
		System.out.println("Stopping Formula1 Car");
    }
}

class CommodityCar extends Car
{
	@Override
    public void Drive()
    {
		System.out.println("Driving Commodity Car");
    }
	@Override
    public void SlowDown()
    {
		System.out.println("Slowing down Commodity Car");
    }
	@Override
    public void Stop()
    {
		System.out.println("Stopping Commodity Car");
    }
}

class Bicycle extends Vehicle
{
	@Override
    public void Drive()
    {
		System.out.println("Driving Bicycle");
    }
	@Override
    public void SlowDown()
    {
		System.out.println("Slowing down Bicycle");
    }
	@Override
    public void Stop()
    {
		System.out.println("Stopping Bicycle");
    }

}

public class MainClass {

	public static void main(String[] args) {
        Vehicle[] vehicleSet = new Vehicle[3];
        VehiclePrefs vehicleprefs = new VehiclePrefs();
        vehicleprefs.Motorized = true;
        vehicleprefs.MaxSpeed = 150;
        vehicleSet[0] = Vehicle.CreateVehicle(vehicleprefs);
        vehicleprefs = new VehiclePrefs();
        vehicleprefs.Motorized = false;
        vehicleprefs.MaxSpeed = 25;
        vehicleSet[1] = Vehicle.CreateVehicle(vehicleprefs);
        vehicleprefs = new VehiclePrefs();
        vehicleprefs.Motorized = true;
        vehicleprefs.MaxSpeed = 250;
        
        vehicleSet[2] = Vehicle.CreateVehicle(vehicleprefs);

        for (Vehicle v : vehicleSet)
            v.Drive();

        for (Vehicle v : vehicleSet)
            v.SlowDown();

        for (Vehicle v : vehicleSet)
            v.Stop();

	}

}
