#include "MonteCarloPricer.hpp"
#include <random>
#include <cmath>

double MonteCarloPricer::priceEuropean(double spotPrice, double timeToMaturity, const std::function<double(double)>& payoffFunc) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);

    double dt = timeToMaturity / numSteps;
    double drift = (riskFreeRate - 0.5 * volatility * volatility) * dt;
    double diffusion = volatility * std::sqrt(dt);

    double payoffSum = 0.0;

    for (int i = 0; i < numSimulations; ++i) {
        double price = spotPrice;

        for (int j = 0; j < numSteps; ++j) {
            price *= std::exp(drift + diffusion * dist(gen));
        }

        payoffSum += payoffFunc(price);
    }

    return std::exp(-riskFreeRate * timeToMaturity) * (payoffSum / numSimulations);
}

double MonteCarloPricer::priceAmerican(double spotPrice, double timeToMaturity, const std::function<double(double)>& payoffFunc) const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(0.0, 1.0);

    double dt = timeToMaturity / numSteps;
    double drift = (riskFreeRate - 0.5 * volatility * volatility) * dt;
    double diffusion = volatility * std::sqrt(dt);

    std::vector<double> payoffs(numSimulations, 0.0);

    for (int i = 0; i < numSimulations; ++i) {
        double price = spotPrice;

        for (int j = 0; j < numSteps; ++j) {
            price *= std::exp(drift + diffusion * dist(gen));
            double exerciseValue = payoffFunc(price);
            double continuationValue = payoffs[i] * std::exp(-riskFreeRate * dt);
            payoffs[i] = std::max(exerciseValue, continuationValue);
        }
    }

    return std::accumulate(payoffs.begin(), payoffs.end(), 0.0) / numSimulations;
}

