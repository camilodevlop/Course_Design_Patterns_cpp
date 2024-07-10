// Created by Camilo Castillo on 05/05/2024
// Memento Pattern

#include <iostream>
#include <vector>
#include <memory>
#include <iterator>

class BankAccount;
class History;

//------------------------------------------------------------------------------

class Memento
{
    public:
        virtual void restore() = 0;
        virtual ~Memento() = default;
};

class BankAccountMemento : public Memento
{
    public:
        BankAccountMemento(BankAccount& account);
        void restore() override;
        ~BankAccountMemento() = default;

    private:
        BankAccount& account_;
        const float balance_;
};

//------------------------------------------------------------------------------

class Originator
{
    public:
        virtual void deposit(const int amount) = 0;
        virtual ~Originator() = default;
};

class BankAccount : Originator
{
    public:
        BankAccount(float balance, History& history) : balance_(0), history_(history)
        {
            deposit(balance);
        }
        void deposit(const int amount) override; 
        float get_balance() const { return balance_; }

        ~BankAccount() = default;

    friend class BankAccountMemento;

    private:
        float balance_;
        History& history_;
};

//------------------------------------------------------------------------------

// BankAccountMemento Implementation

BankAccountMemento::BankAccountMemento(BankAccount& account) : account_(account), 
             balance_(account.balance_) {}

void BankAccountMemento::restore() 
{
    account_.balance_ = balance_;
}

//------------------------------------------------------------------------------

class History
{
    public:
        History() : iteratorState_(mementos_.begin()) 
        {
            mementos_.clear();
        }

        void push(std::shared_ptr<Memento> memento)
        {
            if (iteratorState_ != mementos_.end())
                mementos_.erase(iteratorState_, mementos_.end());
            mementos_.push_back(memento);
            iteratorState_ = mementos_.end();
        }

        std::shared_ptr<Memento> pop()
        {
            if (mementos_.empty())
                return nullptr;

            auto memento = mementos_.back();
            mementos_.pop_back();
            iteratorState_ = mementos_.end();
            return memento;
        }

        ~History() = default;

        friend class UndoCommand;
        friend class RedoCommand;

    private:
        std::vector<std::shared_ptr<Memento>> mementos_;
        std::vector<std::shared_ptr<Memento>>::iterator iteratorState_;
};

//------------------------------------------------------------------------------

// BankAccount Implementation

void BankAccount::deposit(const int amount)
{
    if (amount > 0)
    {
        balance_ += amount;
        history_.push(std::make_shared<BankAccountMemento>(*this));
    }
}

//------------------------------------------------------------------------------

class Command
{
    public:
        virtual void execute() = 0;
        virtual ~Command() = default;
};

class UndoCommand : public Command
{
    public:
        UndoCommand(History& history) : history_(history) {}
        void execute() override
        {
            if (history_.iteratorState_ != history_.mementos_.begin())
            {
                --history_.iteratorState_;
                (*history_.iteratorState_)->restore();
            }
        }

        ~UndoCommand() = default;

    private:
        History& history_;
};

class RedoCommand : public Command
{
    public:
        RedoCommand(History& history) : history_(history) {}
        void execute() override
        {
            if (history_.iteratorState_ != history_.mementos_.end())
            {
                ++history_.iteratorState_;
                (*history_.iteratorState_)->restore();
            }
        }

        ~RedoCommand() = default;

    private:
        History& history_;
};

//------------------------------------------------------------------------------

int main()
{
    
    History history;
    BankAccount account(1000, history);
    auto undo = std::make_unique<UndoCommand>(history);
    auto redo = std::make_unique<RedoCommand>(history);

    account.deposit(100);
    account.deposit(200);
    account.deposit(300);
    account.deposit(400);
    account.deposit(500);

    undo->execute();
    std::cout << "Balance after undo: " << account.get_balance() << std::endl;
    undo->execute();
    std::cout << "Balance after undo: " << account.get_balance() << std::endl;
    undo->execute();
    std::cout << "Balance after undo: " << account.get_balance() << std::endl;
    undo->execute();
    std::cout << "Balance after undo: " << account.get_balance() << std::endl;
    undo->execute();
    std::cout << "Balance after undo: " << account.get_balance() << std::endl;

    redo->execute();
    std::cout << "Balance after redo: " << account.get_balance() << std::endl;
    redo->execute();
    std::cout << "Balance after redo: " << account.get_balance() << std::endl;


    // If the iterator isn't at the end, the last mementos of the history are deleted
    account.deposit(600);
    std::cout << "Balance after redo: " << account.get_balance() << std::endl;
    redo->execute();
    std::cout << "Balance after redo: " << account.get_balance() << std::endl;
    redo->execute();
    std::cout << "Balance after redo: " << account.get_balance() << std::endl;

    return 0;
}

//------------------------------------------------------------------------------
