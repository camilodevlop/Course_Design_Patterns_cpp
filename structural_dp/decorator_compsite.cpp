// Created by Camilo Castillo on 30/04/2024
// Decorator Pattern: Decorator Composite

#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

//------------------------------------------------------------------------------

struct Graphic
{
    virtual std::string description() const = 0;
    virtual ~Graphic() = default;
};


//------------------------------------------------------------------------------

struct Shape: public Graphic
{
    Shape(const std::string name): name_(name) {}

    std::string description() const override
    { return name_; }

    virtual ~Shape() = default;

    private:
        std::string name_;
};

//------------------------------------------------------------------------------

struct GraphicDecorator: public Graphic
{
    GraphicDecorator(Graphic* graphic): graphic_(graphic) {}

    std::string description() const override
    { return graphic_->description(); }

    virtual ~GraphicDecorator() = default;

    private:
        Graphic* graphic_;
};

//------------------------------------------------------------------------------

struct ColorDecorator: public GraphicDecorator
{
    ColorDecorator(Graphic* graphic, std::string color): GraphicDecorator(graphic), color_(color) {}

    std::string description() const override
    { return GraphicDecorator::description() + ", Color: " + color_; }

    virtual ~ColorDecorator() = default;

    private:
        std::string color_;
};

struct LineThicknessDecorator: public GraphicDecorator
{
    LineThicknessDecorator(Graphic* graphic, int thickness): GraphicDecorator(graphic), thickness_(thickness) {}

    std::string description() const override
    { return GraphicDecorator::description() + ", Line thickness: " + std::to_string(thickness_); }

    virtual ~LineThicknessDecorator() = default;

    private:
        int thickness_;
};

//------------------------------------------------------------------------------

class CompoundGraphic: public Graphic
{
    public:
        CompoundGraphic() = default;

        std::string description() const override
        {
            std::string description;
            for (const auto& graphic : graphics_)
                description += graphic->description() + "\n";
            return description;
        }

        void add(std::unique_ptr<Graphic> graphic)
        { graphics_.push_back(std::move(graphic)); }

        void remove(const int index) 
        {   
            if (index < graphics_.size())
                graphics_.erase(graphics_.begin() + index); 
        }

    private:
    std::vector<std::unique_ptr<Graphic>> graphics_;
};

//------------------------------------------------------------------------------

int main()
{
    std::cout << " Graphic Decorated " << std::endl;

    std::unique_ptr<Graphic> shape = std::make_unique<Shape>("Circle");
    shape = std::make_unique<ColorDecorator>(shape.release(), "red");
    shape = std::make_unique<LineThicknessDecorator>(shape.release(), 2);
    std::cout << shape->description() << std::endl;

    std::unique_ptr<Graphic> shape2 = std::make_unique<Shape>("Square");
    std::cout << shape2->description() << std::endl;


    std::cout << "\n\n Compound Decorated Graphic " << std::endl;

    std::unique_ptr<CompoundGraphic> compound = std::make_unique<CompoundGraphic>();
    compound->add(std::move(shape));
    compound->add(std::move(shape2));

    std::unique_ptr<Graphic> shape3 = std::make_unique<Shape>("Triangle");
    shape3 = std::make_unique<ColorDecorator>(shape3.release(), "blue");
    std::unique_ptr<Graphic> shape4 = std::make_unique<Shape>("Rectangle");
    shape4 = std::make_unique<ColorDecorator>(shape4.release(), "green");
    shape4 = std::make_unique<LineThicknessDecorator>(shape4.release(), 3);

    std::unique_ptr<CompoundGraphic> compound2 = std::make_unique<CompoundGraphic>();
    compound2->add(std::move(shape3));
    compound2->add(std::move(shape4));
    compound2->add(std::move(compound));

    std::cout << compound2->description() << std::endl;

    return 0;
}

//------------------------------------------------------------------------------
