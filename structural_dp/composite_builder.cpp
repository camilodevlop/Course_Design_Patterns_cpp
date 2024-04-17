// Created by Camilo Castillo on 28/02/2024
// Composite Pattern: Composite Builder

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>

//------------------------------------------------------------------------------

class Car
{
    public:
        Car() = default;
        
        void setBrand(const std::string& brand) { brand_ = brand; }
        void setSites(int sites = 1) { sites_ = sites; }
        void setModel(const std::string& model) { model_ = model; }
        void setYear(const std::string& year) { year_ = year; }
        void setEngine(const std::string& engine) { engine_ = engine; }
        void setTransmission(const std::string& transmission) { transmission_ = transmission; }
        void setFuelType(const std::string& fuelType) { fuelType_ = fuelType; }
        void setDriveType(const std::string& driveType) { driveType_ = driveType; }
        void setPrice(const std::string& price) { price_ = price; }
        void setGPS(bool GPS = false) { GPS_ = GPS; }

        void showCar() const
        {
            std::cout << "Brand: " << brand_ << std::endl;
            std::cout << "Sites: " << sites_ << std::endl;
            std::cout << "Model: " << model_ << std::endl;
            std::cout << "Year: " << year_ << std::endl;
            std::cout << "Engine: " << engine_ << std::endl;
            std::cout << "Transmission: " << transmission_ << std::endl;
            std::cout << "Fuel Type: " << fuelType_ << std::endl;
            std::cout << "Drive Type: " << driveType_ << std::endl;
            std::cout << "Price: " << price_ << std::endl;
            std::cout << "GPS: " << (GPS_ ? "Yes" : "No") << std::endl;
        }
        
        ~Car() = default;

    private:
        std::string brand_;
        int sites_;
        std::string model_;
        std::string year_;
        std::string engine_;
        std::string transmission_;
        std::string fuelType_;
        std::string driveType_;
        std::string price_;
        bool GPS_;
};

//------------------------------------------------------------------------------

// Builder (CarParts) as interface.

class CarParts
{
    public:
        virtual void build(std::shared_ptr<Car>) = 0;
        virtual ~CarParts() = default;
};

//------------------------------------------------------------------------------

// Builder (CarParts) sons as leafs.

class CarBrand: public CarParts
{
    public:
        CarBrand(const std::string brand) : brand_(brand) {}
        void build(std::shared_ptr<Car> car) override { car->setBrand(brand_); }
        ~CarBrand() = default;

    private:
        std::string brand_;
};

class CarSites: public CarParts
{
    public:
        CarSites(const int sites): sites_(sites) {}
        void build(std::shared_ptr<Car> car) override { car->setSites(sites_); }
        ~CarSites() = default;

    private:
        int sites_;
};

class CarModel: public CarParts
{
    public:
        CarModel(const std::string model): model_(model) {}
        void build(std::shared_ptr<Car> car) override { car->setModel(model_); }
        ~CarModel() = default;

    private:
        std::string model_;
};

class CarYear: public CarParts
{
    public:
        CarYear(const std::string year): year_(year) {}
        void build(std::shared_ptr<Car> car) override { car->setYear(year_); }
        ~CarYear() = default;

    private:
        std::string year_;
};

class CarEngine: public CarParts
{
    public:
        CarEngine(const std::string engine): engine_(engine) {}
        void build(std::shared_ptr<Car> car) override { car->setEngine(engine_); }
        ~CarEngine() = default;

    private:
        std::string engine_;
};

class CarTransmission: public CarParts
{
    public:
        CarTransmission(const std::string transmission): transmission_(transmission) {}
        void build(std::shared_ptr<Car> car) override { car-> setTransmission(transmission_); }
    private:
        std::string transmission_;
};

class CarFuelType: public CarParts
{
    public:
        CarFuelType(const std::string fuelType): fuelType_(fuelType) {}
        void build(std::shared_ptr<Car> car) override { car->setFuelType(fuelType_); }
        ~CarFuelType() = default;

    private:
        std::string fuelType_;
};

class CarDriveType: public CarParts
{
    public:
        CarDriveType(const std::string driveType): driveType_(driveType) {}
        void build(std::shared_ptr<Car> car) override { car->setDriveType(driveType_); }
        ~CarDriveType() = default;

    private:
        std::string driveType_;
};

class CarPrice: public CarParts
{
    public:
        CarPrice(const std::string price): price_(price) {}
        void build(std::shared_ptr<Car> car) override { car->setPrice(price_); }
        ~CarPrice() = default;

    private:
        std::string price_;
};

class CarGPS: public CarParts
{
    public:
        CarGPS(const bool GPS) : GPS_(GPS) {}
        void build(std::shared_ptr<Car> car) override { car->setGPS(GPS_); }
        ~CarGPS() = default;

    private:
        bool GPS_;
};

//------------------------------------------------------------------------------

// Compound Builder (CompoundCarParts) as composite.

class CompoundCarParts: public CarParts
{
    public:
        CompoundCarParts() = default;
    
        // build() lets to build the car without passing car_ as argument.
        // car_ cannot be passed directly because it's a non-static data member.
        void build() {build(car_);}
        void build(std::shared_ptr<Car> car) override 
        { 
            for(auto& carPart: carParts_) carPart->build(car);
        }
        void reset() {car_ = std::make_shared<Car>();}
        void addCarPart(std::unique_ptr<CarParts>&&);
        void removeCarPart(std::unique_ptr<CarParts>);
        Car getCar() { return *car_;}

        ~CompoundCarParts() = default;

    private:
        std::vector<std::unique_ptr<CarParts>> carParts_;
        std::shared_ptr<Car> car_ = nullptr;
};

void CompoundCarParts::addCarPart(std::unique_ptr<CarParts>&& carPart) 
{ 
    carParts_.push_back(std::move(carPart));
}
void CompoundCarParts::removeCarPart(std::unique_ptr<CarParts> carPart)
{ 
    auto it = std::find(carParts_.begin(), carParts_.end(), carPart);
    if ( it != carParts_.end() )
        carParts_.erase(it);
    std::cout << "CarPartsBuilder not found." << std::endl;
}

//------------------------------------------------------------------------------

// Director (CompoundCarParts) as client.

class Director
{
    public:
        Director(CompoundCarParts& compoundCarParts) : compoundCarParts_(compoundCarParts) {}
        
        void buildLamborghiniSUV()
        {
            compoundCarParts_.reset();            
            compoundCarParts_.addCarPart(std::make_unique<CarBrand>("Lamborghini"));
            compoundCarParts_.addCarPart(std::make_unique<CarSites>(4));
            compoundCarParts_.addCarPart(std::make_unique<CarModel>("Urus"));
            compoundCarParts_.addCarPart(std::make_unique<CarYear>("2024"));
            compoundCarParts_.addCarPart(std::make_unique<CarEngine>("V8"));
            compoundCarParts_.addCarPart(std::make_unique<CarTransmission>("Automatic"));
            compoundCarParts_.addCarPart(std::make_unique<CarFuelType>("Gasoline"));
            compoundCarParts_.addCarPart(std::make_unique<CarDriveType>("AWD"));
            compoundCarParts_.addCarPart(std::make_unique<CarPrice>("$218,009"));
            compoundCarParts_.addCarPart(std::make_unique<CarGPS>(true));
            compoundCarParts_.build();
        }

        void buildFerrariSUV()
        {
            compoundCarParts_.reset();
            compoundCarParts_.addCarPart(std::make_unique<CarBrand>("Ferrari"));
            compoundCarParts_.addCarPart(std::make_unique<CarSites>(4));
            compoundCarParts_.addCarPart(std::make_unique<CarModel>("Purosangue"));
            compoundCarParts_.addCarPart(std::make_unique<CarYear>("2024"));
            compoundCarParts_.addCarPart(std::make_unique<CarEngine>("V12"));
            compoundCarParts_.addCarPart(std::make_unique<CarTransmission>("Automatic"));
            compoundCarParts_.addCarPart(std::make_unique<CarFuelType>("Gasoline"));
            compoundCarParts_.addCarPart(std::make_unique<CarDriveType>("AWD"));
            compoundCarParts_.addCarPart(std::make_unique<CarPrice>("$300,000"));
            compoundCarParts_.addCarPart(std::make_unique<CarGPS>(false));
            compoundCarParts_.build();
        }

        void buildPorcheSUV()
        {
            compoundCarParts_.reset();
            compoundCarParts_.addCarPart(std::make_unique<CarBrand>("Porche"));
            compoundCarParts_.addCarPart(std::make_unique<CarSites>(4));
            compoundCarParts_.addCarPart(std::make_unique<CarModel>("Cayenne"));
            compoundCarParts_.addCarPart(std::make_unique<CarYear>("2022"));
            compoundCarParts_.addCarPart(std::make_unique<CarEngine>("V6"));
            compoundCarParts_.addCarPart(std::make_unique<CarTransmission>("Manual"));
            compoundCarParts_.addCarPart(std::make_unique<CarFuelType>("Gasoline"));
            compoundCarParts_.addCarPart(std::make_unique<CarDriveType>("AWD"));
            compoundCarParts_.addCarPart(std::make_unique<CarPrice>("$150.000"));
            compoundCarParts_.addCarPart(std::make_unique<CarGPS>(true));
            compoundCarParts_.build();
        }

        ~Director() = default;

    private:
        CompoundCarParts& compoundCarParts_;
};

//------------------------------------------------------------------------------

int main()
{
    CompoundCarParts compoundCarParts;
    Director director(compoundCarParts);
    Car lamborghiniUrus, ferrariPurosangue, porcheCayenne;

    std::cout << "Builder-Composite patterns" << std::endl;

    director.buildLamborghiniSUV();
    lamborghiniUrus = compoundCarParts.getCar();
    std::cout << " Lamborghini Urus" << std::endl;
    lamborghiniUrus.showCar();

    director.buildFerrariSUV();
    ferrariPurosangue = compoundCarParts.getCar();
    std::cout << " Ferrari Purosangue " << std::endl;
    ferrariPurosangue.showCar();
    
    director.buildPorcheSUV();
    porcheCayenne = compoundCarParts.getCar();
    std::cout << " Porche Cayenne " << std::endl;
    porcheCayenne.showCar();

    return 0;
}

//------------------------------------------------------------------------------
