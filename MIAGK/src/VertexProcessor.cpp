#include "VertexProcessor.h"

VertexProcessor::VertexProcessor()
{
	setView2ProjMatrix(45.0f, 1.0f, 0.1f, 100.0f);
}

void VertexProcessor::setView2ProjMatrix(float fovY, float aspect, float near, float far)
{
	fovY *= M_PI / 360;
	float f = cos(fovY) / sin(fovY);
	view2proj[0] = {f / aspect, 0, 0, 0};
	view2proj[1] = { 0, f, 0, 0 };
	view2proj[2] = { 0, 0, (far + near) / (near - far), -1};
	view2proj[3] = { 0, 0, 2 * far * near / (near - far), 0};
}

float4x4& VertexProcessor::getView2ProjMatrix()
{
	return view2proj;
}
