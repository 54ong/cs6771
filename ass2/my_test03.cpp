#include <iostream>
#include "SMatrix.h"
/*
test for b(cin)
 */
int main(void) {
  SMatrix m(std::cin);

  std::cout << m << std::endl;
  return 0;
}
