#include "stdafx.h"
#include "matlib.h"
#include "geometry.h"
using namespace std;

int main() {

    // Perform unit testing
    testMatlib();
    //testGeometry();

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