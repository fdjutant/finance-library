#pragma once
#include "stdafx.h"

/*
	A class for BlackScholesModel object
*/
class BlackScholesModel {
public:
	// constructor
	BlackScholesModel(); 
	
	double drift;
	double stockPrice;
	double volatility;
	double riskFreeRate;
	double date;

	std::vector<double> generatePricePath(double toDate, int nSteps) const;
	std::vector<double> generateRiskNeutralPricePath(double toDate, int nSteps) const;

private:
	std::vector<double> generatePricePath(double toDate, int nSteps, double drift) const;
};

void testBlackScholesModel();