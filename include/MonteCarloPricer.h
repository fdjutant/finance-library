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
	double price(const PathIndependentOption& option, const BlackScholesModel& model);
	double priceAntitheticSampling(const CallOption& option, const BlackScholesModel& model);
	double priceDiscreteTimeKnockOut(const UpAndOutOption& option, const BlackScholesModel& model);
	double computeDelta(const CallOption& callOption, const BlackScholesModel& model);
	std::vector<double> computeCI(const CallOption& callOption, const BlackScholesModel& model) const;

};

void testMonteCarloPricer();