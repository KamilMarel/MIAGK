#pragma once
#include "Buffer.h"

class Rasterizer
{
public:
	Rasterizer(Buffer* bufferToUse);
	~Rasterizer();
	void rasterizeTriangle(const float4& aCanonicalCoordinates,
						   const float4& bCanonicalCoordinates,
						   const float4& cCanonicalCoordinates,
						   const color& aVertexColor,
						   const color& bVertexColor,
						   const color& cVertexColor);

	Buffer* buffer;
};