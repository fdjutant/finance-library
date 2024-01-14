#pragma once

const double pi_value = 3.14159265358979;

// forward declaration: allow recalling object within the object
class CartesianPoint;

/*
	An object for CartesianPoint and its constructor
*/
class CartesianPoint {
public:
	CartesianPoint();
	double x;
	double y;

	double distanceTo(const CartesianPoint& p2) const;
};

/*
	A class for Polar point object
*/
class PolarPoint {
public:
	PolarPoint(); // declare default constructor
	double r;
	double theta;
};


/*
	A class for circle object
*/
class Circle {
public:
	Circle(); 
	double radius;
	double area() const;
	double circumference() const;
};

////////////////////////
///// functions ////////
////////////////////////

/*
	Compute a perimeter of a triangle
*/
double perimeter(const CartesianPoint& p1, const CartesianPoint& p2, const CartesianPoint& p3);

/**
 * Compute area of a circle
**/
double area(double radius);

/**
 * Compute circumference of a circle
**/
double circumference(double radius);

/*
	Convert polar to Cartesian
*/
CartesianPoint polarToCartesian(const PolarPoint&);


/**
 * Unit testing 
**/
void testGeometry();
