// Created by Camilo Castillo on 13/02/2024
// Prototype Pattern: registry implementation using a factory class

#include <iostream>
#include <memory>

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

class Ellipse : public Shape
{
    public:
        Ellipse(int radius1, int radius2, std::string color) : 
            mRadius1(radius1), mRadius2(radius2), mColor(color) {}
        Ellipse(const Ellipse& other) : 
            mRadius1(other.mRadius1), mRadius2(other.mRadius2), mColor(other.mColor) {}

        std::unique_ptr<Shape> clone() const override
        { return std::make_unique<Ellipse>(*this); }
        
        void draw() const override
        { 
            std::cout << "\nDrawing an ellipse" << "Radius1: " << mRadius1 
                      << ", Radius2: " << mRadius2 << ", Color: " << mColor
                      << std::endl; 
        }
        ~Ellipse() override {}

    private:
        int mRadius1;
        int mRadius2;
        std::string mColor;
};

//------------------------------------------------------------------------------

class ShapeFactory
{
    public:
        virtual std::unique_ptr<Shape> createShape() = 0;
        virtual ~ShapeFactory() = default;
};

class RectangleFactory : public ShapeFactory
{
    public:
        RectangleFactory() : mRectangle(10, 20, "red") {}
        std::unique_ptr<Shape> createShape() override
        { return mRectangle.clone(); }
        ~RectangleFactory() override {}

    private:
        Rectangle mRectangle;
};

class CircleFactory : public ShapeFactory
{
    public:
        CircleFactory() : mCircle(10, "red") {}
        std::unique_ptr<Shape> createShape() override
        { return mCircle.clone(); }
        ~CircleFactory() override {}

    private:
        Circle mCircle;
};

class SquareFactory : public ShapeFactory
{
    public:
        SquareFactory() : mSquare(10, "red") {}
        std::unique_ptr<Shape> createShape() override
        { return mSquare.clone(); }
        ~SquareFactory() override {}

    private:
        Square mSquare;
};

class EllipseFactory : public ShapeFactory
{
    public:
        EllipseFactory() : mEllipse(10, 20, "red") {}
        std::unique_ptr<Shape> createShape() override
        { return mEllipse.clone(); }
        ~EllipseFactory() override {}

    private:
        Ellipse mEllipse;
};

//------------------------------------------------------------------------------

int main()
{
    RectangleFactory rectangleFactory;
    std::unique_ptr<Shape> rectangle1 = rectangleFactory.createShape();
    rectangle1->draw();
    std::unique_ptr<Shape> rectangle2 = rectangleFactory.createShape();
    rectangle2->draw();

    CircleFactory circleFactory;
    std::unique_ptr<Shape> circle = circleFactory.createShape();
    circle->draw();

    SquareFactory squareFactory;
    std::unique_ptr<Shape> square = squareFactory.createShape();
    square->draw();

    EllipseFactory ellipseFactory;
    std::unique_ptr<Shape> ellipse = ellipseFactory.createShape();
    ellipse->draw();

    return 0;
}

//------------------------------------------------------------------------------
