// SVector2D.h 10-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

template <class T>
struct SVector2D
{
public:
	T x, y;

	SVector2D();
	SVector2D(T newX, T newY);

	// Maths operations
	// Returns the magnitude of this vector
	float Magnitude();
	// Normalises this vector
	void Normalise();
	// Returns the normalised form of this vector
	SVector2D<T> Normalised();

	// Operator overloads
	SVector2D<T>& operator=(const SVector2D<T>& rhs);
	SVector2D<T>& operator*=(const SVector2D<T>& rhs);
	SVector2D<T> operator+(const SVector2D<T>& rhs);
	SVector2D<T> operator-(const SVector2D<T>& rhs);
	bool operator==(const SVector2D<T>& rhs);

private:
	// Adds two vectors together and returns a new vector
	static SVector2D<T> Add(const SVector2D<T>* lhs, const SVector2D<T>* rhs);
	// Subtracts rhs from lhs and returns a new vector
	static SVector2D<T> Subtract(const SVector2D<T>* lhs, const SVector2D<T>* rhs);
};

template <class T>
SVector2D<T>::SVector2D()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
}

template <class T>
SVector2D<T>::SVector2D(T newX, T newY)
{
	x = newX;
	y = newY;
}

// Maths operations
// Returns the magnitude of this vector
template <class T>
float SVector2D<T>::Magnitude()
{
	SVector2D<T> magVec;
	magVec.x = x * x;
	magVec.y = y * y;
	float mag = magVec.x + magVec.y;
	return sqrtf(mag);
}

// Normalises this vector
template <class T>
void SVector2D<T>::Normalise()
{
	SVector2D<T> normal = this->Normalised();
	this->Set(normal.x, normal.y);
}

// Returns the normalised form of this vector
template <class T>
SVector2D<T> SVector2D<T>::Normalised()
{
	float magnitueSquare = x * x + y * y;

	// Makes sure the length is not zero
	if (maths::Compf(magnitueSquare))
	{
		return SVector2D<T>();
	}
	else
	{
		float invLength = 1.0f / sqrtf(magnitueSquare);
		return SVector2D<T>(x * invLength, y * invLength);
	}
}

// Operator overloads
// Equals
template <class T>
SVector2D<T>& SVector2D<T>::operator=(const SVector2D<T>& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return (*this);
}

// multiplication assignment
template <class T>
SVector2D<T>& SVector2D<T>::operator*=(const SVector2D<T>& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return (*this);
}

// Add
template <class T>
SVector2D<T> SVector2D<T>::operator+(const SVector2D<T>& rhs)
{
	return Add(this, &rhs);
}

// Subtract
template <class T>
SVector2D<T> SVector2D<T>::operator-(const SVector2D<T>& rhs)
{
	return Subtract(this, &rhs);
}

// Equals to
template <class T>
bool SVector2D<T>::operator==(const SVector2D<T>& rhs)
{
	if (maths::Compf(this->x, rhs.x))
	{
		if (maths::Compf(this->y, rhs.y))
		{
			return true;
		}
	}
	return false;
}

// Private functions
// Adds two vectors together and returns a new vector
template <class T>
SVector2D<T> SVector2D<T>::Add(const SVector2D<T>* lhs, const SVector2D<T>* rhs)
{
	SVector2D<T> sum;
	sum.x = lhs->x + rhs->x;
	sum.y = lhs->y + rhs->y;
	return sum;
}

// Subtracts rhs from lhs and returns a new vector
template <class T>
SVector2D<T> SVector2D<T>::Subtract(const SVector2D<T>* lhs, const SVector2D<T>* rhs)
{
	SVector2D<T> sum;
	sum.x = lhs->x - rhs->x;
	sum.y = lhs->y - rhs->y;
	return sum;
}
