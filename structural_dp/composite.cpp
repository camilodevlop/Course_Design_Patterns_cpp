// Created by Camilo Castillo on 28/02/2024
// Composite Pattern

#include <iostream>
#include <memory>
#include <list>

//------------------------------------------------------------------------------

class Graphic
{
    public:
        virtual void move(int x, int y) = 0;
        virtual void draw() const = 0;
        virtual ~Graphic() = default;
};

//------------------------------------------------------------------------------

class Point : public Graphic
{
    public:
        Point(int x, int y) : x_(x), y_(y) {}

        void move(int x, int y) override 
        { 
            x_ += x; y_ += y; 
            std::cout << "Graphic moved to (" << x_ << ", " << y_ << ")" << std::endl;
        }

        void draw() const override 
        { 
            std::cout << "Point at (" << x_ << ", " << y_ << ")" << std::endl; 
        }

        ~Point() override = default;

    protected:
        int x_;
        int y_;
};

class Circle : public Point
{
    public:
        Circle(int x, int y, int radius) : Point(x, y), radius_(radius) {}

        void draw() const override 
        { 
            std::cout << "Circle at (" << x_ << ", " << y_ << ") with radius " << radius_ << std::endl; 
        }

        ~Circle() override = default;

    private:
        int radius_;
};

//------------------------------------------------------------------------------

class CompoundGraphic : public Graphic
{
    public:
        void move(int x, int y) override
        {
            for (auto& graphic : graphics_)
                graphic->move(x, y);
        }

        void draw() const override
        {
            for (auto& graphic : graphics_)
                graphic->draw();
        }

        void add(std::unique_ptr<Graphic>&& graphic) { graphics_.push_back(std::move(graphic)); }
        void remove(Graphic* graphic) 
        { 
            graphics_.remove_if([graphic](const std::unique_ptr<Graphic>& g) { return g.get() == graphic; });
        }

        ~CompoundGraphic() override = default;

    private:
        std::list<std::unique_ptr<Graphic>> graphics_;
};

//------------------------------------------------------------------------------

int main()
{
    std::unique_ptr<CompoundGraphic> graphic = std::make_unique<CompoundGraphic>();
    graphic->add(std::make_unique<Point>(1, 2));
    graphic->add(std::make_unique<Circle>(5, 3, 10));

    std::unique_ptr<CompoundGraphic> graphicGroup = std::make_unique<CompoundGraphic>();
    graphicGroup->add(std::make_unique<Point>(13, 12));
    graphicGroup->add(std::make_unique<Circle>(15, 13, 20));

    graphic->add(std::move(graphicGroup));

    graphic->move(2, 3);

    return 0;
}

//------------------------------------------------------------------------------
