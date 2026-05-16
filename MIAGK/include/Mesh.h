#pragma once

#include <vector>
#include "Rasterizer.h"
#include "VertexProcessor.h"

struct Vertex
{
	float3 position;
	float3 normal;
	
	Vertex(const float3& position)
	{
		this->position = position;
	}
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void draw(Rasterizer& rasterizer, VertexProcessor& vertexProcessor);
	void makeNormals();

protected:
	std::vector<Vertex> vertices;
	std::vector<int3> indices;
};

