#ifndef SABR_MODEL_HPP
#define SABR_MODEL_HPP

class SABRModel {
private:
    double alpha; // Volatility level
    double beta;  // Elasticity of volatility
    double rho;   // Correlation between forward rate and volatility
    double nu;    // Volatility of volatility

public:
    SABRModel(double alpha, double beta, double rho, double nu)
        : alpha(alpha), beta(beta), rho(rho), nu(nu) {}

    double priceSwaption(double forwardRate, double strikeRate, double maturity) const;
};

#endif // SABR_MODEL_HPP

