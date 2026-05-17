#pragma once

#include "Mesh.h"

class Cylinder : public Mesh
{
public:
	Cylinder(float radius, float height, unsigned int horizontalDetailLevel, unsigned int verticalDetailLevel);
	~Cylinder();
};