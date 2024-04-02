#include "DigitalCallOption.h"
#include "MonteCarloPricer.h"
#include "BlackScholesModel.h"
#include "matlib.h"
#include "CallOption.h"
using namespace std;

////////////////////////
////// Constructor /////
////////////////////////

DigitalCallOption::DigitalCallOption() :
	strike(0.0),
	maturity(0.0) {
}

////////////////////////
////// Functions ///////
////////////////////////

double DigitalCallOption::payoff(double stockAtMaturity) const {
	if (stockAtMaturity > strike) {
		return 1;
	}
	else {
		return 0;
	}
}

double DigitalCallOption::getMaturity() const {
	return maturity;
}

/////////////////////////
///     Testing     /////
/////////////////////////
static void testDigitalCallOptionPayoff() {
	rng("default");

	DigitalCallOption dco;
	dco.strike = 100;
	dco.maturity = 2;

	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.0;
	m.stockPrice = 100.0;
	m.drift = 0.1;
	m.date = 1;

	MonteCarloPricer pricer;
	double price = pricer.price(dco, m);
	//double payoff = dco.payoff(stockAtMaturity);
	DEBUG_PRINT("price = " << price);
	ASSERT_APPROX_EQUAL(price, 0.5, 0.1);

}

void testDigitalCallOption() {
	setDebugEnabled(true);
	TEST(testDigitalCallOptionPayoff);
}