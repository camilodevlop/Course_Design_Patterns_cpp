// Created by Camilo Castillo on 05/02/2024
// Factory Method Pattern reusing existing objects

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>

using namespace std;

//------------------------------------------------------------------------------

class Availability
{
    public:
        virtual bool isAvailable() const = 0;
        virtual void setAvailability(bool availability) = 0;

        virtual ~Availability() {}
};

class VehicleAvailability : public Availability
{
    public:
        VehicleAvailability() : mAvailability(true) {}
        bool isAvailable() const override { return mAvailability; }
        void setAvailability(bool availability) override { mAvailability = availability; }

        ~VehicleAvailability() override {}

    private:
        bool mAvailability;
};

//------------------------------------------------------------------------------

// Abstract base class (product)

class Vehicle
{
    public:
        virtual string VehicleType() const = 0;
        virtual bool isAvailable() const = 0;
        virtual void setAvailability(bool availability) = 0;

        virtual ~Vehicle() {}
};

//------------------------------------------------------------------------------

// Concrete class (product)

class Car : public Vehicle
{
    public:
        VehicleAvailability mAvailability;

        string VehicleType() const override { return "Car"; }
        bool isAvailable() const override { return mAvailability.isAvailable(); }
        void setAvailability(bool availability) override { mAvailability.setAvailability(availability); }

        ~Car() override {}

};

class Bike : public Vehicle
{
    public:
        VehicleAvailability mAvailability;

        string VehicleType() const override { return "Bike"; }
        bool isAvailable() const override { return mAvailability.isAvailable(); }
        void setAvailability(bool availability) override { mAvailability.setAvailability(availability); }
        ~Bike() override {}
};


//------------------------------------------------------------------------------

// Abstract base class (creator)

class VehicleFactory
{
    public:
        virtual shared_ptr<Vehicle> createVehicle() = 0;
        virtual ~VehicleFactory() {}
};

//------------------------------------------------------------------------------

// Concrete class (creator)

class CarFactory : public VehicleFactory
{
    public:
        shared_ptr<Vehicle> createVehicle() override { return make_shared<Car>(); }
        ~CarFactory() override {}
};

class BikeFactory : public VehicleFactory
{
    public:
        shared_ptr<Vehicle> createVehicle() override { return make_shared<Bike>(); }
        ~BikeFactory() override {}
};

//------------------------------------------------------------------------------

class VehicleClient
{
    public:
        VehicleClient(VehicleFactory& factory, int vehiclePoolSize) : 
                        mFactory(factory), mVehiclePoolSize(vehiclePoolSize) {}
        shared_ptr<Vehicle> createVehicle();

    private:
        VehicleFactory& mFactory;
        vector<shared_ptr<Vehicle>> mVehicles;
        shared_ptr<Vehicle> mVehicle;
        int mVehiclePoolSize;
};

shared_ptr<Vehicle> VehicleClient::createVehicle()
{
    if (mVehicles.size() == mVehiclePoolSize)
    {
        for (auto& vehicle : mVehicles)
        {
            if (vehicle -> isAvailable())
            {
                mVehicle = vehicle;
                return mVehicle;
            }
        }

        cout << "Wait: No available vehicles" << endl;
        return nullptr;
    }
    
    mVehicle = mFactory.createVehicle();
    mVehicles.push_back(mVehicle);
    return mVehicles.back();
}

//------------------------------------------------------------------------------

int main()
{
    CarFactory carFactory;
    VehicleClient carClient(carFactory, 2);

    shared_ptr<Vehicle> car1 = carClient.createVehicle();
    shared_ptr<Vehicle> car2 = carClient.createVehicle();

    car1 -> setAvailability(false);
    car2 -> setAvailability(false);
    
    shared_ptr<Vehicle> car3 = carClient.createVehicle();

    cout << "\n\t car2: " << car2 << " car3: " << car3 << (car3 == car2 ? " == " : " != ") << endl;

    return 0;
}

//------------------------------------------------------------------------------
