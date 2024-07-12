// Created by Camilo Castillo on 11/07/2024
// Observer Pattern

#include <iostream>
#include <list>
#include <string>

//------------------------------------------------------------------------------

class Observer
{
    public:
        virtual void update(const std::string& message) = 0;
        virtual ~Observer() = default;
};

//------------------------------------------------------------------------------

class Subject
{
    public:
        virtual void attach(Observer* observer ) = 0;
        virtual void detach(Observer* observer ) = 0;
        virtual void notify() = 0;
        virtual ~Subject() = default;
};

//------------------------------------------------------------------------------

class ConcreteSubject : public Subject
{
    public:
        void attach(Observer* observer) override
        {
            observers_.push_back(observer);
        }

        void detach(Observer* observer) override
        {
            observers_.remove(observer);
        }

        void notify() override
        {
            howManyObserver();
            for (auto observer : observers_)
                observer->update(message_);
        }

        void create_message(const std::string& message)
        {
            message_ = message;
            notify();
        }

        void howManyObserver() const
        {
            std::cout << "There are " << observers_.size() 
                      << " observers in the list." << std::endl;
        }

        virtual ~ConcreteSubject()
        {
            std::cout << "Goodbye, I was the subject." << std::endl;
        }

    private:
        std::list<Observer*> observers_;
        std::string message_;
};

//------------------------------------------------------------------------------

class ConcreteObserver : public Observer
{
    public:
        ConcreteObserver(ConcreteSubject& subject) : subject_(subject)
        {
            subject_.attach(this);
            std::cout << "Hi, I'm the observer " << ++ConcreteObserver::static_number_ << std::endl;
            number_ = ConcreteObserver::static_number_;
        }

        void update(const std::string& message) override
        {
            message_ = message;
            std::cout << "Observer " << number_ << " has received the message: " << message_ << std::endl;
        }

        void printInfo() const
        {
            std::cout << "Observer " << number_ << " has message: " << message_ << std::endl;
        }

        virtual ~ConcreteObserver()
        {
            std::cout << "Goodbye, I was the observer " << number_ << std::endl;
        }

    private:
        std::string message_;
        ConcreteSubject& subject_;
        static int static_number_;
        int number_;
};

int ConcreteObserver::static_number_ = 0;

//------------------------------------------------------------------------------

int main()
{
    ConcreteSubject subject;
    ConcreteObserver observer1(subject);
    ConcreteObserver observer2(subject);
    ConcreteObserver observer3(subject);
    ConcreteObserver observer4(subject);
    ConcreteObserver observer5(subject);
    ConcreteObserver observer6(subject);

    subject.create_message("Hello World!");

    observer1.printInfo();
    observer2.printInfo();
    observer3.printInfo();
    observer4.printInfo();
    observer5.printInfo();
    observer6.printInfo();

    subject.detach(&observer1);
    subject.detach(&observer6);
    subject.create_message("The second message");
    
    observer1.printInfo();
    observer2.printInfo();
    observer3.printInfo();
    observer4.printInfo();
    observer5.printInfo();
    observer6.printInfo();

    subject.attach(&observer1);
    subject.create_message("The third message");

    return 0;
}

//------------------------------------------------------------------------------
