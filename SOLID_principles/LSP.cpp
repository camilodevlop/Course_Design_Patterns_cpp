// Created by Camilo Castillo on 30/01/2024
// Liskov Substitution Principle (LSP)

#include <iostream>

using namespace std;

//------------------------------------------------------------------------------

class TwoDimensionalShape
{
    public:
        virtual float getArea() const = 0;
        virtual ~TwoDimensionalShape() {}
};

//------------------------------------------------------------------------------

class Rectangle : public TwoDimensionalShape
{
    public:
        Rectangle(float width, float height) : mWidth(width), mHeight(height) {}

        int getWidth() const { return mWidth; }
        void setWidth(float width) { mWidth = width; }
        int getHeight() const { return mHeight; }
        void setHeight(float height) { Rectangle::mHeight = height; }
    
        float getArea() const override { return mWidth * mHeight; }
        ~Rectangle() override {}

    protected:
        float mWidth, mHeight;

};

class FootballField : public TwoDimensionalShape
{
    public:
        FootballField(float width, float height) : mWidth(width), mHeight(height) {}

        int getWidth() const { return mWidth; }
        void setWidth(float width) { mWidth = width; }
        int getHeight() const { return mHeight; }
        void setHeight(float height) { FootballField::mHeight = height; }
    
        float getArea() const override { return mWidth * mHeight; }
        ~FootballField() override {}

    protected:
        float mWidth, mHeight;
};

//------------------------------------------------------------------------------

class AreaCalculator
{
    public:
        static float getArea(TwoDimensionalShape& shape) { return shape.getArea(); }
};

//------------------------------------------------------------------------------

int main()
{
    Rectangle rectangle(10, 20);
    FootballField footballField(100, 50);

    cout << "Rectangle area: " << AreaCalculator::getArea(rectangle) << endl;
    cout << "Football field area: " << AreaCalculator::getArea(footballField) << endl;

    return 0;
}

//------------------------------------------------------------------------------
