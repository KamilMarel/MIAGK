#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer* bufferToUse)
{
	this->buffer = bufferToUse;
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::rasterizeTriangle(const float4& aCanonicalCoordinates, 
								   const float4& bCanonicalCoordinates,
								   const float4& cCanonicalCoordinates,
								   const color& aVertexColor,
								   const color& bVertexColor,
								   const color& cVertexColor)
{
	float2 a2DCanonicalCoordinates(aCanonicalCoordinates.x, aCanonicalCoordinates.y);
	float2 b2DCanonicalCoordinates(bCanonicalCoordinates.x, bCanonicalCoordinates.y);
	float2 c2DCanonicalCoordinates(cCanonicalCoordinates.x, cCanonicalCoordinates.y);

	unsigned int bufferSizeX = buffer->getSizeX();
	unsigned int bufferSizeY = buffer->getSizeY();

	float2 a2DWindowCoordinates = canonicalToWindowCoordinates(a2DCanonicalCoordinates, bufferSizeX, bufferSizeY);
	float2 b2DWindowCoordinates = canonicalToWindowCoordinates(b2DCanonicalCoordinates, bufferSizeX, bufferSizeY);
	float2 c2DWindowCoordinates = canonicalToWindowCoordinates(c2DCanonicalCoordinates, bufferSizeX, bufferSizeY);

	float drawingRectMinX = minFloat(a2DWindowCoordinates.x, b2DWindowCoordinates.x, c2DWindowCoordinates.x);
	float drawingRectMaxX = maxFloat(a2DWindowCoordinates.x, b2DWindowCoordinates.x, c2DWindowCoordinates.x);
	float drawingRectMinY = minFloat(a2DWindowCoordinates.y, b2DWindowCoordinates.y, c2DWindowCoordinates.y);
	float drawingRectMaxY = maxFloat(a2DWindowCoordinates.y, b2DWindowCoordinates.y, c2DWindowCoordinates.y);

	float clippedDrawingRectMinX = maxFloat(drawingRectMinX, 0);
	float clippedDrawingRectMaxX = minFloat(drawingRectMaxX, bufferSizeX - 1);
	float clippedDrawingRectMinY = maxFloat(drawingRectMinY, 0);
	float clippedDrawingRectMaxY = minFloat(drawingRectMaxY, bufferSizeY - 1);

	float differenceAxBx = a2DWindowCoordinates.x - b2DWindowCoordinates.x;
	float differenceBxCx = b2DWindowCoordinates.x - c2DWindowCoordinates.x;
	float differenceCxAx = c2DWindowCoordinates.x - a2DWindowCoordinates.x;
	float differenceAyBy = a2DWindowCoordinates.y - b2DWindowCoordinates.y;
	float differenceByCy = b2DWindowCoordinates.y - c2DWindowCoordinates.y;
	float differenceCyAy = c2DWindowCoordinates.y - a2DWindowCoordinates.y;
	float differenceCxBx = c2DWindowCoordinates.x - b2DWindowCoordinates.x;
	float differenceAxCx = a2DWindowCoordinates.x - c2DWindowCoordinates.x;
	float differenceAyCy = a2DWindowCoordinates.y - c2DWindowCoordinates.y;

	for (int y = clippedDrawingRectMinY; y <= clippedDrawingRectMaxY; y++)
	{
		for (int x = clippedDrawingRectMinX; x <= clippedDrawingRectMaxX; x++)
		{
			bool edgeABIsTopLeft = (differenceAyBy < 0 || (differenceAyBy == 0 && differenceAxBx > 0)) ? true : false;
			bool edgeBCIsTopLeft = (differenceByCy < 0 || (differenceByCy == 0 && differenceBxCx > 0)) ? true : false;
			bool edgeCAIsTopLeft = (differenceCyAy < 0 || (differenceCyAy == 0 && differenceCxAx > 0)) ? true : false;

			bool edgeABHalfSpaceConditionResult = false;
			bool edgeBCHalfSpaceConditionResult = false;
			bool edgeCAHalfSpaceConditionResult = false;
			if (edgeABIsTopLeft)
			{
				edgeABHalfSpaceConditionResult = differenceAxBx * (y - a2DWindowCoordinates.y) - differenceAyBy * (x - a2DWindowCoordinates.x) >= 0;
			}
			else
			{
				edgeABHalfSpaceConditionResult = differenceAxBx * (y - a2DWindowCoordinates.y) - differenceAyBy * (x - a2DWindowCoordinates.x) > 0;
			}
			if (edgeBCIsTopLeft)
			{
				edgeBCHalfSpaceConditionResult = differenceBxCx * (y - b2DWindowCoordinates.y) - differenceByCy * (x - b2DWindowCoordinates.x) >= 0;
			}
			else
			{
				edgeBCHalfSpaceConditionResult = differenceBxCx * (y - b2DWindowCoordinates.y) - differenceByCy * (x - b2DWindowCoordinates.x) > 0;
			}
			if (edgeCAIsTopLeft)
			{
				edgeCAHalfSpaceConditionResult = differenceCxAx * (y - c2DWindowCoordinates.y) - differenceCyAy * (x - c2DWindowCoordinates.x) >= 0;
			}
			else
			{
				edgeCAHalfSpaceConditionResult = differenceCxAx * (y - c2DWindowCoordinates.y) - differenceCyAy * (x - c2DWindowCoordinates.x) > 0;
			}

			if (edgeABHalfSpaceConditionResult == true &&
				edgeBCHalfSpaceConditionResult == true &&
				edgeCAHalfSpaceConditionResult == true)
			{
				float interpolationLambda1 = (differenceByCy * (x - c2DWindowCoordinates.x) + differenceCxBx * (y - c2DWindowCoordinates.y)) /
					(differenceByCy * differenceAxCx + differenceCxBx * differenceAyCy);
				float interpolationLambda2 = (differenceCyAy * (x - c2DWindowCoordinates.x) + differenceAxCx * (y - c2DWindowCoordinates.y)) /
					(differenceCyAy * differenceBxCx + differenceAxCx * differenceByCy);
				float interpolationLambda3 = 1 - interpolationLambda1 - interpolationLambda2;

				float depth = interpolationLambda1 * aCanonicalCoordinates.z +
							  interpolationLambda2 * bCanonicalCoordinates.z +
							  interpolationLambda3 * cCanonicalCoordinates.z;

				if (depth < buffer->getDepthAtPosition(x, y))
				{
					color interpolatedColor = aVertexColor * interpolationLambda1 +
											  bVertexColor * interpolationLambda2 +
											  cVertexColor * interpolationLambda3;

					buffer->writePixel(x, y, interpolatedColor);
					buffer->writeDepth(x, y, depth);
				}
			}
		}
	}
}
