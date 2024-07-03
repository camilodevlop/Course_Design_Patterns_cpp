// Created by Camilo Castillo on 03/07/2024
// Mediator Pattern: ChatRoom (Mediator), Person (Component)

#include <vector>

//------------------------------------------------------------------------------

struct ChatRoom
{
    std::vector<Person*> people_;

    void broadcast(const std::string& origin, const std::string& message);
    void join(Person* p);
    void message(const std::string& origin, const std::string& who, 
                  const std::string& message)
    {
        auto target = std::find_if(begin(people_), end(people_),
            [&](const Person* p) { return p->name_ == who; });
        if (target != end(people_))
            (*target)->receive(origin, message);
    }
};

//------------------------------------------------------------------------------
