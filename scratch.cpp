#include "scratch.h"
#include "stdafx.h"
#include "testing.h"
using namespace std;


static void writingHaiku(ostream& out) {
	out << "The wren\n";
	out << "Earn his living\n";
	out << "Noiselessly.\n";
}

void testWriteHaiku() {
	
	// write a Haiku to cout
	writingHaiku(cout);

	// write a Haiku to a file
	ofstream out;
	out.open("./txtFiles/haiku.txt");
	if (out.is_open()) {
		writingHaiku(out);
	}
	else {
		cout << "Unsuccesful";
	}
	out.close();

}

void writingOfstream() {
	// create an ofstream
	ofstream out;

	// choose where to write
	out.open("./txtFiles/myfile.txt");

	if (out.is_open()) {
		cout << "Success!";
	}
	else {
		cout << "Unsuccessful";
	}

	out << "The first line\n";
	out << "The second line\n";
	out << "The third line\n";

	// close the file after finished
	out.close();
}

static void polarToCartesian(double r, double theta, double& x, double& y) {
	x = r * cos(theta);
	y = r * sin(theta);
}

void testPolarToCartesian() {
	double PI = 3.14159265358979;
	double r = 2.0;
	double theta = PI / 2;
	double x = 0.0, y = 0.0;
	polarToCartesian(r, theta, x, y);
	ASSERT_APPROX_EQUAL(x, 0.0, 0.001);
	ASSERT_APPROX_EQUAL(y, 2.0, 0.001);
	cout << "x = " << x << ", y = " << y << "\n";
}

void printNextValue2(int& x) {
	x = x + 1;
	cout << "B: value of x is " << x << "\n";
}

void printNextValue(int x) {
	x = x + 1;
	cout << "B: value of x is " << x << "\n";
}


double sum(const vector<double>& v) {
	double total = 0.0;
	int n = (int)v.size();
	for (int i = 0; i < n; i++) {
		total += v[i];
	}
	return total;
}

void printVector() {
	
	// create a vector
	vector<double> myVector;

	// add three vectors to the end
	myVector.push_back(12.0);
	myVector.push_back(13.0);
	myVector.push_back(14.0);

	// read the first, second and third elements
	//cout << myVector[0] << "\n";
	//cout << myVector[1] << "\n";
	//cout << myVector[2] << "\n";

	// print vector using for loops
	int n = (int)myVector.size(); // casting from size_t to int
	for (int i = 0; i < n; i++) {
		cout << myVector[i] << "\n";
	}

	// create a vector of length 10
	// consisting entirely of 3.0's
	vector<double> ten3s(10, 3.0);

	// create a vector which is a copy of another
	vector<double> copy(ten3s);
	ASSERT(ten3s.size() == copy.size());

	// replace it with myVector
	copy = myVector;
	ASSERT(myVector.size() == copy.size());

	// print ten3s and copy vector
	int num = (int)copy.size();
	cout << "print ten3s and copy vector\n";
	for (int i = 0; i < num; i++) {
		cout << ten3s[i] << "\t" << copy[i] << "\n";
	}

	// initialize an integer vector
	vector<int> threeInts({ 2, 3, 4 });

}


void printNumber() {
	//int a = 2;
	cout << "print the Number test";
}