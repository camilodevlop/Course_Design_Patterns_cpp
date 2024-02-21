// Created by Camilo Castillo on 13/02/2024
// Protorype Pattern: Furniture (Client)

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

//------------------------------------------------------------------------------

int main()
{
    Rectangle rectangle1(10, 20, "red");
    std::unique_ptr<Shape> rectangle2 = rectangle1.clone();
    rectangle1.draw();
    rectangle2->draw();

    Rectangle rectangle3(30, 40, "blue");
    std::unique_ptr<Shape> rectangle4 = rectangle3.clone();
    rectangle3.draw();
    rectangle4->draw();

    return 0;
}


//------------------------------------------------------------------------------
