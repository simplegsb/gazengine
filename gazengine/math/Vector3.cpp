#include <cmath>

#include "Vector3.h"

using namespace std;

Vector3::Vector3() :
	x(0.0f),
	y(0.0f),
	z(0.0f)
{
}

Vector3::Vector3(float x, float y, float z) :
	x(x),
	y(y),
	z(z)
{
}

Vector3 Vector3::crossProduct(const Vector3& other) const
{
	Vector3 product;
	product.x = y * other.z - z * other.y;
	product.y = z * other.x - x * other.z;
	product.z = x * other.y - y * other.x;

	return product;
}

float Vector3::dotProduct(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector3::length() const
{
	return sqrt(pow(abs(x), 2) + pow(abs(y), 2) + pow(abs(z), 2));
}

void Vector3::normalise()
{
	float length = this->length();
	x = x / length;
	y = y / length;
	z = z / length;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

Vector3& Vector3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 copy(lhs);
	copy -= rhs;

	return copy;
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 copy(lhs);
	copy += rhs;

	return copy;
}

Vector3 operator*(const float lhs, Vector3& rhs)
{
	return rhs * lhs;
}

Vector3 operator*(const Vector3& lhs, float rhs)
{
	Vector3 copy(lhs);
	copy *= rhs;

	return copy;
}

Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
{
	Vector3 copy(lhs);
	copy *= rhs;

	return copy;
}

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.x == rhs.x &&
		lhs.y == rhs.y &&
		lhs.z == rhs.z;
}

bool operator!=(const Vector3& lhs, const Vector3& rhs)
{
	return !(lhs == rhs);
}

ostream& operator<<(ostream& lhs, const Vector3& rhs)
{
	lhs << "[" << rhs.x << ", " << rhs.y << ", " << rhs.z << "]";

	return lhs;
}
