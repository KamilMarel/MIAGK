#pragma once

#include "Mesh.h"

class Cone : public Mesh
{
public:
	Cone(unsigned int radius, unsigned int height, unsigned int detailLevel);
	~Cone();
};