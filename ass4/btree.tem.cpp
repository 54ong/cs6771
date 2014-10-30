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

/**
 * Operation which inserts the specified element
 * into the btree if a matching element isn't already
 * present.  In the event where the element truly needs
 * to be inserted, the size of the btree is effectively
 * increases by one, and the pair that gets returned contains
 * an iterator to the inserted element and true in its first and
 * second fields.
 *
 * If a matching element already exists in the btree, nothing
 * is added at all, and the size of the btree stays the same.  The
 * returned pair still returns an iterator to the matching element, but
 * the second field of the returned pair will store false.  This
 * second value can be checked to after an insertion to decide whether
 * or not the btree got bigger.
 *
 * The insert method makes use of T's zero-arg constructor and
 * operator= method, and if these things aren't available,
 * then the call to btree<T>::insert will not compile.  The implementation
 * also makes use of the class's operator== and operator< as well.
 *
 * @param elem the element to be inserted.
 * @return a pair whose first field is an iterator positioned at
 *         the matching element in the btree, and whose second field
 *         stores true if and only if the element needed to be added
 *         because no matching element was there prior to the insert call.
 */
template<typename T> std::pair<iterator, bool>
btree<T>::insert(const T& elem) {
	if (__maxNodeElems == 0)
		return make_pair(end(), false);

	Node **ptr_ = &root_;
	Node *parent = NULL;
	bool new_head = false;
	bool new_tail = false;

	while (true) {
		Node *node_ = *ptr_;
		// No element in the btree currently, create a new Node elem
		if(node_ == nullptr){
			node_ = new Node(parent, __maxNodeElems, elem);
			if(*ptr_ == root_) {
				head_ = root_;
				tail_ = root_;
			} else if(new_head == true) {
				head_ = *ptr_;
				new_head = false;
			} else if(new_tail == true) {
				tail_ = *ptr_;
				new_tail = false;
			}
			++__tree_Size_;
			return make_pair(iterator(*node_, 0, this), true);
		} else if(!node_->is_full()){
			// insert elem in current node
			size_t i = 0;
			for(; i < node_-> __occupied_size_; ++i){

			}


			return make_pair(iterator(node_, i, this), true);
		} else {
			// current node is full, will create and insert a descendant node

		}

	}


}

/**
 * Puts a breadth-first traversal of the B-Tree onto the output
 * stream os. Elements must, in turn, support the output operator.
 * Elements are separated by space. Should not output any newlines.
 *
 * @param os a reference to a C++ output stream
 * @param tree a const reference to a B-Tree object
 * @return a reference to os
 */
template<typename T> std::ostream&
operator<<(std::ostream& os, const btree<T>& tree) {
	if (tree.__maxNodeElems == 0)
		return os;
	vector<typename btree<T>::Node *> _currLevel;
	vector<typename btree<T>::Node *> _nextLevel;

	_currLevel.push_back(tree.root_);
	while (!_currLevel.empty()) {
		typename vector<typename btree<T>::Node *>::const_iterator iter;
		for (iter = _currLevel.begin(); iter != _currLevel.end(); ++iter) {
			typename btree<T>::Node * _node = *iter;
			size_t i = 0;
			for(; i < _node->__occupied_size_; ++i){
				os << _node->__elem_[i] << " ";
				if(_node->__descendants_[i] != nullptr){
					_nextLevel.push_back(_node->__descendants_[i]);
				}
			}
			if(_node->__descendants_[i] != nullptr){
				_nextLevel.push_back(_node->__descendants_[i]);
			}
		}
		_currLevel = _nextLevel;
		_nextLevel.clear();
	}
}

