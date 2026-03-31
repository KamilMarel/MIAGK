#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Rasterizer.h"

const unsigned int BUFFER_SIZE_X = 1024, BUFFER_SIZE_Y = 1024;

const color BUFFER_CLEAR_COLOR(0, 150, 201);

int main()
{
    Buffer buffer(BUFFER_SIZE_X, BUFFER_SIZE_Y);
    buffer.clearColor(BUFFER_CLEAR_COLOR);

    Rasterizer rasterizer(&buffer);
    rasterizer.rasterizeTriangle(float3(-0.5f, 0.0f, 0.0f),
                                 float3(0.0f, 0.5f, 0.0f),
                                 float3(0.5f, 0.0f, 0.0f),
                                 color(255, 255, 255));

    buffer.saveToFile();
}