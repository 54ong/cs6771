#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix m(5, 7);

  m.setVal(2, 6, 5);
  m.setVal(2, 0, 3);
  m.setVal(2, 3, 4);
  m.setVal(0, 3, 1);
  m.setVal(4, 1, 2);
  m.setVal(4, 3, 6);
  try{
    cout << m(4,6) << endl;
  }catch(const MatrixError &e){
    cerr << e.what()<< endl;
  }
  return 0;
}
