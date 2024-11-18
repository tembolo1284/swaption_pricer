#ifndef BLACK_MODEL_HPP
#define BLACK_MODEL_HPP

#include <cmath>
#include <functional>

class BlackModel {
public:
    // Calculate the price of a European swaption
    static double priceSwaption(double forwardRate, double strikeRate, double volatility, double maturity, double discountFactor);

private:
    // Helper function to calculate the CDF of a standard normal distribution
    static double normalCDF(double x);
};

#endif // BLACK_MODEL_HPP

