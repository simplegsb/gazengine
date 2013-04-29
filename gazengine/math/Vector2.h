#ifndef VECTOR2_H_
#define VECTOR2_H_

struct Vector2
{
	float x;

	float y;

	Vector2();

	Vector2(float x, float y);

	float angleTo(const Vector2& other) const;

	float crossProduct(const Vector2& other) const;

	float dotProduct(const Vector2& other) const;

	float length() const;

	float lengthSquared() const;

	void normalise();

	Vector2& operator-=(const Vector2& other);

	Vector2& operator+=(const Vector2& other);

	Vector2& operator*=(float scalar);

	Vector2& operator*=(const Vector2& other);

	Vector2& operator/=(float scalar);

	Vector2& operator/=(const Vector2& other);

	void rotate(float angle);
};

Vector2 operator-(const Vector2& lhs, const Vector2& rhs);

Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

Vector2 operator*(const Vector2& lhs, float rhs);

Vector2 operator*(const Vector2& lhs, const Vector2& rhs);

Vector2 operator/(const Vector2& lhs, float rhs);

Vector2 operator/(const Vector2& lhs, const Vector2& rhs);

#endif /* VECTOR2_H_ */
