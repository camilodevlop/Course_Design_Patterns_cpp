// Created by Camilo Castillo on 03/07/2024
// Mediator Pattern: ChatRoom (Mediator), Person (Component)

#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/mediator_person.hpp>
#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/mediator_chatroom.hpp>

//------------------------------------------------------------------------------

int main()
{
    ChatRoom room;
    Person camilo{"Camilo"};
    Person victor{"Victor"};
    Person juan{"Juan"};
    
    room.join(&camilo);
    room.join(&victor);
    room.join(&juan);

    camilo.say("Hello, room!");
    victor.say("Hello, Camilo!");
    juan.say("Hello, everyone!");

    camilo.privateMessage("Juan", "I'm going to the gym");
    juan.privateMessage("Camilo", "I'm going to the cinema");

    return 0;
}

//------------------------------------------------------------------------------
