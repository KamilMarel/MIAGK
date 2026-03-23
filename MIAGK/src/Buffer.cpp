#include "Buffer.h"
#include "stb_image_write.h"

Buffer::Buffer()
{
	pixels = new unsigned char[sizeX * sizeY * 3];
}

Buffer::Buffer(unsigned int sizeX, unsigned int sizeY) : Buffer()
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Buffer::~Buffer()
{
	delete[] pixels;
}

void Buffer::clearColor(unsigned char red, unsigned char green, unsigned char blue)
{
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			int pixelIndex = (y * sizeX * 3) + x * 3;
			pixels[pixelIndex] = red;
			pixels[pixelIndex + 1] = green;
			pixels[pixelIndex + 2] = blue;
		}
	}
}

void Buffer::saveToFile()
{
	stbi_write_bmp("image.bmp", sizeX, sizeY, 3, pixels);
}
