#ifndef FINITE_DIFFERENCE_METHOD_HPP
#define FINITE_DIFFERENCE_METHOD_HPP

#include <vector>
#include <functional>

class FiniteDifferenceMethod {
public:
    enum OptionType { Call, Put };

    FiniteDifferenceMethod(int spaceSteps, int timeSteps, double riskFreeRate, double volatility);

    double priceEuropeanOption(double spotPrice, double strikePrice, double maturity, OptionType type) const;
    double priceAmericanOption(double spotPrice, double strikePrice, double maturity, OptionType type) const;

private:
    int spaceSteps;
    int timeSteps;
    double riskFreeRate;
    double volatility;

    std::vector<double> generateSpaceGrid(double spotPrice, double maxSpotPrice) const;
    std::vector<double> generateTimeGrid(double maturity) const;
};

#endif // FINITE_DIFFERENCE_METHOD_HPP

