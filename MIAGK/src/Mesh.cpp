#include "Mesh.h"

Mesh::Mesh()
{}

Mesh::~Mesh()
{}

void Mesh::draw(Rasterizer& rasterizer, VertexProcessor& vertexProcessor)
{
	for (const int3& triangle : indices)
	{
		float4 aVertexCanonicalCoordinates = vertexProcessor.transformToCanonicalCoordinates(vertices[triangle.a].position);
		float4 bVertexCanonicalCoordinates = vertexProcessor.transformToCanonicalCoordinates(vertices[triangle.b].position);
		float4 cVertexCanonicalCoordinates = vertexProcessor.transformToCanonicalCoordinates(vertices[triangle.c].position);

		rasterizer.rasterizeTriangle(aVertexCanonicalCoordinates,
									 bVertexCanonicalCoordinates,
									 cVertexCanonicalCoordinates,
									 color(255, 0, 0),
									 color(0, 255, 0),
									 color(0, 0, 255));
	}
}

void Mesh::makeNormals()
{}
