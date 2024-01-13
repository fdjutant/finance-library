#include "PutOption.h"
#include "stdafx.h"
#include "matlib.h"
using namespace std;

////////////////////////
////// Constructor /////
////////////////////////


/*
	Payoff function for PutOption object
*/
double PutOption::payoff(double stockAtMaturity) const {
	if (stockAtMaturity < strike) {
		return strike - stockAtMaturity;
	}
	else {
		return 0.0;
	}
}

/*
	Pricing function for PutOption object
*/
double PutOption::price(const BlackScholesModel& bsm) const {

	double S = bsm.stockPrice;
	double K = strike;
	double sigma = bsm.volatility;
	double r = bsm.riskFreeRate;
	double T = maturity - bsm.date;

	double numerator = log(S / K) + (r + sigma * sigma * 0.5) * T;
	double denominator = sigma * sqrt(T);
	double d1 = numerator / denominator;
	double d2 = d1 - denominator;

	return normcdf(-d2) * K * exp(-r * T) - normcdf(-d1) * S;
}

/////////////////////////
///     Testing     /////
/////////////////////////

static void testPutOptionPayOff() {
	PutOption putOption;
	putOption.strike = 100.0;
	ASSERT_APPROX_EQUAL(putOption.payoff(105.0), 0.0, 0.001);
	ASSERT_APPROX_EQUAL(putOption.payoff(95.0), 5.0, 0.001);
}

static void testPutOptionPrice() {
	PutOption putOption;
	putOption.strike = 105.0;
	putOption.maturity = 2.0;

	BlackScholesModel bsm;
	bsm.date = 1.0;
	bsm.volatility = 0.1;
	bsm.riskFreeRate = 0.05;
	bsm.stockPrice = 100.0;

	double price = putOption.price(bsm);
	ASSERT_APPROX_EQUAL(price, 3.925, 0.001);
}

void testPutOption() {
	
	setDebugEnabled(true);
	TEST(testPutOptionPayOff);
	TEST(testPutOptionPrice);

}