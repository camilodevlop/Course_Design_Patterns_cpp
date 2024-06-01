// Created by Camilo Castillo on 31/05/2024
// Chain of Responsibility Pattern: Factory

#include </Users/camiloalejandro/Documents/Courses/design_patterns_cpp/behavioral_dp/chain_resp_factories.hpp>
#include <memory>


//------------------------------------------------------------------------------

int main()
{
    ChainPrinters printer;
    HandlingSetters setter;

    std::unique_ptr<ChainResponsibility> maxChain = std::make_unique<MaxChainResponsibility>();
    std::cout << "\nChain of Responsibility: MaxChainResponsibility" << std::endl;
    printer.print(*maxChain);
    std::cout << "\nHandling the chain...\n" << std::endl;
    maxChain->handle();

    std::cout << "\nEnabling/Disabling handlers..." << std::endl;
    setter.setHandling(*maxChain, 2, false);
    setter.setHandling(*maxChain, 5, false);
    setter.setHandling(*maxChain, 8, false);
    setter.setHandling(*maxChain, 11, false);
    printer.print(*maxChain);
    std::cout << "\nHandling the chain...\n" << std::endl;
    maxChain->handle();


    std::unique_ptr<ChainResponsibility> minimalChain = std::make_unique<MinChainResponsibility>();
    std::cout << "\nChain of Responsibility: MinChainResponsibility" << std::endl;
    printer.print(*minimalChain);
    std::cout << "\nHandling the chain...\n" << std::endl;
    minimalChain->handle();

    std::cout << "\nEnabling/Disabling handlers..." << std::endl;
    setter.setHandling(*minimalChain, 2, false);
    printer.print(*minimalChain);
    std::cout << "\nHandling the chain...\n" << std::endl;
    minimalChain->handle();

    
    std::unique_ptr<ChainResponsibility> mediumChain = std::make_unique<MediumChainResponsibility>();
    std::cout << "\nChain of Responsibility: MediumChainResponsibility" << std::endl;
    printer.print(*mediumChain);
    std::cout << "\nHandling the chain...\n" << std::endl;
    mediumChain->handle();

    std::cout << "\nEnabling/Disabling handlers..." << std::endl;
    setter.setHandling(*mediumChain, 2, false);
    setter.setHandling(*mediumChain, 5, false);
    printer.print(*mediumChain);
    std::cout << "\nHandling the chain...\n" << std::endl;
    mediumChain->handle();

    return 0;
}

//------------------------------------------------------------------------------
