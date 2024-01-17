#pragma once
#include "stdafx.h"

class LineChart {
public:
	void addEntry(double xValue, double yValue);
	void setSeries(std::vector<double> Xs, std::vector<double> Ys);
	void writeAsHTML(std::ostream& out) const;
	void writeAsHTML(const std::string& file) const;
private:
	std::vector<double> xValues;
	std::vector<double> yValues;
};

void testLineChart();