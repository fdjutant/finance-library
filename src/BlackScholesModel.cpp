#include "BlackScholesModel.h"
#include "stdafx.h"
#include "matlib.h"
#include "LineChart.h"
using namespace std;

////////////////////////
////// Constructor /////
///////////////////////

BlackScholesModel::BlackScholesModel() :
	drift(0.0),
	stockPrice(0.0),
	volatility(0.0),
	riskFreeRate(0.0),
	date(0.0) {
}

////////////////////////
////// Functions ///////
////////////////////////

vector<double> BlackScholesModel::generatePricePath(double toDate, int nSteps) const {
	return generatePricePath(toDate, nSteps, drift);
}

vector<double> BlackScholesModel::generateRiskNeutralPricePath(double toDate, int nSteps) const {
	return generatePricePath(toDate, nSteps, riskFreeRate);
}

vector<double>  BlackScholesModel::generatePricePath(double toDate, int nSteps, double drift) const {

	vector<double> path(nSteps, 0.0);
	vector<double> epsilon = randn(nSteps);

	double dt = (toDate - date) / nSteps;
	double a = (drift - volatility * volatility * 0.5) * dt;
	double b = volatility * sqrt(dt);

	double currentLogS = log(stockPrice);
	for (int i = 0; i < nSteps; i++) {
		double dLogS = a + b * epsilon[i];
		double logS = currentLogS + dLogS;
		path[i] = exp(logS);
		currentLogS = logS;
	}
	return path;
}

/////////////////////////
///     Testing     /////
/////////////////////////

static void testVisually() {
	
	BlackScholesModel bsm;
	bsm.riskFreeRate = 0.05;
	bsm.volatility = 0.1;
	bsm.stockPrice = 100.0;
	bsm.date = 2.0;

	int nSteps = 10000;
	double maturity = 4.0;

	vector<double> path = bsm.generatePricePath(maturity, nSteps);
	double dt = (maturity - bsm.date) / nSteps;
	vector<double> times = linspace(dt, maturity, nSteps);

	LineChart lineChart;
	lineChart.setSeries(times, path);
	lineChart.writeAsHTML("./outputFiles/examplePricePath.html");
}

static void testGenerateRiskNeutralPricePath() {
	
	BlackScholesModel bsm;
	bsm.riskFreeRate = 0.05;
	bsm.volatility = 0.1;
	bsm.stockPrice = 100.0;
	bsm.date = 2.0;

	int nPaths = 10000;
	int nSteps = 5;
	double maturity = 4.0;

	vector<double> finalPrices(nPaths, 0.0);
	for (int i = 0; i < nPaths; i++) {
		vector<double> path = bsm.generateRiskNeutralPricePath(maturity, nSteps);
		finalPrices[i] = path.back(); // extract the latest timepoint pricepoint
	}

	ASSERT_APPROX_EQUAL(mean(finalPrices), exp(bsm.riskFreeRate * 2.0) * bsm.stockPrice, 0.5);

}

void testBlackScholesModel() {
	setDebugEnabled(false);
	//TEST(testVisually);
	TEST(testGenerateRiskNeutralPricePath);
}