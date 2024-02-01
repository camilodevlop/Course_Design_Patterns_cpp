// Created by Camilo Castillo on 31/01/2024
// Dependency Inversion Principle (DIP)

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

//------------------------------------------------------------------------------

enum class Relationship { parent, child, sibling };
struct Person { string name; };

//------------------------------------------------------------------------------

class RelationshipBrowser
{
    public:
        virtual vector<Person> findAllChildrenOf(const string& name) = 0;
        virtual ~RelationshipBrowser() {}
};

//------------------------------------------------------------------------------

class Relationships : public RelationshipBrowser
{
    public:
        Relationships() {}

        vector<tuple<Person, Relationship, Person>> mRelations;

        void addParentAndChild(const Person& parent, const Person& child) {
            mRelations.push_back({parent, Relationship::parent, child});
            mRelations.push_back({child, Relationship::child, parent});
        }

        vector<Person> findAllChildrenOf(const string& name) override {
            vector<Person> result;
            for (auto&& [first, rel, second] : mRelations) {
                if (first.name == name && rel == Relationship::parent) {
                    result.push_back(second);
                }
            }
            return result;
        }

        ~Relationships() override {}
};

//------------------------------------------------------------------------------

class Research
{
    public:
        Research(RelationshipBrowser& browser) {
            for (auto& child : browser.findAllChildrenOf("John")) {
                cout << "John has a child called " << child.name << endl;
            }
        }
    
    ~Research() = default;
};

//------------------------------------------------------------------------------

int main()
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};
    Relationships relationships;

    relationships.addParentAndChild(parent, child1);
    relationships.addParentAndChild(parent, child2);

    Research _(relationships);

    return 0;
}

//------------------------------------------------------------------------------
