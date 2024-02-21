// Created by Camilo Castillo on 07/02/2024
// Abstract Factory Pattern: Furniture (Factories)

#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/creational_dp/abstract_factory_furniture.hpp>
#include <memory>

//------------------------------------------------------------------------------

class FurnitureFactory
{
    public:
        virtual unique_ptr<Chair> createChair() = 0;
        virtual unique_ptr<Sofa> createSofa() = 0;
        virtual unique_ptr<CoffeeTable> createCoffeeTable() = 0;

        virtual ~FurnitureFactory() = default;
};

//------------------------------------------------------------------------------

class ModernFurnitureFactory : public FurnitureFactory
{
    public:
        unique_ptr<Chair> createChair() override { return make_unique<ModernChair>(); }
        unique_ptr<Sofa> createSofa() override { return make_unique<ModernSofa>(); }
        unique_ptr<CoffeeTable> createCoffeeTable() override { return make_unique<ModernCoffeeTable>(); }

        ~ModernFurnitureFactory() override {}
};

class VictorianFurnitureFactory : public FurnitureFactory
{
    public:
        unique_ptr<Chair> createChair() override { return make_unique<VictorianChair>(); }
        unique_ptr<Sofa> createSofa() override { return make_unique<VictorianSofa>(); }
        unique_ptr<CoffeeTable> createCoffeeTable() override { return make_unique<VictorianCoffeeTable>(); }

        ~VictorianFurnitureFactory() override {}
};

class ArtDecoFurnitureFactory : public FurnitureFactory
{
    public:
        unique_ptr<Chair> createChair() override { return make_unique<ArtDecoChair>(); }
        unique_ptr<Sofa> createSofa() override { return make_unique<ArtDecoSofa>(); }
        unique_ptr<CoffeeTable> createCoffeeTable() override { return make_unique<ArtDecoCoffeeTable>(); }

        ~ArtDecoFurnitureFactory() override {}
};

//------------------------------------------------------------------------------
