# Swaption Pricer

## Overview
This project provides a comprehensive framework for pricing swaptions using various numerical and analytical models, including:
- **Hull-White Model**
- **Extended Vasicek Model**
- **SABR Model**
- **Black Model**
- **Binomial Tree Model** (for American options)
- **Finite Difference Methods** (European and American options)
- **Monte Carlo Methods** (European and American options with early exercise)

The project includes Google Test cases for validating model implementations.

---

## Project Structure

```plaintext
swaption_pricer/

├── include/                   # Header files

│   ├── HullWhiteModel.hpp

│   ├── ExtendedVasicekModel.hpp

│   ├── SABRModel.hpp

│   ├── BlackModel.hpp

│   ├── BinomialTreeModel.hpp

│   ├── MonteCarloPricer.hpp

│   ├── FiniteDifferenceMethod.hpp

├── src/                       # Source files

│   ├── HullWhiteModel.cpp

│   ├── ExtendedVasicekModel.cpp

│   ├── SABRModel.cpp

│   ├── BlackModel.cpp

│   ├── BinomialTreeModel.cpp

│   ├── MonteCarloPricer.cpp

│   ├── FiniteDifferenceMethod.cpp

├── tests/                     # Google Test cases

│   ├── TestModels.cpp

│   ├── TestMonteCarlo.cpp

│   ├── TestBlackModel.cpp

│   ├── TestBinomialTreeModel.cpp

│   ├── TestFiniteDifferenceMethod.cpp

├── main.cpp                   # Main entry point

├── CMakeLists.txt             # CMake build configuration

├── README.md                  # Project documentation

## Build Instructions

```bash
git clone url
cd swaption_pricer
```

### Generate the build system:

```bash
cmake -B build -G Ninja
```

### Build the project:

```bash
cmake --build build

```

### Run the tests:
```bash
ctest --output-on-failure --test-dir build
```

### Run the main program:

```bash
./build/swaption_pricer
```

## Models and Features

### Hull-White Model

A one-factor interest rate model for pricing swaptions.

### Extended Vasicek Model

Generalizes the Vasicek model to include long-term mean reversion.

###SABR Model

Captures stochastic volatility and implied volatility smiles.

### Black Model

Used for European swaptions with a lognormal forward rate assumption.

### Binomial Tree Model

Handles American-style options with early exercise decisions.

### Finite Difference Methods

  - European Options: Solves the Black-Scholes PDE for European options.
  - American Options: Incorporates early exercise conditions using the Crank-Nicolson method.
