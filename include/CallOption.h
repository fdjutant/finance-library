#pragma once
#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

/*
	A class for Call Option contracts
*/
class CallOption : public PathIndependentOption {
public:
	CallOption();
	double strike;
	double maturity;

	double payoff(double stockAtMaturity) const;
	double price(const BlackScholesModel& bsm) const;

	double getMaturity() const;
};

void testCallOption();