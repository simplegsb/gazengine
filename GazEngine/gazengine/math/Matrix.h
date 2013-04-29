#ifndef MATRIX_H_
#define MATRIX_H_

#include <ostream>

template<typename Data, unsigned int Columns, unsigned int Rows>
class Matrix
{
	public:
		Matrix();

		Matrix(const Matrix<Data, Columns, Rows>& original);

		Matrix(Data* data);

		~Matrix();

		Data* getData();

		const Data* getData() const;

		Data getDeterminant() const;

		void invert();

		Data& operator[](unsigned int index);

		const Data& operator[](unsigned int index) const;

		Matrix<Data, Columns, Rows>& operator*=(const Matrix<Data, Rows, Columns>& rhs);

		Matrix<Data, Columns, Rows>& operator=(const Matrix<Data, Columns, Rows>& original);

		void setData(Data* data);

		void setIdentity();

		void transpose();

	private:
		Data* data;
};

typedef Matrix<float, 3, 3> Matrix33;

typedef Matrix<float, 4, 4> Matrix44;

template<typename Data, unsigned int Columns, unsigned int Rows>
Matrix<Data, Columns, Rows> operator*(const Matrix<Data, Columns, Rows>& lhs, const Matrix<Data, Rows, Columns>& rhs);

template<typename Data, unsigned int Columns, unsigned int Rows>
bool operator!=(const Matrix<Data, Columns, Rows>& lhs, const Matrix<Data, Columns, Rows>& rhs);

template<typename Data, unsigned int Columns, unsigned int Rows>
std::ostream& operator<<(std::ostream& stream, const Matrix<Data, Columns, Rows>& matrix);

template<typename Data, unsigned int Columns, unsigned int Rows>
bool operator==(const Matrix<Data, Columns, Rows>& lhs, const Matrix<Data, Columns, Rows>& rhs);

#include "Matrix.tpp"

#endif /* MATRIX_H_ */
