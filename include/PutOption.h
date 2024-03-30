#pragma once
#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

/*
	An object for Put Option contracts
*/
class PutOption : public PathIndependentOption {
public:
	PutOption();
	double strike;
	double maturity;

	double payoff(double stockAtMaturity) const;
	double price(const BlackScholesModel& bsm) const;
	double getMaturity() const;
};

void testPutOption();