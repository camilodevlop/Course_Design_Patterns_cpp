// Created by Camilo Castillo on 11/07/2024
// Observer Pattern: using templates

#include <string>
#include <vector>

template <typename> class Observer;

//------------------------------------------------------------------------------

template <typename T>
class Observable
{
    public:
        void notify(T& source, const std::string& field_name)
        {
            for (auto observer : observers_)
                observer->field_changed(source, field_name);
        }

        void subscribe(Observer<T>& observer)
        {
            observers_.push_back(&observer);
        }

        void unsubscribe(Observable<T>& observer)
        {
            observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), 
                             observers_.end());
        }

    private:
        std::vector<Observer<T>*> observers_;
};

//------------------------------------------------------------------------------
