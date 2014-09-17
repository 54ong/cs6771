#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix a(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      a.setVal(i + 1000000, j + 1000000, -1);
  std::cout << a  << std::endl;	


  SMatrix b(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      b.setVal(i + 1000000, j + 1000000, -1);
  std::cout << b  << std::endl;	
  if( a != b )
    std::cout << "They are NOT equal"  << std::endl;
  else	
    std::cout << "They are equal"  << std::endl;
  return 0;
}
