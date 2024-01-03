#pragma once

const double pi_value = 3.14159265358979;

/*
	A class for circle object
*/
class Circle {
public:
	double radius;
	double area() const;
	double circumference() const;
};

/*
	A class for Polar point object
*/
class PolarPoint {
public:
	double r;
	double theta;
};

/*
	A class for Cartesian point object
*/
class CartesianPoint {
public:
	double x;
	double y;
};

/*
	Convert polar to Cartesian
*/
CartesianPoint polarToCartesian(const PolarPoint&);


/*
	Convert polar to cartesian
*/
void testPolarToCartesian();

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
