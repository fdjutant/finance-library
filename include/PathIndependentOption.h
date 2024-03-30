#pragma once
#include "stdafx.h"

class PathIndependentOption {
public:
	
	// virtual destructor
	virtual ~PathIndependentOption(){}

	// returns the payoff at maturity
	virtual double payoff(double finalStokePrice) const = 0;

	// returns the maturity of the option
	virtual double getMaturity() const = 0;

};