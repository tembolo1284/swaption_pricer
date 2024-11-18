#ifndef BINOMIAL_TREE_MODEL_HPP
#define BINOMIAL_TREE_MODEL_HPP

class BinomialTreeModel {
public:
    BinomialTreeModel(int steps, double riskFreeRate, double volatility);

    double priceAmericanOption(double spotPrice, double strikePrice, double maturity, bool isCall = true) const;

private:
    int steps;
    double riskFreeRate;
    double volatility;
};

#endif // BINOMIAL_TREE_MODEL_HPP

