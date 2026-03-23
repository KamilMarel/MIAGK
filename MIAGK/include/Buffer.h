#include "stb_image_write.h"

class Buffer
{
public:
	Buffer();
	Buffer(unsigned int sizeX, unsigned int sizeY);
	~Buffer();

	void clearColor(unsigned char red, unsigned char green, unsigned char blue);
	void saveToFile();

private:
	unsigned int sizeX = 1024, sizeY = 1024;
	unsigned char* pixels;
};

