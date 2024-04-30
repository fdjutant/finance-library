#include "matlib.h"
#include "stdafx.h"
#include "BlackScholesModel.h"
#include "CallOption.h"
using namespace std;

/*
    Estimate improper integrals using integration
    by substitution
*/
double integralToInfinity(RealFunction& f, double x, int nPoints) {
    class Integrand : public RealFunction {
    public:
        double x;
        RealFunction& f;

        double evaluate(double s) {
            return 1 / (s * s) * f.evaluate(1 / s + x - 1);
        }

        Integrand(double x, RealFunction& f) : x(x), f(f)
        {}
    };

    Integrand i(x, f);
    return integral(i, 0, 1, nPoints);
}

double integralFromInfinity(RealFunction& f, double x, int nPoints) {
    class ReversingIntegrand : public RealFunction {
    public: 
        RealFunction& f;

        double evaluate(double x) {
            return f.evaluate(-x);
        }

        ReversingIntegrand(RealFunction& f) : f(f)
        {}
    };

    ReversingIntegrand i(f);
    return integralToInfinity(i, -x, nPoints);
}

double integralOverR(RealFunction& f, int nPoints) {
    return integralFromInfinity(f, 0, nPoints) + integralToInfinity(f, 0, nPoints);
}

// Integrate using the rectangular rule
double integral(RealFunction& f, double a, double b, int nPoints) {
    
    double h = (b - a) / nPoints;
    double x = a + 0.5 * h;
    double total = 0.0;
    for (int i = 0; i < nPoints; i++) {
        double y = f.evaluate(x);
        total += y;
        x += h;
    }
    return h * total;

}

// Generate a percentile given a vector
double prctile(const vector<double>& x, double p) {

    int n = (int)x.size();
    vector<double> sorted = x;
    sort(sorted.begin(), sorted.end());

    // check the index corresponding to the percentage p
    double index = (p / 100.0) * (n - 1); // (n-1) due to C++ indexing starting from 0
    if (abs(int(index) - index) <= 0.0001) {
        return sorted[index]; // if the index returns integer
    }
    else {
        int lowerIndex = (int)floor(index);
        int upperIndex = lowerIndex + 1;

        // find the two values
        double lowerValue = sorted[lowerIndex];
        double upperValue = sorted[upperIndex];

        // add interpolation factor
        return lowerValue + (upperValue - lowerValue) * (index - lowerIndex);
    }
    
}

/*
    Generate equally spaced vector
*/
vector<double> linspace(double startPoint, double finalPoint, double N) {
    
    ASSERT(N >= 2);

    vector<double> x(N, 0.0);
    x[0] = startPoint; 
    double inc = (finalPoint - startPoint) / (N - 1);
    for (int i = 1; i < N; i++) {
        x[i] = x[i-1] + inc;
    }

    return x;
}

/*
    Box-Muller algorithm
*/
vector<double> randnBoxMuller(int N) {

    vector<double> x(N);
    int K = (int)round(N/2);
    int i = 0;
    while (K > 0){
        
        // generate a pair sampled from a uniform dist
        vector<double> u = randuniform(2);

        // find a pair sampled from normal dist
        double n1 = sqrt(-2 * log(u[0])) * cos(2 * PI * u[1]);
        double n2 = sqrt(-2 * log(u[0])) * sin(2 * PI * u[1]);

        // take only n1 in case N is an odd value
        if (N % 2 == 1 && K == 1) {
            x[i] = n1;
        }
        else {
            x[i] = n1;
            x[i + 1] = n2;
        }
        K--;
        i = i + 2; 
    }    

    return x;
}

/*
    Generate a random sampling that follows a uniform distribution and normal distribution 
*/
//vector<double> randuniform(int n) {
//    vector<double> x(n);
//    for (int i = 0; i < n; i++) {
//        x[i] = (rand() + 1.0) / (RAND_MAX + 1.0);
//    }
//    return x;
//}

/*
    Generate a random sampling that follows a uniform distribution and normal distribution using mersenneTwister algorithm
*/

// MersenneTwister random number generator
static mt19937 mersenneTwister;

// reset the number generator 
void rng(const string& description) {
    ASSERT(description == "default");
    mersenneTwister.seed(mt19937::default_seed);
}

//  Create uniformly distributed random numbers 
vector<double> randuniform(int n) {
    vector<double> ret(n, 0.0);
    for (int i = 0; i < n; i++) {
        ret[i] = (mersenneTwister() + 0.5) /
            (mersenneTwister.max() + 1.0);
    }
    return ret;
}

/*
   Create a normally distributed random numbers
*/
vector<double> randn(int n) {
    vector<double> x = randuniform(n);
    for (int i = 0; i < n; i++){
        x[i] = normInv(x[i]);
    }
    return x;
}

/*
   Find max and min from a vector
*/
double min(const vector<double>& x) {
    
    int n = (int)x.size();
    ASSERT(n > 0);

    double temp = x[0];
    for (int i = 1; i < n; i++) {
        if (x[i] < temp) {
            temp = x[i];
        }
    }

    return temp;
}

double max(const vector<double>& x) {
    
    int n = (int)x.size();
    ASSERT(n > 0);

    double temp = x[0];
    for (int i = 1; i < n; i++) {
        if (x[i] > temp) {
            temp = x[i];
        }
    }

    return temp;
}

/*
   Compute sum, mean, standard deviation
*/
double sum(const vector<double>& x) {
    int n = (int)x.size();
    ASSERT(n > 0);
    int i = 0;
    double sum = 0.0;
    while (i < n) {
        sum += x[i];
        i++;
    }
    return sum;
}

double mean(const vector<double>& x) {
    int n = (int)x.size();
    ASSERT(n > 0);    
    return sum(x) / n;
}

double standardDeviation(const vector<double>& x, bool population) {
    
    DEBUG_PRINT("population = " << population);
    ASSERT((population == 0) || (population == 1));

    int Nsize = (int)x.size();
    ASSERT(Nsize > 0);

    double meanValue = mean(x);
    double sum = 0.0;
    for (int i = 0; i < Nsize; i++) {
        sum += pow((x[i] - meanValue),2);
    }
    if (population) {
        ASSERT(Nsize > 0);
        return sqrt(sum / Nsize);
    }
    else {
        ASSERT(Nsize-1 > 0);
        return sqrt(sum / (Nsize - 1));
    }
}

/*
    Solve roots of quadratic equation
*/
void solveQuadratic_NoVector(double a, double b, double c, double& root1, double& root2) {

    root1 = (-b + sqrt((b * b - 4.0 * a * c))) / (2.0 * a);
    root2 = (-b - sqrt((b * b - 4.0 * a * c))) / (2.0 * a);

}

void solveQuadratic(double a, double b, double c, vector<double>& roots) {

    roots[0] = (-b + sqrt((b * b - 4.0 * a * c))) / (2.0 * a);
    roots[1] = (-b - sqrt((b * b - 4.0 * a * c))) / (2.0 * a);

}

/*
    Compute normalized CDF and its inverse
*/
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

    //DEBUG_PRINT("normcdf(" << x << ")");

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

    //DEBUG_PRINT("normInv(" << x << ")");

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

static double integratePayOff(double a, double b, const PathIndependentOption& option) {

    class PayOffFunction : public RealFunction {
    public:

        const PathIndependentOption& option;

        PayOffFunction(const PathIndependentOption& option) : option(option) {}

        double evaluate(double x) {
            return option.payoff(x);
        }
    };

    PayOffFunction integrand(option);
    return integral(integrand, a, b, 1000);

}

double blackScholesPutPrice(double K, double T, double S, double sigma, double r) {

    DEBUG_PRINT("blackScholesCallPrice(" << K << "," << T << "," << S << "," << sigma << "," << r << ")");

    double denominator = sigma * sqrt(T);
    double numerator = log(S / K) + (r + 0.5 * sigma) * T;

    double d1 = numerator / denominator;
    double d2 = d1 - denominator;

    //double callPriceOption = normcdf(d1) * S - normcdf(d2) *K * exp(-r * T);
    double putPriceOption = normcdf(-d2) * K * exp(-r * T) - normcdf(-d1) * S;

    return putPriceOption;
}

double blackScholesCallPrice(double K, double T, double S,double sigma, double r) {

    double denominator = sigma * sqrt(T);
    double numerator = log(S / K) +
        (r + 0.5 * sigma * sigma) * T;

    double d1 = numerator / denominator;
    double d2 = d1 - denominator;

    double callPriceOption = normcdf(d1) * S -
        normcdf(d2) * K * exp(-r * T);

    return callPriceOption;
}

// Generate a vector
static void genVector(vector<double>& v) {
    v.push_back(-3.0);
    v.push_back(-2.0);
    v.push_back(-1.0);
    v.push_back(0.0);
    v.push_back(1.0);
    v.push_back(2.0);
    v.push_back(3.0);
}

// Compute total compounded saving
double valueCompounded(double P, double r, double n, double t, double C) {
    double totalInterest = pow((1 + (r / n)), (n * t));
    return P * totalInterest + C * ((totalInterest - 1) / (r / n));
}

class NormalPDF : public RealFunction {
public:
    double stdev = 1.0;
    double expectation = 0.0;

    double evaluate(double x) {
        return exp(-((x - expectation) * (x - expectation)) / 2 * stdev * stdev) * (1 / (sqrt(2 * PI * stdev * stdev)));
    }
};

/////////////////////////
//////   Testing   //////
/////////////////////////


static void testIntegralInfinity() {
    NormalPDF normalPDF;
    double estimateToInfinity = integralToInfinity(normalPDF, -2.0, 1000);
    ASSERT_APPROX_EQUAL(estimateToInfinity, 1-normcdf(-2.0), 0.001);
    double estimateFromInfinity = integralFromInfinity(normalPDF, 2.0, 1000);
    ASSERT_APPROX_EQUAL(estimateFromInfinity, normcdf(2.0), 0.001);
    double estimateOverR = integralOverR(normalPDF, 1000);
    ASSERT_APPROX_EQUAL(estimateOverR, 1.0, 0.001);
}

static void testValueCompounded() {
    double P = 0;
    double C = 150;
    double r = 0.05;
    double n = 12;
    double t = 18;
    double total = valueCompounded(P, r, n, t, C);
    DEBUG_PRINT("total saving = " << total << "\n");
}

static void testIntegralNormalPDF() {

    NormalPDF integrand;
    integrand.stdev = 1.0;
    integrand.expectation = 0.0;
    double estimate = integral(integrand, -2.0, 2.0, 1000);
    ASSERT_APPROX_EQUAL(estimate, 0.95, 0.01);
    ASSERT_APPROX_EQUAL(estimate, normcdf(2.0), 0.1);

}

static void testIntegral() {
    
    class SinFunc : public RealFunction {
    public:
        double evaluate(double x) {
            return sin(x);
        }
    };

    SinFunc integrand;
    double estimate = integral(integrand, 1.0, 3.0, 1000);
    double expected = -cos(3.0) + cos(1.0);
    ASSERT_APPROX_EQUAL(estimate, expected, 0.0001);
}

static void testPrctile() {
    vector<double> v = { 1, 5, 3, 9, 7 };
    ASSERT_APPROX_EQUAL(prctile(v, 100.0), 9.0, 0.001);
    ASSERT_APPROX_EQUAL(prctile(v, 0.0), 1.0, 0.001);
    ASSERT_APPROX_EQUAL(prctile(v, 50.0), 5.0, 0.001);
    ASSERT_APPROX_EQUAL(prctile(v, 17.0), 2.36, 0.001);
    ASSERT_APPROX_EQUAL(prctile(v, 62.0), 5.96, 0.001);
}


static void testLinspace() {
    vector<double> x = linspace(0, 1, 10);

    DEBUG_PRINT("x.size() = " << (int)x.size());
    ASSERT((int)x.size() == 10);

    DEBUG_PRINT("x[0] = " << x[0]);
    ASSERT_APPROX_EQUAL(x[0], 0.0, 0.0001);
    
    DEBUG_PRINT("x[9] = " << x[9]);
    ASSERT_APPROX_EQUAL(x[9], 1.0, 0.0001);

}

static void testRandnBoxMuller() {

    int n = 1000;
    vector<double> x = randnBoxMuller(n);
    ASSERT_APPROX_EQUAL(mean(x), 0.0, 0.1);
    ASSERT_APPROX_EQUAL(standardDeviation(x, true), 1.0, 0.1);

}

static void testRandn() {

    int n = 1000;
    vector<double> x = randn(n);

    ASSERT_APPROX_EQUAL(mean(x), 0.0, 0.1);
    ASSERT_APPROX_EQUAL(standardDeviation(x, true), 1.0, 0.1);
}

static void testRanduniform() {
   
    int n = 1000;
    ASSERT_APPROX_EQUAL(mean(randuniform(n)), 0.5, 0.1);

}

static void testMinMax() {

    vector<double> v;
    genVector(v);

    ASSERT_APPROX_EQUAL(min(v), -3.0, 0.001);
    ASSERT_APPROX_EQUAL(max(v), 3.0, 0.001);

}

static void testStandardDeviation() {

    // test specific values
    vector<double> x;
    genVector(x);

    ASSERT_APPROX_EQUAL(standardDeviation(x, true), 2.0, 0.001);
    ASSERT_APPROX_EQUAL(standardDeviation(x, false), sqrt(28.0/6.0), 0.001);

}

static void testMean() {

    // test specific values
    vector<double> x;
    genVector(x);
    double meanValue = mean(x);
    ASSERT_APPROX_EQUAL(meanValue, 0.0, 0.001);
}

static void testSolveQuadratic() {

    /* test specific values
    (x + 3) (2x - 5) = 0;
    2x^2 + x - 15 = 0
    */
    double a = 2.0, b = 1.0, c = -15;

    // without vector
    double x1 = 0.0, x2 = 0.0;
    solveQuadratic_NoVector(a, b, c, x1, x2);
    DEBUG_PRINT("x1 = " << x1 << "\n");
    DEBUG_PRINT("x2 = " << x2 << "\n");
    ASSERT_APPROX_EQUAL(x1, 5.0 / 2.0, 0.001);
    ASSERT_APPROX_EQUAL(x2, -3.0, 0.001);

    // with vector
    vector<double> roots(2);
    solveQuadratic(a, b, c, roots);
    ASSERT_APPROX_EQUAL(roots[0], 5.0 / 2.0, 0.001);
    ASSERT_APPROX_EQUAL(roots[1], -3.0, 0.001);

}

static void testNormCdf() {
    
    // test bounds
    ASSERT(normcdf(0.3) > 0);
    ASSERT(normcdf(0.3) < 1);

    // test extreme values
    ASSERT_APPROX_EQUAL(normcdf(-1e10), 0 , 0.001);
    ASSERT_APPROX_EQUAL(normcdf(1e10), 1, 0.001);

    // test increasing
    ASSERT(normcdf(0.3) < normcdf(0.5));

    // test symmetry
    ASSERT_APPROX_EQUAL(normcdf(0.3), 1.0 - normcdf(-0.3), 0.0001);
    ASSERT_APPROX_EQUAL(normcdf(0.0), 0.5, 0.0001);

    // test inverse
    ASSERT_APPROX_EQUAL(normcdf(normInv(0.3)), 0.3, 0.0001);

    // test well known value
    ASSERT_APPROX_EQUAL(normcdf(1.96), 0.975, 0.001);

}

static void testNormInv() {

    // test well-known value
    ASSERT_APPROX_EQUAL(normInv(0.975), 1.96, 0.001);

}

static void testblackScholesPutPrice() {
    
    // set some testing parameters
    double K = 100.0;      // strike price
    double T = 0.5;        // time to maturity
    double S = 110.0;      // spot price
    double sigma = 0.1;    // volatility
    double r = 0.03;       // risk-free interest rate

    // test that the put option is nearly worthless if the stock price (S) is far above the strike price (K)
    ASSERT(S < 10.0 * K);

    // test that the price of the put option is always positive
    ASSERT(blackScholesPutPrice(K, T, S, sigma, r) > 0.0);

    // TO DO: test the put-call parity formula
}

void testMatlib() {

    setDebugEnabled(true);
    TEST(testIntegralInfinity);
    //TEST(testIntegralNormalPDF);
    //TEST(testValueCompounded);
    //TEST(testIntegral);
    //TEST(testNormCdf);
    //TEST(testNormInv);
    //TEST(testblackScholesPutPrice);
    //TEST(testSolveQuadratic);
    //TEST(testMean);
    //TEST(testStandardDeviation);
    //TEST(testMinMax);
    //TEST(testRanduniform);
    //TEST(testRandn);
    //TEST(testRandnBoxMuller);
    //TEST(testLinspace);
    //TEST(testPrctile);

}