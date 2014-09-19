/**
 * On williams this test take about 0.2 secs when executed 
 * with my implementation, * which only uses straightforward
 * optimisations.
 *
 *
 * % uname -a
 * Linux williams 2.6.23.17-general #1 SMP Mon Jul 7 16:59:01 EST 2008 i686 GNU/Linux
 * % time ./test3 > test3.sol
 * 
 * real	0m0.228s
 * user	0m0.204s
 * sys	0m0.012s
 */

#include <iostream>
#include "SMatrix.h"

int main(void) {
  SMatrix a(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      a.setVal(i + 1000000, j + 1000000, -1);

  SMatrix b(500000000, 1000000000);
  for (SMatrix::size_type i = 0; i < 200; ++i)
    for (SMatrix::size_type j = 0; j < 200; ++j)
      b.setVal(i + 1000000, j + 1000000, -1);

  std::cout << a + b << std::endl;

  return 0;
}
