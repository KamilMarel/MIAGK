#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Rasterizer.h"
#include "VertexProcessor.h"
#include "SimpleTriangle.h"

const unsigned int BUFFER_SIZE_X = 512, BUFFER_SIZE_Y = 512;
const color BUFFER_CLEAR_COLOR(0, 150, 201);

int main()
{
	Buffer buffer(BUFFER_SIZE_X, BUFFER_SIZE_Y);
	buffer.clearColor(BUFFER_CLEAR_COLOR);
	buffer.clearDepth(1.0f);

	Rasterizer rasterizer(&buffer);
	VertexProcessor vertexProcessor;
	vertexProcessor.setLookAt(float3(0, 0, 0), float3(0, 0, -1), float3(0, 1, 0));
	vertexProcessor.setView2ProjMatrix(70.0f, 1.0f, 0.1f, 100.0f);
	vertexProcessor.multByTranslation(float3(0, 0, -3));

	SimpleTriangle simpleTriangle;
	simpleTriangle.draw(rasterizer, vertexProcessor);

	buffer.saveToFile();
}