#include "UpAndOutOption.h"
#include "stdafx.h"
#include "matlib.h"
using namespace std;

/*
	Payoff function for a countinuous-time knock-out call option 
*/
double UpAndOutOption::computePayoff(const std::vector<double>& prices) const {

	int Nsize = (int)prices.size();
	for (int i = 0; i < Nsize; i++) {
		if (prices[i] > barrier) {
			return 0.0;
		}
	}

	if (prices.back() > strike) {
		return prices.back() - strike;
	}
	else {
		return 0.0;
	}
}

/////////////////////////
///     Testing     /////
/////////////////////////
static void testComputePayOff() {
	
	UpAndOutOption uoo;
	uoo.barrier = 150.0;
	uoo.strike = 105.0;
	uoo.maturity = 2.0;
	
	vector<double> St = { 100.0, 99.0, 70.0, 100.2, 106.0, 149.99};
	vector<double> St2 = { 100.0, 99.0, 70.0, 150.2, 106.0, 149.99 };
	
	ASSERT_APPROX_EQUAL(uoo.computePayoff(St), 44.99, 0.001);
	ASSERT_APPROX_EQUAL(uoo.computePayoff(St2), 0.0, 0.001);
}

void testUpAndOutOption() {
	TEST(testComputePayOff);
}