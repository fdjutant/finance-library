#pragma once
#include "stdafx.h"

class RealFunction {
public:
	
	virtual ~RealFunction() {};
	virtual double evaluate(double x) = 0;

};