#pragma once
#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

/*
	A class for Digital Call Option
*/
class DigitalCallOption : public PathIndependentOption {
public:
	DigitalCallOption();
	double strike;
	double maturity;

	double payoff(double stockAtMaturity) const;
	double getMaturity() const;

};

void testDigitalCallOption();