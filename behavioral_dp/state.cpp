// Created by Camilo Castillo on 16/07/2024
// State Pattern

#include <iostream>
#include <memory>

class DocumentState;

//------------------------------------------------------------------------------

// Context
class Document
{
    public:
        Document() = default;
        void setState(std::shared_ptr<DocumentState> state);
        void publish();
        void moderate();
        void edit();

        ~Document() = default;

    private:
        std::shared_ptr<DocumentState> state_;
};

//------------------------------------------------------------------------------

// State Interface

class DocumentState
{
    public:
        virtual void publish(Document& document)
        {
            std::cout << "Action not allowed in the current state." << std::endl;
        }

        virtual void moderate(Document& document)
        {
            std::cout << "Action not allowed in the current state." << std::endl;
        }

        virtual void edit(Document& document)
        {
            std::cout << "Action not allowed in the current state." << std::endl;
        }
        
        virtual ~DocumentState() = default;

};

//------------------------------------------------------------------------------

// Concrete States

class Draft : public DocumentState
{
    public:
        void publish(Document& document) override;
        void edit(Document& document) override
        {
            std::cout << "Document is being edited in Draft State." << std::endl;
        }
        
};

class Moderation : public DocumentState
{
    public:
        void publish(Document& document) override;
};

class Published : public DocumentState
{
    public:
        void edit(Document& document) override
        {
            std::cout << "Document is being edited in Published State." << std::endl;
        }
};

// Implementation of the transitions

void Draft::publish(Document& document)
{
    std::cout << "Document moved from Draft to Moderation." << std::endl;
    document.setState(std::make_shared<Moderation>());
}

void Moderation::publish(Document& document)
{
    std::cout << "Document moved from Moderation to Published." << std::endl;
    document.setState(std::make_shared<Published>());
}

//------------------------------------------------------------------------------

// Context (Document) Implementation

void Document::setState(std::shared_ptr<DocumentState> state)
{
    state_ = state;
}

void Document::publish()
{
    state_->publish(*this);
}

void Document::moderate()
{
    state_->moderate(*this);
}

void Document::edit()
{
    state_->edit(*this);
}

//------------------------------------------------------------------------------

int main()
{
    Document document;
    document.setState(std::make_shared<Draft>());

    // Draft State
    std::cout << "Draft State" << std::endl;
    document.edit();
    document.moderate();
    document.publish();

    // Moderation State
    std::cout << "Moderation State" << std::endl;
    document.edit();
    document.moderate();
    document.publish();

    // Published State 
    std::cout << "Published State" << std::endl;
    document.edit();
    document.moderate();
    document.publish();

    return 0;
}

//------------------------------------------------------------------------------
