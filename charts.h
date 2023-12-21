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