#pragma once
#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

/*
	A class for Digital Put Option
*/
class DigitalPutOption : public PathIndependentOption {
public:
	DigitalPutOption();
	double strike;
	double maturity;

	double payoff(double stockAtMaturity) const;
	double getMaturity() const;

};

void testDigitalPutOption();