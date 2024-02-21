// Created by Camilo Castillo on 09/02/2024
// Builder Factory Pattern

#include <iostream>
#include <memory>

//------------------------------------------------------------------------------

class Car
{
    public:
        void setBrand(const std::string& brand) { mBrand = brand; }
        void setSeats(int seats = 1) { mSeats = seats; }
        void setModel(const std::string& model) { mModel = model; }
        void setYear(const std::string& year) { mYear = year; }
        void setEngine(const std::string& engine) { mEngine = engine; }
        void setTransmission(const std::string& transmission) { mTransmission = transmission; }
        void setFuelType(const std::string& fuelType) { mFuelType = fuelType; }
        void setDriveType(const std::string& driveType) { mDriveType = driveType; }
        void setPrice(const std::string& price) { mPrice = price; }
        void setGps(bool gps = false) { mGps = gps; }

        void showCar() const
        {
            std::cout << "Brand: " << mBrand << std::endl;
            std::cout << "Model: " << mModel << std::endl;
            std::cout << "Year: " << mYear << std::endl;
            std::cout << "Engine: " << mEngine << std::endl;
            std::cout << "Transmission: " << mTransmission << std::endl;
            std::cout << "Fuel Type: " << mFuelType << std::endl;
            std::cout << "Drive Type: " << mDriveType << std::endl;
            std::cout << "Price: " << mPrice << std::endl;
        }
        
        ~Car() = default;

    private:
        std::string mBrand;
        int mSeats;
        std::string mModel;
        std::string mYear;
        std::string mEngine;
        std::string mTransmission;
        std::string mFuelType;
        std::string mDriveType;
        std::string mPrice;
        bool mGps;
};

class CarManual
{
    public:
        void setBrand(const std::string& brand) { mBrand = brand; }
        void setSeats(int seats = 1) { mSeats = seats; }
        void setModel(const std::string& model) { mModel = model; }
        void setYear(const std::string& year) { mYear = year; }
        void setEngine(const std::string& engine) { mEngine = engine; }
        void setTransmission(const std::string& transmission) { mTransmission = transmission; }
        void setFuelType(const std::string& fuelType) { mFuelType = fuelType; }
        void setDriveType(const std::string& driveType) { mDriveType = driveType; }
        void setPrice(const std::string& price) { mPrice = price; }
        void setGps(bool gps = false) { mGps = gps; }

        void showCar() const
        {
            std::cout << "Brand: " << mBrand << std::endl;
            std::cout << "Model: " << mModel << std::endl;
            std::cout << "Year: " << mYear << std::endl;
            std::cout << "Engine: " << mEngine << std::endl;
            std::cout << "Transmission: " << mTransmission << std::endl;
            std::cout << "Fuel Type: " << mFuelType << std::endl;
            std::cout << "Drive Type: " << mDriveType << std::endl;
            std::cout << "Price: " << mPrice << std::endl;
        }

        ~CarManual() = default;

    private:
        std::string mBrand;
        int mSeats;
        std::string mModel;
        std::string mYear;
        std::string mEngine;
        std::string mTransmission;
        std::string mFuelType;
        std::string mDriveType;
        std::string mPrice;
        bool mGps;
};

//------------------------------------------------------------------------------

template <typename T>
class Builder
{
    public:
        virtual Builder& reset() = 0;
        virtual Builder& buildBrand(const std::string& brand) = 0;
        virtual Builder& buildSeats(int seats) = 0;
        virtual Builder& buildModel(const std::string& model) = 0;
        virtual Builder& buildYear(const std::string& year) = 0;
        virtual Builder& buildEngine(const std::string& engine) = 0;
        virtual Builder& buildTransmission(const std::string& transmission) = 0;
        virtual Builder& buildFuelType(const std::string& fuelType) = 0;
        virtual Builder& buildDriveType(const std::string& driveType) = 0;
        virtual Builder& buildPrice(const std::string& price) = 0;
        virtual Builder& buildGps(bool gps) = 0;
        virtual std::unique_ptr<T> get() = 0;

        virtual ~Builder() = default;
};

class CarBuilder : public Builder<Car>
{
    public:
        virtual Builder& reset() override
        {
            mCar = std::make_unique<Car>();
            return *this;
        }
        Builder& buildBrand(const std::string& brand) override { mCar->setBrand(brand); return *this; }
        Builder& buildSeats(int seats) override { mCar->setSeats(seats); return *this; }
        Builder& buildModel(const std::string& model) override { mCar->setModel(model); return *this; }
        Builder& buildYear(const std::string& year) override { mCar->setYear(year); return *this; }
        Builder& buildEngine(const std::string& engine) override { mCar->setEngine(engine); return *this; }
        Builder& buildTransmission(const std::string& transmission) override { mCar->setTransmission(transmission); return *this; }
        Builder& buildFuelType(const std::string& fuelType) override { mCar->setFuelType(fuelType); return *this; }
        Builder& buildDriveType(const std::string& driveType) override { mCar->setDriveType(driveType); return *this; }
        Builder& buildPrice(const std::string& price) override { mCar->setPrice(price); return *this; }
        Builder& buildGps(bool gps) override { mCar->setGps(gps); return *this; }

        std::unique_ptr<Car> get() override { return std::move(mCar); }

        ~CarBuilder() override {}

        private:
            std::unique_ptr<Car> mCar = nullptr;
};

class CarManualBuilder : public Builder<CarManual>
{
    public:
        virtual Builder& reset() override
        {
            mCarManual = std::make_unique<CarManual>();
            return *this;
        }
        Builder& buildBrand(const std::string& brand) override { mCarManual->setBrand(brand); return *this; }
        Builder& buildSeats(int seats) override { mCarManual->setSeats(seats); return *this; }
        Builder& buildModel(const std::string& model) override { mCarManual->setModel(model); return *this; }
        Builder& buildYear(const std::string& year) override { mCarManual->setYear(year); return *this; }
        Builder& buildEngine(const std::string& engine) override { mCarManual->setEngine(engine); return *this; }
        Builder& buildTransmission(const std::string& transmission) override { mCarManual->setTransmission(transmission); return *this; }
        Builder& buildFuelType(const std::string& fuelType) override { mCarManual->setFuelType(fuelType); return *this; }
        Builder& buildDriveType(const std::string& driveType) override { mCarManual->setDriveType(driveType); return *this; }
        Builder& buildPrice(const std::string& price) override { mCarManual->setPrice(price); return *this; }
        Builder& buildGps(bool gps) override { mCarManual->setGps(gps); return *this; }

        std::unique_ptr<CarManual> get() override { return std::move(mCarManual); }

        ~CarManualBuilder() override {}

        private:
            std::unique_ptr<CarManual> mCarManual = nullptr;
};

//------------------------------------------------------------------------------

template <typename T>
class Director
{
    public:
        Director(Builder<T>& builder) : mBuilder(builder) {}
        
        void makeLamborghiniSUV()
        {
            mBuilder.reset();
            mBuilder.buildBrand("Lamborghini");
            mBuilder.buildSeats(4);
            mBuilder.buildModel("Urus");
            mBuilder.buildYear("2022");
            mBuilder.buildEngine("V8");
            mBuilder.buildTransmission("Automatic");
            mBuilder.buildFuelType("Gasoline");
            mBuilder.buildDriveType("AWD");
            mBuilder.buildPrice("$200,000");
            mBuilder.buildGps(true);
        }
        
        void makeFerrariSUV()
        {
            mBuilder.reset();
            mBuilder.buildBrand("Ferrari");
            mBuilder.buildSeats(4);
            mBuilder.buildModel("Purosangue");
            mBuilder.buildYear("2023");
            mBuilder.buildEngine("V12");
            mBuilder.buildTransmission("Automatic");
            mBuilder.buildFuelType("Gasoline");
            mBuilder.buildDriveType("AWD");
            mBuilder.buildPrice("$250,000");
            mBuilder.buildGps(true);
        }

        void makePorcheSUV()
        {
            mBuilder.reset();
            mBuilder.buildBrand("Porche");
            mBuilder.buildSeats(4);
            mBuilder.buildModel("Cayenne");
            mBuilder.buildYear("2022");
            mBuilder.buildEngine("V6");
            mBuilder.buildTransmission("Automatic");
            mBuilder.buildFuelType("Gasoline");
            mBuilder.buildDriveType("AWD");
            mBuilder.buildPrice("$150,000");
            mBuilder.buildGps(true);
        }

    private:
        Builder<T>& mBuilder;
        
};

//------------------------------------------------------------------------------

int main()
{
    CarBuilder carBuilder;
    Director<Car> carDirector(carBuilder);

    CarManualBuilder carManualBuilder;
    Director<CarManual> carManualDirector(carManualBuilder);


    std::cout << "\n\nBuilder Factory Pattern\n\n" << std::endl;

    std::cout << "\tLamborghini SUV" << std::endl;
    carDirector.makeLamborghiniSUV();
    std::unique_ptr<Car> lamborghiniSUV = carBuilder.get();
    lamborghiniSUV->showCar();

    std::cout << "\n\tLamborghini SUV Manual" << std::endl;
    carManualDirector.makeLamborghiniSUV();
    std::unique_ptr<CarManual> lamborghiniSUVManual = carManualBuilder.get();
    lamborghiniSUVManual->showCar();

    std::cout << "\n\n\tFerrari SUV" << std::endl;
    carDirector.makeFerrariSUV();
    std::unique_ptr<Car> ferrariSUV = carBuilder.get();
    ferrariSUV->showCar();

    std::cout << "\n\tFerrari SUV Manual" << std::endl;
    carManualDirector.makeFerrariSUV();
    std::unique_ptr<CarManual> ferrariSUVManual = carManualBuilder.get();
    ferrariSUVManual->showCar();

    std::cout << "\n\n\tPorche SUV" << std::endl;
    carDirector.makePorcheSUV();
    std::unique_ptr<Car> porcheSUV = carBuilder.get();
    porcheSUV->showCar();

    std::cout << "\n\tPorche SUV Manual" << std::endl;
    carManualDirector.makePorcheSUV();
    std::unique_ptr<CarManual> porcheSUVManual = carManualBuilder.get();
    porcheSUVManual->showCar();

    return 0;
}

//------------------------------------------------------------------------------
