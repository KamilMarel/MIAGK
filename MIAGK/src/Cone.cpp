#include "Cone.h"

Cone::Cone(float radius, float height, unsigned int detailLevel)
{
	float step = (2 * M_PI) / (3 + detailLevel * 1.0f);

	for (float t = 0; t < 2 * M_PI; t += step)
	{
		float offsetX = radius * cos(t);
		float offsetZ = radius * sin(t);
		vertices.push_back(Vertex(float3(offsetX, 0, offsetZ)));
	}
	vertices.push_back(Vertex(float3(0, 0, 0)));
	vertices.push_back(Vertex(float3(0, height, 0)));

	int topVertexIndex = vertices.size() - 1;
	int bottomMiddleVertexIndex = vertices.size() - 2;
	for (int vertexIndex = 1; vertexIndex < bottomMiddleVertexIndex; vertexIndex++)
	{
		indices.push_back(int3(topVertexIndex, vertexIndex, vertexIndex - 1));
		indices.push_back(int3(bottomMiddleVertexIndex, vertexIndex - 1, vertexIndex));
	}
	indices.push_back(int3(topVertexIndex, 0, bottomMiddleVertexIndex - 1));
	indices.push_back(int3(bottomMiddleVertexIndex, bottomMiddleVertexIndex - 1, 0));
}

Cone::~Cone()
{}
