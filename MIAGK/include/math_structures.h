#include <iostream>

struct float3
{
	float x, y, z;

	float3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}
	float3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float3 operator+(const float3& other) const
	{
		return { x + other.x, 
				 y + other.y,
				 z + other.z };
	}

	float3 operator*(const float other) const
	{
		return { x * other,
				 y * other,
				 z * other };
	}

	friend std::ostream& operator<<(std::ostream& os, const float3& obj)
	{
		os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
		return os;
	}
};

struct float2
{
	float x, y;

	float2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	float2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float2 operator+(const float2& other) const
	{
		return { x + other.x,
				 y + other.y };
	}

	float2 operator*(const float other) const
	{
		return { x * other,
				 y * other };
	}

	friend std::ostream& operator<<(std::ostream& os, const float2& obj)
	{
		os << "(" << obj.x << ", " << obj.y << ")";
		return os;
	}
};

struct color
{
	unsigned char r, g, b;

	color()
	{
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	color(unsigned char r, unsigned char g, unsigned char b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	friend std::ostream& operator<<(std::ostream& os, const color& obj)
	{
		os << "(" << obj.r << ", " << obj.g << ", " << obj.b << ")";
		return os;
	}
};