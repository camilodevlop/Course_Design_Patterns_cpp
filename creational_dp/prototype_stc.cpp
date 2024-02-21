// Created by Camilo Castillo on 15/02/2024
// Prototype Pattern: registry implementation using a static map

#include <iostream>
#include <memory>
#include <map>

//------------------------------------------------------------------------------

class Shape
{
    public:
        static std::map<std::string, std::unique_ptr<Shape>> sRegistry;
        
        virtual std::unique_ptr<Shape> clone() const = 0;
        virtual void draw() const = 0;
        virtual ~Shape() = default;
};

std::map<std::string, std::unique_ptr<Shape>> Shape::sRegistry;

//------------------------------------------------------------------------------

class ShapeRegistryManager
{
    public:
        static void registerShape(const std::string& shapeName, std::unique_ptr<Shape> shape)
        {
            if (!isShapeRegistered(shapeName))
                Shape::sRegistry[shapeName] = std::move(shape);
        }
        
        static void unregisterShape(const std::string& shapeName)
        {
            if (isShapeRegistered(shapeName))
                Shape::sRegistry.erase(shapeName);
        }
        
        static std::unique_ptr<Shape> createShape(const std::string& shapeName)
        {
            if (isShapeRegistered(shapeName))
                return Shape::sRegistry[shapeName]->clone();
            else
                return nullptr;
        } 

    private:
        static bool isShapeRegistered(const std::string& shapeName)
        {
            return Shape::sRegistry.find(shapeName) != Shape::sRegistry.end();
        }
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

class Square : public Shape
{
    public:
        Square(int side, std::string color) : 
            mSide(side), mColor(color) {}
        Square(const Square& other) : 
            mSide(other.mSide), mColor(other.mColor) {}

        std::unique_ptr<Shape> clone() const override
        { return std::make_unique<Square>(*this); }
        
        void draw() const override
        { 
            std::cout << "\nDrawing a square" << "Side: " << mSide 
                      << ", Color: " << mColor
                      << std::endl; 
        }
        ~Square() override {}

    private:
        int mSide;
        std::string mColor;
};

//------------------------------------------------------------------------------

int main()
{
    Rectangle redRectangle(10, 20, "red");
    Rectangle blueRectangle(30, 40, "blue");
    Circle redCircle(15, "red");
    Circle blueCircle(25, "blue");
    Square redSquare(10, "red");
    Square blueSquare(20, "blue");

    ShapeRegistryManager::registerShape("redRectangle", redRectangle.clone());
    ShapeRegistryManager::registerShape("blueRectangle", blueRectangle.clone());
    ShapeRegistryManager::registerShape("redCircle", redCircle.clone());
    ShapeRegistryManager::registerShape("blueCircle", blueCircle.clone());
    ShapeRegistryManager::registerShape("redSquare", redSquare.clone());
    ShapeRegistryManager::registerShape("blueSquare", blueSquare.clone());

    std::unique_ptr<Shape> redRectangleClone = ShapeRegistryManager::createShape("redRectangle");
    std::unique_ptr<Shape> blueRectangleClone = ShapeRegistryManager::createShape("blueRectangle");
    std::unique_ptr<Shape> redCircleClone = ShapeRegistryManager::createShape("redCircle");
    std::unique_ptr<Shape> blueCircleClone = ShapeRegistryManager::createShape("blueCircle");
    std::unique_ptr<Shape> redSquareClone = ShapeRegistryManager::createShape("redSquare");
    std::unique_ptr<Shape> blueSquareClone = ShapeRegistryManager::createShape("blueSquare");

    redRectangleClone->draw();
    blueRectangleClone->draw();
    redCircleClone->draw();
    blueCircleClone->draw();
    redSquareClone->draw();
    blueSquareClone->draw();

    return 0;
}

//------------------------------------------------------------------------------
