// Created by Camilo Castillo on 07/02/2024
// Abstract Factory Pattern: Furniture (Products)

#include <iostream>

using namespace std;

//------------------------------------------------------------------------------

class Chair
{
    public:
        virtual void description() const = 0;
        virtual ~Chair() = default;
};

class ModernChair : public Chair
{
    public:
        void description() const override { cout << "Modern Chair" << endl; }
        ~ModernChair() override {}
};

class VictorianChair : public Chair
{
    public:
        void description() const override { cout << "Victorian Chair" << endl; }
        ~VictorianChair() override {}
};

class ArtDecoChair : public Chair
{
    public:
        void description() const override { cout << "Art Deco Chair" << endl; }
        ~ArtDecoChair() override {}
};


//------------------------------------------------------------------------------

class Sofa
{
    public:
        virtual void description() const = 0;
        virtual ~Sofa() = default;
};

class ModernSofa : public Sofa
{
    public:
        void description() const override { cout << "Modern Sofa" << endl; }
        ~ModernSofa() override {}
};

class VictorianSofa : public Sofa
{
    public:
        void description() const override { cout << "Victorian Sofa" << endl; }
        ~VictorianSofa() override {}
};

class ArtDecoSofa : public Sofa
{
    public:
        void description() const override { cout << "Art Deco Sofa" << endl; }
        ~ArtDecoSofa() override {}
};

//------------------------------------------------------------------------------

class CoffeeTable
{
    public:
        virtual void description() const = 0;
        virtual ~CoffeeTable() = default;
};

class ModernCoffeeTable : public CoffeeTable
{
    public:
        void description() const override { cout << "Modern Coffee Table" << endl; }
        ~ModernCoffeeTable() override {}
};

class VictorianCoffeeTable : public CoffeeTable
{
    public:
        void description() const override { cout << "Victorian Coffee Table" << endl; }
        ~VictorianCoffeeTable() override {}
};

class ArtDecoCoffeeTable : public CoffeeTable
{
    public:
        void description() const override { cout << "Art Deco Coffee Table" << endl; }
        ~ArtDecoCoffeeTable() override {}
};

//------------------------------------------------------------------------------
