#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <iostream>

struct Vector3
{
	float x;

	float y;

	float z;

	Vector3();

	Vector3(float x, float y, float z);

	Vector3 crossProduct(const Vector3& other) const;

	float dotProduct(const Vector3& other) const;

	float length() const;

	void normalise();

	Vector3& operator-=(const Vector3& other);

	Vector3& operator+=(const Vector3& other);

	Vector3& operator*=(float scalar);

	Vector3& operator*=(const Vector3& other);
};

Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

Vector3 operator+(const Vector3& lhs, const Vector3& rhs);

Vector3 operator*(const float lhs, Vector3& rhs);

Vector3 operator*(const Vector3& lhs, float rhs);

Vector3 operator*(const Vector3& lhs, const Vector3& rhs);

bool operator==(const Vector3& lhs, const Vector3& rhs);

bool operator!=(const Vector3& lhs, const Vector3& rhs);

std::ostream& operator<<(std::ostream& lhs, const Vector3& rhs);

#endif /* VECTOR3_H_ */
