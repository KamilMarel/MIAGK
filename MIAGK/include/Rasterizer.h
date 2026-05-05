#pragma once
#include "Buffer.h"
#include "VertexProcessor.h"

class Rasterizer
{
public:
	Rasterizer(Buffer* bufferToUse);
	~Rasterizer();
	void rasterizeTriangle(const float3& a, 
						   const float3& b, 
						   const float3& c, 
						   const color& aVertexColor,
						   const color& bVertexColor,
						   const color& cVertexColor);
private:
	Buffer* buffer;
	VertexProcessor vertexProcessor;
};