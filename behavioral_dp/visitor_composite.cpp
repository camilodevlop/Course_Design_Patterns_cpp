// Created by Camilo Castillo on 24/07/2024
// Visitor method combined with compound method.

#include <iostream>
#include <vector>
#include <memory>

class Visitor;

//------------------------------------------------------------------------------

// Element Interface

class DocumentPart
{
    public:
        virtual void accept(Visitor& visitor) = 0;
        virtual ~DocumentPart() = default;
};

//------------------------------------------------------------------------------

// Concrete Elements

class Paragraph : public DocumentPart
{
    public:
        void accept(Visitor& visitor) override;
};

class List : public DocumentPart
{
    public:
        void accept(Visitor& visitor) override;
};

class Table : public DocumentPart
{
    public:
        void accept(Visitor& visitor) override;
};

//------------------------------------------------------------------------------

// Visitor abstract class

class Visitor
{
    public:
        virtual void visitParagraph(Paragraph& paragraph) 
        {
            std::cout << "The visits for paragraph aren't defined in this visitor."
                      << std::endl;
        }

        virtual void visitList(List& list) 
        {
            std::cout << "The visits for list aren't defined in this visitor."
                      << std::endl;
        }

        virtual void visitTable(Table& table) 
        {
            std::cout << "The visits for table aren't defined in this visitor."
                      << std::endl;
        }

        virtual ~Visitor() = default;

    protected:
        Visitor() = default;
};

//------------------------------------------------------------------------------

// Concrete Visitors

class HTMLVisitor : public Visitor                  // It can't visit tables.
{
    public:
        void visitParagraph(Paragraph& paragraph) override
        {
            std::cout << "HTMLVisitor visited a paragraph." << std::endl;
        }

        void visitList(List& list) override
        {
            std::cout << "HTMLVisitor visited a list." << std::endl;
        }
};

class LaTeXVisitor : public Visitor                  // It can't visit lists.
{
    public:
        void visitParagraph(Paragraph& paragraph) override
        {
            std::cout << "LaTeXVisitor visited a paragraph." << std::endl;
        }

        void visitTable(Table& table) override
        {
            std::cout << "LaTeXVisitor visited a table." << std::endl;
        }
};

class MarkdownVisitor : public Visitor                // It can't visit paragraphs.
{
    public:
        void visitList(List& list) override
        {
            std::cout << "MarkdownVisitor visited a list." << std::endl;
        }

        void visitTable(Table& table) override
        {
            std::cout << "MarkdownVisitor visited a table." << std::endl;
        }
};

//------------------------------------------------------------------------------

// Function implementations of the concrete elements

void Paragraph::accept(Visitor& visitor)
{
    visitor.visitParagraph(*this);
}

void List::accept(Visitor& visitor)
{
    visitor.visitList(*this);
}

void Table::accept(Visitor& visitor)
{
    visitor.visitTable(*this);
}

//------------------------------------------------------------------------------

// Composite method

class CompoundDocumentPart : public DocumentPart
{
    public:
        void accept(Visitor& visitor) override
        {
            for (auto& documentPart : documentParts_)
                documentPart->accept(visitor);
        }

        void addDocumentPart(std::unique_ptr<DocumentPart>&& documentPart)
        {
            documentParts_.push_back(std::move(documentPart));
        }

        void remove(DocumentPart* documentPart)
        {
            documentParts_.erase(std::remove_if(documentParts_.begin(), documentParts_.end(),
                                                [documentPart](const std::unique_ptr<DocumentPart>& part)
                                                {
                                                    return part.get() == documentPart;
                                                }),
                                documentParts_.end());
        }

        ~CompoundDocumentPart() override = default;

    private:
        std::vector<std::unique_ptr<DocumentPart>> documentParts_;
};

//------------------------------------------------------------------------------

int main()
{
    CompoundDocumentPart compoundDocumentPart;
    compoundDocumentPart.addDocumentPart(std::make_unique<Paragraph>());
    compoundDocumentPart.addDocumentPart(std::make_unique<List>());
    compoundDocumentPart.addDocumentPart(std::make_unique<Table>());

    std::cout << "\nHTMLVisitor:" << std::endl;
    HTMLVisitor htmlVisitor;
    compoundDocumentPart.accept(htmlVisitor);

    std::cout << "\nLaTeXVisitor:" << std::endl;
    LaTeXVisitor latexVisitor;
    compoundDocumentPart.accept(latexVisitor);

    std::cout << "\nMarkdownVisitor:" << std::endl;
    MarkdownVisitor markdownVisitor;
    compoundDocumentPart.accept(markdownVisitor);

    return 0;
}

//------------------------------------------------------------------------------
