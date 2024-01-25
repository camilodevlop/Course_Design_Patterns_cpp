// Created by Camilo Castillo on 24/01/2024
// Open-Close Principle (OCP)

#include <iostream>
#include <vector>

using namespace std;

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

//------------------------------------------------------------------------------

struct Product
{
    string name;
    Color color;
    Size size;
};

//------------------------------------------------------------------------------

template <typename T> struct Specification
{
    virtual bool is_satisfied(T* item) = 0;
    virtual ~Specification() {};
};

class ColorSpecification : public Specification<Product>
{
    Color mColor;

    public:
        ColorSpecification(Color color) : mColor{color} {}

        bool is_satisfied(Product* item) override
        {
            return item->color == mColor;
        }

        ~ColorSpecification() override {};
};

class ColorAndSizeSpecification : public Specification<Product>
{
    Color mColor;
    Size mSize;

    public:
        ColorAndSizeSpecification(Color color, Size size) : mColor{color}, mSize{size} {}

        bool is_satisfied(Product* item) override
        {
            return item->color == mColor && item->size == mSize;
        }

        ~ColorAndSizeSpecification() override {};
};

//------------------------------------------------------------------------------

template <typename T> struct Filter
{
    virtual vector<T*> filter(vector<T*>& items, Specification<T>& spec) = 0;
    virtual ~Filter() {};
};

struct BetterFilter : public Filter<Product>
{
    BetterFilter() = default;

    vector<Product*> filter(vector<Product*>& items, Specification<Product>& spec) override
    {
        vector<Product*> result;
        for (auto& item : items)
        {
            if (spec.is_satisfied(item))
                result.push_back(item);
        }
        return result;
    }

    ~BetterFilter() override {};

    private:
        vector<Product*> mItems;
};

//------------------------------------------------------------------------------






//------------------------------------------------------------------------------

int main()
{
    Product apple{"Apple", Color::Green, Size::Large};
    Product tree{"Tree", Color::Blue, Size::Medium};
    Product house{"House", Color::Green, Size::Large};
    vector<Product*> items{&apple, &tree, &house};

    BetterFilter betterFilter {};
    ColorSpecification greenColor{Color::Green};
    ColorAndSizeSpecification greenAndLarge{Color::Green, Size::Large};

    vector<Product*> greenThings = betterFilter.filter(items, greenColor);
    for (auto& item : greenThings)
        cout << item->name << " is green" << endl;
        //cout << (*item).name << " is green" << endl;

    vector<Product*> greenAndLargeThings = betterFilter.filter(items, greenAndLarge); 
    for (auto& item : greenAndLargeThings)
        cout << item->name << " is green and large" << endl;

    return 0;
}

//------------------------------------------------------------------------------
