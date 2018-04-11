// Maths.cpp 13-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#include "BUILD_ORDER.h"

namespace maths
{
	// Returns the faceing vector of a tle model as a 3D vector
	SVector3D<float> FacingVector(tle::ISceneNode* model)
	{
		// A matrix flaot array
		float matrix[16];

		// Gets the matrix
		model->GetMatrix(matrix);

		// Creates a vector with the faceing vector floats
		// and returns it
		return SVector3D<float>(matrix[8], matrix[9], matrix[10]);
	}

	// Returns true is too floats are within epsilon of each other
	// Can also be used to compare to zero if b is not supplied
	bool Compf(float a, float b)
	{
		if (a <= b + kEpsilon && a >= b - kEpsilon)
		{
			return true;
		}
		return false;
	}
}