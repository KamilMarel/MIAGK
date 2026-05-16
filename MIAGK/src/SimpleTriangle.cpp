#include "SimpleTriangle.h"

SimpleTriangle::SimpleTriangle()
{
	vertices.push_back(Vertex(float3(-0.5f, 0.0f, 0.0f)));
	vertices.push_back(Vertex(float3(0.0f, 0.5f, 0.0f)));
	vertices.push_back(Vertex(float3(0.5f, 0.0f, 0.0f)));
	indices.push_back(int3(0, 1, 2));
}

SimpleTriangle::~SimpleTriangle()
{}