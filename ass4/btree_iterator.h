#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>
using namespace std;

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template<typename T> class btree;
template<typename T> class btree_iterator;
template<typename T> class const_btree_iterator;

template<typename T> class btree_iterator {
	typedef ptrdiff_t                  	difference_type;
	typedef bidirectional_iterator_tag	iterator_category;
	typedef T 						   	value_type;
	typedef T* 							pointer;
	typedef T& 							reference;
	friend class const_btree_iterator<T>;

	reference operator*() const;
	pointer operator->() const { return &(operator*()); }
	btree_iterator& operator++();
	bool operator==(const List_Iterator& other) const;
	bool operator!=(const List_Iterator& other) const
	{ return !operator==(other); }
	List_Iterator(typename List<T>::Node *pointee = nullptr) : pointee_(pointee) {}
	private:
	typename List<T>::Node *pointee_;


};

template<typename T> class const_btree_iterator {

};

#include "btree_iterator.tem"

#endif
