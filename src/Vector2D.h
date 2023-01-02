#pragma once
#include <iostream>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();		// default constructor
	Vector2D(float x, float y);		// 

	Vector2D& add(const Vector2D& vector);	// adds a vector to the current vector
	Vector2D& subtract(const Vector2D& vector);	// subtracts a vector to the current vector
	Vector2D& multiply(const Vector2D& vector);	// multiplies a vector to the current vector
	Vector2D& divide(const Vector2D& vector);	// divides a vector to the current vector
	bool equals(const Vector2D& vector);	// checks if the two vectors are equivalent

	friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+=(const Vector2D& vector);
	Vector2D& operator-=(const Vector2D& vector);
	Vector2D& operator*=(const Vector2D& vector);
	Vector2D& operator/=(const Vector2D& vector);
	bool operator==(const Vector2D& vector);
	
	Vector2D& operator*(const int& i);
	Vector2D& zero();
	Vector2D& binary();

	friend std::ostream& operator << (std::ostream& stream, const Vector2D vector);
};