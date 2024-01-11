#include "geometry.h"
#include "stdafx.h"
using namespace std;

/*
	Compute perimetry of a triangle
*/
double perimeter(const CartesianPoint& p1, const CartesianPoint& p2, const CartesianPoint& p3) {
	double length1 = p1.distanceTo(p2);
	double length2 = p1.distanceTo(p3);
	double length3 = p2.distanceTo(p3);
	return length1 + length2 + length3;
}

/*
	Euclidian distance function
*/
double CartesianPoint::distanceTo(const CartesianPoint& p2) const {
	double dx = p2.x - x;
	double dy = p2.y - y;

	return sqrt(dx * dx + dy * dy);
}

/*
	Convert polar to Cartesian
*/
CartesianPoint polarToCartesian(const PolarPoint& p) {
	CartesianPoint c;
	c.x = p.r * cos(p.theta);
	c.y = p.r * sin(p.theta);
	return c;
}

static void polarToCartesian(double r, double theta, double& x, double& y) {
	x = r * cos(theta);
	y = r * sin(theta);
}

double Circle::area() const {
	return pi_value * radius * radius;
}

double Circle::circumference() const {
	return 2.0 * pi_value * radius;
}

double area( double radius ) {

	DEBUG_PRINT("area(" << radius << ")");
	return pi_value * radius * radius;

}

double circumference(double radius) {
	
	DEBUG_PRINT("circumference(" << radius << ")");
	return pi_value * radius * 2.0;

}

/////////////////////////
///     Testing     /////
/////////////////////////

static void testPerimeter() {
	CartesianPoint p1, p2, p3;
	p1.x = 0.0; p1.y = 0.0;
	p2.x = 3.0; p2.y = 0.0;
	p3.x = 0.0; p3.y = 4.0;
	double trianglePerimeter = perimeter(p1, p2, p3);
	ASSERT_APPROX_EQUAL(trianglePerimeter, 12.000, 0.0001);
}

static void testDistanceTo() {
	CartesianPoint p1;
	p1.x = 1;
	p1.y = 1;
	CartesianPoint p2;
	p2.x = 4;
	p2.y = 5;
	double d = p1.distanceTo(p2);
	ASSERT_APPROX_EQUAL(d, 5.0, 0.0001);
}

static void testPolarToCartesian() {
	PolarPoint p;
	p.r = 2.0;
	p.theta = pi_value / 2.0;
	CartesianPoint c = polarToCartesian(p);
	ASSERT_APPROX_EQUAL(c.x, 0.0, 0.001);
	ASSERT_APPROX_EQUAL(c.y, 2.0, 0.001);
}
static void testCircumferenceOfCircle() {
	Circle c;
	c.radius = 3.0;

	// test bounds
	ASSERT(c.circumference() > 0);

	// test specific value
	ASSERT_APPROX_EQUAL(c.circumference(), 2.0 * pi_value * 3.0, 0.001);
}

static void testAreaOfCircle() {
	Circle c;
	c.radius = 3.0;

	// test bounds
	ASSERT(c.area() > 0);

	// test specific value
	ASSERT_APPROX_EQUAL(c.area(), pi_value * 9.0, 0.001);
}

static void testPolarToCartesian_old() {
	double PI = 3.14159265358979;
	double r = 2.0;
	double theta = PI / 2;
	double x = 0.0, y = 0.0;
	polarToCartesian(r, theta, x, y);
	ASSERT_APPROX_EQUAL(x, 0.0, 0.001);
	ASSERT_APPROX_EQUAL(y, 2.0, 0.001);
	cout << "x = " << x << ", y = " << y << "\n";
}

static void testArea() {

	// test bounds
	ASSERT(area(1.0) > 0);

	// test increasing monotonic
	ASSERT(area(3.0) > area(1.0));

	// test well known value
	ASSERT_APPROX_EQUAL(area(3.0), pi_value * 9.0, 0.001);

}

static void testCircumference() {

	// test bounds
	ASSERT(circumference(1.0) > 0);

	// test increasing monotonic
	ASSERT(circumference(2.0) > circumference(1.0));

	// test well-known value
	ASSERT_APPROX_EQUAL(circumference(3.0), pi_value * 6.0, 0.001);

}

void testGeometry() {

	setDebugEnabled(true);
	//TEST(testArea);
	//TEST(testCircumference);
	//TEST(testPolarToCartesian);
	//TEST(testAreaOfCircle);
	//TEST(testCircumferenceOfCircle);
	//TEST(testPolarToCartesian);
	TEST(testDistanceTo);
	TEST(testPerimeter);
}
