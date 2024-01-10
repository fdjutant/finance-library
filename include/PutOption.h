#pragma once
#include "BlackScholesModel.h"

/*
	A call for Put Option contracts
*/
class PutOption {
public:
	double strike;
	double maturity;

	double payoff(double stockAtMaturity) const;
	double price(const BlackScholesModel& bsm) const;
};

void testPutOption();