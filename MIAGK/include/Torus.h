#pragma once

#include "Mesh.h"

class Torus : public Mesh
{
public:
	Torus(float torusRadius, float cylinderRadius, unsigned int torusDetailLevel, unsigned int cylinderDetailLevel);
	~Torus();
};