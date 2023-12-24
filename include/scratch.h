#pragma once
#include "stdafx.h"

/**
* function to write CSV
**/
void writeCSVChart(const std::string& filename, const std::vector<double>& x, const std::vector<double>& y);

/**
* function to test string
**/
void usingString();
void notEfficientString();
void efficientString();

/**
* function to test ofstream
**/
void writingOfstream();
void testWriteHaiku();

/**
* function to convert polar to cartesian
**/
void testPolarToCartesian();

/**
* function to print next value
**/
void printNextValue(int x);
void printNextValue2(int& x);

/**
* function to sum vector
**/
double sum(const std::vector<double>& v);

/**
* function to print vector
**/
void printVector();

/**
* function to print number
**/
void printNumber();