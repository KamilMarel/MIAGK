#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer* bufferToUse)
{
	this->buffer = bufferToUse;
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::rasterizeTriangle(const float3& a, const float3& b, const float3& c, const color& fillColor)
{
	float2 a2DCanonicalCoordinates(a.x, a.y);
	float2 b2DCanonicalCoordinates(b.x, b.y);
	float2 c2DCanonicalCoordinates(c.x, c.y);

	unsigned int bufferSizeX = buffer->getSizeX();
	unsigned int bufferSizeY = buffer->getSizeY();

	float2 a2DWindowCoordinates = canonicalToWindowCoordinates(a2DCanonicalCoordinates, bufferSizeX, bufferSizeY);
	float2 b2DWindowCoordinates = canonicalToWindowCoordinates(b2DCanonicalCoordinates, bufferSizeX, bufferSizeY);
	float2 c2DWindowCoordinates = canonicalToWindowCoordinates(c2DCanonicalCoordinates, bufferSizeX, bufferSizeY);

	for (int y = 0; y < bufferSizeY; y++)
	{
		for (int x = 0; x < bufferSizeX; x++)
		{
			if ((a2DWindowCoordinates.x - b2DWindowCoordinates.x) * (y - a2DWindowCoordinates.y) - (a2DWindowCoordinates.y - b2DWindowCoordinates.y) * (x - a2DWindowCoordinates.x) > 0 &&
				(b2DWindowCoordinates.x - c2DWindowCoordinates.x) * (y - b2DWindowCoordinates.y) - (b2DWindowCoordinates.y - c2DWindowCoordinates.y) * (x - b2DWindowCoordinates.x) > 0 &&
				(c2DWindowCoordinates.x - a2DWindowCoordinates.x) * (y - c2DWindowCoordinates.y) - (c2DWindowCoordinates.y - a2DWindowCoordinates.y) * (x - c2DWindowCoordinates.x) > 0)
			{
				buffer->writePixel(x, y, fillColor);
			}
		}
	}
}
