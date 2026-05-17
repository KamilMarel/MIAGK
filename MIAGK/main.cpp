#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Rasterizer.h"
#include "VertexProcessor.h"
#include "Cone.h"
#include "Cylinder.h"

const unsigned int BUFFER_SIZE_X = 512, BUFFER_SIZE_Y = 512;
const color BUFFER_CLEAR_COLOR(0, 150, 201);

int main()
{
	Buffer buffer(BUFFER_SIZE_X, BUFFER_SIZE_Y);
	buffer.clearColor(BUFFER_CLEAR_COLOR);
	buffer.clearDepth(1.0f);

	Rasterizer rasterizer(&buffer);

	VertexProcessor coneVertexProcessor;
	coneVertexProcessor.setLookAt(float3(0, 0, 0), float3(0, 0, -1), float3(0, 1, 0));
	coneVertexProcessor.setView2ProjMatrix(70.0f, 1.0f, 0.1f, 100.0f);
	coneVertexProcessor.multByRotation(30, float3(0, 0, 1));
	coneVertexProcessor.multByRotation(60, float3(1, 0, 0));
	coneVertexProcessor.multByTranslation(float3(-3, 3, -8));
	Cone cone(1, 2, 5);
	cone.draw(rasterizer, coneVertexProcessor);

	VertexProcessor cylinderVertexProcessor;
	cylinderVertexProcessor.setLookAt(float3(0, 0, 0), float3(0, 0, -1), float3(0, 1, 0));
	cylinderVertexProcessor.setView2ProjMatrix(70.0f, 1.0f, 0.1f, 100.0f);
	cylinderVertexProcessor.multByRotation(30, float3(0, 0, 1));
	cylinderVertexProcessor.multByRotation(60, float3(1, 0, 0));
	cylinderVertexProcessor.multByTranslation(float3(3, 2, -8));
	Cylinder cylinder(1, 2, 10, 5);
	cylinder.draw(rasterizer, cylinderVertexProcessor);

	buffer.saveToFile();
}