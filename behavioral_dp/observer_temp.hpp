// Created by Camilo Castillo on 11/07/2024
// Observer Pattern: using templates

#include <string>

//------------------------------------------------------------------------------

template <typename T>
class Observer
{
    public:
        virtual void field_changed(T& source, const std::string& field_name) = 0;
        virtual ~Observer() = default;
};

//------------------------------------------------------------------------------
