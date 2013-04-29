#include "MathFunctions.h"

template<typename Data>
Data crossProduct(const Vector<Data, 2>& lhs, const Vector<Data, 2>& rhs)
{
	return lhs.X() * rhs.X() + lhs.Y() * rhs.Y();
}

template<typename Data>
Vector<Data, 3> crossProduct(const Vector<Data, 3>& lhs, const Vector<Data, 3>& rhs)
{
	Vector<Data, 3> crossProduct;

	crossProduct.X() = lhs.Y() * rhs.Z() - lhs.Z() * rhs.Y();
	crossProduct.Y() = lhs.Z() * rhs.X() - lhs.X() * rhs.Z();
	crossProduct.Z() = lhs.X() * rhs.Y() - lhs.Y() * rhs.X();

	return crossProduct;
}

template<typename Data>
Vector<Data, 3> getOut3(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(&matrix[8], false);
}

template<typename Data>
const Vector<Data, 3> getOut3(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(const_cast<Data*>(&matrix[8]), false);
}

template<typename Data>
Vector<Data, 4> getOut4(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(&matrix[8], false);
}

template<typename Data>
const Vector<Data, 4> getOut4(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(const_cast<Data*>(&matrix[8]), false);
}

template<typename Data>
Data getProximity(const Vector<Data, 2>& lhs, const Vector<Data, 2>& rhs)
{
	Vector<Data, 2> difference = lhs;
	difference -= rhs;

	return difference.getMagnitude();
}

template<typename Data>
Data getProximity(const Vector<Data, 3>& lhs, const Vector<Data, 3>& rhs)
{
	Vector<Data, 3> difference = lhs;
	difference -= rhs;

	return difference.getMagnitude();
}

template<typename Data>
Vector<Data, 3> getRight3(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(&matrix[0], false);
}

template<typename Data>
const Vector<Data, 3> getRight3(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(const_cast<Data*>(&matrix[0]), false);
}

template<typename Data>
Vector<Data, 4> getRight4(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(&matrix[0], false);
}

template<typename Data>
const Vector<Data, 4> getRight4(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(const_cast<Data*>(&matrix[0]), false);
}

template<typename Data>
Vector<Data, 3> getTranslation3(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(&matrix[12], false);
}

template<typename Data>
const Vector<Data, 3> getTranslation3(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(const_cast<Data*>(&matrix[12]), false);
}

template<typename Data>
Vector<Data, 4> getTranslation4(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(&matrix[12], false);
}

template<typename Data>
const Vector<Data, 4> getTranslation4(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(const_cast<Data*>(&matrix[12]), false);
}

template<typename Data>
Vector<Data, 3> getUp3(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(&matrix[4], false);
}

template<typename Data>
const Vector<Data, 3> getUp3(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 3>(const_cast<Data*>(&matrix[4]), false);
}

template<typename Data>
Vector<Data, 4> getUp4(Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(&matrix[4], false);
}

template<typename Data>
const Vector<Data, 4> getUp4(const Matrix<Data, 4, 4>& matrix)
{
	return Vector<Data, 4>(const_cast<Data*>(&matrix[4]), false);
}

template<typename Data>
void homogenize(Vector<Data, 4>& vector)
{
	vector /= vector.W();
}

template<typename Data, unsigned int Columns, unsigned int Rows>
Vector<Data, Rows> operator*(const Matrix<Data, Columns, Rows>& matrix, const Vector<Data, Rows>& vector)
{
	Vector<Data, Rows> product;

	// For every row in the matrix.
	for (unsigned int row = 0; row < Rows; row++)
	{
		Data sum = 0;

		// For every element in the vector and every element in the current row of the matrix.
		for (unsigned int element = 0; element < Columns; element++)
		{
			// Add the product of the two to the value for the new vector.
			sum += matrix[row + element * Columns] * vector[element];
		}

		product[row] = sum;
	}

	return product;
}

template<typename Data, unsigned int Columns, unsigned int Rows>
Vector<Data, Columns> operator*(const Vector<Data, Columns>& vector, const Matrix<Data, Columns, Rows>& matrix)
{
	Vector<Data, Columns> product;

	// For every column in the matrix.
	for (unsigned int column = 0; column < Columns; column++)
	{
		Data sum = 0;

		// For every element in the vector and every element in the current column of the matrix.
		for (unsigned int element = 0; element < Rows; element++)
		{
			// Add the product of the two to the value for the new vector.
			sum += vector[element] * matrix[column * Rows + element];
		}

		product[column] = sum;
	}

	return product;
}

template<typename Data>
void rotate(Matrix<Data, 3, 3>& matrix, const Data angle, const Vector<Data, 3>& axis)
{
	// Precompute information.
	Data cosine = cos(angle);
	Data sine = sin(angle);
	Data oneMinusCosine = 1 - cosine;

	Data sineX = sine * axis.X();
	Data sineY = sine * axis.Y();
	Data sineZ = sine * axis.Z();

	Data xy = axis.X() * axis.Y();
	Data xz = axis.X() * axis.Z();
	Data yz = axis.Y() * axis.Z();

	// Setup rotation matrix.
	// X axis component.
	Data d00 = axis.X() * axis.X() * oneMinusCosine + cosine;
	Data d01 = xy * oneMinusCosine + sineZ;
	Data d02 = xz * oneMinusCosine - sineY;

	// Y axis component.
	Data d10 = xy * oneMinusCosine - sineZ;
	Data d11 = axis.Y() * axis.Y() * oneMinusCosine + cosine;
	Data d12 = yz * oneMinusCosine + sineX;

	// Z axis component.
	Data d20 = xz * oneMinusCosine + sineY;
	Data d21 = yz * oneMinusCosine - sineX;
	Data d22 = axis.Z() * axis.Z() * oneMinusCosine + cosine;

	Data temp00 = matrix[0] * d00 + matrix[3] * d01 + matrix[6] * d02;
	Data temp01 = matrix[1] * d00 + matrix[4] * d01 + matrix[7] * d02;
	Data temp02 = matrix[2] * d00 + matrix[5] * d01 + matrix[8] * d02;
	Data temp10 = matrix[0] * d10 + matrix[3] * d11 + matrix[6] * d12;
	Data temp11 = matrix[1] * d10 + matrix[4] * d11 + matrix[7] * d12;
	Data temp12 = matrix[2] * d10 + matrix[5] * d11 + matrix[8] * d12;
	matrix[6] = matrix[0] * d20 + matrix[3] * d21 + matrix[6] * d22;
	matrix[7] = matrix[1] * d20 + matrix[4] * d21 + matrix[7] * d22;
	matrix[8] = matrix[2] * d20 + matrix[5] * d21 + matrix[8] * d22;
	matrix[0] = temp00;
	matrix[1] = temp01;
	matrix[2] = temp02;
	matrix[3] = temp10;
	matrix[4] = temp11;
	matrix[5] = temp12;
}

template<typename Data>
void rotate(Matrix<Data, 4, 4>& matrix, const Data angle, const Vector<Data, 4>& axis)
{
	// Precompute information.
	Data cosine = cos(angle);
	Data sine = sin(angle);
	Data oneMinusCosine = 1 - cosine;

	Data sineX = sine * axis.X();
	Data sineY = sine * axis.Y();
	Data sineZ = sine * axis.Z();

	Data xy = axis.X() * axis.Y();
	Data xz = axis.X() * axis.Z();
	Data yz = axis.Y() * axis.Z();

	// Setup rotation matrix.
	// X axis component.
	Data d00 = axis.X() * axis.X() * oneMinusCosine + cosine;
	Data d01 = xy * oneMinusCosine + sineZ;
	Data d02 = xz * oneMinusCosine - sineY;

	// Y axis component.
	Data d10 = xy * oneMinusCosine - sineZ;
	Data d11 = axis.Y() * axis.Y() * oneMinusCosine + cosine;
	Data d12 = yz * oneMinusCosine + sineX;

	// Z axis component.
	Data d20 = xz * oneMinusCosine + sineY;
	Data d21 = yz * oneMinusCosine - sineX;
	Data d22 = axis.Z() * axis.Z() * oneMinusCosine + cosine;

	Data temp00 = matrix[0] * d00 + matrix[4] * d01 + matrix[8] * d02;
	Data temp01 = matrix[1] * d00 + matrix[5] * d01 + matrix[9] * d02;
	Data temp02 = matrix[2] * d00 + matrix[6] * d01 + matrix[10] * d02;
	Data temp03 = matrix[3] * d00 + matrix[7] * d01 + matrix[11] * d02;
	Data temp10 = matrix[0] * d10 + matrix[4] * d11 + matrix[8] * d12;
	Data temp11 = matrix[1] * d10 + matrix[5] * d11 + matrix[9] * d12;
	Data temp12 = matrix[2] * d10 + matrix[6] * d11 + matrix[10] * d12;
	Data temp13 = matrix[3] * d10 + matrix[7] * d11 + matrix[11] * d12;
	matrix[8] = matrix[0] * d20 + matrix[4] * d21 + matrix[8] * d22;
	matrix[9] = matrix[1] * d20 + matrix[5] * d21 + matrix[9] * d22;
	matrix[10] = matrix[2] * d20 + matrix[6] * d21 + matrix[10] * d22;
	matrix[11] = matrix[3] * d20 + matrix[7] * d21 + matrix[11] * d22;
	matrix[0] = temp00;
	matrix[1] = temp01;
	matrix[2] = temp02;
	matrix[3] = temp03;
	matrix[4] = temp10;
	matrix[5] = temp11;
	matrix[6] = temp12;
	matrix[7] = temp13;
}

template<typename Data>
void rotate(Vector<Data, 2>& vector, const Data angle)
{
	Data cosine = cos(angle);
	Data sine = sin(angle);

	vector.X(vector.X() * cosine - vector.Y() * sine);
	vector.Y(vector.X() * sine + vector.Y() * cosine);
}

template<typename Data>
void setTranslation(Matrix<Data, 4, 4>& matrix, const Vector<Data, 3>& translation)
{
	matrix[12] = translation.X();
	matrix[13] = translation.Y();
	matrix[14] = translation.Z();
	matrix[15] = 1.0f;
}

template<typename Data>
void setTranslation(Matrix<Data, 4, 4>& matrix, const Vector<Data, 4>& translation)
{
	matrix[12] = translation.X();
	matrix[13] = translation.Y();
	matrix[14] = translation.Z();
	matrix[15] = translation.W();
}

template<typename Data>
void translate(Matrix<Data, 4, 4>& matrix, const Vector<Data, 4>& translation)
{
	matrix[12] += matrix[0] * translation.X() + matrix[4] * translation.Y() + matrix[8] * translation.Z();
	matrix[13] += matrix[1] * translation.X() + matrix[5] * translation.Y() + matrix[9] * translation.Z();
	matrix[14] += matrix[2] * translation.X() + matrix[6] * translation.Y() + matrix[10] * translation.Z();
	matrix[15] += matrix[3] * translation.X() + matrix[7] * translation.Y() + matrix[11] * translation.Z();
}
