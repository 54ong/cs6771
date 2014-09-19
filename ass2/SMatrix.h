#ifndef SMATRIX_H
#define SMATRIX_H

#include <exception>
#include <map>
#include <string>
#include <cstring>
#include <utility>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

#include <cstddef>

// matrix error class
class MatrixError: public std::exception {
public:
	MatrixError(const std::string& what_arg) :
			_what(what_arg) {
	}
	virtual const char* what() const throw () {
		return _what.c_str();
	}
	virtual ~MatrixError() throw () {
	}
private:
	std::string _what;
};

// sparse matrix class
class SMatrix {
public:
	// public interface
	// *** YOU SHOULD NOT MODIFY THE PUBLIC INTERFACE IN ANY WAY! ***

	// types
	typedef size_t size_type;

	// friends
	friend bool operator==(const SMatrix&, const SMatrix&);
	friend bool operator!=(const SMatrix&, const SMatrix&);
	friend SMatrix operator+(const SMatrix&, const SMatrix&) throw (MatrixError);
	friend SMatrix operator-(const SMatrix&, const SMatrix&) throw (MatrixError);
	friend SMatrix operator*(const SMatrix&, const SMatrix&) throw (MatrixError);
	friend SMatrix transpose(const SMatrix&);
	friend std::ostream& operator<<(std::ostream&, const SMatrix&);

	// constructors
	SMatrix(size_type size = 1); // the default constructor
	SMatrix(size_type, size_type);
	SMatrix(std::istream&);
	SMatrix(const SMatrix&);   // copy
	SMatrix(SMatrix&&);        // move
	SMatrix(const std::initializer_list<std::initializer_list<int>>&); // initializer_list

	// operators
	SMatrix& operator=(const SMatrix&);  // copy
	SMatrix& operator=(SMatrix&&);       // move
	SMatrix& operator+=(const SMatrix&) throw (MatrixError);
	SMatrix& operator-=(const SMatrix&) throw (MatrixError);
	SMatrix& operator*=(const SMatrix&) throw (MatrixError);
	int operator()(size_type, size_type) const throw (MatrixError);

	// operations
	inline size_type rows() const {
		return this->row_num;
	}
	;
	inline size_type cols() const {
		return this->column_num;
	}
	;
	bool setVal(size_type, size_type, int) throw (MatrixError);

	// `iterator' operations
	void begin() const;
	bool end() const;
	void next() const;
	int value() const;
	int value(size_type, size_type) const;

	// destructor
	~SMatrix();

	// static members
	static SMatrix identity(size_type);

private:
	// private data members
	int *vals_;
	size_type *cidx_;
	std::map<size_type, std::pair<size_t, unsigned int> > ridx_;

	int arr_size; 		// the size of vals_ and cidx_ array
	int arr_used;		// array vals_, cidx_ used (number of non-zero entries)
	int row_num;  		// total number of rows
	int column_num; 	//total number of colums
	mutable size_type iter_row;
	mutable size_type iter_column;

	// you may/should augment the private interface as required by your implementation
	std::pair<std::pair<size_t, size_t>, int> parse_input(const std::string&);
	bool is_element_exist(const size_type, const size_type) const;
	bool is_insert_new_element(const size_type, const size_type, int);
	bool is_remove_elemetn(const size_type, const size_type);
	bool is_update_element(const size_type, const size_type, int);

	// debugging functions
	void print_ridx_() const;
};

#endif
