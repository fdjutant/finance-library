#include "geometry.h"
#include "stdafx.h"

double area( double radius ) {
	return pi_value * radius * radius;
}

double circumference(double radius) {
	return pi_value * radius * 2.0;
}
