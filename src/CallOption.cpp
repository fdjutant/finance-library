#include "CallOption.h"
#include "stdafx.h"
#include "matlib.h"
using namespace std;

/*
    Payoff function for CallOption object
*/
double CallOption::payoff(double stockAtMaturity) const {
    if (stockAtMaturity > strike) {
        return stockAtMaturity - strike;
    }
    else {
        return 0.0;
    }
}

/*
    Pricing function for CallOption object
*/
double CallOption::price(const BlackScholesModel& bsm) const {

    double S = bsm.stockPrice;
    double K = strike;
    double sigma = bsm.volatility;
    double r = bsm.riskFreeRate;
    double T = maturity - bsm.date;

    double numerator = log(S / K) + (r + sigma * sigma * 0.5) * T;
    double denominator = sigma * sqrt(T);
    double d1 = numerator / denominator;
    double d2 = d1 - denominator;

    return S * normcdf(d1) - exp(-r * T) * K * normcdf(d2);
}
