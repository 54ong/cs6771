// your btree implementation goes here
#include "btree.h";
#include "btree_iterator.h";

/**
 * Default constructor for BTree.
 *
 * @param maxNodeElems the maximum number of elements
 *        that can be stored in each B-Tree node
 */
template<typename T>
btree<T>::btree(size_t maxNodeElems = 40) :
		root_(NULL), head_(NULL), tail_(NULL), __maxNodeElems(maxNodeElems),
			__tree_Size_(0) { }

/**
 * Copy constructor
 * Creates a new B-Tree as a copy of original.
 *
 * @param original a const lvalue reference to a B-Tree object
 */
template<typename T>
btree<T>::btree(const btree<T>& original) :
		root_(new Node(*(original.root_))), head_(NULL), tail_(NULL), __maxNodeElems(
				original.__maxNodeElems), __tree_Size_(0) {

}

/**
 * Move constructor
 * Creates a new B-Tree by "stealing" from original.
 *
 * @param original an rvalue reference to a B-Tree object
 */
template<typename T>
btree<T>::btree(btree<T> && original) :
		root_(original.root_), head_(original.head_), tail_(original.tail_), __maxNodeElems(
				original.__maxNodeElems), __tree_Size_(0) {
}

template<typename T>
btree<T>::~btree() {
	delete root_;
}

/**
 * Copy assignment
 * Replaces the contents of this object with a copy of rhs.
 *
 * @param rhs a const lvalue reference to a B-Tree object
 */
template<typename T> btree<T>&
btree<T>::operator=(const btree<T>& rhs) {
	if (this != rhs) {
		delete root_;
		root_ = nullptr;
		head_ = nullptr;
		tail_ = nullptr;
		root_ = rhs.root_;
		__maxNodeElems = rhs.__maxNodeElems;
		__tree_Size_ = 0;
	}
	return *this;
}

/**
 * Move assignment
 * Replaces the contents of this object with the "stolen"
 * contents of original.
 *
 * @param rhs a const reference to a B-Tree object
 */
template<typename T> btree<T>&
btree<T>::operator=(btree<T> && rhs) {
	if (this != &rhs) {
		delete root_;
		root_ = nullptr;
		head_ = nullptr;
		tail_ = nullptr;
		root_ = rhs.root_;
		__maxNodeElems = rhs.__maxNodeElems;
		__tree_Size_ = 0;

		rhs.root_ = new Node(__maxNodeElems);
		rhs.head_ = nullptr;
		rhs.tail_ = nullptr;
		rhs.__tree_Size_ = 0;
	}
	return *this;
}

template<typename T> typename btree<T>::iterator
begin() const {
	return iterator(head_, 0. this);
}

template<typename T> typename btree<T>::iterator
end() const {
	return iterator(nullptr, 0, this);
}

template<typename T> typename btree<T>::reverse_iterator
rbegin() const {
	return reverse_iterator(end());
}

template<typename T> typename btree<T>::reverse_iterator
rend() const {
	return reverse_iterator(begin());
}

template<typename T> typename btree<T>::const_iterator
cbegin() const {
	return const_iterator(head_, 0, this);
}

template<typename T> typename btree<T>::const_iterator
cend() const {
	return const_iterator(nullptr, 0, this);
}

template<typename T> typename btree<T>::const_reverse_iterator
crbegin() const {
	return const_reverse_iterator(end());
}

template<typename T> typename btree<T>::const_reverse_iterator
crend() const {
	return const_reverse_iterator(begin());
}

template<typename T> typename btree<T>::iterator
btree<T>::find(const T& elem) {
}

template<typename T> typename btree<T>::const_iterator
btree<T>::find(const T& elem) const {
}

template<typename T> std::pair<iterator, bool>
btree<T>::insert(const T& elem) {

}

template<typename T> std::ostream&
operator<<<T>(std::ostream& os, const btree<T>& tree) {

}

