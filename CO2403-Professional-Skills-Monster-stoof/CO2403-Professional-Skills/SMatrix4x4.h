// SMatrix4x4.h 13-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#include "BUILD_ORDER.h"
#pragma once

// The Matrix 4x4 class. Used to store 16 floats for use with rending engines.
// Adapted from CMatrix4x4 in Lab Worksheet CO2301-05 by Gareth Bellaby
struct SMatrix4x4
{
public:
	// Matrix elements
	float e00, e01, e02, e03;
	float e10, e11, e12, e13;
	float e20, e21, e22, e23;
	float e30, e31, e32, e33;

	// Default constructer
	SMatrix4x4();

	// Makes the matrix into an identiy matrix
	void MakeIdentity();

	// Sets a single row of the matrix using an IVector3D, leaves the
	// forth element unchanged
	void SetRow(const int iRow, const SVector3D<float>& vector);
};
