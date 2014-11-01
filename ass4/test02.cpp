#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

void foo(const btree<int> &b) {
	std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

int main(void) {
	btree<int> b(3);

	b.insert(1);
	b.insert(10);
	b.insert(3);
	b.insert(4);

//	btree<int>::iterator iter = b.begin();
//		std::cout << *iter << std::endl;
//	iter = b.end();
//	std::cout << *iter << std::endl;

	for (btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter)
		std::cout << *iter << std::endl;

//	foo(b);

	return 0;
}
