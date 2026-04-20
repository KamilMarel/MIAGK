#include "math_structures.h"

inline float2 canonicalToWindowCoordinates(const float2& coordinatesToConvert, unsigned int windowSizeX, unsigned int windowSizeY)
{
	return { (coordinatesToConvert.x + 1) * windowSizeX * 0.5f,
			 (coordinatesToConvert.y + 1) * windowSizeY * 0.5f };
}

inline float minFloat(float a, float b, float c)
{
	float minValue = a;
	if (b < minValue)
	{
		minValue = b;
	}
	if (c < minValue)
	{
		minValue = c;
	}
	return minValue;
}

inline float maxFloat(float a, float b, float c)
{
	float maxValue = a;
	if (b > maxValue)
	{
		maxValue = b;
	}
	if (c > maxValue)
	{
		maxValue = c;
	}
	return maxValue;
}

inline float minFloat(float a, float b)
{
	return (a < b) ? a : b;
}

inline float maxFloat(float a, float b)
{
	return (a > b) ? a : b;
}