// Created by Camilo Castillo on 03/07/2024
// Mediator Pattern: ChatRoom (Mediator), Person (Component)


#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/mediator_person.hpp>
#include <algorithm>
#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/mediator_chatroom.hpp>

//------------------------------------------------------------------------------

void ChatRoom::broadcast(const std::string& origin, const std::string& message)
{
    for (auto person : people_)
        if (person->name_ != origin)
            person->receive(origin, message);
}

//------------------------------------------------------------------------------

void ChatRoom::join(Person* p)
{
    std::string join_msg = p->name_ + " joins the chat";
    broadcast("room", join_msg);
    p->room_ = this;
    people_.push_back(p);
}

//------------------------------------------------------------------------------
