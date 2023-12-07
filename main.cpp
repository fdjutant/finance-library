#include <iostream>
#include "matlib.h"
using namespace std;

int main() {

    cout << "normcdf(1.96)="
        << normcdf(1.96) << "\n";
    cout << "norminv(0.975)="
        << normInv(0.975) << "\n";

    return 0;
}