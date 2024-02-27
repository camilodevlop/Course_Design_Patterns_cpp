// Created by Camilo Castillo on 26/02/2024
// Adapter Pattern: reusing several existing subclasses that lack some common
// functionality. In this case, the adapter pattern is not useful for the 
// particular functions of each subclass. For example, the adapteer can't call 
// the talk() function of the Human class. 

#include <iostream>

//------------------------------------------------------------------------------

class Animal
{
    public:
        virtual void walk() const = 0;
        virtual void eat() const = 0;
        virtual ~Animal() = default;
};

//------------------------------------------------------------------------------

class Human : public Animal
{
    public:
        Human(std::string language = std::string{}, float speed = 0.0f, 
              std::string food = std::string{}) : language_(language),
              speed_(speed), food_(food) {}
        void speak() const { std::cout << "I speak " << language_ << std::endl; }
        void walk() const override { std::cout << "I walk at " << speed_ << " km/h" << std::endl; }
        void eat() const override { std::cout << "I eat " << food_ << std::endl; }
        ~Human() = default;

    private:
        std::string language_;
        float speed_;
        std::string food_;
};

class Bird : public Animal
{
    public:
        Bird(float fly_speed = 0.0f, float speed = 0.0f, std::string food = std::string{}) :
             fly_speed_(fly_speed), speed_(speed), food_(food) {}
        void fly() const { std::cout << "I fly at " << fly_speed_ << " km/h" << std::endl; }
        void walk() const override { std::cout << "I walk at " << speed_ << " km/h" << std::endl; }
        void eat() const override { std::cout << "I eat " << food_ << std::endl; }
        ~Bird() = default;

    private:
        float fly_speed_;
        float speed_;
        std::string food_;
};

class Fish : public Animal
{
    public:
        Fish(float swim_speed = 0.0f, float speed = 0.0f, std::string food = std::string{}) :
             swim_speed_(swim_speed), speed_(speed), food_(food) {}
        void swim() const { std::cout << "I swim at " << swim_speed_ << " km/h" << std::endl; }
        void walk() const override { std::cout << "I can't walk" << std::endl; }
        void eat() const override { std::cout << "I eat " << food_ << std::endl; }
        ~Fish() = default;

    private: 
        float swim_speed_;
        float speed_;
        std::string food_;
};

//------------------------------------------------------------------------------

class AnimalAdapter : public Animal
{
    public:
        AnimalAdapter(Animal& animal) : animal_(animal) {}
        void walk() const override { animal_.walk(); }
        void eat() const override { animal_.eat(); }
        void breathe() const { std::cout << "Now I can breathe" << std::endl; }
        ~AnimalAdapter() = default;

    private:
        Animal& animal_;

};

//------------------------------------------------------------------------------

int main()
{
    Human human("Spanish", 5.0f, "meat");
    Bird bird(10.0f, 1.0f, "seeds");
    Fish fish(20.0f, 0.5f, "plankton");

    AnimalAdapter humanAdapted(human);
    AnimalAdapter birdAdapted(bird);
    AnimalAdapter fishAdapted(fish);

    std::cout << "\nHuman adapted: " << std::endl;
    humanAdapted.breathe();
    humanAdapted.walk();
    humanAdapted.eat();

    std::cout << "\nBird adapted: " << std::endl;
    birdAdapted.breathe();
    birdAdapted.walk();
    birdAdapted.eat();

    std::cout << "\nFish adapted: " << std::endl;
    fishAdapted.breathe();
    fishAdapted.walk();
    fishAdapted.eat();

    return 0;
}

//------------------------------------------------------------------------------
