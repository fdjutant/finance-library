#include "matlib.h"
#include "stdafx.h"
#include "testing.h"
using namespace std;

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
vector<double> randuniform(int n) {
    vector<double> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = (rand() + 1.0) / (RAND_MAX + 1.0);
    }
    return x;
}

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

    DEBUG_PRINT("normInv(" << x << ")");

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

/////////////////////////
///     Testing     /////
/////////////////////////

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
    
    setDebugEnabled(false);
    TEST( testNormCdf );

    setDebugEnabled(false);
    TEST( testNormInv );

    setDebugEnabled(false);
    TEST(testblackScholesPutPrice);

    setDebugEnabled(false);
    TEST(testSolveQuadratic);

    setDebugEnabled(false);
    TEST(testMean);

    setDebugEnabled(false);
    TEST(testStandardDeviation);

    setDebugEnabled(false);
    TEST(testMinMax);

    setDebugEnabled(false);
    TEST(testRanduniform);

    setDebugEnabled(false);
    TEST(testRandn);

    setDebugEnabled(false);
    TEST(testRandnBoxMuller);

}