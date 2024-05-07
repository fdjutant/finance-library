#pragma once
#include "stdafx.h"
#include "BlackScholesModel.h"	
#include "PathIndependentOption.h" 

/*
	A class to estimate pricing by integrating
	the PDF of stock price
*/
class RectangularPricer {
public:
	int nSteps;
	double price(const BlackScholesModel& model, const PathIndependentOption& option);

	RectangularPricer() : nSteps(1000) {};
};

void testRectangleRulePricer();