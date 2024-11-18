#ifndef HULL_WHITE_MODEL_HPP
#define HULL_WHITE_MODEL_HPP

#include <vector>

class HullWhiteModel {
private:
    double meanReversion;  // Speed of mean reversion (a)
    double volatility;     // Volatility of the short rate (sigma)

public:
    HullWhiteModel(double reversion, double vol)
        : meanReversion(reversion), volatility(vol) {}

    double priceSwaption(double swapRate, double strikeRate, double maturity, double tenor) const;

    std::vector<double> generateShortRatePath(double initialRate, double maturity, int steps) const;
};

#endif // HULL_WHITE_MODEL_HPP

