#include "SABRModel.hpp"
#include <cmath>

double SABRModel::priceSwaption(double forwardRate, double strikeRate, double maturity) const {
    double F = forwardRate;
    double K = strikeRate;

    if (F == K) {
        return alpha * std::pow(F, beta);
    }

    double logFK = std::log(F / K);
    double z = (nu / alpha) * std::pow(F * K, (1 - beta) / 2) * logFK;
    double xz = std::log((std::sqrt(1 - 2 * rho * z + z * z) + z - rho) / (1 - rho));

    double impliedVolatility = alpha * std::pow(F * K, (1 - beta) / 2) * z / xz;

    double d1 = (logFK + 0.5 * impliedVolatility * impliedVolatility * maturity) /
                (impliedVolatility * std::sqrt(maturity));
    double d2 = d1 - impliedVolatility * std::sqrt(maturity);

    auto normalCDF = [](double x) { return 0.5 * (1 + std::erf(x / std::sqrt(2))); };

    return F * normalCDF(d1) - K * normalCDF(d2);
}

