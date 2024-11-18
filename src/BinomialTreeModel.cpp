#include "BinomialTreeModel.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

BinomialTreeModel::BinomialTreeModel(int steps, double riskFreeRate, double volatility)
    : steps(steps), riskFreeRate(riskFreeRate), volatility(volatility) {}

double BinomialTreeModel::priceAmericanOption(double spotPrice, double strikePrice, double maturity, bool isCall) const {
    double dt = maturity / steps;
    double discount = std::exp(-riskFreeRate * dt);
    double u = std::exp(volatility * std::sqrt(dt));
    double d = 1 / u;
    double p = (std::exp(riskFreeRate * dt) - d) / (u - d);

    std::vector<double> prices(steps + 1);
    std::vector<double> optionValues(steps + 1);

    for (int i = 0; i <= steps; ++i) {
        prices[i] = spotPrice * std::pow(u, steps - i) * std::pow(d, i);
        optionValues[i] = isCall ? std::max(0.0, prices[i] - strikePrice) : std::max(0.0, strikePrice - prices[i]);
    }

    for (int step = steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            optionValues[i] = discount * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);
            prices[i] = prices[i] * u / d;
            double exerciseValue = isCall ? std::max(0.0, prices[i] - strikePrice) : std::max(0.0, strikePrice - prices[i]);
            optionValues[i] = std::max(optionValues[i], exerciseValue);
        }
    }

    return optionValues[0];
}

