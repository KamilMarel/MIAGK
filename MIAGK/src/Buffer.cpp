#include "Buffer.h"

Buffer::Buffer()
{
	pixels = new unsigned char[sizeX * sizeY * 3];
	depth = new float[sizeX * sizeY];
}

Buffer::Buffer(unsigned int sizeX, unsigned int sizeY) : Buffer()
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Buffer::~Buffer()
{
	delete[] pixels;
	delete[] depth;
}

const unsigned int Buffer::getSizeX() const
{
	return sizeX;
}

const unsigned int Buffer::getSizeY() const
{
	return sizeY;
}

void Buffer::writePixel(unsigned int pixelPosX, unsigned int pixelPosY, const color& pixelColor)
{
	unsigned int pixelIndex = pixelPosToPixelIndex(pixelPosX, pixelPosY);
	pixels[pixelIndex] = pixelColor.r;
	pixels[pixelIndex + 1] = pixelColor.g;
	pixels[pixelIndex + 2] = pixelColor.b;
}

void Buffer::writeDepth(unsigned int pixelPosX, unsigned int pixelPosY, float depthValue)
{
	unsigned int pixelIndex = pixelPosToDepthIndex(pixelPosX, pixelPosY);
	depth[pixelIndex] = depthValue;
}

void Buffer::clearColor(unsigned char red, unsigned char green, unsigned char blue)
{
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			writePixel(x, y, color(red, green, blue));
		}
	}
}

void Buffer::clearColor(const color& colorToClearWith)
{
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			writePixel(x, y, colorToClearWith);
		}
	}
}

void Buffer::clearDepth(float clearValue)
{
	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			writeDepth(x, y, clearValue);
		}
	}
}

void Buffer::saveToFile() const
{
	stbi_write_bmp("image.bmp", sizeX, sizeY, 3, pixels);
}

float Buffer::getDepthAtPosition(unsigned int pixelPosX, unsigned int pixelPosY)
{
	return depth[pixelPosToDepthIndex(pixelPosX, pixelPosY)];
}

const unsigned int Buffer::pixelPosToPixelIndex(unsigned int pixelPosX, unsigned int pixelPosY) const
{
	return ( ( ( (sizeY - 1) - pixelPosY) * sizeX * 3) + pixelPosX * 3 );
}

const unsigned int Buffer::pixelPosToDepthIndex(unsigned int pixelPosX, unsigned int pixelPosY) const
{
	return ( ( ( (sizeY - 1) - pixelPosY) * sizeX) + pixelPosX);
}
