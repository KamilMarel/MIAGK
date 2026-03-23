#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Buffer.h"

const unsigned int BUFFER_SIZE_X = 1024, BUFFER_SIZE_Y = 1024;

const unsigned int BUFFER_CLEAR_COLOR_RED = 95,
                   BUFFER_CLEAR_COLOR_GREEN = 191,
                   BUFFER_CLEAR_COLOR_BLUE = 201;

int main()
{
    Buffer buffer(BUFFER_SIZE_X, BUFFER_SIZE_Y);
    buffer.clearColor(BUFFER_CLEAR_COLOR_RED, 
                      BUFFER_CLEAR_COLOR_GREEN, 
                      BUFFER_CLEAR_COLOR_BLUE);
    buffer.saveToFile();
}