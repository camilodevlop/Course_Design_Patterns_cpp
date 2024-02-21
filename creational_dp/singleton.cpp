// Created by Camilo Castillo on 19/02/2024
// Singleton Pattern

#include <iostream>

//------------------------------------------------------------------------------

class Logger
{
    public:
        static Logger& instance()
        {
            static Logger logger;
            return logger;
        }

        void log(const std::string& message)
        {
            std::cout << message << std::endl;
        }

    private:
        Logger() = default;
        ~Logger() = default;
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
};

//------------------------------------------------------------------------------

int main()
{
    Logger::instance().log("Hello, Singleton Pattern!");
    return 0;
}

//------------------------------------------------------------------------------
