#pragma once
#include "stdafx.h"

/*
	A class for BlackScholesModel object
*/
class BlackScholesModel {
public:

	BlackScholesModel(); 
	
	double drift;
	double stockPrice;
	double volatility;
	double riskFreeRate;
	double date;

	std::vector<double> generatePricePath(double toDate, int nSteps, int optionGenerator) const;
	std::vector<double> generateRiskNeutralPricePath(double toDate, int nSteps, int optionGenerator) const;
	std::vector<double> generateRiskNeutralPricePathToComputeDelta(double toDate, int nSteps, int optionGenerator) const;

private:
	std::vector<double> generatePricePath(double toDate, int nSteps, double drift, int optionGenerator) const;
	std::vector<double> generatePricePathToComputeDelta(double toDate, int nSteps, double drift, int optionGenerator) const;

};

void testBlackScholesModel();