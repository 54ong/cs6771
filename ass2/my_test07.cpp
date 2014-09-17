// You should design a similar test case to test your
// copy and move assignment operators

#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix m1(2, 3);

  for (SMatrix::size_type i = 0; i < 2; ++i)
    for (SMatrix::size_type j = 0; j < 3; ++j)
      m1.setVal(i, j, i+j);
      cout << "m1: " << endl << m1 << endl;
  return 0;
}
