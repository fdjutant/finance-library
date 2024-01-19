#include "MonteCarloPricer.h"
#include "matlib.h"
using namespace std;

////////////////////////
////// Constructor /////
///////////////////////

MonteCarloPricer::MonteCarloPricer() :
	nScenarios(10000) {
}

////////////////////////
////// Functions ///////
////////////////////////

double MonteCarloPricer::price(const CallOption& callOption, const BlackScholesModel& model) {
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.generateRiskNeutralPricePath(callOption.maturity, 1);
		double stockPrice = path.back();
		double payoff = callOption.payoff(stockPrice);
		total += payoff;
	}
	double mean = total / nScenarios;
	double r = model.riskFreeRate;
	double T = callOption.maturity - model.date;
	return exp(-r * T) * mean;
}

/////////////////////////
///     Testing     /////
/////////////////////////

static void testPriceCallOption() {
	rng("default");

	CallOption c;
	c.strike = 110;
	c.maturity = 2;
	
	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.05;
	m.stockPrice = 100.0;
	m.drift = 0.1;
	m.date = 1;

	MonteCarloPricer pricer;
	double price = pricer.price(c, m);
	double expected = c.price(m);
	ASSERT_APPROX_EQUAL(price, expected, 0.1);

}

void testMonteCarloPricer() {
	setDebugEnabled(false);
	TEST(testPriceCallOption);
}