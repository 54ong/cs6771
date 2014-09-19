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

SMatrix::SMatrix(size_type size) :
		SMatrix(size, size) {
}

SMatrix::SMatrix(size_type row, size_type column) {
	int tmp = 0;
	if (row * column % 5) {
		tmp = row * column / 5 + 1;
	} else {
		tmp = row * column / 5;
	}
	arr_size = min(tmp, 1000);
	arr_used = 0;
	row_num = row;
	column_num = column;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];
	iter_row = 0;
	iter_column = 0;
}

// How to use initializer list to use constructor
// SMatrix(i, j) in this constructor?
SMatrix::SMatrix(std::istream &is) {

	string str;
	is >> str;
	pair<pair<size_t, size_t>, int> p = parse_input(str);

	int row = p.first.first;
	int column = p.first.second;
	int tmp = 0;
	if (row * column % 5) {
		tmp = row * column / 5 + 1;
	} else {
		tmp = row * column / 5;
	}
	arr_size = min(tmp, 1000);
	arr_used = 0;
	row_num = row;
	column_num = column;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];
	iter_row = 0;
	iter_column = 0;

	while (is >> str) {
		pair<pair<size_t, size_t>, int> sub = parse_input(str);
		setVal(sub.first.first, sub.first.second, sub.second);
	}
}

// copy constructor
SMatrix::SMatrix(const SMatrix &matrix) {
	arr_size = matrix.arr_size;
	arr_used = matrix.arr_used;
	row_num = matrix.row_num;
	column_num = matrix.column_num;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];
	ridx_ = matrix.ridx_;

	iter_row = matrix.iter_row;
	iter_column = matrix.iter_column;

	copy(matrix.vals_, matrix.vals_ + arr_size, vals_);
	copy(matrix.cidx_, matrix.cidx_ + arr_size, cidx_);
}

// move constructor
SMatrix::SMatrix(SMatrix&& matrix) :
		vals_(matrix.vals_), cidx_(matrix.cidx_), ridx_(
				std::move(matrix.ridx_)), arr_size(matrix.arr_size), arr_used(
				matrix.arr_used), row_num(matrix.row_num), column_num(
				matrix.column_num), iter_row(0), iter_column(0) {
//	arr_size = matrix.arr_size;
//	arr_used = matrix.arr_used;
//	row_num = matrix.row_num;
//	column_num = matrix.column_num;
//	iter_row = matrix.iter_row;
//	iter_column = matrix.iter_column;
//	ridx_ = matrix.ridx_;
//	vals_ = new int[arr_size];
//	cidx_ = new size_type[arr_size];
//
//	move(matrix.vals_, matrix.vals_ + matrix.arr_size, vals_);
//	move(matrix.cidx_, matrix.cidx_ + matrix.arr_size, cidx_);
//	matrix.~SMatrix();
	matrix = SMatrix(0, 0);
}

// initializer_list
SMatrix::SMatrix(
		const std::initializer_list<std::initializer_list<int>>& list) {
	int size = list.size();
	arr_size = min(size, 1000);
	arr_used = 0;
	row_num = 0;
	column_num = 0;
	iter_row = 0;
	iter_column = 0;
	vals_ = new int[arr_size];
	cidx_ = new size_type[arr_size];

	for (auto iter : list) {
		auto i = iter.begin();
		int row = *i;
		int col = *++i;
		int val = *++i;

		if (row_num < row)
			row_num = row + 1;
		if (column_num < col)
			column_num = col + 1;
		setVal(row, col, val);
	}

}

SMatrix::~SMatrix() {
	arr_size = 0;
	arr_used = 0;
	row_num = 0;
	column_num = 0;
	iter_row = 0;
	iter_column = 0;

	delete[] vals_;
	delete[] cidx_;
	vals_ = nullptr;
	cidx_ = nullptr;
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

		//which would be more efficient, memcyp() or std::copy()?
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
//		matrix.~SMatrix();
		matrix = SMatrix(0, 0);
	}
	return *this;
}

SMatrix& SMatrix::operator+=(const SMatrix& m) throw (MatrixError) {
	if (this->rows() != m.rows() || this->cols() != m.cols()) {
		throw MatrixError("Matrix size error: ");
	}

//	SMatrix tmp(rows(), cols());
	if (m.arr_used == 0) {
		return *this;
	} else if (arr_used == 0 && m.arr_used != 0) {
		*this = m;
		return *this;
	}

	auto iter = ridx_.begin();
	auto m_iter = m.ridx_.begin();
	size_t lhs_i;
	size_t rhs_i;
	while (iter != ridx_.end() && m_iter != m.ridx_.end()) {
		lhs_i = iter->first;
		rhs_i = m_iter->first;
		if (lhs_i > rhs_i) {
			size_t rhs_startIdx = m_iter->second.first;
			unsigned int rhs_numValsInRow = m_iter->second.second;
			for (unsigned int k = 0; k < rhs_numValsInRow; ++k) {
				size_t rhs_j = m.cidx_[rhs_startIdx + k];
				int rhs_v = m.vals_[rhs_startIdx + k];
				setVal(rhs_i, rhs_j, rhs_v);
			}
			++m_iter;
		} else if (lhs_i < rhs_i) {
			size_t lhs_startIdx = iter->second.first;
			unsigned int lhs_numValsInRow = iter->second.second;
			for (unsigned int k = 0; k < lhs_numValsInRow; ++k) {
				size_t lhs_j = cidx_[lhs_startIdx + k];
				int lhs_v = vals_[lhs_startIdx + k];
				setVal(lhs_i, lhs_j, lhs_v);
			}
			++iter;
		} else if (lhs_i == rhs_i) {
			map<size_t, int> m_row; // result of the current row
			size_t lhs_startIdx = iter->second.first;
			unsigned int lhs_numValsInRow = iter->second.second;
			for (unsigned int k = 0; k < lhs_numValsInRow; ++k) {
				size_t lhs_j = cidx_[lhs_startIdx + k];
				int lhs_v = vals_[lhs_startIdx + k];
				m_row[lhs_j] = lhs_v;
			}
			size_t rhs_startIdx = m_iter->second.first;
			unsigned int rhs_numValsInRow = m_iter->second.second;
			for (unsigned int k = 0; k < rhs_numValsInRow; ++k) {
				size_t rhs_j = m.cidx_[rhs_startIdx + k];
				int rhs_v = m.vals_[rhs_startIdx + k];
				m_row[rhs_j] += rhs_v;
			}
			map<size_t, int>::const_iterator mit;
			for (mit = m_row.begin(); mit != m_row.end(); ++mit) {
				if (mit->second == 0)
					continue;
				setVal(lhs_i, mit->first, mit->second);
			}
			++iter;
			++m_iter;
		}
	}
	while (iter == ridx_.end() && m_iter != m.ridx_.end()) {
		rhs_i = m_iter->first;
		size_t rhs_startIdx = m_iter->second.first;
		unsigned int rhs_numValsInRow = m_iter->second.second;
		for (unsigned int k = 0; k < rhs_numValsInRow; ++k) {
			size_t rhs_j = m.cidx_[rhs_startIdx + k];
			int rhs_v = m.vals_[rhs_startIdx + k];
			setVal(rhs_i, rhs_j, rhs_v);
		}
		++m_iter;
	}
	while (iter != ridx_.end() && m_iter == m.ridx_.end()) {
		lhs_i = iter->first;
		size_t lhs_startIdx = iter->second.first;
		unsigned int lhs_numValsInRow = iter->second.second;
		for (unsigned int k = 0; k < lhs_numValsInRow; ++k) {
			size_t lhs_j = cidx_[lhs_startIdx + k];
			int lhs_v = vals_[lhs_startIdx + k];
			setVal(lhs_i, lhs_j, lhs_v);
		}
		++iter;
	}

//	for (size_type i = 0; i < rows(); ++i) {
//		for (size_type j = 0; j < cols(); ++j) {
//			int l = value(i, j);
//			int r = m.value(i, j);
//			if (l == 0 && r == 0)
//				continue;
//			setVal(i, j, l + r);
//		}
//	}

	return *this;
}

SMatrix& SMatrix::operator-=(const SMatrix& m) throw (MatrixError) {
	if (this->rows() != m.rows() || this->cols() != m.cols()) {
		throw MatrixError("Matrix size error: ");
	}

//	if (this == m)
//		return SMatrix(rows(), cols());

	for (size_type i = 0; i < rows(); ++i) {
		for (size_type j = 0; j < cols(); ++j) {
			int l = value(i, j);
			int r = m.value(i, j);
			if (l == 0 && r == 0)
				continue;
			setVal(i, j, l - r);
		}
	}

	return *this;
}

SMatrix& SMatrix::operator*=(const SMatrix& m) throw (MatrixError) {
	if (this->cols() != m.rows()) {
		throw MatrixError("Matrix size error: ");
	}

	if (arr_used == 0) {
		*this = SMatrix(rows(), m.cols());
		return *this;
	}

	SMatrix ms(rows(), m.cols());
	for (auto iter = ridx_.begin(); iter != ridx_.end(); ++iter) {
		map<size_t, int> m_row;
		size_t row = iter->first;
		auto min = iter->second.first;
		auto max = iter->second.first + iter->second.second;

		for (auto i = min; i < max; ++i) {
			size_t j = cidx_[i];
			int lhs_v = vals_[i];
			auto m_iter = m.ridx_.find(j);
			if (m_iter == m.ridx_.end())
				continue;
			// rhs_i == lhs_j, so no need to define
			auto m_min = m_iter->second.first;
			auto m_max = m_iter->second.first + m_iter->second.second;
			for (auto k = m_min; k < m_max; ++k) {
				size_t m_j = m.cidx_[k];
				int rhs_v = m.vals_[k];
				m_row[m_j] += lhs_v * rhs_v;
			}
		}

		for (auto mcit = m_row.begin(); mcit != m_row.end(); ++mcit) {
			if (mcit->second == 0)
				continue;
			ms.setVal(row, mcit->first, mcit->second);
		}
	}

	*this = ms;

	return *this;
}

int SMatrix::operator()(size_type row, size_type column) const
		throw (MatrixError) {
	if (rows() < row || cols() < column)
		throw MatrixError("Matrix bound error: ");

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

bool SMatrix::setVal(size_type row, size_type col, int val) throw (MatrixError) {

	if (row >= rows() || col >= cols()) {
		throw MatrixError("Matrix bound error: ");
	}

	bool is_succ = false;
	bool is_exist = is_element_exist(row, col);

	if (is_exist) {
		if (val == 0) {
			is_succ = is_remove_elemetn(row, col);
		} else {
			is_succ = is_update_element(row, col, val);
		}
	} else {
		if (val != 0) {
			is_succ = is_insert_new_element(row, col, val);
		}
	}

	return is_succ;
}

/*************************************************************
 *
 * Friends Functions
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

SMatrix transpose(const SMatrix &m) {
	SMatrix res(m.cols(), m.rows());
	for (auto i = m.ridx_.begin(); i != m.ridx_.end(); ++i) {
		auto row = (*i).first;
		auto col_min = (*i).second.first;
		auto col_max = (*i).second.first + (*i).second.second;
		for (auto j = col_min; j < col_max; ++j) {
			auto col = m.cidx_[j];
			res.setVal(col, row, m.vals_[j]);
		}
	}

	return res;
}

// this operator will be used as the primary testing mechanism
// make sure that it behaves ***EXACTLY*** as specified
std::ostream& operator<<(std::ostream &os, const SMatrix &m) {

	if (m.rows() > 0 && m.cols() > 0) {
		os << "(" << m.rows() << "," << m.cols() << "," << m.arr_used << ")";
		for (auto iter = m.ridx_.cbegin(); iter != m.ridx_.cend(); ++iter) {
			os << endl;
			int r = iter->first;
			size_t c = iter->second.first;
			unsigned int last_in_row = c + iter->second.second;
			for (auto i = c; i < last_in_row; ++i) {
				os << "(" << r << "," << m.cidx_[i] << "," << m.vals_[i] << ")";
				if (i < last_in_row - 1)
					os << " ";
			}
		}
	}

	return os;
}

/*************************************************************
 *
 * Iterators
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

int SMatrix::value(size_type row, size_type col) const {
	return (*this)(row, col);
}

/*************************************************************
 *
 * Helper Functions
 *
 *************************************************************/

std::pair<std::pair<size_t, size_t>, int> SMatrix::parse_input(
		const std::string& str) {
	size_t row;
	size_t column;
	int val;

	std::string s = str.substr(1, str.length() - 2);
	std::replace(s.begin(), s.end(), ',', ' ');
	std::istringstream iss(s);
	iss >> row >> column >> val;
	std::pair<std::pair<size_t, size_t>, int> ptr = make_pair(
			make_pair(row, column), val);
	return ptr;
}

/*
 * Check if the entry (row, col) given exist in the ridx_, cidx_
 */
bool SMatrix::is_element_exist(const size_type row, const size_type col) const {
	if (ridx_.find(row) != ridx_.end()) {
		auto iter = ridx_.find(row);
		auto min = iter->second.first;
		auto max = iter->second.first + iter->second.second;
//		cout << "min " << min << " max " << max << endl;
//		cout << cidx_[min] << " " << cidx_[max - 1] << endl;
//		cout << (cidx_[min] <= col && cidx_[max - 1] > col) << endl;

		for (auto i = min; i < max; ++i) {
			if (cidx_[i] == col)
				return true;
		}
	}
	return false;
}

bool SMatrix::is_insert_new_element(const size_type row, const size_type col,
		int val) {

	// double vals_, cidx_ size if array reaches capacity
	if (arr_used >= arr_size) {
		arr_size *= 2;
		int * vals = new int[arr_size];
		size_type * cidx = new size_type[arr_size];

		for (auto i = 0; i < arr_used; ++i) {
			vals[i] = vals_[i];
			cidx[i] = cidx_[i];
		}
		delete[] vals_;
		delete[] cidx_;
		vals_ = vals;
		cidx_ = cidx;
	}

	// row already in ridx_
	if (ridx_.find(row) != ridx_.end()) {
		int min = ridx_.at(row).first;
		int max = ridx_.at(row).first + ridx_.at(row).second;

		++ridx_.at(row).second;
		for (auto iter = ridx_.begin(); iter != ridx_.end(); ++iter) {
			if (iter->second.first > ridx_.at(row).first)
				iter->second.first += 1;
		}

		// find the position to insert the new entry
		auto i = min;
		for (; i < max; ++i) {
			if (cidx_[i] >= col)
				break;
		}

		auto tmp1 = vals_[i];
		auto tmp2 = cidx_[i];
		vals_[i] = val;
		cidx_[i] = col;
		++i;
		for (; i <= arr_used; ++i) {
			auto tm1 = vals_[i];
			auto tm2 = cidx_[i];

			vals_[i] = tmp1;
			cidx_[i] = tmp2;
			tmp1 = tm1;
			tmp2 = tm2;
		}
	} else {
		vals_[arr_used] = val;
		cidx_[arr_used] = col;
		ridx_.insert(
				std::pair<size_type, std::pair<size_t, unsigned int>>(row,
						make_pair(arr_used, 1)));
	}
	++arr_used;

	return true;
}

bool SMatrix::is_remove_elemetn(const size_type row, const size_type col) {
	if (!is_element_exist(row, col) || arr_used < 1)
		return false;

	auto min = ridx_.at(row).first;
	auto max = ridx_.at(row).first + ridx_.at(row).second;

//	print_ridx_();
//	cout << min << " " << ridx_.at(row).second << endl;

	// update ridx_, move all pairs after fidx_.find(row) forward
	// (row, col) is the only entry on the row, need to delete the
	// entire row
	if (ridx_.at(row).second == 1) {
//		print_ridx_();
		ridx_.erase(ridx_.find(row));
//		print_ridx_();
	} else {
//		print_ridx_();
		--ridx_.at(row).second;
		for (auto iter = ridx_.begin(); iter != ridx_.end(); ++iter) {
			if (iter->second.first > min)
				iter->second.first -= 1;
		}
//		print_ridx_();
	}

	// remove entry from vals_ and cidx_
//	int max = ridx_.at(row).first + ridx_.at(row).second;

	auto i = min;
	for (; i < max; ++i) {
		if (cidx_[i] >= col)
			break;
	}

	for (; i < arr_used; ++i) {
		cidx_[i] = cidx_[i + 1];
		vals_[i] = vals_[i + 1];
	}
	cidx_[arr_used - 1] = 0;
	vals_[arr_used - 1] = 0;
	--arr_used;
	if(ridx_.size() ==1){
		auto iter = ridx_.begin();
		iter->second.first = 0;
	}

//	print_ridx_();
	return true;
}

bool SMatrix::is_update_element(const size_type row, const size_type col,
		int val) {
	if (!is_element_exist(row, col) || arr_used < 1)
		return false;

	if (ridx_.find(row) != ridx_.end()) {
		auto iter = ridx_.find(row);
		auto min = iter->second.first;
		auto max = iter->second.first + iter->second.second;
		for (auto i = min; i < max; ++i) {
			if (cidx_[i] == col)
				vals_[i] = val;
		}
	}

	return false;
}

/*************************************************************
 *
 * Debugging Functions
 *
 *************************************************************/

void SMatrix::print_ridx_() const {
	cout << endl;
	for (auto iter = ridx_.begin(); iter != ridx_.end(); ++iter) {
		cout << "row: " << iter->first << " ";
		cout << "col: " << iter->second.first << " ";
		cout << "len: " << iter->second.second << " " << endl;
	}
	cout << endl;
	for (auto i = 0; i < arr_used; ++i)
		cout << cidx_[i] << " ";
	cout << endl;
	for (auto i = 0; i < arr_used; ++i)
		cout << vals_[i] << " ";
	cout << endl;
}
