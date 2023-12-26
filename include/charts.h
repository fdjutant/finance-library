#pragma once
#include "stdafx.h"

/**
* perform unit testing for charts
**/
void testCharts();

/**
* function to generate pie chart
**/
void pieChart(const std::string& filename, const std::vector<std::string>& labels, const std::vector<double>& values);

/*
	function to generate a line chart
*/
void lineChart(const std::string& filename, const std::vector<double>& x, const std::vector<double>& y);