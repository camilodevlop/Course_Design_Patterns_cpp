// Created by Camilo Castillo on 03/07/2024
// Mediator Pattern: ChatRoom (Mediator), Person (Component)

#include <vector>

//------------------------------------------------------------------------------

class ChatRoom;

class Person
{
    public:
        std::string name_;
        std::vector<std::string> chatLog_;
        ChatRoom* room_ = nullptr;
       
        Person(const std::string& name);
        void say(const std::string& message) const;
        void privateMessage(const std::string& who, const std::string& message) const;
        void receive(const std::string& origin, const std::string& message);
        bool operator==(const Person& other) const;
        bool operator!=(const Person& other) const;


        ~Person() = default;
};

//------------------------------------------------------------------------------
