#include "RectangleRulePricer.h"
#include "stdafx.h"
#include <limits>
#include "RealFunction.h"
#include "matlib.h"
#include "CallOption.h"

////////////////////////
////// Functions ///////
////////////////////////

double RectangularPricer::price(const BlackScholesModel& model, const PathIndependentOption& option) {

	class IntegrandPricingPDF : public RealFunction {
	public:
		const BlackScholesModel& model;
		const PathIndependentOption& option;

		double evaluate(double x) {
			double t = option.getMaturity();
			double sigma = model.volatility;
			double So = model.stockPrice;
			double muTilde = model.riskFreeRate - 0.5*sigma*sigma;
			
			double pricePDF = (1 / (sigma * sqrt(2 * PI * t))) * exp(-pow((x - log(So) - muTilde * t), 2) / (2 * sigma * sigma * t));
			double payoff = option.payoff(exp(x));

			if (isfinite(payoff)) {
				return payoff * pricePDF;
			}
			else {
				return 0;
			}

		}

		IntegrandPricingPDF(const BlackScholesModel& model, const PathIndependentOption& option) : model(model), option(option) {}
	};

	IntegrandPricingPDF integrand(model, option);
	double expectation = integralOverR(integrand, 1000);
	return exp(-model.riskFreeRate * option.getMaturity()) * expectation;
}


/////////////////////////
///     Testing     /////
/////////////////////////
static void testPrice() {
	BlackScholesModel m;
	m.stockPrice = 100.0;
	m.volatility = 0.1;
	m.drift = 0;
	m.riskFreeRate = 0.1;
	
	CallOption c;
	c.strike = 100.0;
	c.maturity = 2.0;

	double expected = c.price(m);
	
	RectangularPricer pricer;
	double actual = pricer.price(m, c);
	ASSERT_APPROX_EQUAL(actual, expected, 0.01);
}

void testRectangleRulePricer() {
	TEST(testPrice);
}
