#include <iostream>
#include <sstream>
#include "SMatrix.h"

using namespace std;

int main(void) {
	// constructors test
//  SMatrix m(3);
//	SMatrix m(3, 5);
//  SMatrix m;
//  SMatrix m(std::cin);

//	SMatrix m(5, 7);
//	m.setVal(2, 6, 5);
//	m.setVal(2, 0, 3);
//	m.setVal(2, 3, 4);
//	m.setVal(3, 2, 9);
//	m.setVal(0, 3, 10);
//	m.setVal(0, 4, 1);
//	m.setVal(4, 1, 2);
//	m.setVal(0, 3, 2);

// copy & move constructors
//	SMatrix m2;
//	m2 = m;
//	SMatrix m2 = m;
//	cout << "m1 is " << m << endl;
//	cout << "m2 is " << m2 << endl;
//
//	SMatrix m3;
//	m3 = move(m2);
//	SMatrix m3 = move(m2);
//	cout << "m1: " << endl << m << endl;
//	cout << "m2: " << endl << m2 << endl;
//	cout << "m3: " << endl << m3 << endl;

//	 istringstream iss("(1000,1000,0)");
//
//	 SMatrix b(iss);
//	 cout << b << endl;

// setValue
//	SMatrix m1(2, 3);
//	for (auto i = 0; i < 2; ++i)
//		for (auto j = 0; j < 3; ++j)
//			m1.setVal(i, j, i + j);
//	cout << "m1: " << endl << m1 << endl;

	SMatrix a(500000000, 1000000000);
	for (SMatrix::size_type i = 0; i < 200; ++i)
		for (SMatrix::size_type j = 0; j < 200; ++j)
			a.setVal(i + 1000000, j + 1000000, -1);

	std::cout << a << std::endl;

	return 0;
}
