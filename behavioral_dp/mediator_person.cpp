// Created by Camilo Castillo on 03/07/2024
// Mediator Pattern: ChatRoom (Mediator), Person (Component)

#include <iostream>
#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/mediator_person.hpp>
#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/mediator_chatroom.hpp>

//------------------------------------------------------------------------------

Person::Person(const std::string& name) : name_(name) {}

void Person::say(const std::string& message) const
{
    room_->broadcast(name_, message);
}

//------------------------------------------------------------------------------

void Person::privateMessage(const std::string& who, const std::string& message) const
{
    room_->message(name_, who, message);
}

//------------------------------------------------------------------------------

void Person::receive(const std::string& origin, const std::string& message)
{
    std::string msg = "[" + name_ + "'s chat session] " + origin + ": " + message;
    std::cout << msg << "\n";
    chatLog_.emplace_back(msg);
}

//------------------------------------------------------------------------------

bool Person::operator==(const Person& other) const
{
    return name_ == other.name_;
}

//------------------------------------------------------------------------------

bool Person::operator!=(const Person& other) const
{
    return name_ != other.name_;
}

//------------------------------------------------------------------------------
