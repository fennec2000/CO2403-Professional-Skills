// SMatrix4x4.cpp 13-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#include "BUILD_ORDER.h"

// Def constructer, left blank intentionaly
SMatrix4x4::SMatrix4x4() { }

// Makes the matrix into an identiy matrix
void SMatrix4x4::MakeIdentity()
{
	e00 = 1.0f;
	e01 = 0.0f;
	e02 = 0.0f;
	e03 = 0.0f;

	e10 = 0.0f;
	e11 = 1.0f;
	e12 = 0.0f;
	e13 = 0.0f;

	e20 = 0.0f;
	e21 = 0.0f;
	e22 = 1.0f;
	e23 = 0.0f;

	e30 = 0.0f;
	e31 = 0.0f;
	e32 = 0.0f;
	e33 = 1.0f;
}

// Sets a single row of the matrix using an IVector3D, leaves the
// forth element unchanged
void SMatrix4x4::SetRow(const int iRow, const SVector3D<float>& vector)
{
	float* startPos = &e00 + iRow * 4;
	startPos[0] = vector.x;
	startPos[1] = vector.y;
	startPos[2] = vector.z;
}
