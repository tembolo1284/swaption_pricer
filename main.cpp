#include <iostream>
#include "HullWhiteModel.hpp"
#include "ExtendedVasicekModel.hpp"
#include "SABRModel.hpp"
#include "BlackModel.hpp"
#include "BinomialTreeModel.hpp"
#include "MonteCarloPricer.hpp"
#include "FiniteDifferenceMethod.hpp"

int main() {
    // Parameters
    double forwardRate = 0.025;      // Forward swap rate (2.5%)
    double strikeRate = 0.03;        // Strike rate (3.0%)
    double riskFreeRate = 0.01;      // Risk-free rate (1.0%)
    double volatility = 0.2;         // Volatility (20%)
    double maturity = 1.0;           // Time to maturity (1 year)
    double tenor = 5.0;              // Swap tenor (5 years)
    int numSimulations = 10000;      // Monte Carlo simulations
    int numSteps = 100;              // Time steps

    // Hull-White Model
    HullWhiteModel hwModel(0.03, 0.01); // Mean reversion = 0.03, volatility = 0.01
    double hwPrice = hwModel.priceSwaption(forwardRate, strikeRate, maturity, tenor);
    std::cout << "Hull-White Swaption Price: " << hwPrice << std::endl;

    // Extended Vasicek Model
    ExtendedVasicekModel evModel(0.03, 0.01, 0.02); // Mean reversion = 0.03, volatility = 0.01, long-term rate = 0.02
    double evPrice = evModel.priceSwaption(forwardRate, strikeRate, maturity, tenor);
    std::cout << "Extended Vasicek Swaption Price: " << evPrice << std::endl;

    // SABR Model
    SABRModel sabrModel(0.2, 0.5, -0.2, 0.3); // Example SABR parameters
    double sabrPrice = sabrModel.priceSwaption(forwardRate, strikeRate, maturity);
    std::cout << "SABR Swaption Price: " << sabrPrice << std::endl;

    // Black Model
    double discountFactor = std::exp(-riskFreeRate * maturity); // Discount factor
    double blackPrice = BlackModel::priceSwaption(forwardRate, strikeRate, volatility, maturity, discountFactor);
    std::cout << "Black Model Swaption Price: " << blackPrice << std::endl;

    // Binomial Tree Model
    BinomialTreeModel binomialTree(100, riskFreeRate, volatility);
    double americanOptionPrice = binomialTree.priceAmericanOption(forwardRate, strikeRate, maturity, true); // Call option
    std::cout << "Binomial Tree American Option Price: " << americanOptionPrice << std::endl;

    // Monte Carlo - European Option
    MonteCarloPricer monteCarlo(numSimulations, numSteps, riskFreeRate, volatility);
    auto europeanPayoff = [strikeRate](double finalRate) { return std::max(0.0, finalRate - strikeRate); };
    double europeanMonteCarloPrice = monteCarlo.priceEuropean(forwardRate, maturity, europeanPayoff);
    std::cout << "European Swaption Price (Monte Carlo): " << europeanMonteCarloPrice << std::endl;

    // Monte Carlo - American Option
    auto americanPayoff = [strikeRate](double finalRate) { return std::max(0.0, finalRate - strikeRate); };
    double americanMonteCarloPrice = monteCarlo.priceAmerican(forwardRate, maturity, americanPayoff);
    std::cout << "American Swaption Price (Monte Carlo): " << americanMonteCarloPrice << std::endl;

    // Finite Difference Method - European Option
    FiniteDifferenceMethod fdm(100, 100, riskFreeRate, volatility); // 100 space steps, 100 time steps
    double fdmEuropeanPrice = fdm.priceEuropeanOption(forwardRate, strikeRate, maturity, FiniteDifferenceMethod::Call);
    std::cout << "FDM European Option Price: " << fdmEuropeanPrice << std::endl;

    // Finite Difference Method - American Option
    double fdmAmericanPrice = fdm.priceAmericanOption(forwardRate, strikeRate, maturity, FiniteDifferenceMethod::Put);
    std::cout << "FDM American Option Price: " << fdmAmericanPrice << std::endl;

    return 0;
}

