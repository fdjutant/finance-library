#pragma once
#include "stdafx.h"
#include "CallOption.h"
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
	double price(const CallOption& option, const const BlackScholesModel& model);
};

void testMonteCarloPricer();