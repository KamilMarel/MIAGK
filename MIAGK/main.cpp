#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Rasterizer.h"

const unsigned int BUFFER_SIZE_X = 512, BUFFER_SIZE_Y = 512;
const color BUFFER_CLEAR_COLOR(0, 150, 201);

int main()
{
	Buffer buffer(BUFFER_SIZE_X, BUFFER_SIZE_Y);
	buffer.clearColor(BUFFER_CLEAR_COLOR);
	buffer.clearDepth(1.0f);

	Rasterizer rasterizer(&buffer);
	rasterizer.rasterizeTriangle(float3(-0.5f, 0.0f, -5.0f),
								 float3(0.0f, 0.5f, -5.0f),
								 float3(0.5f, 0.0f, -5.0f),
								 color(255, 0, 0),
								 color(0, 255, 0),
								 color(0, 0, 255));
	rasterizer.rasterizeTriangle(float3(-1.0f, 0.5f, -4.0f),
								 float3(0.0f, 0.5f, -5.0f),
								 float3(-0.5f, 0.0f, -5.0f),
								 color(255, 0, 0),
								 color(0, 255, 0),
								 color(0, 0, 255));

	buffer.saveToFile();
}