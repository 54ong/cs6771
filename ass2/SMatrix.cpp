#include "SMatrix.h"

using namespace std;
// Your fantastic implementation goes here!
// You should test it extensively to ensure that it behaves exactly 
// as required by the specification, it does not leak memory and is
// optimised for performance!

/*************************************************************
 *
 * Constructors
 *
 *************************************************************/

SMatrix::SMatrix(size_type size) {
	int tmp = 0;
	if (size * size % 5) {
		tmp = size * size / 5 + 1;
	} else {
		tmp = size * size / 5;
	}
	arr_size = min(tmp, 1000);
	row_num = size;
	column_num = size;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];
	iter_row = 0;
	iter_column = 0;
}

SMatrix::SMatrix(size_type row, size_type column) {
	int tmp = 0;
	if (row * column % 5) {
		tmp = row * column / 5 + 1;
	} else {
		tmp = row * column / 5;
	}
	arr_size = min(tmp, 1000);
	row_num = row;
	column_num = column;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];
	iter_row = 0;
	iter_column = 0;
}

SMatrix::SMatrix(std::istream& is) {

}

SMatrix::SMatrix(const SMatrix& matrix) {
	// copy
	arr_size = matrix.arr_size;
	row_num = matrix.row_num;
	column_num = matrix.column_num;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];
	iter_row = matrix.iter_row;
	iter_column = matrix.iter_column;

	memcpy(vals_, matrix.vals_, sizeof(int) * matrix.arr_size);
	memcpy(cidx_, matrix.cidx_, sizeof(int) * matrix.arr_size);
}

SMatrix::SMatrix(SMatrix&& matrix) {
	// move
	arr_size = matrix.arr_size;
	ridx_ = matrix.ridx_;
	row_num = matrix.row_num;
	column_num = matrix.column_num;
	iter_row = matrix.iter_row;
	iter_column = matrix.iter_column;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];

	move(matrix.vals_, matrix.vals_ + matrix.arr_size, vals_);
	move(matrix.cidx_, matrix.cidx_ + matrix.arr_size, cidx_);
	matrix.~SMatrix();
}

SMatrix::SMatrix(
		const std::initializer_list<std::initializer_list<int>>& list) {
	// initializer_list

}

SMatrix::~SMatrix() {
	arr_size = 0;
	row_num = 0;
	column_num = 0;
	iter_row = 0;
	iter_column = 0;

	delete[] vals_;
	delete[] cidx_;
	vals_ = nullptr;
	cidx_ = nullptr;
	ridx_.clear();
}

/*************************************************************
 *
 * Operators
 *
 *************************************************************/

// copy assignment
SMatrix& SMatrix::operator=(const SMatrix &matrix) {
	if (*this != matrix) {
		arr_size = matrix.arr_size;
		row_num = matrix.row_num;
		column_num = matrix.column_num;

		delete[] vals_;
		delete[] cidx_;
		vals_ = new int[arr_size];
		cidx_ = new size_type[arr_size];
		ridx_ = matrix.ridx_;

		memcpy(vals_, matrix.vals_, sizeof(int) * matrix.arr_size);
		memcpy(cidx_, matrix.cidx_, sizeof(int) * matrix.arr_size);

	}
	return *this;
}

// move assignment
SMatrix& SMatrix::operator=(SMatrix &&matrix) {
	if (*this != matrix) {
		arr_size = matrix.arr_size;
		row_num = matrix.row_num;
		column_num = matrix.column_num;

		vals_ = new int[arr_size];
		cidx_ = new size_type[arr_size];
		ridx_ = matrix.ridx_;

		move(matrix.vals_, matrix.vals_ + matrix.arr_size, vals_);
		move(matrix.cidx_, matrix.cidx_ + matrix.arr_size, cidx_);
		matrix.~SMatrix();
	}
	return *this;
}

SMatrix& SMatrix::operator+=(const SMatrix& matrix) throw (MatrixError) {
	*this = *this + matrix;
	return *this;
}

SMatrix& SMatrix::operator-=(const SMatrix& matrix) throw (MatrixError) {
	*this = *this - matrix;
	return *this;
}

SMatrix& SMatrix::operator*=(const SMatrix& matrix) throw (MatrixError) {
	*this = *this * matrix;
	return *this;
}

int SMatrix::operator()(size_type row, size_type column) const
		throw (MatrixError) {
	if (rows() < row || column_num < column)
		throw MatrixError("Row/Column out of Matrix range");

	auto iter = ridx_.find(row);
	if (iter != ridx_.end()) {
		for (auto i = iter->second.first;
				i < iter->second.first + iter->second.second; ++i) {
			if (cidx_[i] == column)
				return vals_[i];
		}
	}
	return 0;
}

bool SMatrix::setVal(size_type row, size_type column, int val)
		throw (MatrixError) {
	return false;
}

/*************************************************************
 *
 * Friends
 *
 *************************************************************/
bool operator==(const SMatrix &a, const SMatrix &b) {
	if (a.rows() != b.rows() || b.cols() != b.cols())
		return false;
	if (a.arr_size != b.arr_size)
		return false;
	if (a.ridx_.size() != b.ridx_.size())
		return false;
	for (auto i = 0; i < a.arr_size; ++i) {
		if (a.vals_[i] != b.vals_[i] || a.cidx_[i] != b.cidx_[i])
			return false;
	}
	// compare map ridx_

	return true;
}

bool operator!=(const SMatrix &a, const SMatrix &b) {
	return !(a == b);
}

SMatrix operator+(const SMatrix &a, const SMatrix &b) throw (MatrixError) {
	if (a.cols() == b.cols() && a.rows() == b.rows()) {
		auto temp = a;
		temp += b;
		return temp;
	} else {
		throw MatrixError("Matrix size error: ");
	}
}

SMatrix operator-(const SMatrix &a, const SMatrix &b) throw (MatrixError) {
	if (a != b) {
		if (a.rows() == b.rows() && a.cols() == b.cols()) {
			auto temp = a;
			return temp -= b;
		} else {
			throw MatrixError("Matrix size error: ");
		}
	} else {
		// matrix a, b are equal, "-" will result in an empty matrix
		SMatrix temp(a.rows(), a.cols());
		return temp;
	}
}

SMatrix operator*(const SMatrix &a, const SMatrix &b) throw (MatrixError) {
	if (a.cols() == b.rows()) {
		auto temp = a;
		return temp *= b;
	} else {
		throw MatrixError("Matrix size error: ");
	}
}

SMatrix transpose(const SMatrix &matrix) {

}

std::ostream& operator<<(std::ostream &os, const SMatrix &m) {

	// this operator will be used as the primary testing mechanism
	// make sure that it behaves ***EXACTLY*** as specified

	return os;
}

/*************************************************************
 *
 * Iterators Operations
 *
 *************************************************************/

void SMatrix::begin() const {
	iter_row = 0;
	iter_column = 0;
}

bool SMatrix::end() const {
	return (iter_row < rows() && iter_column < cols()) ? false : true;
}

void SMatrix::next() const {
	if (iter_column < cols()) {
		++iter_column;
	} else {
		++iter_row;
		iter_column = 0;
	}
}

int SMatrix::value() const {
	return (*this)(iter_row, iter_column);
}

