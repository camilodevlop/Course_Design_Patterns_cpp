// Created by Camilo Castillo on 07/02/2024
// Abstract Factory Pattern: Furniture (Client)

#include <iostream>
#include <memory>

#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/creational_dp/abstract_factory_factories.hpp>

using namespace std;

//------------------------------------------------------------------------------

class Client
{
    public:
        Client(unique_ptr<FurnitureFactory> factory) : mFactory(std::move(factory)) {}

        void createFurniture()
        {
            mChair = mFactory->createChair();
            mSofa = mFactory->createSofa();
            mCoffeeTable = mFactory->createCoffeeTable();
        }

        void showFurniture()
        {
            mChair->description();
            mSofa->description();
            mCoffeeTable->description();
        }

    private:
        unique_ptr<FurnitureFactory> mFactory;
        unique_ptr<Chair> mChair = nullptr;
        unique_ptr<Sofa> mSofa = nullptr;
        unique_ptr<CoffeeTable> mCoffeeTable = nullptr;
};

//------------------------------------------------------------------------------

int main()
{ 
    unique_ptr<FurnitureFactory> modernFactory = make_unique<ModernFurnitureFactory>();
    unique_ptr<FurnitureFactory> victorianFactory = make_unique<VictorianFurnitureFactory>();
    unique_ptr<FurnitureFactory> artDecoFactory = make_unique<ArtDecoFurnitureFactory>();

    cout << "\n\tModern Furniture" << endl;
    Client client1(std::move(modernFactory));
    client1.createFurniture();
    client1.showFurniture();

    cout << "\n\tVictorian Furniture" << endl;
    Client client2(std::move(victorianFactory));
    client2.createFurniture();
    client2.showFurniture();

    cout << "\n\tArt Deco Furniture" << endl;
    Client client3(std::move(artDecoFactory));
    client3.createFurniture();
    client3.showFurniture();

    return 0;
}

//------------------------------------------------------------------------------
