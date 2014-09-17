#include <iostream>
#include "SMatrix.h"
/*
test for b(cin)
 */
using namespace std;
int main(void) {
  SMatrix m(std::cin);
  cout << "before transpose:" << endl;
  SMatrix::size_type count = 1;
  for (m.begin(); !m.end(); m.next()) {
    cout << m.value() << " ";
    if (count % m.cols() == 0)
      cout << endl;
    ++count;
  }
  cout  << endl  << m << endl;
  SMatrix m2 = transpose(m);
  cout << "after transpose:" << endl;
  count = 1;
  for (m2.begin(); !m2.end(); m2.next()) {
    cout << m2.value() << " ";
    if (count % m2.cols() == 0)
      cout << endl;
    ++count;
  }

  cout << endl  << m2 << endl;

  return 0;
}
