// Created by Camilo Castillo on 18/07/2024
// Template method

#include <iostream>


//------------------------------------------------------------------------------

class Game
{
    public:
        Game(unsigned int number_of_players) : number_of_players_(number_of_players) {}
        
        // Template method
        void run()
        {
            start();
            while (!haveWinner())
            {
                takeTurn();
            }
            std::cout << "Player " << getWinner() << " wins." << std::endl;
        }

        virtual ~Game() = default;

    
    protected:
        unsigned int number_of_players_;
        unsigned int current_player_{0};
        virtual void start() = 0;
        virtual bool haveWinner() = 0;
        virtual void takeTurn() = 0;
        virtual unsigned int getWinner() = 0;
};

//------------------------------------------------------------------------------

class Chess : public Game
{
    public:
        Chess() : Game(2) {}
        ~Chess() = default;

    protected:
        void start() override
        {
            std::cout << "Starting a game of chess with " << number_of_players_ << " players." << std::endl;
        }
       
        bool haveWinner() override
        {
            return turn_ == max_turns_;
        }

        void takeTurn() override
        {
            std::cout << "Turn " << turn_ << " taken by player " << current_player_ 
                      << "." << std::endl;
            ++turn_;
            current_player_ = (current_player_ + 1) % number_of_players_;
        }

        unsigned int getWinner() override
        {
            return current_player_;
        }

    private:
            int turn_{0}, max_turns_{10};
};

//------------------------------------------------------------------------------

int main()
{
    Chess chess;
    chess.run();

    return 0;
}

//------------------------------------------------------------------------------
