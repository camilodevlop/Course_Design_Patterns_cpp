// Created by Camilo Castillo on 19/02/2024
// Singleton Pattern: prototype of a Shape class

#include <iostream>
#include <memory>
#include <map>

//------------------------------------------------------------------------------

template <typename T>
class Shape
{
    public:
        virtual std::unique_ptr<T> clone() const = 0;
        virtual ~Shape() = default;
};

//------------------------------------------------------------------------------

class Rectangle : public Shape<Rectangle>
{
    public:
        Rectangle() : mWidth(int{}), mHeight(int{}), mColor(std::string{}) {}
        Rectangle(int width, int height, std::string color) : 
            mWidth(width), mHeight(height), mColor(color) {}
        Rectangle(const Rectangle& other) : 
            mWidth(other.mWidth), mHeight(other.mHeight), mColor(other.mColor) {}

        std::unique_ptr<Rectangle> clone() const override
        { return std::make_unique<Rectangle>(*this); }

        int getWidth() const { return mWidth; }
        void setWidth(int width) { mWidth = width; }
        int getHeight() const { return mHeight; }
        void setHeight(int height) { mHeight = height; }
        std::string getColor() const { return mColor; }
        void setColor(std::string color) { mColor = color; }

        ~Rectangle() override {}

    private:
        int mWidth;
        int mHeight;
        std::string mColor;
};

class Circle : public Shape<Circle>
{
    public:
        Circle() : mRadius(int{}), mColor(std::string{}) {}
        Circle(int radius, std::string color) : 
            mRadius(radius), mColor(color) {}
        Circle(const Circle& other) : 
            mRadius(other.mRadius), mColor(other.mColor) {}

        std::unique_ptr<Circle> clone() const override
        { return std::make_unique<Circle>(*this); }

        int getRadius() const { return mRadius; }
        void setRadius(int radius) { mRadius = radius; }
        std::string getColor() const { return mColor; }
        void setColor(std::string color) { mColor = color; }

        ~Circle() override {}

    private:
        int mRadius;
        std::string mColor;
};

//------------------------------------------------------------------------------

template <typename T>
class GetterMembersShape
{
    public:
        GetterMembersShape() = default;
        virtual void printMembers(const std::unique_ptr<T>& shape) const = 0;
        virtual ~GetterMembersShape() = default;
};

class GetterMembersRectangle : public GetterMembersShape<Rectangle>
{
    public:
        GetterMembersRectangle() = default;

        void printMembers(const std::unique_ptr<Rectangle>& rectangle) const override
        {
            std::cout << "\nRectangle:" 
                      << "\nWidth: " << rectangle->getWidth() 
                      << "\nHeight: " << rectangle->getHeight()
                      << "\nColor: " << rectangle->getColor() << std::endl; 
        }

        ~GetterMembersRectangle() override {}
};

class GetterMembersCircle : public GetterMembersShape<Circle>
{
    public:
        GetterMembersCircle() = default;

        void printMembers(const std::unique_ptr<Circle>& circle) const override
        {
            std::cout << "\nCircle:" 
                      << "\nRadius: " << circle->getRadius() 
                      << "\nColor: " << circle->getColor() << std::endl; 
        }

        ~GetterMembersCircle() override {}
};


//------------------------------------------------------------------------------

template <typename T>
class SetterMembersShape
{
    public:
        SetterMembersShape() = default;
        virtual ~SetterMembersShape() = default;
};

class SetterMembersRectangle : public SetterMembersShape<Rectangle>
{
    public:
        SetterMembersRectangle() = default;

        void set(std::unique_ptr<Rectangle>& rectangle, int width, int height, std::string color) const
        {
            rectangle->setWidth(width);
            rectangle->setHeight(height);
            rectangle->setColor(color);
        }

        ~SetterMembersRectangle() override {}
};

class SetterMembersCircle : public SetterMembersShape<Circle>
{
    public:
        SetterMembersCircle() = default;

        void set(std::unique_ptr<Circle>& circle, int radius, std::string color) const
        {
            circle->setRadius(radius);
            circle->setColor(color);
        }

        ~SetterMembersCircle() override {}
};

//------------------------------------------------------------------------------

template <typename T>
class Shaper
{
    public:
        Shaper(const Shaper&) = delete;
        Shaper& operator=(const Shaper&) = delete;

        static Shaper& instance()
        {
            static Shaper instance;
            return instance;
        }

        void registerShape(const std::string& shapeName, std::unique_ptr<T> shape)
        {
            if (!isShapeRegistered(shapeName))
                mRegistry[shapeName] = std::move(shape);
        }
        
        void unregisterShape(const std::string& shapeName)
        {
            if (isShapeRegistered(shapeName))
                mRegistry.erase(shapeName);
        }
        
        std::unique_ptr<T> createShape(const std::string& shapeName)
        {
            if (isShapeRegistered(shapeName))
                return mRegistry[shapeName]->clone();
            else
                return nullptr;
        } 

    private:
        Shaper() = default;

        bool isShapeRegistered(const std::string& shapeName)
        {
            return mRegistry.find(shapeName) != mRegistry.end();
        }

        std::map<std::string, std::unique_ptr<T>> mRegistry;
};

//------------------------------------------------------------------------------

int main()
{
    // Getters and setters.
    GetterMembersRectangle getterMembersRectangle;
    SetterMembersRectangle setterMembersRectangle;
    GetterMembersCircle getterMembersCircle;
    SetterMembersCircle setterMembersCircle;

    // Shapes.
    Rectangle rectangle;
    Circle circle;

    // Register shapes.
    Shaper<Rectangle>::instance().registerShape("rectangle", std::make_unique<Rectangle>(rectangle));
    Shaper<Circle>::instance().registerShape("circle", std::make_unique<Circle>(circle));

    // Create shapes.
    std::unique_ptr<Rectangle> rectangleBlue = Shaper<Rectangle>::instance().createShape("rectangle");
    std::cout << "\nRectangle blue" << std::endl;
    getterMembersRectangle.printMembers(rectangleBlue);
    setterMembersRectangle.set(rectangleBlue, 10, 20, "blue");
    getterMembersRectangle.printMembers(rectangleBlue);

    std::unique_ptr<Circle> circleRed = Shaper<Circle>::instance().createShape("circle");
    std::cout << "\nCircle red" << std::endl;
    getterMembersCircle.printMembers(circleRed);
    setterMembersCircle.set(circleRed, 10, "red");
    getterMembersCircle.printMembers(circleRed);

    // Register new shapes.
    Shaper<Rectangle>::instance().registerShape("rectangleBlue", std::move(rectangleBlue));
    Shaper<Circle>::instance().registerShape("circleRed", std::move(circleRed));

    // Create new shapes.
    std::unique_ptr<Rectangle> rectangleBlueClone = Shaper<Rectangle>::instance().createShape("rectangleBlue");
    std::cout << "\nRectangle blue clone" << std::endl;
    getterMembersRectangle.printMembers(rectangleBlueClone);
    setterMembersRectangle.set(rectangleBlueClone, 30, 40, "blue");
    getterMembersRectangle.printMembers(rectangleBlueClone);

    std::unique_ptr<Circle> circleRedClone = Shaper<Circle>::instance().createShape("circleRed");
    std::cout << "\nCircle red clone" << std::endl;
    getterMembersCircle.printMembers(circleRedClone);
    setterMembersCircle.set(circleRedClone, 20, "red");
    getterMembersCircle.printMembers(circleRedClone);

    return 0;
}

//------------------------------------------------------------------------------
