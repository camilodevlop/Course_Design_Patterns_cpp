// Created by Camilo Castillo on 04/06/2024
// Command Pattern

#include <iostream>
#include <string>
#include <vector>
#include <memory>

//------------------------------------------------------------------------------

class Application;
class Editor;
class CommandHistory;
class Backup;
class Undo;

//------------------------------------------------------------------------------

class Command
{
    public:
        Command(Application* app, Editor* editor) : app_(app), editor_(editor) {}
        virtual bool execute() = 0;
        virtual std::unique_ptr<Command> clone() const = 0;
        virtual ~Command() = default;
        
        Undo* undoObject_;

        friend class Backup;
        friend class Undo;

    protected:
        std::string backup_;
        Application* app_;
        Editor* editor_;
        Backup* backupObject_;
};

//------------------------------------------------------------------------------

class Editor
{
    public:
        std::string text = "This text is a test!";
        bool getSelection(std::string selection);
        void deleteSelection(std::string selection);
        void replaceSelection(std::string selection, std::string replacement);
        ~Editor() = default;

    private:
        std::string getLastWord(const std::string& str);
};

bool Editor::getSelection(std::string selection) {
    if (text.find(selection) != std::string::npos) return true;
    std::cout << "Selection not found" << std::endl;
    return false;
}

void Editor::deleteSelection(std::string selection) {
    if (text.find(selection) != std::string::npos)
        text.erase(text.find(selection), selection.size());
}

void Editor::replaceSelection(std::string selection, std::string replacement) {
    if (text.find(selection) != std::string::npos)
        text.replace(text.find(selection), selection.size(), replacement);
}

//------------------------------------------------------------------------------


class CommandHistory
{
    public:
        void push(std::unique_ptr<Command>& command) { 
            history_.push_back(std::move(command)); 
        }
        
        std::unique_ptr<Command> pop() {
            if (history_.empty()) return nullptr;
            std::unique_ptr<Command> command = std::move(history_.back());
            history_.pop_back();
            return command;
        }

        ~CommandHistory() = default;

    private:
        std::vector<std::unique_ptr<Command>> history_;
};

//------------------------------------------------------------------------------

class Undo
{
    public:
        void undo(Command* command) {
            command->editor_->text = command->backup_; 
        }
};

//------------------------------------------------------------------------------

// Receiver

class Application
{
    public:
        std::string clipboard;
        CommandHistory history;

        void executeCommand(Command* command) {
            if (command->execute()) {
                std::unique_ptr<Command> clone = command->clone();
                history.push(clone);
            }
        }

        void undo() {
            std::unique_ptr<Command> command = history.pop();
            if (command) command->undoObject_->undo(command.get());
        }
};

//------------------------------------------------------------------------------

class Backup
{
    public:
        void saveBackup(Command* command) { 
            command->backup_ = command->editor_->text; 
        }
};

//------------------------------------------------------------------------------

// Concrete Commands: these must be here because they need to know about the 
// Application, Editor and CommandHistory

class CopyCommand : public Command
{
    public:
        CopyCommand(Application* app, Editor* editor) : Command(app, editor) {}
        bool execute() override {
            std::string selection;
            std::cout << "\nEditor contains: " << editor_->text << "\n"
                      << "Input the text you want to copy: ";
            std::getline(std::cin, selection);

            if (editor_->getSelection(selection))
                app_->clipboard = selection;

            return false;
        }

        std::unique_ptr<Command> clone() const override {
            return nullptr;
        }

        ~CopyCommand() = default;
};

class CutCommand : public Command
{
    public:
        CutCommand(Application* app, Editor* editor) : Command(app, editor) {}
        bool execute() override {
            std::string selection;
            std::cout << "\nEditor contains: " << editor_->text << "\n"
                      << "Input the text you want to cut: ";
            std::getline(std::cin, selection);

            if (!editor_->getSelection(selection)) return false;

            backupObject_->saveBackup(this);
            app_->clipboard = selection;
            editor_->deleteSelection(selection);
            return true;
        }

        std::unique_ptr<Command> clone() const override {
            return std::make_unique<CutCommand>(*this);
        }

        ~CutCommand() = default;
};

class PasteCommand : public Command
{
    public:
        PasteCommand(Application* app, Editor* editor) : Command(app, editor) {}
        bool execute() override {
            if (app_->clipboard.empty()) return false;
            backupObject_->saveBackup(this);
            editor_->text += app_->clipboard;
            return true;
        }

        std::unique_ptr<Command> clone() const override {
            return std::make_unique<PasteCommand>(*this);
        }

        ~PasteCommand() = default;
};

class UndoCommand : public Command
{
    public:
        UndoCommand(Application* app, Editor* editor) : Command(app, editor) {}
        bool execute() override {
            app_->undo();
            return false;
        }
   
        std::unique_ptr<Command> clone() const override {
            return nullptr;
        }

        ~UndoCommand() = default;
};

//------------------------------------------------------------------------------

int main()
{
    Application app;
    Editor editor;

    CopyCommand copy(&app, &editor);
    CutCommand cut(&app, &editor);
    PasteCommand paste(&app, &editor);
    UndoCommand undo(&app, &editor);

    app.executeCommand(&copy);

    app.executeCommand(&cut);
    std::cout << "\n1st cut command - editor contains:\n" 
              << editor.text << std::endl;

    app.executeCommand(&paste);
    std::cout << "\n1st paste command- editor contains:\n" 
              << editor.text << std::endl;
    app.executeCommand(&paste);
    std::cout << "\n2nd paste command - editor contains:\n" 
              << editor.text << std::endl;
    app.executeCommand(&paste);
    std::cout << "\n3rd paste command - editor contains:\n" 
              << editor.text << std::endl;
    
    app.executeCommand(&undo);
    std::cout << "\n1st undo - editor contains what is in 2nd paste:\n" 
              << editor.text << std::endl;
    app.executeCommand(&undo);
    std::cout << "\n2nd undo - editor contains what is in 1st paste:\n" 
              << editor.text << std::endl;
    app.executeCommand(&undo);
    std::cout << "\n3rd undo - editor contains what is in the 1st cut:\n" 
              << editor.text << std::endl;
    app.executeCommand(&undo);
    std::cout << "\n4th undo - editor contains what is in before the 1st cut:\n" 
              << editor.text << std::endl;

    return 0;
}

//------------------------------------------------------------------------------

