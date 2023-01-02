#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;

}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& Vector2D::add(const Vector2D& vector)	// adds a vector to the current vector
{
	this->x += vector.x;
	this->y += vector.y;

	return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& vector)	// subtracts a vector to the current vector
{
	this->x -= vector.x;
	this->y -= vector.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vector)	// mutliplies a vector to the current vector
{
	this->x *= vector.x;
	this->y *= vector.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vector)	// divides a vector to the current vector
{
	this->x /= vector.x;
	this->y /= vector.y;

	return *this;
}

bool Vector2D::equals(const Vector2D& vector)
{
	if (this->x == vector.x && this->y == vector.y) {
		return true;
	}
	return false;
}


Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
	return this->add(vector);
}

Vector2D& Vector2D::operator-=(const Vector2D& vector)
{
	return this->subtract(vector);
}

Vector2D& Vector2D::operator*=(const Vector2D& vector)
{
	return this->multiply(vector);
}

Vector2D& Vector2D::operator/=(const Vector2D& vector)
{
	return this->divide(vector);
}

bool Vector2D::operator==(const Vector2D& vector)
{
	return this->equals(vector);
}

Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

Vector2D& Vector2D::binary()
{
	if (this->x != 0) { this->x = abs(this->x) / this->x; }
	if (this->y != 0) { this->y = abs(this->y) / this->y; }

	return *this;
}

std::ostream& operator << (std::ostream& stream, const Vector2D vector)
{
	stream << "(" << vector.x << "," << vector.y << ")";	// (x,y)
	return stream;
}