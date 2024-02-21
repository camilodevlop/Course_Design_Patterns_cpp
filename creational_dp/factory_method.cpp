// Created by Camilo Castillo on 02/02/2024
// Factory Method Pattern

#include <iostream>
#include <memory>

using namespace std;

//------------------------------------------------------------------------------

// Abstract base class (product)

class Vehicle
{
    public:
        virtual string VehicleType() const = 0;
        virtual ~Vehicle() {}
};

//------------------------------------------------------------------------------

// Concrete class (product)

class Car : public Vehicle
{
    public:
        string VehicleType() const override { return "Car"; }
        ~Car() override {}
};

class Bike : public Vehicle
{
    public:
        string VehicleType() const override { return "Bike"; }
        ~Bike() override {}
};

//------------------------------------------------------------------------------

// Abstract base class (creator)

class VehicleFactory
{
    public:
        virtual unique_ptr<Vehicle> createVehicle() = 0;
        virtual ~VehicleFactory() {}
};

//------------------------------------------------------------------------------

// Concrete class (creator)

class CarFactory : public VehicleFactory
{
    public:
        unique_ptr<Vehicle> createVehicle() override { return make_unique<Car>(); }
        ~CarFactory() override {}
};

class BikeFactory : public VehicleFactory
{
    public:
        unique_ptr<Vehicle> createVehicle() override { return make_unique<Bike>(); }
        ~BikeFactory() override {}
};

//------------------------------------------------------------------------------

class VehicleClient
{
    public:
        VehicleClient(VehicleFactory& factory) : mFactory(factory) {}
        void createVehicle() { mVehicle = mFactory.createVehicle(); }
        void printVehicleType() { cout << mVehicle->VehicleType() << endl; }
    private:
        VehicleFactory& mFactory;
        unique_ptr<Vehicle> mVehicle;
};

//------------------------------------------------------------------------------

int main()
{
    CarFactory carFactory;
    BikeFactory bikeFactory;

    VehicleClient carClient(carFactory);
    carClient.createVehicle();
    carClient.printVehicleType();

    VehicleClient bikeClient(bikeFactory);
    bikeClient.createVehicle();
    bikeClient.printVehicleType();

    return 0;
}

//------------------------------------------------------------------------------
