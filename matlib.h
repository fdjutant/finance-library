#pragma once
#include "stdafx.h"
static const double PI = 3.14159265358979;

/**
* Compute the mean of a vector
*/
double mean(const std::vector<double>& x);

/**
* Solve roots for a quadratic equation
*/
void solveQuadratic_NoVector(double a, double b, double c, double& root1, double& root2);
void solveQuadratic(double a, double b, double c, std::vector<double>& roots);


/**
 * Compute the cumulative distributive
 * function (CDF) of the normal distribution
*/
double normcdf(double x);

/**
 * Compute the inverse of normdcdf
*/
double normInv(double x);

/**
 * Perform unit testing
*/
void testMatlib();
void testblackScholesPutPrice(double K, double T, double S, double sigma, double r);

/**
 * black-Scholes Put Price
**/
double blackScholesPutPrice(double strikePrice, double timeToMaturity, double spotPrice, double volatility, double riskFreeInterestRate);