// Created by Camilo Castillo on 22/05/2024
// Chain of Responsibility Pattern

#include <iostream>
#include <memory>
#include <vector>

// Similarities between this example and the classic one.
// Handler is replaced by ComponentWithContextualHelp.
// Abstract class Handler is replaced by Component.
// ConcreteHandler is replaced by Button, Panel, and Dialog.

//------------------------------------------------------------------------------

class ComponentWithContextualHelp
{
    public:
        virtual void setNext(std::unique_ptr<ComponentWithContextualHelp> next) = 0;
        virtual void showHelp() = 0;
        virtual ~ComponentWithContextualHelp() = default;
};

//------------------------------------------------------------------------------

class Component : public ComponentWithContextualHelp
{
    public:
        Component() = default;

        void setNext(std::unique_ptr<ComponentWithContextualHelp> next) override {
            if (next_) next_->setNext(std::move(next));
            else next_ = std::move(next);
        }

        void showHelp() override {
            if (next_) next_->showHelp();
        }

    protected:
        std::unique_ptr<ComponentWithContextualHelp> next_ = nullptr;
};

//------------------------------------------------------------------------------

class Button : public Component
{
    public:
        Button(const std::string& buttonName) : buttonName_(buttonName) {}

        void showHelp() override {
            std::cout << buttonName_;
            Component::showHelp();
        }
    private:
        std::string buttonName_;
};

//------------------------------------------------------------------------------

class Panel : public Component
{
    public:
        Panel(const std::string& panelName) : panelName_(panelName) {}

        void showHelp() override {
            std::cout << panelName_;
            Component::showHelp();
        }
    private:
        std::string panelName_;
};

class Dialog : public Component
{
    public:
        Dialog(const std::string& dialogName) : dialogName_(dialogName) {}

        void showHelp() override {
            std::cout << dialogName_;
            Component::showHelp();
        }
    private:
        std::string dialogName_;
};

//------------------------------------------------------------------------------

int main()
{
    // Chain of responsibility 1
    Component root;
    std::unique_ptr<Component> buttonGrayscale = std::make_unique<Button>("Grayscale -> ");
    std::unique_ptr<Component> panelColor = std::make_unique<Panel>("Color -> ");
    std::unique_ptr<Component> panelSettings = std::make_unique<Panel>("Settings -> ");
    std::unique_ptr<Component> dialogPrint = std::make_unique<Dialog>("Print help text");
    
    root.setNext(std::move(buttonGrayscale));
    root.setNext(std::move(panelColor));
    root.setNext(std::move(panelSettings));
    root.setNext(std::move(dialogPrint));

    std::cout << "Help text: " << std::endl;
    root.showHelp();

    // Chain of responsibility 2
    Component root2;
    std::unique_ptr<Component> buttonSave = std::make_unique<Button>("Save button -> ");
    std::unique_ptr<Component> panelFile = std::make_unique<Panel>("File -> ");
    std::unique_ptr<Component> panelSave = std::make_unique<Panel>("Save -> ");
    std::unique_ptr<Component> dialogSave = std::make_unique<Dialog>("Save message");

    buttonSave->setNext(std::move(panelFile));
    buttonSave->setNext(std::move(panelSave));
    buttonSave->setNext(std::move(dialogSave));

    std::cout << "\n\nSave process: " << std::endl;
    buttonSave->showHelp();

    return 0;
}

//------------------------------------------------------------------------------
