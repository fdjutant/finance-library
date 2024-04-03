#pragma once
#include "stdafx.h"
#include "RealFunction.h"
#include "PathIndependentOption.h"

const double PI = 3.14159265358979;

// Generate seed for random number generator
void rng(const std::string& description);

// Generate a percentile given a vector
double prctile(const std::vector<double>& vecInput, double percentage);

// Generate a vector with equi-distant between elements
std::vector<double> linspace(double startPoint, double finalPoint, double N);

// Generate uniformly distributed random numbers 
std::vector<double> randuniform(int n);

// Generate normally distributed random numbers 
std::vector<double> randn(int n);

// Find max and min of a vector
double min(const std::vector<double>& x);
double max(const std::vector<double>& x);

// Compute sum, mean, std of a vector
double sum(const std::vector<double>& x);
double mean(const std::vector<double>& x);
double standardDeviation(const std::vector<double>& x, bool population);

// Solve roots for a quadratic equation
void solveQuadratic_NoVector(double a, double b, double c, double& root1, double& root2);
void solveQuadratic(double a, double b, double c, std::vector<double>& roots);

// Compute the cumulative distributive function (CDF) and its invrese of the normal distribution
double normcdf(double x);
double normInv(double x);

// Integrate using the rectangular rule
double integral(RealFunction& f, double a, double b, int nPoints);

// Compute total compounded saving
double valueCompounded(double principal, double interestRate, double nTimesPerYear, double duration, double contributionMonthly);

// Black-Scholes model: call option and put option
double blackScholesCallPrice(double strikePrice, double timeToMaturity, double spotPrice, double volatility, double riskFreeInterestRate);
double blackScholesPutPrice(double strikePrice, double timeToMaturity, double spotPrice, double volatility, double riskFreeInterestRate);

// Perform unit testing
void testMatlib();
