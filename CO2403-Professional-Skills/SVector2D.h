// SVector2D.h 10-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

template <class T>
struct SVector2D
{
	T x, y;

	SVector2D();
	SVector2D(T newX, T newY);
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