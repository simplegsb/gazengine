#ifndef MATHFUNCTIONS_H_
#define MATHFUNCTIONS_H_

#include "Matrix.h"
#include "Vector.h"

namespace MathFunctions
{
	template<typename Data>
	Data crossProduct(const Vector<Data, 2>& lhs, const Vector<Data, 2>& rhs);

	template<typename Data>
	Vector<Data, 3> crossProduct(const Vector<Data, 3>& lhs, const Vector<Data, 3>& rhs);

	template<typename Data>
	Data getProximity(const Vector<Data, 2>& lhs, const Vector<Data, 2>& rhs);

	template<typename Data>
	Data getProximity(const Vector<Data, 3>& lhs, const Vector<Data, 3>& rhs);

	template<typename Data>
	Vector<Data, 3> getTranslation3(Matrix<Data, 4, 4>& matrix);

	template<typename Data>
	const Vector<Data, 3> getTranslation3(const Matrix<Data, 4, 4>& matrix);

	template<typename Data>
	Vector<Data, 4> getTranslation4(Matrix<Data, 4, 4>& matrix);

	template<typename Data>
	const Vector<Data, 4> getTranslation4(const Matrix<Data, 4, 4>& matrix);

	template<typename Data>
	void homogenize(Vector<Data, 2>& vector);

	/**
	 * <p>
	 * Multiplies the given Vector with the given Matrix. The Vector is placed on the right hand side of the
	 * equation and treated as a column vector:
	 * </p>
	 *
	 * ----------------     -----
	 *  x | x | x | x |  *  | x |
	 * ----------------     -----
	 *  x | x | x | x |     | x |
	 * ----------------     -----
	 *  x | x | x | x |     | x |
	 * ----------------     -----
	 *  x | x | x | x |     | x |
	 * ----------------     -----
	 */
	template<typename Data, unsigned int Columns, unsigned int Rows>
	Vector<Data, Rows> operator*(const Matrix<Data, Columns, Rows>& matrix, const Vector<Data, Rows>& vector);

	/**
	 * <p>
	 * Multiplies the given Vector with the given Matrix. The Vector is placed on the left hand side of the
	 * equation and treated as a row vector:
	 * </p>
	 *
	 * -----------------     -----------------
	 * | x | x | x | x |  *  | x | x | x | x |
	 * -----------------     -----------------
	 *                       | x | x | x | x |
	 *                       -----------------
	 *                       | x | x | x | x |
	 *                       -----------------
	 *                       | x | x | x | x |
	 *                       -----------------
	 */
	template<typename Data, unsigned int Columns, unsigned int Rows>
	Vector<Data, Columns> operator*(const Vector<Data, Columns>& vector, const Matrix<Data, Columns, Rows>& matrix);

	template<typename Data>
	void rotate(Matrix<Data, 3, 3>& matrix, const Data angle, const Vector<Data, 3>& axis);

	template<typename Data>
	void rotate(Matrix<Data, 4, 4>& matrix, const Data angle, const Vector<Data, 4>& axis);

	template<typename Data>
	void rotate(Vector<Data, 2>& vector, const Data angle);

	template<typename Data>
	void setTranslation(Matrix<Data, 4, 4>& matrix, const Vector<Data, 3>& translation);

	template<typename Data>
	void setTranslation(Matrix<Data, 4, 4>& matrix, const Vector<Data, 4>& translation);

	template<typename Data>
	void translate(Matrix<Data, 4, 4>& matrix, const Vector<Data, 4>& translation);
};

#include "MathFunctions.tpp"

#endif /* MATHFUNCTIONS_H_ */
