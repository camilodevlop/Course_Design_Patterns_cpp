// Created by Camilo Castillo on 10/05/2024
// Flyweight Pattern

#include <iostream>
#include <memory>
#include <map>

//------------------------------------------------------------------------------

class TreeType
{
    public:
        TreeType(const std::string& name, const std::string& color, const std::string& texture)
            : name_(name), color_(color), texture_(texture) {}
        
        void draw(std::string canvas, int x = 0, int y = 0)
        {
            std::cout << "Drawing " << name_ << " at " << x << ", " << y 
                      << " with color " << color_ 
                      << " and texture " << texture_ 
                      << " on " << canvas << std::endl;
        }

        ~TreeType() = default;

    private:
        const std::string name_, color_, texture_;
};

//------------------------------------------------------------------------------

class TreeFactory
{
    public:
        TreeFactory() = default;

        std::shared_ptr<TreeType> getTreeType(const std::string& name, const std::string& color, const std::string& texture)
        {
            auto it = treeTypes_.find(name);
            if(it == treeTypes_.end())
                treeTypes_[name] = std::make_shared<TreeType>(name, color, texture);
            
            return treeTypes_[name];
        }

        ~TreeFactory() { treeTypes_.clear(); }

        int getTreeTypesCount() { return treeTypes_.size(); }

    private:
        std::map<std::string, std::shared_ptr<TreeType>> treeTypes_;
};

//------------------------------------------------------------------------------

class Tree
{
    public:
        Tree(std::shared_ptr<TreeType> treeType, int x, int y)
            : treeType_(treeType), x_(x), y_(y) {}
        
        void draw(std::string canvas) { treeType_->draw( canvas, x_, y_); }

        ~Tree() = default;

    private:
        std::shared_ptr<TreeType> treeType_;
        int x_, y_;
};

//------------------------------------------------------------------------------

class Forest
{
    public:
        void plantTree(const std::string& name, const std::string& color, const std::string& texture, int x, int y)
        {
            auto treeType = treeFactory_.getTreeType(name, color, texture);
            trees_.push_back(Tree(treeType, x, y));
        }

        void draw(std::string canvas = "canvas")
        {
            for(auto& tree : trees_) tree.draw(canvas);
        }

        ~Forest() { trees_.clear(); }

        int getTreeTypesCount() { return treeFactory_.getTreeTypesCount(); }

    private:
        TreeFactory treeFactory_;
        std::vector<Tree> trees_;
};

//------------------------------------------------------------------------------

int main()
{
    Forest forest;

    // Pine
    forest.plantTree("Pine", "Green", "Rough", 10, 10);
    forest.plantTree("Pine", "Green", "Rough", 20, 20);
    forest.plantTree("Pine", "Green", "Rough", 30, 30);
    forest.plantTree("Pine", "Green", "Rough", 40, 40);

    // Oak
    forest.plantTree("Oak", "Brown", "Smooth", 50, 50);
    forest.plantTree("Oak", "Brown", "Smooth", 60, 60);
    forest.plantTree("Oak", "Brown", "Smooth", 70, 70);
    forest.plantTree("Oak", "Brown", "Smooth", 80, 80);

    // Willow
    forest.plantTree("Willow", "Green", "Rough", 90, 90);
    forest.plantTree("Willow", "Green", "Rough", 100, 100);
    forest.plantTree("Willow", "Green", "Rough", 110, 110);
    forest.plantTree("Willow", "Green", "Rough", 120, 120);

    forest.draw();

    std::cout << "Tree types count: " << forest.getTreeTypesCount() << std::endl;

    return 0;
}

//------------------------------------------------------------------------------
