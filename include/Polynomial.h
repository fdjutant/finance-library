#pragma once
#include "stdafx.h"

// forward declaration: allow recalling object within the object
class Polynomial;

class Polynomial {
public:
	std::vector<double> a;
	double x;

	double evaluate() const;
	double add(Polynomial polynom1) const;

	// constructors
	Polynomial();
	Polynomial(std::vector<double> coefficients);
	Polynomial(double c);
};

void testPolynomial();