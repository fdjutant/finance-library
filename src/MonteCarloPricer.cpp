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
		vector<double> path = model.generateRiskNeutralPricePath(callOption.maturity, 1, 1);
		double stockPrice = path.back();
		double payoff = callOption.payoff(stockPrice);
		total += payoff;
	}
	double mean = total / nScenarios;
	double r = model.riskFreeRate;
	double T = callOption.maturity - model.date;
	return exp(-r * T) * mean;
}

double MonteCarloPricer::priceAntitheticSampling(const CallOption& callOption, const BlackScholesModel& model) {
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.generateRiskNeutralPricePath(callOption.maturity, 1, 1);
		double stockPrice = path.back();
		double payoff = callOption.payoff(stockPrice);
		vector<double> path2 = model.generateRiskNeutralPricePath(callOption.maturity, 1, -1);
		stockPrice = path2.back();
		double payoff2 = callOption.payoff(stockPrice);
		total += payoff + payoff2;
	}
	double mean = total / (2*nScenarios);
	double r = model.riskFreeRate;
	double T = callOption.maturity - model.date;
	return exp(-r * T) * mean;
}



double MonteCarloPricer::price(const PutOption& putOption, const BlackScholesModel& model) {
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.generateRiskNeutralPricePath(putOption.maturity, 1, 1);
		double stockPrice = path.back();
		double payoff = putOption.payoff(stockPrice);
		total += payoff;
	}
	double mean = total / nScenarios;
	double r = model.riskFreeRate;
	double T = putOption.maturity - model.date;
	return exp(-r * T) * mean;
}

/////////////////////////
///     Testing     /////
/////////////////////////

static void testPriceCallOptionAntitheticSampling() {
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
	double priceAntitheticSampling = pricer.priceAntitheticSampling(c, m);
	double price = pricer.price(c, m);
	double expected = c.price(m);
	DEBUG_PRINT("Predicted price using Antithetic sampling = " << priceAntitheticSampling);
	DEBUG_PRINT("predicted price = " << price);
	DEBUG_PRINT("expected price = " << expected);

	ASSERT_APPROX_EQUAL(priceAntitheticSampling, expected, 0.1);

}

static void testPricePutOption() {
	rng("default");

	PutOption p;
	p.strike = 110;
	p.maturity = 2;
	
	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.05;
	m.stockPrice = 100.0;
	m.drift = 0.1;
	m.date = 1;

	MonteCarloPricer pricer;
	double price = pricer.price(p, m);
	double expected = p.price(m);
	ASSERT_APPROX_EQUAL(price, expected, 0.1);

}

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
	setDebugEnabled(true);
	//TEST(testPriceCallOption);
	//TEST(testPricePutOption);
	TEST(testPriceCallOptionAntitheticSampling);
}