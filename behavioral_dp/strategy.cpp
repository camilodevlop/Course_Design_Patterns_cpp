// Created by Camilo Castillo on 16/07/2024
// Strategy Pattern

#include <iostream>
#include <memory>
#include <string>

//------------------------------------------------------------------------------

// Strategy interface

class PaymentStrategy
{
    public:
        virtual void pay(const float amount) = 0;
        virtual ~PaymentStrategy() = default;
};

// Concrete strategies

class PayPalPayment : public PaymentStrategy
{
    public:
        PayPalPayment(const std::string& email) : email_(email) {}
        void pay(const float amount) override
        {
            std::cout << "Paying " << amount << " using PayPal." << std::endl;
        }

        ~PayPalPayment() = default;


    private:
        std::string email_;
};

class CreditCardPayment : public PaymentStrategy
{
    public:
        CreditCardPayment(const std::string& name, const std::string& cardNumber) : 
                                            name_(name), cardNumber_(cardNumber) {}

        void pay(const float amount) override
        {
            std::cout << "Paying " << amount << " using Credit Card." << std::endl;
        }

        ~CreditCardPayment() = default;

    private:
        std::string name_;
        std::string cardNumber_;
};

//------------------------------------------------------------------------------

// Context

class ShoppingCart
{
    public:
        ShoppingCart(std::unique_ptr<PaymentStrategy> paymentStrategy) : 
                        paymentStrategy_(std::move(paymentStrategy)) {}

        void setPaymentStrategy (std::unique_ptr<PaymentStrategy> paymentStrategy)
        {
            paymentStrategy_ = std::move(paymentStrategy);
        }

        void pay(const float amount)
        {
            paymentStrategy_->pay(amount);
        }

        ~ShoppingCart() = default;

    private:
        std::unique_ptr<PaymentStrategy> paymentStrategy_;
};


//------------------------------------------------------------------------------

int main()
{
    std::unique_ptr<PaymentStrategy> payPal = 
                                std::make_unique<PayPalPayment>("email@mail.com");
    std::unique_ptr<PaymentStrategy> creditCard = 
                        std::make_unique<CreditCardPayment>("Camilo", "123456789");

    ShoppingCart cart(std::move(payPal));
    cart.pay(100);

    cart.setPaymentStrategy(std::move(creditCard));
    cart.pay(200);

    return 0;
}

//------------------------------------------------------------------------------
