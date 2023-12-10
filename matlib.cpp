#include "matlib.h"
#include "stdafx.h"
#include "testing.h"

static inline double hornerFunction(double x, double a0, double a1) {
    return a0 + x * a1;
}

static inline double hornerFunction(double x, double a0, double a1, double a2) {
    return a0 + x * hornerFunction(x, a1, a2);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3) {
    return a0 + x * hornerFunction(x, a1, a2, a3);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4) {
    return a0 + x * hornerFunction(x, a1, a2, a3, a4);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
    double a5) {
    return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
    double a5, double a6) {
    return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
    double a5, double a6, double a7) {
    return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6, a7);
}

static inline double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4,
    double a5, double a6, double a7, double a8) {
    return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6, a7, a8);
}

static const double Root2PI = sqrt(2.0 * 3.141592653589793);
double normcdf(double x) {

      DEBUG_PRINT("normcdf(" << x << ")");

    if (x < 0) {
        return 1 - normcdf(-x);
    }

    double k = 1 / (1 + 0.2316419 * x);
    double poly = hornerFunction(k, 0.0, 0.319381530, -0.356563782,
        1.781477937, -1.821255978, 1.330274429);
    double approx = 1.0 - (1 / Root2PI) * exp(-0.5 * x * x) * poly;

    return approx;
}


double normInv(double x) {

    // Moro's algorithm
    double y = x - 0.5;
    double r;

    if (abs(y) < 0.42) {
        r = y * y;
        double t = y * hornerFunction(r, 2.50662823884, -18.61500062529,
            41.39119773534, -25.44106049637) /
            hornerFunction(r, 1.0, -8.47351093090, 23.08336743743,
                -21.06224101826, 3.13082909833);
        return t;
    }
    else {

        if (y < 0) { r = x; }
        else { r = 1 - x; }

        double s = log(-log(r));

        double t = hornerFunction(s, 0.3374754822726147, 0.9761690190917186,
            0.1607979714918209, 0.0276438810333863,
            0.0038405729373609, 0.0003951896511919,
            0.0000321767881768, 0.0000002888167364,
            0.0000003960315187);

        if (x < 0.5) { return -t; }
        else { return t; }
    }

}


