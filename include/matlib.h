#pragma once
#include "stdafx.h"
static const double PI = 3.14159265358979;

/*
	Generate a vector with equi-distant between elements
*/
std::vector<double> linspace(double startPoint, double finalPoint, double N);

/*
	Generate a random sampling that follows a uniform distribution and normal distribution
*/
std::vector<double> randuniform(int n);
std::vector<double> randn(int n);

/*
	Find max and min of a vector
*/
double min(const std::vector<double>& x);
double max(const std::vector<double>& x);

/*
	Compute sum, mean, std of a vector
*/
double sum(const std::vector<double>& x);
double mean(const std::vector<double>& x);
double standardDeviation(const std::vector<double>& x, bool population);

/*
	Solve roots for a quadratic equation
*/
void solveQuadratic_NoVector(double a, double b, double c, double& root1, double& root2);
void solveQuadratic(double a, double b, double c, std::vector<double>& roots);

/*
	Compute the cumulative distributive function (CDF) of the normal distribution
*/
double normcdf(double x);

/*
	Compute the inverse of normdcdf
*/
double normInv(double x);

/*
	Black-Scholes Put Price
*/
double blackScholesPutPrice(double strikePrice, double timeToMaturity, double spotPrice, double volatility, double riskFreeInterestRate);

/*
	Perform unit testing
*/
void testMatlib();
