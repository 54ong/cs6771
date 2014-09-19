#include <iostream>
#include "SMatrix.h"
/*
 test for copy and move constructor
 */

using namespace std;

int main(void) {
	SMatrix m1(std::cin);
	SMatrix m2 = m1;
	cout << "m1 is " << m1 << endl;
	cout << "m2 is " << m2 << endl;

	SMatrix m3 = move(m2);

	cout << "m1: " << endl << m1 << endl;
	cout << "m2: " << endl << m2 << endl;
	cout << "m3: " << endl << m3 << endl;

	return 0;
}
