// Created by Camilo Castillo on 28/05/2024
// Chain of Responsibility Pattern: Factory (Factories)

#include <iostream>
#include <ostream>
#include <memory>
#include <vector>
#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/chain_resp_handlers.hpp>


class ChainResponsibility
{
    public:
        void handle() { chain_[0]->handle(); }
        virtual ~ChainResponsibility() = default;

        friend class ChainPrinters;
        friend class HandlingSetters;

    protected:
        std::vector<std::shared_ptr<BaseHandler>> chain_;
};

//------------------------------------------------------------------------------

class ChainPrinters
{
    public:
        ChainPrinters() = default;

        void print(const ChainResponsibility &chain) const {
            std::cout << "\nIndex\t\tHandler\t\t\t\tEnable" << std::endl;
            for (int i = 0; i < chain.chain_.size(); ++i)
                std::cout << i << "\t\t" << chain.chain_[i]->getHandlerName() << "\t\t" 
                << chain.chain_[i]->getHandlingStatus() << std::endl;
        }

        ~ChainPrinters() = default;
};

//------------------------------------------------------------------------------

class HandlingSetters
{
    public:
        HandlingSetters() = default;

        void setHandling(ChainResponsibility &chain, int index, bool enableHandling) {
            if (index >= 0 && index < chain.chain_.size())
                chain.chain_[index]->setHandling(enableHandling);
            else
                std::cout << "Index out of range" << std::endl;
        }

        ~HandlingSetters() = default;
};

//------------------------------------------------------------------------------

class MaxChainResponsibility : public ChainResponsibility
{
    public:
        MaxChainResponsibility() : ChainResponsibility() {
            chain_.push_back(std::make_shared<AuthenticationPrimary>());
            chain_.push_back(std::make_shared<AuthenticationSecondary>());
            chain_.push_back(std::make_shared<AuthenticationTertiary>());
            
            chain_.push_back(std::make_shared<AuthorizationPrimary>());
            chain_.push_back(std::make_shared<AuthorizationSecondary>());
            chain_.push_back(std::make_shared<AuthorizationTertiary>());

            chain_.push_back(std::make_shared<ValidationPrimary>());
            chain_.push_back(std::make_shared<ValidationSecondary>());
            chain_.push_back(std::make_shared<ValidationTertiary>());

            chain_.push_back(std::make_shared<CachingPrimary>());
            chain_.push_back(std::make_shared<CachingSecondary>());
            chain_.push_back(std::make_shared<CachingTertiary>());

            for (int i = 0; i < chain_.size() - 1; ++i)
                chain_[i]->setNext(chain_[i + 1]);
            }

        ~MaxChainResponsibility() override = default;
};

//------------------------------------------------------------------------------

class MinChainResponsibility : public ChainResponsibility
{
    public:
        MinChainResponsibility() : ChainResponsibility() {
            chain_.push_back(std::make_shared<AuthenticationPrimary>());
            chain_.push_back(std::make_shared<AuthorizationPrimary>());
            chain_.push_back(std::make_shared<ValidationPrimary>());
            chain_.push_back(std::make_shared<CachingPrimary>());

            for (int i = 0; i < chain_.size() - 1; ++i)
                chain_[i]->setNext(chain_[i + 1]);
            }

        ~MinChainResponsibility() override = default;
};

//------------------------------------------------------------------------------

class MediumChainResponsibility : public ChainResponsibility
{
    public:
        MediumChainResponsibility() : ChainResponsibility() {
            chain_.push_back(std::make_shared<AuthenticationPrimary>());
            chain_.push_back(std::make_shared<AuthenticationSecondary>());
            chain_.push_back(std::make_shared<AuthorizationPrimary>());
            chain_.push_back(std::make_shared<AuthorizationSecondary>());
            chain_.push_back(std::make_shared<ValidationPrimary>());
            chain_.push_back(std::make_shared<ValidationSecondary>());
            chain_.push_back(std::make_shared<CachingPrimary>());
            chain_.push_back(std::make_shared<CachingSecondary>());

            for (int i = 0; i < chain_.size() - 1; ++i)
                chain_[i]->setNext(chain_[i + 1]);
            }

        ~MediumChainResponsibility() override = default;
};

//------------------------------------------------------------------------------
