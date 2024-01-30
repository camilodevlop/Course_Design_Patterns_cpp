// Created by Camilo Castillo on 30/01/2024
// Interface Segregation Principle (ISP)

#include <iostream>

using namespace std;

//------------------------------------------------------------------------------

class CloudStorageProvider
{
    public:
        virtual void storeFile(string& name) = 0;
        virtual void getFile(string& name) = 0;

        virtual ~CloudStorageProvider() {}
};

class CNDProvider
{
    public:
        virtual void CNDAddress() = 0;

        virtual ~CNDProvider() {}
};

class CloudHostingProvider
{
    public:
        virtual void CreatedServer(string region) = 0;
        virtual void listServers() = 0;

        virtual ~CloudHostingProvider() {}
};

//------------------------------------------------------------------------------

class Amazon : public CloudStorageProvider, public CNDProvider, public CloudHostingProvider
{
    public:
        Amazon() {}

        void storeFile(string& name) override { cout << "Amazon: storeFile " <<  name << endl; }
        void getFile(string& name) override { cout << "Amazon: getFile " << name << endl; }
        void CNDAddress() override { cout << "Amazon: CNDAddress" << endl; }
        void CreatedServer(string region) override { cout << "Amazon: CreatedServer " << region << endl; }
        void listServers() override { cout << "Amazon: listServers" << endl; }

        ~Amazon() override {}
};

class Dropbox : public CloudStorageProvider
{
    public:
        Dropbox() {}

        void storeFile(string& name) override { cout << "Dropbox: storeFile " << name << endl; }
        void getFile(string& name) override { cout << "Dropbox: getFile " << name << endl; }

        ~Dropbox() override {}
};


//------------------------------------------------------------------------------

int main()
{
    Amazon amazon;
    Dropbox dropbox;

    string name = "file.txt";

    amazon.storeFile(name);
    amazon.getFile(name);
    amazon.CNDAddress();
    amazon.CreatedServer("us-east-1");
    amazon.listServers();

    dropbox.storeFile(name);
    dropbox.getFile(name);

    return 0;
}



//------------------------------------------------------------------------------
