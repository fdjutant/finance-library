#include "stdafx.h"
#include "matlib.h"
#include "geometry.h"
#include "scratch.h"
#include "charts.h"
using namespace std;

int main() {

    // Perform unit testing
    testMatlib();
    //testGeometry();
    //testCharts();

    // Check CartesianPoint class
    //CartesianPoint p;
    //p.x = 100;
    //p.y = 150;
    //cout << "Coordinates (" << p.x << ", " << p.y << ")\n";
    //p.x *= 2;
    //p.y *= 2;
    //cout << "Rescaled coordinates (" << p.x << ", " << p.y << ")\n";

    // Generate a line chart
    // Price of a call option against the current stock price using Equation(A.6).Assume the volatility (sigma) is 0.2, the strike price (K) is 100, the time to maturity (T) is 1.0, and the risk - free interest rate (r) is 0.05
    //double strikePrice = 100;
    //double volatility = 0.2;
    //double riskFreeInterestRate = 0.01;
    //double timeToMaturity = 1.0;

    //int timePoints = 1000;
    //vector<double> S = linspace(100, 1500, timePoints);
    //vector<double> C(timePoints);
    //for (int i = 0; i < timePoints; i++) {
    //    C[i] = blackScholesCallPrice(strikePrice, timeToMaturity, S[i], volatility, riskFreeInterestRate);
    //}
    //lineChart("./outputFiles/blackScholesCallPrice.html", S, C);
    
    // y = x^2
    //int numPoints = 1000;
    //vector<double> x = linspace(0, 5, numPoints);
    //vector<double> y(numPoints);
    //for (int i = 0; i < numPoints; i++) {
    //    y[i] = x[i] * x[i];
    //}
    //lineChart("./outputFiles/theLineChart.html", x, y);

    // Generate a pie chart
    //vector<string> activity = {"Swimming", "Coding", "Working", "Cooking", "Sleeping"};
    //vector<double> hours = { 2, 3, 8, 2, 8 };
    //pieChart("./outputFiles/thePieChart.html", activity, hours);

    // Generate csv for plotting
    //vector<double> x(100), y(100);
    //int n = (int)x.size();
    //for (int i = 0; i < n; i++) {
    //    x[i] = i;
    //    y[i] = i * i;
    //}
    //writeCSVChart("./outputFiles/data.csv", x, y);

    // Test string class
    //usingString();
    //notEfficientString();
    //efficientString();

    // Test ofstream class
    //writingOfstream();
    //testWriteHaiku();

    // Pass by reference without const
    //testPolarToCartesian();

    // Pass-by-reference vs pass-by-value
    //int x = 5;
    //cout << "A: value of x is " << x << "\n";
    //printNextValue2(x);
    //cout << "C: value of x is " << x << "\n";

    // Test vector class
    //vector<double> vectorA(10, 4.0);
    //cout << "Sum of vectorA elements is " << sum(vectorA);

    // Test scratch
    //printNumber();
    //printVector();

    // Black-Scholes pricing
    /*double strike = 100.0;
    double spot = 110.0;
    double vol = 0.1;
    double riskFreeRate = 0.03;
    double timeToMaturity = 0.5;
    cout << "The call option price is ";
    cout << blackScholesPutPrice(strike, timeToMaturity, spot, vol, riskFreeRate);
    cout << "\n";*/

    // Print sample known values
    //cout << "normcdf(1.96)="
    //     << normcdf(1.96) << "\n";
    //cout << "norminv(0.975)="
    //     << normInv(0.975) << "\n\n";

    // Compute area and circum of a circle given
    // the radius
    //double radius;
    //cout << "Input the radius of a circle: ";
    //cin >> radius;
    //cout << "The area of the circle is " << area( radius ) << "\n";
    //cout << "The circumference of the circle is " << circumference(radius) << "\n";

    return 0;

}