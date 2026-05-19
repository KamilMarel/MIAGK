#include "Light.h"

Light::Light(const float3& position, const float3& ambient, const float3& diffuse, const float3& specular, float shininess)
{
	this->position = position;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

Light::~Light()
{}

float3 Light::calculate(const Vertex& vertex, const VertexProcessor& vertexProcessor) const
{
	Fragment vertexAsFragmentStructure(vertex.position, vertex.normal);
	return calculate(vertexAsFragmentStructure, vertexProcessor);
}
