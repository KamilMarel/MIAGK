#include "math_structures.h"

inline float2 canonicalToWindowCoordinates(const float2& coordinatesToConvert, unsigned int windowSizeX, unsigned int windowSizeY)
{
	return { (coordinatesToConvert.x + 1) * windowSizeX * 0.5f,
			 (coordinatesToConvert.y + 1) * windowSizeY * 0.5f };
}