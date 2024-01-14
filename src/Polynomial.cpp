#include "Polynomial.h"
#include "stdafx.h"
using namespace std;

////////////////////////
////// Constructor /////
////////////////////////

// default constructor
Polynomial::Polynomial() :
	a(0, 0.0),
	x(0.0){
}
// alternative constructor 1
Polynomial::Polynomial(vector<double> vectorInput) :
	a(vectorInput),
	x(0.0) {
} 
// alternative constructor 2
Polynomial::Polynomial(double c) :
	a(1, c),
	x(1.0){
}

////////////////////////
////// Functions ///////
////////////////////////
double Polynomial::evaluate() const {
	double y = 0.0;
	for (int i = 0; i < (int)a.size(); i++) {
		y += a[i] * pow(x,i);
	}
	return y;
}

double Polynomial::add(Polynomial polynom2) const {
	Polynomial polynom1;
	polynom1.a = a;
	polynom1.x = x;
	double total = polynom1.evaluate()  + polynom2.evaluate();

	return total;
}

/////////////////////////
///     Testing     /////
/////////////////////////

static void testEvaluate() {

	// Test with default constructor
	Polynomial polynomDefault;
	polynomDefault.x = 2.5;
	DEBUG_PRINT("Test evaluate function with default constructor")
	double yDefault = polynomDefault.evaluate();
	ASSERT_APPROX_EQUAL(yDefault, 0.0, 0.001);

	// Test with alternative constructor 1
	vector<double> a = { 1, 2, 3, 4, 5 };
	Polynomial polynomAlt1(a);
	polynomAlt1.x = 2.5;
	DEBUG_PRINT("Test with alternative constructor 1");
	double yAlt1 = polynomAlt1.evaluate();
	ASSERT_APPROX_EQUAL(yAlt1, 282.5625, 0.001);

	// Test with alternative constructor 3
	Polynomial polynomAlt2(2.0);
	polynomAlt2.x = 2.5;
	DEBUG_PRINT("Test with alternative constructor 2");
	double yAlt2 = polynomAlt2.evaluate();
	ASSERT_APPROX_EQUAL(yAlt2, 2.0, 0.001);
}

static void testAdd() {
	Polynomial polynom1;
	Polynomial polynom2;

	// Test add function with specific values
	DEBUG_PRINT("Test evaluate function with specific values");

	polynom1.a = { 1, 2, 3, 4, 5 };
	polynom1.x = 2.5;
	polynom2.a = { 1, 2, 3, 4, 5 };
	polynom2.x = 2.5;
	double totalTwoPolynoms = polynom1.add(polynom2);
	ASSERT_APPROX_EQUAL(totalTwoPolynoms, 2.0*282.5625, 0.001);

}

void testPolynomial() {
	setDebugEnabled(true);
	TEST(testEvaluate);
	//TEST(testAdd);
}