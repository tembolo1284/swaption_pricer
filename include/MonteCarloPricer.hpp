#ifndef MONTE_CARLO_PRICER_HPP
#define MONTE_CARLO_PRICER_HPP

#include <functional>

class MonteCarloPricer {
private:
    int numSimulations;
    int numSteps;
    double riskFreeRate;
    double volatility;

public:
    MonteCarloPricer(int simulations, int steps, double rate, double vol)
        : numSimulations(simulations), numSteps(steps), riskFreeRate(rate), volatility(vol) {}

    double priceEuropean(double spotPrice, double timeToMaturity, const std::function<double(double)>& payoffFunc) const;

    double priceAmerican(double spotPrice, double timeToMaturity, const std::function<double(double)>& payoffFunc) const;
};

#endif // MONTE_CARLO_PRICER_HPP

