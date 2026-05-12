#include "Rasterizer.h"

Rasterizer::Rasterizer(Buffer* bufferToUse)
{
	this->buffer = bufferToUse;
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::rasterizeTriangle(const float3& a, 
								   const float3& b, 
								   const float3& c, 
								   const color& aVertexColor,
								   const color& bVertexColor,
								   const color& cVertexColor)
{
	float4 a4DObjCoordinates(a.x, a.y, a.z, 1.0f);
	float4 b4DObjCoordinates(b.x, b.y, b.z, 1.0f);
	float4 c4DObjCoordinates(c.x, c.y, c.z, 1.0f);

	float4 a4DCanonicalCoordinates = vertexProcessor.getView2ProjMatrix() * vertexProcessor.getWorld2ViewMatrix() * vertexProcessor.getObj2WorldMatrix() * a4DObjCoordinates;
	float4 b4DCanonicalCoordinates = vertexProcessor.getView2ProjMatrix() * vertexProcessor.getWorld2ViewMatrix() * vertexProcessor.getObj2WorldMatrix() * b4DObjCoordinates;
	float4 c4DCanonicalCoordinates = vertexProcessor.getView2ProjMatrix() * vertexProcessor.getWorld2ViewMatrix() * vertexProcessor.getObj2WorldMatrix() * c4DObjCoordinates;
	a4DCanonicalCoordinates = a4DCanonicalCoordinates / a4DCanonicalCoordinates.w;
	b4DCanonicalCoordinates = b4DCanonicalCoordinates / b4DCanonicalCoordinates.w;
	c4DCanonicalCoordinates = c4DCanonicalCoordinates / c4DCanonicalCoordinates.w;

	float2 a2DCanonicalCoordinates(a4DCanonicalCoordinates.x, a4DCanonicalCoordinates.y);
	float2 b2DCanonicalCoordinates(b4DCanonicalCoordinates.x, b4DCanonicalCoordinates.y);
	float2 c2DCanonicalCoordinates(c4DCanonicalCoordinates.x, c4DCanonicalCoordinates.y);

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

				float depth = interpolationLambda1 * a.z +
							  interpolationLambda2 * b.z +
							  interpolationLambda3 * c.z;

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

	// NO OPTIMIZATIONS AND NO CLIPPING
	// 
	//for (int y = 0; y < bufferSizeY; y++)
	//{
	//	for (int x = 0; x < bufferSizeX; x++)
	//	{
	//		if ((a2DWindowCoordinates.x - b2DWindowCoordinates.x) * (y - a2DWindowCoordinates.y) - (a2DWindowCoordinates.y - b2DWindowCoordinates.y) * (x - a2DWindowCoordinates.x) > 0 &&
	//			(b2DWindowCoordinates.x - c2DWindowCoordinates.x) * (y - b2DWindowCoordinates.y) - (b2DWindowCoordinates.y - c2DWindowCoordinates.y) * (x - b2DWindowCoordinates.x) > 0 &&
	//			(c2DWindowCoordinates.x - a2DWindowCoordinates.x) * (y - c2DWindowCoordinates.y) - (c2DWindowCoordinates.y - a2DWindowCoordinates.y) * (x - c2DWindowCoordinates.x) > 0)
	//		{
	//			buffer->writePixel(x, y, fillColor);
	//		}
	//	}
	//}
}
