#pragma once

#include "math_functions.h"

struct Fragment
{
	float3 position;
	float3 normal;

	Fragment(const float3& position, const float3& normal)
	{
		this->position = position;
		this->normal = normal;
	}
};