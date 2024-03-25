#pragma once
#include "BlackScholesModel.h"

/*
	A class for Call Option contracts
*/
class CallOption {
public:
	double strike;
	double maturity;

	double payoff(double stockAtMaturity) const;
	double price(const BlackScholesModel& bsm) const;

};

void testCallOption();