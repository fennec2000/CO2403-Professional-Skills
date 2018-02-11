#pragma once

template <class T>
struct SVector2D
{
	T x, y;

	SVector2D();
	SVector2D(T newX, T newY);
};

template <class T>
SVector2D::SVector2D()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
}

template <class T>
SVector2D::SVector2D(T newX, T newY)
{
	x = newX;
	y = newY;
}