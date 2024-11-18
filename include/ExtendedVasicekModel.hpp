#ifndef EXTENDED_VASICEK_MODEL_HPP
#define EXTENDED_VASICEK_MODEL_HPP

#include <vector>

class ExtendedVasicekModel {
private:
    double meanReversion;   // Mean reversion speed (a)
    double volatility;      // Volatility of the short rate (sigma)
    double longTermRate;    // Long-term interest rate (b)

public:
    ExtendedVasicekModel(double reversion, double vol, double longTermRate)
        : meanReversion(reversion), volatility(vol), longTermRate(longTermRate) {}

    double priceSwaption(double swapRate, double strikeRate, double maturity, double tenor) const;

    std::vector<double> generateShortRatePath(double initialRate, double maturity, int steps) const;
};

#endif // EXTENDED_VASICEK_MODEL_HPP

