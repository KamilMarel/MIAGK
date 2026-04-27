#include "stb_image_write.h"
#include "math_functions.h"

class Buffer
{
public:
	Buffer();
	Buffer(unsigned int sizeX, unsigned int sizeY);
	~Buffer();

	const unsigned int getSizeX() const;
	const unsigned int getSizeY() const;

	void writePixel(unsigned int pixelPosX, unsigned int pixelPosY, const color& pixelColor);
	void writeDepth(unsigned int pixelPosX, unsigned int pixelPosY, float depthValue);
	void clearColor(unsigned char red, unsigned char green, unsigned char blue);
	void clearColor(const color& colorToClearWith);
	void clearDepth(float clearValue);
	void saveToFile() const;
	float getDepthAtPosition(unsigned int pixelPosX, unsigned int pixelPosY);

private:
	unsigned int sizeX = 1024, sizeY = 1024;
	unsigned char* pixels;
	float* depth;

	const unsigned int pixelPosToPixelIndex(unsigned int pixelPosX, unsigned int pixelPosY) const;
	const unsigned int pixelPosToDepthIndex(unsigned int pixelPosX, unsigned int pixelPosY) const;
};

