#include "ExtendedVasicekModel.hpp"
#include <random>
#include <cmath>

double ExtendedVasicekModel::priceSwaption(double swapRate, double strikeRate, double maturity, double tenor) const {
    double d1 = (swapRate - strikeRate) / (volatility * std::sqrt(maturity));
    double d2 = d1 - volatility * std::sqrt(maturity);

    auto normalCDF = [](double x) { return 0.5 * (1 + std::erf(x / std::sqrt(2))); };

    return (swapRate * normalCDF(d1) - strikeRate * normalCDF(d2)) * tenor;
}

std::vector<double> ExtendedVasicekModel::generateShortRatePath(double initialRate, double maturity, int steps) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);

    std::vector<double> rates(steps + 1);
    rates[0] = initialRate;

    double dt = maturity / steps;
    for (int i = 1; i <= steps; ++i) {
        double drift = meanReversion * (longTermRate - rates[i - 1]) * dt;
        double diffusion = volatility * std::sqrt(dt) * dist(gen);
        rates[i] = rates[i - 1] + drift + diffusion;
    }

    return rates;
}

