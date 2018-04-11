// Maths.h 13-02-2018
// William John Atkin WJAtkin@UCLan.ac.uk

#pragma once
#include "BUILD_ORDER.h"

namespace maths
{
	// For testing if floats are near zero
	const float kEpsilon = 0.0001f;

	// Direction Vectors
	const SVector3D<float> X_AXIS_VECTOR = { 1.0f, 0.0f, 0.0f };
	const SVector3D<float> Y_AXIS_VECTOR = { 0.0f, 1.0f, 0.0f };
	const SVector3D<float> Z_AXIS_VECTOR = { 0.0f, 1.0f, 1.0f };

	// Returns the faceing vector of a tle model as a 3D vector
	SVector3D<float> FacingVector(tle::ISceneNode* model);

	// Returns true is two floats are within kEpsilon of each other
	// Can also be used to compare to zero if b is not supplied
	bool Compf(float a, float b = 0.0f);
}