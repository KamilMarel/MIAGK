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
	void clearColor(unsigned char red, unsigned char green, unsigned char blue);
	void clearColor(const color& colorToClearWith);
	void saveToFile() const;

private:
	unsigned int sizeX = 1024, sizeY = 1024;
	unsigned char* pixels;

	const unsigned int pixelPosToPixelIndex(unsigned int pixelPosX, unsigned int pixelPosY) const;
};

