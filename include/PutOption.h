#pragma once
#include "BlackScholesModel.h"

/*
	An object for Put Option contracts
*/
class PutOption {
public:
	PutOption();
	double strike;
	double maturity;

	double payoff(double stockAtMaturity) const;
	double price(const BlackScholesModel& bsm) const;
};

void testPutOption();