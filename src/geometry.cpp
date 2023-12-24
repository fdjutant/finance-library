#include "geometry.h"
#include "stdafx.h"
#include "testing.h"

double area( double radius ) {

	DEBUG_PRINT("area(" << radius << ")");
	return pi_value * radius * radius;

}

double circumference(double radius) {
	
	DEBUG_PRINT("circumference(" << radius << ")");
	return pi_value * radius * 2.0;

}

static void testArea() {

	// test bounds
	ASSERT(area(1.0) > 0);

	// test increasing monotonic
	ASSERT(area(3.0) > area(1.0));

	// test well know value
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
	TEST(testArea);

	setDebugEnabled(true);
	TEST(testCircumference);

}
