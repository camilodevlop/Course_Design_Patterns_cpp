// Created by Camilo Castillo on 25/04/2024
// Decorator Pattern

#include <iostream>
#include <memory>

//------------------------------------------------------------------------------

class DataSource
{
    public:
        virtual void writeData(const std::string& data) = 0;
        virtual std::string readData() const = 0;
        virtual ~DataSource() = default;
};

//------------------------------------------------------------------------------

class FileDataSource: public DataSource
{
    public:
        FileDataSource(const std::string& filename ): filename_(filename) {}
        
        void writeData(const std::string& data) override
        { std::cout << "Writing data to file " << filename_ << std::endl; }

        std::string readData() const override
        { 
            std::cout << "Reading data from file " << filename_ << std::endl;
            return "data";
        }

        ~FileDataSource() override = default;

    private:
        std::string filename_;
};

//------------------------------------------------------------------------------

class DataSourceDecorator: public DataSource
{
    public:
        DataSourceDecorator(DataSource* source): source_(source) { }

        void writeData(const std::string& data) override
        { source_->writeData(data); }

        std::string readData() const override
        { return source_->readData(); }
        
        ~DataSourceDecorator() override = default;

    private:
        DataSource* source_;
};

class EncryptionDecorator: public DataSourceDecorator
{
    public:
        EncryptionDecorator(DataSource* source): DataSourceDecorator(source) { }

        void writeData(const std::string& data) override
        { 
            std::cout << "Encrypting data" << std::endl;
            DataSourceDecorator::writeData(data);
        }

        std::string readData() const override
        { 
            std::cout << "Decrypting data" << std::endl;
            return DataSourceDecorator::readData();
        }

        ~EncryptionDecorator() override = default;
};

class CompressionDecorator: public DataSourceDecorator
{
    public:
        CompressionDecorator(DataSource* source): DataSourceDecorator(source) { }

        void writeData(const std::string& data) override
        { 
            std::cout << "Compressing data" << std::endl;
            DataSourceDecorator::writeData(data);
        }

        std::string readData() const override
        { 
            std::cout << "Decompressing data" << std::endl;
            return DataSourceDecorator::readData();
        }

        ~CompressionDecorator() override = default;
};

//------------------------------------------------------------------------------

class SalaryManager
{
    public:
        SalaryManager(DataSource* source): source_(source) { }

        void writeData(const std::string& data)
        { source_->writeData(data); }

        std::string readData() const
        { return source_->readData(); }
        
        ~SalaryManager() = default;

    private:
        DataSource* source_;
};

//------------------------------------------------------------------------------

int main() 
{
    std::unique_ptr<DataSource> source = std::make_unique<FileDataSource>("data.txt");
    source = std::make_unique<EncryptionDecorator>(source.release());
    source = std::make_unique<CompressionDecorator>(source.release());

    SalaryManager manager(source.get());
    manager.writeData("data");
    manager.readData();

    return 0;
}

//------------------------------------------------------------------------------
