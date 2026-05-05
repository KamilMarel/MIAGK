#pragma once
#include "math_functions.h"

class VertexProcessor
{
public:
	VertexProcessor();
	void setView2ProjMatrix(float fovY, float aspect, float near, float far);
	float4x4& getView2ProjMatrix();
private:
	float4x4 view2proj;
};