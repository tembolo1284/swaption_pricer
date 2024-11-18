#include "FiniteDifferenceMethod.hpp"
#include <vector>
#include <cmath>
#include <algorithm>

FiniteDifferenceMethod::FiniteDifferenceMethod(int spaceSteps, int timeSteps, double riskFreeRate, double volatility)
    : spaceSteps(spaceSteps), timeSteps(timeSteps), riskFreeRate(riskFreeRate), volatility(volatility) {}

std::vector<double> FiniteDifferenceMethod::generateSpaceGrid(double spotPrice, double maxSpotPrice) const {
    std::vector<double> spaceGrid(spaceSteps + 1);
    double dx = maxSpotPrice / spaceSteps;
    for (int i = 0; i <= spaceSteps; ++i) {
        spaceGrid[i] = i * dx;
    }
    return spaceGrid;
}

std::vector<double> FiniteDifferenceMethod::generateTimeGrid(double maturity) const {
    std::vector<double> timeGrid(timeSteps + 1);
    double dt = maturity / timeSteps;
    for (int i = 0; i <= timeSteps; ++i) {
        timeGrid[i] = i * dt;
    }
    return timeGrid;
}

double FiniteDifferenceMethod::priceEuropeanOption(double spotPrice, double strikePrice, double maturity, OptionType type) const {
    auto spaceGrid = generateSpaceGrid(spotPrice, 2 * spotPrice);
    auto timeGrid = generateTimeGrid(maturity);

    std::vector<double> optionValues(spaceSteps + 1);

    for (int i = 0; i <= spaceSteps; ++i) {
        if (type == Call) {
            optionValues[i] = std::max(0.0, spaceGrid[i] - strikePrice);
        } else {
            optionValues[i] = std::max(0.0, strikePrice - spaceGrid[i]);
        }
    }

    double dx = spaceGrid[1] - spaceGrid[0];
    double dt = timeGrid[1] - timeGrid[0];
    double alpha = 0.5 * volatility * volatility * dt / (dx * dx);
    double gamma = 1 - riskFreeRate * dt - 2 * alpha;

    for (int t = timeSteps - 1; t >= 0; --t) {
        std::vector<double> newOptionValues(spaceSteps + 1);
        for (int i = 1; i < spaceSteps; ++i) {
            newOptionValues[i] = alpha * optionValues[i - 1] + gamma * optionValues[i] + alpha * optionValues[i + 1];
        }

        newOptionValues[0] = 0.0;
        newOptionValues[spaceSteps] = (type == Call) ? spaceGrid[spaceSteps] - strikePrice : strikePrice - spaceGrid[spaceSteps];

        optionValues = newOptionValues;
    }

    for (int i = 0; i < spaceSteps; ++i) {
        if (spotPrice >= spaceGrid[i] && spotPrice <= spaceGrid[i + 1]) {
            double slope = (optionValues[i + 1] - optionValues[i]) / (spaceGrid[i + 1] - spaceGrid[i]);
            return optionValues[i] + slope * (spotPrice - spaceGrid[i]);
        }
    }

    return 0.0;
}

double FiniteDifferenceMethod::priceAmericanOption(double spotPrice, double strikePrice, double maturity, OptionType type) const {
    auto spaceGrid = generateSpaceGrid(spotPrice, 2 * spotPrice);
    auto timeGrid = generateTimeGrid(maturity);

    std::vector<double> optionValues(spaceSteps + 1);

    for (int i = 0; i <= spaceSteps; ++i) {
        optionValues[i] = (type == Call) ? std::max(0.0, spaceGrid[i] - strikePrice) : std::max(0.0, strikePrice - spaceGrid[i]);
    }

    double dx = spaceGrid[1] - spaceGrid[0];
    double dt = timeGrid[1] - timeGrid[0];
    double alpha = 0.5 * volatility * volatility * dt / (dx * dx);
    double gamma = 1 - riskFreeRate * dt - 2 * alpha;

    for (int t = timeSteps - 1; t >= 0; --t) {
        std::vector<double> newOptionValues(spaceSteps + 1);
        for (int i = 1; i < spaceSteps; ++i) {
            newOptionValues[i] = alpha * optionValues[i - 1] + gamma * optionValues[i] + alpha * optionValues[i + 1];
            double exerciseValue = (type == Call) ? std::max(0.0, spaceGrid[i] - strikePrice) : std::max(0.0, strikePrice - spaceGrid[i]);
            newOptionValues[i] = std::max(newOptionValues[i], exerciseValue);
        }

        newOptionValues[0] = 0.0;
        newOptionValues[spaceSteps] = (type == Call) ? spaceGrid[spaceSteps] - strikePrice : strikePrice - spaceGrid[spaceSteps];

        optionValues = newOptionValues;
    }

    for (int i = 0; i < spaceSteps; ++i) {
        if (spotPrice >= spaceGrid[i] && spotPrice <= spaceGrid[i + 1]) {
            double slope = (optionValues[i + 1] - optionValues[i]) / (spaceGrid[i + 1] - spaceGrid[i]);
            return optionValues[i] + slope * (spotPrice - spaceGrid[i]);
        }
    }

    return 0.0;
}

