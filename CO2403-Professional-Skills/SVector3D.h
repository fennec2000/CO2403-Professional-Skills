#pragma once

template <class T>
struct SVector3D
{
	T x, y, z;

	SVector3D();
	SVector3D(T newX, T newY, T newZ);
};

template <class T>
SVector3D::SVector3D()
{
	x = static_cast<T>(0);
	y = static_cast<T>(0);
	z = static_cast<T>(0);
}

template <class T>
SVector3D::SVector3D(T newX, T newY, T newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}