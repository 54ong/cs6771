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

//	SMatrix m1(3, 3);
//	SMatrix m2(3, 3);
//	for (SMatrix::size_type i = 0; i < 3; ++i) {
//		for (SMatrix::size_type j = 0; j < 3; ++j) {
//			m1.setVal(i, j, -1);
//			m2.setVal(j, i, 1);
//		}
//	}
//	SMatrix m1(500000000, 1000000000);
//	SMatrix m2(1000000000, 500000000);
//	for (SMatrix::size_type i = 0; i < 200; ++i) {
//		for (SMatrix::size_type j = 0; j < 200; ++j) {
//			m1.setVal(i + 1000000, j + 1000000, -(i + j + 1));
//			m2.setVal(i + 1000000, j + 1000000, i + j + 1);
//		}
//	}
//	m1 *= m2;
//	cout << "after addition" << endl << "m1: " << endl << m1 << endl;
//	cout << "m2: " << endl << m2 << endl;
//	SMatrix a(500000000, 1000000000);
//	for (SMatrix::size_type i = 0; i < 200; ++i)
//		for (SMatrix::size_type j = 0; j < 200; ++j)
//			a.setVal(i + 1000000, j + 1000000, -1);
//
//	SMatrix b(1000000000, 500000000);
//	for (SMatrix::size_type i = 0; i < 200; ++i)
//		for (SMatrix::size_type j = 0; j < 200; ++j)
//			b.setVal(i + 1000000, j + 1000000, -1);
//
//	std::cout << a * b << std::endl;
//	SMatrix m(5, 7);
//
//	m.setVal(2, 6, 5);
//	m.setVal(2, 0, 3);
//	m.setVal(2, 3, 4);
//	m.setVal(0, 3, 1);
//	m.setVal(4, 1, 2);
//	m.setVal(4, 3, 6);
//
//	const SMatrix m2 = m;
//	SMatrix::size_type count = 1;
//	for (m2.begin(); !m2.end(); m2.next()) {
//		cout << m2.value() << " ";
//		if (count % m2.cols() == 0)
//			cout << endl;
//		++count;
//	}
//
//	cout << endl << m2 << endl;
	// identity
//	SMatrix m = SMatrix::identity(200);
//	SMatrix::size_type count = 1;
//	for (m.begin(); !m.end(); m.next()) {
//		cout << m.value() << " ";
//		if (count % m.cols() == 0)
//			cout << endl;
//		++count;
//	}
//	cout << endl << m << endl;

	// transpose
//	SMatrix m(5, 7);
//	m.setVal(2, 6, 5);
//	m.setVal(2, 0, 3);
//	m.setVal(3, 0, 3);
//	m.setVal(2, 3, 4);
//	m.setVal(0, 3, 1);
//	m.setVal(4, 1, 2);
//	m.setVal(4, 3, 6);
//	cout << "before transpose:" << endl;
//	cout << endl << m << endl;
//	SMatrix m2 = transpose(m);
//	cout << endl << m2 << endl;

	// equality
//	SMatrix a(500, 100);
//	for (SMatrix::size_type i = 0; i < 20; ++i)
//		for (SMatrix::size_type j = 0; j < 20; ++j)
//			a.setVal(i + 10, j + 10, -1);
//	a.setVal(388, 99, 1);
//	std::cout << a << std::endl;
//
//	SMatrix b(500, 100);
//	for (SMatrix::size_type i = 0; i < 20; ++i)
//		for (SMatrix::size_type j = 0; j < 20; ++j)
//			b.setVal(i + 10, j + 10, -1);
//	b.setVal(400, 88, 1);
//	b.setVal(388, 99, 1);
//	std::cout << b << std::endl;
//	if (a != b)
//		std::cout << "They are NOT equal" << std::endl;
//	else
//		std::cout << "They are equal" << std::endl;
//	SMatrix a(500000000, 1000000000);
//	for (SMatrix::size_type i = 0; i < 200; ++i)
//		for (SMatrix::size_type j = 0; j < 200; ++j)
//			a.setVal(i + 1000000, j + 1000000, -1);
//	std::cout << a << std::endl;
//
//	SMatrix b(500000000, 1000000000);
//	for (SMatrix::size_type i = 0; i < 200; ++i)
//		for (SMatrix::size_type j = 0; j < 200; ++j)
//			b.setVal(i + 1000000, j + 1000000, -1);
//	b.setVal(9,2,100);
//	std::cout << b << std::endl;
//	if (a == b)
//		std::cout << "They are equal" << std::endl;
//	else
//		std::cout << "They are NOT equal" << std::endl;

	// opt ()
//	SMatrix m(5, 7);
//	m.setVal(2, 6, 5);
//	m.setVal(2, 0, 3);
//	m.setVal(2, 3, 4);
//	m.setVal(0, 3, 1);
//	m.setVal(4, 1, 2);
//	m.setVal(4, 3, 6);
//	try {
//		cout << m(4, 1) << endl;
//	} catch (const MatrixError &e) {
//		cerr << e.what() << endl;
//	}

// opt +
//	SMatrix m1(5, 7);
//	m1.setVal(2, 0, 3);
//	m1.setVal(0, 3, 1);
//	m1.setVal(4, 1, 2);
//	m1.setVal(3, 1, 2);
//	m1.setVal(1, 1, 1);
//
//	SMatrix m2(5, 7);
//	m2.setVal(2, 6, 5);
//	m2.setVal(2, 0, 3);
//	m2.setVal(2, 3, 4);
//	m2.setVal(0, 3, 1);
//
//	cout << "before addition" << endl << "m1: " << endl << m1 << endl;
//	cout << "m2: " << endl << m2 << endl;
//
//	SMatrix m3 = m1 - m2;
//	SMatrix m3 = m2 - m1;
//	cout << "after addition" << endl << "m3: " << endl << m3 << endl;

	return 0;
}
