// Created by Camilo Castillo on 13/02/2024
// Prototype Pattern: registry implementation using a map

#include <iostream>
#include <memory>
#include <map>

//------------------------------------------------------------------------------

class Shape
{
    public:
        virtual std::unique_ptr<Shape> clone() const = 0;
        virtual void draw() const = 0;
        virtual ~Shape() = default;
};

//------------------------------------------------------------------------------

class Rectangle : public Shape
{
    public:
        Rectangle(int width, int height, std::string color) : 
            mWidth(width), mHeight(height), mColor(color) {}
        Rectangle(const Rectangle& other) : 
            mWidth(other.mWidth), mHeight(other.mHeight), mColor(other.mColor) {}

        std::unique_ptr<Shape> clone() const override
        { return std::make_unique<Rectangle>(*this); }
        
        void draw() const override
        { 
            std::cout << "\nDrawing a rectangle" << "Width: " << mWidth 
                      << ", Height: " << mHeight << ", Color: " << mColor
                      << std::endl; 
        }
        ~Rectangle() override {}

    private:
        int mWidth;
        int mHeight;
        std::string mColor;
};

class Circle : public Shape
{
    public:
        Circle(int radius, std::string color) : 
            mRadius(radius), mColor(color) {}
        Circle(const Circle& other) : 
            mRadius(other.mRadius), mColor(other.mColor) {}

        std::unique_ptr<Shape> clone() const override
        { return std::make_unique<Circle>(*this); }
        
        void draw() const override
        { 
            std::cout << "\nDrawing a circle" << "Radius: " << mRadius 
                      << ", Color: " << mColor
                      << std::endl; 
        }
        ~Circle() override {}

    private:
        int mRadius;
        std::string mColor;
};

//------------------------------------------------------------------------------

class Registry
{
    public:
        void addShape(std::string name, std::unique_ptr<Shape> shape)
        {
            if (isShapeRegistered(name))
                std::cout << "Shape with name " << name << " is not registered" << std::endl;
            else
                mShapes[name] = std::move(shape);
        }

        std::unique_ptr<Shape> createShape(std::string name)
        {
            if (isShapeRegistered(name))
                return mShapes[name]->clone();
            else
                std::cout << "Shape with name " << name << " is not registered" << std::endl;
                return nullptr;
        }

    private:
        std::map<std::string, std::unique_ptr<Shape>> mShapes;

        bool isShapeRegistered(std::string name)
        {
            return mShapes.find(name) != mShapes.end();
        }
};

//------------------------------------------------------------------------------

int main()
{
    Registry registry;

    Rectangle blueRectangle(10, 20, "blue");
    Rectangle redRectangle(30, 40, "red");
    Circle greenCircle(50, "green");
    Circle yellowCircle(60, "yellow");

    registry.addShape("blueRectangle", std::make_unique<Rectangle>(blueRectangle));
    registry.addShape("redRectangle", std::make_unique<Rectangle>(redRectangle));
    registry.addShape("greenCircle", std::make_unique<Circle>(greenCircle));
    registry.addShape("yellowCircle", std::make_unique<Circle>(yellowCircle));

    std::unique_ptr<Shape> blueRectangleClone = registry.createShape("blueRectangle");
    std::unique_ptr<Shape> redRectangleClone = registry.createShape("redRectangle");
    std::unique_ptr<Shape> greenCircleClone = registry.createShape("greenCircle");
    std::unique_ptr<Shape> yellowCircleClone = registry.createShape("yellowCircle");

    (*blueRectangleClone).draw();
    (*redRectangleClone).draw();
    (*greenCircleClone).draw();
    (*yellowCircleClone).draw();

    return 0;
}

//------------------------------------------------------------------------------

