#pragma once
/*
	A class for BlackScholesModel object
*/
class BlackScholesModel {
public:
	BlackScholesModel();
	double stockPrice;
	double volatility;
	double riskFreeRate;
	double date;
};