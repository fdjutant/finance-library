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

double MonteCarloPricer::price(const PathIndependentOption& option, const BlackScholesModel& model) {
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.generateRiskNeutralPricePath(option.getMaturity(), 1, 1);
		double stockPrice = path.back();
		double payoff = option.payoff(stockPrice);
		total += payoff;
	}
	double mean = total / nScenarios;
	double r = model.riskFreeRate;
	double T = option.getMaturity() - model.date;
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

double MonteCarloPricer::priceDiscreteTimeKnockOut(const UpAndOutOption& UpAndOutOption, const BlackScholesModel& model) {
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.generateRiskNeutralPricePath(UpAndOutOption.maturity, 100, 1);
		double payoff = UpAndOutOption.computePayoff(path);
		total += payoff;
	}
	double mean = total / nScenarios;
	double r = model.riskFreeRate;
	double T = UpAndOutOption.maturity - model.date;
	return exp(-r * T) * mean;
}

double MonteCarloPricer::computeDelta(const CallOption& callOption, const BlackScholesModel& model) {
	double h = model.stockPrice * pow(10, -6);
	
	double total1 = 0.0;
	double total2 = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		vector<double> generatedPrice = model.generateRiskNeutralPricePathToComputeDelta(callOption.maturity, 1, 1);
		
		double stockPrice1 = generatedPrice[0];
		double stockPrice2 = generatedPrice[1];

		double payoff1 = callOption.payoff(stockPrice1);
		double payoff2 = callOption.payoff(stockPrice2);

		total1 += payoff1;
		total2 += payoff2;
	}
	double mean1 = total1 / nScenarios;
	double mean2 = total2 / nScenarios;
	double r = model.riskFreeRate;
	double T = callOption.maturity - model.date;
	double pricing1 = exp(-r * T) * mean1;
	double pricing2 = exp(-r * T) * mean2;
	DEBUG_PRINT("pricing1 = " << pricing1 << "\n" << "pricing2 = " << pricing2);

	return (pricing1 - pricing2) / (2 * h);
}

vector<double> MonteCarloPricer::computeCI(const CallOption& callOption, const BlackScholesModel& model) const {
	
	vector<double> price;
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		vector<double> path = model.generateRiskNeutralPricePath(callOption.maturity, 1, 1);
		double stockPrice = path.back();
		double payoff = callOption.payoff(stockPrice);
		total += payoff;
		price.push_back(payoff);
	}
	double r = model.riskFreeRate;
	double T = callOption.maturity - model.date;
	double meanPrice = exp(-r * T) * (total / nScenarios);
	double std = exp(-r * T) * standardDeviation(price, true);

	// compute the confidence interval
	vector<double> CI(2, 0);
	double Zscore = 1.96; // 95% confidence interval
	CI[0] = meanPrice - Zscore * (std / sqrt(nScenarios));
	CI[1] = meanPrice + Zscore * (std / sqrt(nScenarios));

	return CI;
}

/////////////////////////
///     Testing     /////
/////////////////////////


static void testComputeCI() {

	rng("default");

	CallOption c;
	c.strike = 110.0;
	c.maturity = 2.0;

	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.05;
	m.stockPrice = 106.0;
	m.drift = 0.01;
	m.date = 1.0;

	MonteCarloPricer pricer;
	vector<double> CI = pricer.computeCI(c, m);
	double price = pricer.price(c, m);

	DEBUG_PRINT("price: " << price);
	DEBUG_PRINT("CI: " << CI[0] << " and " << CI[1]);
	ASSERT(CI[0] > 0.0 && CI[1] > 0.0);
}

static void testComputeDelta() {
	rng("default");

	CallOption c;
	c.strike = 105.0;
	c.maturity = 2.0;

	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.05;
	m.stockPrice = 106.0;
	m.drift = 0.1;
	m.date = 1;

	MonteCarloPricer pricer;
	double delta = pricer.computeDelta(c, m);

	DEBUG_PRINT("delta = " << delta);
	ASSERT((delta > -1) & (delta < 1));

}

static void testPriceDiscreteTimeKnockOut() {
	rng("default");

	UpAndOutOption uoo;
	uoo.strike = 105.0;
	uoo.maturity = 2.0;
	uoo.barrier = 1000.0; // price should be about the same with call option because barrier is high

	CallOption c;
	c.strike = 105.0;
	c.maturity = 2.0;

	PutOption p;
	p.strike = 105.0;
	p.maturity = 2.0;
	
	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.05;
	m.stockPrice = 100.0;
	m.drift = 0.1;
	m.date = 1;

	MonteCarloPricer pricer;
	double priceDiscreteTimeKnockOut = pricer.priceDiscreteTimeKnockOut(uoo, m);
	double expected = c.price(m);

	ASSERT_APPROX_EQUAL(priceDiscreteTimeKnockOut, expected, 0.1);
}

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
	double price = pricer.price(c, m); // with a regular path generator
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

static void testPriceCallPutOption() {
	rng("default");

	CallOption c;
	c.strike = 110;
	c.maturity = 2;
	
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
	double priceC = pricer.price(c, m);
	double expectedC = c.price(m);
	double priceP = pricer.price(p, m);
	double expectedP = p.price(m);
	DEBUG_PRINT("Monte Carlo Call Option price: " << priceP << " and " << priceC);
	ASSERT_APPROX_EQUAL(priceC, expectedC, 0.1);
	ASSERT_APPROX_EQUAL(priceP, expectedP, 0.1);

}

void testMonteCarloPricer() {
	setDebugEnabled(true);
	TEST(testPriceCallPutOption);
	//TEST(testPriceCallOptionAntitheticSampling);
	//TEST(testPriceDiscreteTimeKnockOut);
	//TEST(testComputeDelta);
	//TEST(testComputeCI);
}