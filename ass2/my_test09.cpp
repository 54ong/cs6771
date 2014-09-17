
#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix m1(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      m1.setVal(i + 1000000, j + 1000000, -1);

   SMatrix m2(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      m2.setVal(i + 1000000, j + 1000000, -1);

  cout << "before addition" << endl << "m1: " << endl << m1 << endl;
  cout << "m2: " << endl << m2 << endl;

  m2 -= m1;
  cout << "after addition" << endl << "m1: " << endl << m1 << endl;
  cout << "m2: " << endl << m2 << endl;
  return 0;
}
