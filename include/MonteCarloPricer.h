#pragma once
#include "stdafx.h"
#include "CallOption.h"
#include "PutOption.h"
#include "UpAndOutOption.h"
#include "BlackScholesModel.h"

/*
	A class for pricing using Monte Carlo
*/
class MonteCarloPricer {
public:
	// Constructor
	MonteCarloPricer();

	// Number of scenarios
	int nScenarios;

	// Price a call option
	double price(const CallOption& option, const BlackScholesModel& model);
	double priceAntitheticSampling(const CallOption& option, const BlackScholesModel& model);

	// Price a put option
	double price(const PutOption& option, const BlackScholesModel& model);
};

void testMonteCarloPricer();