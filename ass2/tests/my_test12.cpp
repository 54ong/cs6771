#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
	SMatrix m(5, 7);

	m.setVal(2, 6, 5);
	m.setVal(2, 0, 3);
	m.setVal(3, 0, 3);
	m.setVal(2, 3, 4);
	m.setVal(0, 3, 1);
	m.setVal(4, 1, 2);
	m.setVal(4, 3, 6);
	cout << "before transpose:" << endl;
	SMatrix::size_type count = 1;
	for (m.begin(); !m.end(); m.next()) {
		cout << m.value() << " ";
		if (count % m.cols() == 0)
			cout << endl;
		++count;
	}
	cout << endl << m << endl;
	SMatrix m2 = transpose(m);
	cout << "after transpose:" << endl;
	count = 1;
	for (m2.begin(); !m2.end(); m2.next()) {
		cout << m2.value() << " ";
		if (count % m2.cols() == 0)
			cout << endl;
		++count;
	}

	cout << endl << m2 << endl;

	return 0;
}
