// SVector3D.h 10-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

template <class T>
struct SVector3D
{
	T x, y, z;

	SVector3D();
	SVector3D(T newX, T newY, T newZ);

	// Maths operations
	// Returns the magnitude of this vector
	float Magnitude();
	// Normalises this vector
	void Normalise();
	// Returns the normalised form of this vector
	SVector3D<T> Normalised();

	// Operator overloads
	SVector3D<T>& operator=(const SVector3D<T>& rhs);
	SVector3D<T> operator+(const SVector3D<T>& rhs);
	SVector3D<T> operator-(const SVector3D<T>& rhs);
	bool operator==(const SVector3D<T>& rhs);

	// Static maths opereations
	static SVector3D<T> SVector3D<T>::CrossProduct(const SVector3D<T>* lhs, const SVector3D<T>* rhs);

private:
	// Adds two vectors together and returns a new vector
	static SVector3D<T> Add(const SVector3D<T>* lhs, const SVector3D<T>* rhs);
	// Subtracts rhs from lhs and returns a new vector
	static SVector3D<T> Subtract(const SVector3D<T>* lhs, const SVector3D<T>* rhs);
};

template <class T>
SVector3D<T>::SVector3D()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
	z = static_cast<T>(0);
}

template <class T>
SVector3D<T>::SVector3D(T newX, T newY, T newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

// Maths operations
// Returns the magnitude of this vector
template <class T>
float SVector3D<T>::Magnitude()
{
	SVector3D<T> magVec;
	magVec.x = x * x;
	magVec.y = y * y;
	magVec.z = z * y;
	float mag = magVec.x + magVec.y + magVec.z;
	return sqrtf(mag);
}

// Normalises this vector
template <class T>
void SVector3D<T>::Normalise()
{
	SVector3D<T> normal = this->Normalised();
	this->Set(normal.x, normal.y, normal.z);
}

// Returns the normalised form of this vector
template <class T>
SVector3D<T> SVector3D<T>::Normalised()
{
	float magnitueSquare = x * x + y * y + z * z;

	float invLength = 1.0f / sqrtf(magnitueSquare);
	return SVector3D<T>(x * invLength, y * invLength, z * invLength);
}

// Operator overloads
// Equals
template <class T>
SVector3D<T>& SVector3D<T>::operator=(const SVector3D<T>& rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return (*this);
}

// Add
template <class T>
SVector3D<T> SVector3D<T>::operator+(const SVector3D<T>& rhs)
{
	return Add(this, &rhs);
}

// Subtract
template <class T>
SVector3D<T> SVector3D<T>::operator-(const SVector3D<T>& rhs)
{
	return Subtract(this, &rhs);
}

// Equals to
template <class T>
bool SVector3D<T>::operator==(const SVector3D<T>& rhs)
{
	if (maths::Compf(this->x, rhs.x))
	{
		if (maths::Compf(this->y, rhs.y))
		{
			if (maths::Compf(this->z, rhs.z))
			{
				return true;
			}
		}
	}
	return false;
}

// Returns the cross product of two vectors
template <class T>
SVector3D<T> SVector3D<T>::CrossProduct(const SVector3D<T>* lhs, const SVector3D<T>* rhs)
{
	return SVector3D<T>(lhs->y * rhs->z - lhs->z * rhs->y, lhs->z * rhs->x - lhs->x * rhs->z, lhs->x * rhs->y - lhs->y * rhs->x);
}

// Private functions
// Adds two vectors together and returns a new vector
template <class T>
SVector3D<T> SVector3D<T>::Add(const SVector3D<T>* lhs, const SVector3D<T>* rhs)
{
	SVector3D<T> sum;
	sum.x = lhs->x + rhs->x;
	sum.y = lhs->y + rhs->y;
	sum.z = lhs->z + rhs->z;
	return sum;
}

// Subtracts rhs from lhs and returns a new vector
template <class T>
SVector3D<T> SVector3D<T>::Subtract(const SVector3D<T>* lhs, const SVector3D<T>* rhs)
{
	SVector3D<T> sum;
	sum.x = lhs->x - rhs->x;
	sum.y = lhs->y - rhs->y;
	sum.z = lhs->z - rhs->z;
	return sum;
}
