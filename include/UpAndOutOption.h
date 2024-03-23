#pragma once
#include "BlackScholesModel.h"

/*
	A class for a countinuous-time knock-out call option with strike K, barrier B, and maturity T, in an option which either pays max{S_T - K, 0} if St < B for all [0,T] or pays 0 otherwise.
*/
class UpAndOutOption {
public:
	double strike;
	double barrier;
	double maturity;
	
	double computePayoff(const std::vector<double>& prices) const;
	/*double price(const BlackScholsModel& bsm) const;*/
};

void testUpAndOutOption();