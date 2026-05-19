#pragma once

#include "Fragment.h"
#include "Mesh.h"

class Light
{
public:
	Light(const float3& position, const float3& ambient, const float3& diffuse, const float3& specular, float shininess);
	~Light();

	virtual float3 calculate(const Fragment& fragment, const VertexProcessor& vertexProcessor) const = 0;
	float3 calculate(const Vertex& vertex, const VertexProcessor& vertexProcessor) const;
private:
	float3 position;
	float3 ambient;
	float3 diffuse;
	float3 specular;
	float shininess;
};
