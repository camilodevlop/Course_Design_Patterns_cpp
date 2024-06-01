// Created by Camilo Castillo on 28/05/2024
// Chain of Responsibility Pattern: Factory (handlers)

#include <iostream>
#include <memory>

//------------------------------------------------------------------------------

class Handler
{
    public:
        virtual void setNext(std::shared_ptr<Handler>) = 0;
        virtual void handle() = 0;
        virtual ~Handler() = default;
};

//------------------------------------------------------------------------------

class BaseHandler : public Handler
{
    public:
        void setNext(std::shared_ptr<Handler> nextHandler) override {
            if (nextHandler_) nextHandler_->setNext(std::move(nextHandler));
            else nextHandler_ = std::move(nextHandler);
        }

        void handle() override {
            if (nextHandler_) nextHandler_->handle();
        }

        virtual std::string getHandlerName() const { return "Base Handler";}
        void setHandling(bool enableHandling) { enableHandling_ = enableHandling; }
        std::string getHandlingStatus() const { return enableHandling_ ? "True" : "False"; }
    
    protected:
        std::shared_ptr<Handler> nextHandler_ = nullptr;
        bool enableHandling_ = true;
};

//------------------------------------------------------------------------------

class AuthenticationPrimary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Primary Authentication" << std::endl;
            BaseHandler::handle();
        }
        
        std::string  getHandlerName() const override { return "Primary Authentication"; }
};

class AuthenticationSecondary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Secondary Authentication" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Secondary Authentication"; }
};

class AuthenticationTertiary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Tertiary Authentication" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Tertiary Authentication"; }
};

//------------------------------------------------------------------------------

class AuthorizationPrimary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Primary Authorization" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Primary Authorization"; }
};

class AuthorizationSecondary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Secondary Authorization" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Secondary Authorization"; }
};

class AuthorizationTertiary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Tertiary Authorization" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Tertiary Authorization"; }
};

//------------------------------------------------------------------------------

class ValidationPrimary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Primary Validation" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Primary Validation"; }
};

class ValidationSecondary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Secondary Validation" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Secondary Validation"; }
};

class ValidationTertiary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Tertiary Validation" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Tertiary Validation"; }
};

//------------------------------------------------------------------------------

class CachingPrimary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Primary Caching" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Primary Caching"; }
};

class CachingSecondary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Secondary Caching" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Secondary Caching"; }
};

class CachingTertiary : public BaseHandler
{
    public:
        void handle() override {
            if (enableHandling_) std::cout << "Tertiary Caching" << std::endl;
            BaseHandler::handle();
        }

        std::string  getHandlerName() const override { return "Tertiary Caching"; }
};

//------------------------------------------------------------------------------
