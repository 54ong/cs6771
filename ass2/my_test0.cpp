#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
//  SMatrix m(3);
//	SMatrix m(3, 5);
//  SMatrix m;
//  SMatrix m(std::cin);

	SMatrix m(5, 7);

	m.setVal(2, 6, 5);
	m.setVal(2, 0, 3);
	m.setVal(2, 3, 4);
	m.setVal(0, 3, 10);
	m.setVal(0,5,1);
	m.setVal(4, 1, 2);
	m.setVal(0,3,2);

	cout << m << endl;

	return 0;
}
