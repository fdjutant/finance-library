#include "scratch.h"
#include "stdafx.h"
#include "testing.h"
using namespace std;

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