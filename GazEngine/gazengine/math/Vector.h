#ifndef VECTOR_H_
#define VECTOR_H_

#include <ostream>

template<typename Data, unsigned int Size>
class Vector
{
	public:
		Vector();

		Vector(const Vector<Data, Size>& original);

		Vector(Data* data, bool takeOwnership);

		Vector(Data d0, Data d1);

		Vector(Data d0, Data d1, Data d2);

		Vector(Data d0, Data d1, Data d2, Data d3);

		~Vector();

		Data& A();

		const Data& A() const;

		Data& B();

		const Data& B() const;

		Data& G();

		const Data& G() const;

		Data* getData();

		const Data* getData() const;

		Data getMagnitude() const;

		Data getMagnitudeSquared() const;

		void negate();

		void normalize();

		Vector<Data, Size>& operator/=(const Vector<Data, Size>& rhs);

		Vector<Data, Size>& operator/=(const Data scalar);

		Data& operator[](unsigned int index);

		const Data& operator[](unsigned int index) const;

		Vector<Data, Size>& operator*=(const Vector<Data, Size>& rhs);

		Vector<Data, Size>& operator*=(const Data scalar);

		Vector<Data, Size>& operator+=(const Vector<Data, Size>& rhs);

		Vector<Data, Size>& operator=(const Vector<Data, Size>& original);

		Vector<Data, Size>& operator-=(const Vector<Data, Size>& rhs);

		Data& R();

		const Data& R() const;

		void setData(Data* data, bool takeOwnership);

		Data& W();

		Data& X();

		Data& Y();

		Data& Z();

		const Data& W() const;

		const Data& X() const;

		const Data& Y() const;

		const Data& Z() const;

	private:
		Data* data;

		bool dataOwner;
};

typedef Vector<float, 2> Vector2;

typedef Vector<float, 3> Vector3;

typedef Vector<float, 4> Vector4;

template<typename Data, unsigned int Size>
Data dotProduct(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs);

template<typename Data, unsigned int Size>
bool operator!=(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs);

template<typename Data, unsigned int Size>
Vector<Data, Size> operator/(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs);

template<typename Data, unsigned int Size>
Vector<Data, Size> operator/(const Vector<Data, Size>& lhs, Data scalar);

template<typename Data, unsigned int Size>
Vector<Data, Size> operator*(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs);

template<typename Data, unsigned int Size>
Vector<Data, Size> operator*(const Vector<Data, Size>& lhs, Data scalar);

template<typename Data, unsigned int Size>
Vector<Data, Size> operator+(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs);

template<typename Data, unsigned int Size>
Vector<Data, Size> operator-(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs);

template<typename Data, unsigned int Size>
std::ostream& operator<<(std::ostream& stream, const Vector<Data, Size>& vector);

template<typename Data, unsigned int Size>
bool operator==(const Vector<Data, Size>& lhs, const Vector<Data, Size>& rhs);

#include "Vector.tpp"

#endif /* VECTOR_H_ */
