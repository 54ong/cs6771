#include <iostream>
#include "SMatrix.h"

int main(void) {
  SMatrix a(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      a.setVal(i + 1000000, j + 1000000, -1);

   std::cout << a  << std::endl;	
  return 0;
}
