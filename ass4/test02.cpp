#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

void foo(const btree<int> &b) {
	btree<int>::iterator iter = b.begin();
	btree<int>::iterator ends = b.end();
	std::cout << *iter << " " << *ends << std::endl;
	std::copy(iter, ends, std::ostream_iterator<int>(std::cout, " "));
//	std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

int main(void) {
	btree<int> b(3);

	b.insert(1);
	b.insert(10);
	b.insert(3);
	b.insert(4);
	b.insert(14);
	b.insert(0);

//	btree<int> c;
//	c = b;

	for (btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter)
		std::cout << *iter << std::endl;
//	cout << std::endl;
//	for (btree<int>::iterator iter = c.begin(); iter != c.end(); ++iter)
//		std::cout << *iter << std::endl;
	foo(b);

	return 0;
}
