#include <iostream>
#include "SMatrix.h"

using namespace std;

int main(void) {
  SMatrix a(500, 100);
  for (SMatrix::size_type i = 0; i < 20; ++i)
    for (SMatrix::size_type j = 0; j < 20; ++j)
      a.setVal(i + 10, j + 10, -1);
  a.setVal(388,99,1);
  std::cout << a  << std::endl;	


  SMatrix b(500, 100);
  for (SMatrix::size_type i = 0; i < 20; ++i)
    for (SMatrix::size_type j = 0; j < 20; ++j)
      b.setVal(i + 10, j + 10, -1);
  b.setVal(400,88,1);
  std::cout << b  << std::endl;	
  if( a != b )
    std::cout << "They are NOT equal"  << std::endl;
  else	
    std::cout << "They are equal"  << std::endl;
  return 0;
}
