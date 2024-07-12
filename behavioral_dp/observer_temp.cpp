// Created by Camilo Castillo on 11/07/2024
// Observer Pattern: using templates

#include <iostream>
#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/observer_temp.hpp>
#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/observable_temp.hpp>

//------------------------------------------------------------------------------

// Observable
class Person : public Observable<Person>
{
    public:
        Person(int age) : age_(age) {}
        int get_age() const { return age_; }
        void set_age(int age)
        { 
            if (age == age_) return;
            age_ = age; 
            notify(*this, "age");
        }

        ~Person() = default;

    private:
        int age_;
};

//------------------------------------------------------------------------------

// Observer
class ConsolePersonObserver : public Observer<Person>
{
    public:
        void field_changed(Person& source, const std::string& field_name) override
        {
            std::cout << "Person's " << field_name << " has changed to ";
            if (field_name == "age") std::cout << source.get_age() << std::endl;
        }
};

//------------------------------------------------------------------------------

int main()
{
    Person person{10};
    ConsolePersonObserver cpo1;
    ConsolePersonObserver cpo2;
    ConsolePersonObserver cpo3;
    ConsolePersonObserver cpo4;

    person.subscribe(cpo1);
    person.subscribe(cpo2);
    person.subscribe(cpo3);
    person.subscribe(cpo4);

    std::cout << "Setting age to 20" << std::endl;
    person.set_age(20);

    return 0;
}

//------------------------------------------------------------------------------
