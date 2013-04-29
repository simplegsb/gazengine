#include <cmath>

#include "Vector2.h"

Vector2::Vector2() :
	x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float x, float y) :
	x(x), y(y)
{
}

float Vector2::angleTo(const Vector2& other) const
{
	return acos(dotProduct(other) / (length() * other.length()));
}

float Vector2::crossProduct(const Vector2& other) const
{
	return x * other.y - y * other.x;
}

float Vector2::dotProduct(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::length() const
{
	return sqrt(lengthSquared());
}

float Vector2::lengthSquared() const
{
	return pow(abs(x), 2) + pow(abs(y), 2);
}

void Vector2::normalise()
{
	float length = this->length();
	x = x / length;
	y = y / length;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;

	return *this;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;

	return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	x *= other.x;
	y *= other.y;

	return *this;
}

void Vector2::rotate(float angle)
{
	float tempX = x * cos(angle) - y * sin(angle);
	float tempY = x * sin(angle) + y * cos(angle);

	x = tempX;
	y = tempY;
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 copy(lhs);
	copy -= rhs;

	return copy;
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 copy(lhs);
	copy += rhs;

	return copy;
}

Vector2 operator*(const Vector2& lhs, float rhs)
{
	Vector2 copy(lhs);
	copy *= rhs;

	return copy;
}

Vector2 operator*(const Vector2& lhs, const Vector2& rhs)
{
	Vector2 copy(lhs);
	copy *= rhs;

	return copy;
}
