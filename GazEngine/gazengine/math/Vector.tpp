#include <cmath>

#include "Vector.h"

using namespace std;

template<typename Data, unsigned int Size>
Vector<Data, Size>::Vector() :
	data(new Data[Size]),
	dataOwner(true)
{
}

template<typename Data, unsigned int Size>
Vector<Data, Size>::Vector(const Vector<Data, Size>& original) :
	data(new Data[Size]),
	dataOwner(true)
{
	operator=(original);
}

template<typename Data, unsigned int Size>
Vector<Data, Size>::Vector(Data* data, bool takeOwnership) :
	data(NULL),
	dataOwner(false)
{
	setData(data, takeOwnership);
}

template<typename Data, unsigned int Size>
Vector<Data, Size>::Vector(Data d0, Data d1) :
	data(new Data[Size]),
	dataOwner(true)
{
	data[0] = d0;
	data[1] = d1;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>::Vector(Data d0, Data d1, Data d2) :
	data(new Data[Size]),
	dataOwner(true)
{
	data[0] = d0;
	data[1] = d1;
	data[2] = d2;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>::Vector(Data d0, Data d1, Data d2, Data d3) :
	data(new Data[Size]),
	dataOwner(true)
{
	data[0] = d0;
	data[1] = d1;
	data[2] = d2;
	data[3] = d3;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>::~Vector()
{
	if (dataOwner)
	{
		delete[] data;
	}
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::A()
{
	return data[3];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::A() const
{
	return data[3];
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::B()
{
	return data[2];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::B() const
{
	return data[2];
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::G()
{
	return data[1];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::G() const
{
	return data[1];
}

template<typename Data, unsigned int Size>
Data* Vector<Data, Size>::getData()
{
	return data;
}

template<typename Data, unsigned int Size>
const Data* Vector<Data, Size>::getData() const
{
	return data;
}

template<typename Data, unsigned int Size>
Data Vector<Data, Size>::getMagnitude() const
{
	return sqrt(getMagnitudeSquared());
}

template<typename Data, unsigned int Size>
Data Vector<Data, Size>::getMagnitudeSquared() const
{
	Data magnitudeSquared = 0;

	for (unsigned int index = 0; index < Size; index++)
	{
		magnitudeSquared += pow(data[index], 2);
	}

	return magnitudeSquared;
}

template<typename Data, unsigned int Size>
void Vector<Data, Size>::negate()
{
	operator*=(-1);
}

template<typename Data, unsigned int Size>
void Vector<Data, Size>::normalize()
{
	operator*=(1 / getMagnitude());
}

template<typename Data, unsigned int Size>
Vector<Data, Size>& Vector<Data, Size>::operator/=(const Vector<Data, Size>& rhs)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		data[index] /= rhs.data[index];
	}

	return *this;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>& Vector<Data, Size>::operator/=(const Data scalar)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		data[index] /= scalar;
	}

	return *this;
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::operator[](unsigned int index)
{
	return data[index];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::operator[](unsigned int index) const
{
	return data[index];
}

template<typename Data, unsigned int Size>
Vector<Data, Size>& Vector<Data, Size>::operator*=(const Vector<Data, Size>& rhs)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		data[index] *= rhs.data[index];
	}

	return *this;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>& Vector<Data, Size>::operator*=(const Data scalar)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		data[index] *= scalar;
	}

	return *this;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>& Vector<Data, Size>::operator+=(const Vector<Data, Size>& rhs)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		data[index] += rhs.data[index];
	}

	return *this;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>& Vector<Data, Size>::operator=(const Vector<Data, Size>& original)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		data[index] = original.data[index];
	}

	return *this;
}

template<typename Data, unsigned int Size>
Vector<Data, Size>& Vector<Data, Size>::operator-=(const Vector<Data, Size>& rhs)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		data[index] -= rhs.data[index];
	}

	return *this;
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::R()
{
	return data[0];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::R() const
{
	return data[0];
}

template<typename Data, unsigned int Size>
void Vector<Data, Size>::setData(Data* data, bool takeOwnership)
{
	if (dataOwner && !takeOwnership)
	{
		delete[] data;
		dataOwner = false;
	}
	else if (!dataOwner && takeOwnership)
	{
		data = new Data[Size];
		dataOwner = true;
	}

	if (takeOwnership)
	{
		for (unsigned int index = 0; index < Size; index++)
		{
			this->data[index] = data[index];
		}
	}
	else
	{
		this->data = data;
	}
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::W()
{
	return data[3];
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::X()
{
	return data[0];
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::Y()
{
	return data[1];
}

template<typename Data, unsigned int Size>
Data& Vector<Data, Size>::Z()
{
	return data[2];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::W() const
{
	return data[3];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::X() const
{
	return data[0];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::Y() const
{
	return data[1];
}

template<typename Data, unsigned int Size>
const Data& Vector<Data, Size>::Z() const
{
	return data[2];
}

template<typename Data, unsigned int Size>
Data dotProduct(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs)
{
	Data dot = 0;

	for (unsigned int index = 0; index < Size; index++)
	{
		dot += lhs[index] * rhs[index];
	}

	return dot;
}

template<typename Data, unsigned int Size>
Vector<Data, Size> operator-(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs)
{
	Vector<Data, Size> sum = lhs;
	sum -= rhs;

	return sum;
}

template<typename Data, unsigned int Size>
bool operator!=(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs)
{
	return !(lhs == rhs);
}

template<typename Data, unsigned int Size>
Vector<Data, Size> operator/(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs)
{
	Vector<Data, Size> product = lhs;
	product /= rhs;

	return product;
}

template<typename Data, unsigned int Size>
Vector<Data, Size> operator/(const Vector<Data, Size>& lhs, Data scalar)
{
	Vector<Data, Size> product = lhs;
	product /= scalar;

	return product;
}

template<typename Data, unsigned int Size>
Vector<Data, Size> operator*(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs)
{
	Vector<Data, Size> product = lhs;
	product *= rhs;

	return product;
}

template<typename Data, unsigned int Size>
Vector<Data, Size> operator*(const Vector<Data, Size>& lhs, Data scalar)
{
	Vector<Data, Size> product = lhs;
	product *= scalar;

	return product;
}

template<typename Data, unsigned int Size>
Vector<Data, Size> operator+(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs)
{
	Vector<Data, Size> sum = lhs;
	sum += rhs;

	return sum;
}

template<typename Data, unsigned int Size>
ostream& operator<<(ostream& stream, const Vector<Data, Size>& vector)
{
	stream << "[";

	for (unsigned int index = 0; index < Size; index++)
	{
		stream << vector[index];
		if (index < Size - 1)
		{
			stream << ",";
		}
	}

	stream << "]";

	return stream;
}

template<typename Data, unsigned int Size>
bool operator==(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs)
{
	for (unsigned int index = 0; index < Size; index++)
	{
		if (lhs[index] == rhs[index])
		{
			return false;
		}
	}

	return true;
}
