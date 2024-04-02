#include "DigitalPutOption.h"
#include "MonteCarloPricer.h"
#include "BlackScholesModel.h"
#include "matlib.h"
using namespace std;

////////////////////////
////// Constructor /////
////////////////////////

DigitalPutOption::DigitalPutOption() :
	strike(0.0),
	maturity(0.0) {
}

////////////////////////
////// Functions ///////
////////////////////////

double DigitalPutOption::payoff(double stockAtMaturity) const {
	if (stockAtMaturity < strike) {
		return 1;
	}
	else {
		return 0;
	}
}

double DigitalPutOption::getMaturity() const {
	return maturity;
}

/////////////////////////
///     Testing     /////
/////////////////////////
static void testDigitalPutOptionPrice() {
	rng("default");

	DigitalPutOption dpo;
	dpo.strike = 100;
	dpo.maturity = 2;

	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.0;
	m.stockPrice = 100.0;
	m.drift = 0.1;
	m.date = 1;

	MonteCarloPricer pricer;
	double price = pricer.price(dpo, m);
	DEBUG_PRINT("price = " << price);
	ASSERT_APPROX_EQUAL(price, 0.5, 0.1);

}

void testDigitalPutOption() {
	setDebugEnabled(true);
	TEST(testDigitalPutOptionPrice);
}