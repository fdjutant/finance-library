#pragma once

const double pi_value = 3.14159265358979;

/*
	Define a class for Cartesian points
*/
class CartesianPoint {
public:
	double x;
	double y;
};

/**
 * Compute area of a circle
**/
double area(double radius);

/**
 * Compute circumference of a circle
**/
double circumference(double radius);

/**
 * Perform a unit testing 
**/
void testGeometry();
