#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix m = SMatrix::identity(200);

 SMatrix::size_type count = 1;
  for (m.begin(); !m.end(); m.next()) {
    cout << m.value() << " ";
    if (count % m.cols() == 0)
      cout << endl;
    ++count;
  }

  cout << endl << m << endl;

  return 0;
}
