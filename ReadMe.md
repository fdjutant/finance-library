# C++ Finance Toolkit: Options, Monte Carlo, Models

[MonteCarloPricer.h](https://github.com/fdjutant/finance-library/blob/master/include/MonteCarloPricer.h)
An object for computing pricing using Monte Carlo.
- price: compute price of either call option or put option derivatives using Monte Carlo calculation, with design patterns implementation.
- priceAntitheticSampling: compute price for either call option or put option derivatives using Monte Carlo calculations with implementing variance reduction techniques, particularly the antithetic sampling, to improve the prediction. 
- priceDiscreteTimeKnockOut: compute price for knock-out options
- computeDelta: compute delta of the call option price from Monte Carlo calculation.
- computeCI: compute confidence interval of the call option pricing from Monte Carlo calculation.

[UpAndOutOption.h](https://github.com/fdjutant/finance-library/blob/master/include/UpAndOutOption.h)
An object for computing payoff from knock-out call option.
- payoff: if at any point the price goes beyond barrier, then payoff will be zero. Otherwise, payoff is equal to the difference between stock price at maturity and strike price, unless stock price at maturity is lower than the strike price, at which case the payoff is zero.

[DigitalPutOption.h](https://github.com/fdjutant/finance-library/blob/master/include/DigitalCallOption.h)
An object for computing payoff from digital put option.
- payoff: if the price at maturity is below the strike price, then payoff will be 1. Otherwise, payoff will be 0.

[DigitalCallOption.h](https://github.com/fdjutant/finance-library/blob/master/include/DigitalCallOption.h)
An object for computing payoff from digital call option.
- payoff: if the price at maturity is above the strike price, then payoff will be 1. Otherwise, payoff will be 0.

[PutOption.h](https://github.com/fdjutant/finance-library/blob/master/include/PutOption.h)
An object for computing put option.
- payoff: if the price at maturity is below the strike price, then payoff will be the difference between the stock price at maturity and the strike price. Otherwise, payoff will be 0.
- price: estimate price for put option using Black-Scholes model.

[CallOption.h](https://github.com/fdjutant/finance-library/blob/master/include/CallOption.h)
An object for computing call option.
- payoff: if the price at maturity is above the strike price, then payoff will be the difference between the stock price at maturity and the strike price. Otherwise, payoff will be 0.
- price: estimate price for call option using Black-Scholes model.

[BlackScholesModel.h](https://github.com/fdjutant/finance-library/blob/master/include/BlackScholesModel.h)
An object for Black Scholes Model.
- generatePricePath: generate price path assuming assets with drift.
- generateRiskNeutralPricePath: generate price path assuming risk neutral, i.e. using risk free rate value as the drift parameter.

[matlib.h](https://github.com/fdjutant/finance-library/blob/master/include/matlib.h)
 - testMatlib: perform unit testings for functions in the library.
 - blackScholesCallPrice: compute Call price using Black Scholes model.
 - blackScholesPutPrice: compute Put price using Black Scholes model.
 - normcdf: compute the Normal distribution cumulative distributive function (CDF)
 - normInv: compute the inverse of Normal distribution cumulative distributive function (CDF)
 - solveQuadratic: find roots of quadratic equations.
 - linspace: generate a vector with equally spaced elements
 - sum: compute sum of a vector.
 - mean: compute mean of a vector.
 - standardDeviation: compute standard deviation, either by population or sample, of a vector.
 - min: find the minimum value from a vector.
 - max: find the maximum value from a vector.
 - prctile: generate a value from a vector given a percentile requested.

 [polynomial.h](https://github.com/fdjutant/finance-library/blob/master/include/polynomial.h)
 - testPolynomial: perform unit testings for functions and constructors in the library
 - evaluate: compute the co-domain of the polynomial given the domain and coefficients
 - add: sum one polynomial to another polynomial

[charts.h](https://github.com/fdjutant/finance-library/blob/master/include/charts.h)
 - testCharts: perform unit testings for functions in the library.
 - pieChart: generate an HTML pie chart (using Google Chart Template) given a paired-vector of labels and values.
 - lineChart: generate an HTML line chart (using Google Chart Template) given a paired-vector of x-and-y values.

