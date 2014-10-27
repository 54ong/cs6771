// your btree implementation goes here
#include "btree.h";
template<typename T>
btree<T>::btree(size_t maxNodeElems = 40) {
}

template<typename T>
btree<T>::btree(const btree<T>& original) {
}

template<typename T>
btree<T>::btree(btree<T> && original) {
}

template<typename T> btree<T>&
btree<T>::operator=(const btree<T>& rhs) {
}

template<typename T> btree<T>&
btree<T>::operator=(btree<T> && rhs) {
}

template<typename T> typename btree<T>::iterator begin() const {
}

template<typename T> typename btree<T>::iterator end() const {
}

template<typename T> typename btree<T>::reverse_iterator rbegin() const {
}

template<typename T> typename btree<T>::reverse_iterator rend() const {
}

template<typename T> typename btree<T>::const_iterator cbegin() const {
}

template<typename T> typename btree<T>::const_iterator cend() const {
}

template<typename T> typename btree<T>::const_reverse_iterator crbegin() const {
}

template<typename T> typename btree<T>::const_reverse_iterator crend() const {
}

template<typename T> typename btree<T>::iterator btree<T>::find(const T& elem) {
}

template<typename T> typename btree<T>::const_iterator btree<T>::find(
		const T& elem) const {
}

template<typename T> std::pair<iterator, bool> btree<T>::insert(const T& elem) {

}

template<typename T> std::ostream&
operator<<<T>(std::ostream& os, const btree<T>& tree) {

}

