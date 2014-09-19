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
//	m.setVal(2, 3, 4);
//	m.setVal(3, 2, 9);
//	m.setVal(0, 3, 10);
//	m.setVal(4, 1, 2);
//	m.setVal(0, 4, 1);
//	m.setVal(3, 1, 8);
//	m.setVal(2, 0, 3);
//	m.setVal(3, 4, 7);
//	cout << "before" << endl << m << endl;
//
//	m.setVal(2, 6, 0);
//	m.setVal(2, 3, 0);
//	m.setVal(3, 2, 0);
//	m.setVal(0, 3, 0);
//	m.setVal(4, 1, 0);
//	m.setVal(0, 4, 0);
//	m.setVal(3, 1, 0);
//	m.setVal(2, 0, 0);
//	m.setVal(3, 4, 0);
//	m.setVal(3, 2, 0);
//	cout << "after" << endl << m << endl;
//	m.setVal(0, 3, 0);
//	cout << "after " << m << endl;
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

//	SMatrix m { { 4, 4, 3 }, { 1, 1, 1 }, { 1, 2, 10 }, { 2, 2, 5 } };
//	std::cout << m << std::endl;

// setValue
//	SMatrix m1(2, 3);
//	for (auto i = 0; i < 2; ++i)
//		for (auto j = 0; j < 3; ++j)
//			m1.setVal(i, j, i + j);
//	cout << "m1: " << endl << m1 << endl;
//
//	SMatrix a(500000000, 1000000000);
//	for (SMatrix::size_type i = 0; i < 200; ++i)
//		for (SMatrix::size_type j = 0; j < 200; ++j)
//			a.setVal(i + 1000000, j + 1000000, -1);
//
//	std::cout << a << std::endl;

//	SMatrix m1(500000000, 1000000000);
//	SMatrix m2(500000000, 1000000000);

	SMatrix m1(2, 2);
	SMatrix m2(2, 2);

	for (SMatrix::size_type i = 0; i < 2; ++i) {
		for (SMatrix::size_type j = 0; j < 2; ++j) {
			m1.setVal(j, i, -1);
			m2.setVal(i, j, 1);
//	for (SMatrix::size_type i = 0; i < 200; ++i) {
//		for (SMatrix::size_type j = 0; j < 200; ++j) {
//			m1.setVal(i + 1000000, j + 1000000, 1);
//			m2.setVal(i + 1000000, j + 1000000, 1);
		}
	}

//	for (SMatrix::size_type i = 0; i < 200; ++i)
//		for (SMatrix::size_type j = 0; j < 200; ++j)
//		m2.setVal(i + 1000000, j + 1000000, 1);

	cout << "before addition" << endl << "m1: " << endl << m1 << endl;
	cout << "m2: " << endl << m2 << endl;
//	for (SMatrix::size_type i = 0; i < 2; ++i) {
//		for (SMatrix::size_type j = 0; j < 2; ++j) {
//			m1.setVal(i, j, 0);
//		}
//	}
//	m2 += m1;
	m1 += m2;
	cout << "after addition" << endl << "m1: " << endl << m1 << endl;
	cout << "m2: " << endl << m2 << endl;

	return 0;
}
