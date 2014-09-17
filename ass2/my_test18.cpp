
#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix m1(5, 7);

  // m1.setVal(2, 0, 3);
    m1.setVal(0, 3, 1);
   m1.setVal(4, 1, 2);
  //  m1.setVal(3, 1, 2);
  //  m1.setVal(1, 1, 1);
  SMatrix m2(5, 7);
  //  m2.setVal(2, 6, 5);
  // m2.setVal(2, 0,-3);
  // m2.setVal(2, 3, 4);
   m2.setVal(0, 3, 1);
  cout << "before subtraction" << endl << "m1: " << endl << m1 << endl;
  cout << "m2: " << endl << m2 << endl;

  SMatrix m3 = m1 - m2;
  cout << "after subtraction" << endl << "m3: " << endl << m3 << endl;
  return 0;
}
