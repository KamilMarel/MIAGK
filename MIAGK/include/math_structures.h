#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

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

	float3 operator-(const float3& other) const
	{
		return { x - other.x,
				 y - other.y,
				 z - other.z };
	}

	float3 operator*(const float other) const
	{
		return { x * other,
				 y * other,
				 z * other };
	}

	const float length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	const float3 normalized() const
	{
		float vectorLength = length();
		return { x / vectorLength,
				 y / vectorLength,
				 z / vectorLength };
	}

	const float3 cross(const float3& other) const
	{
		return { y * other.z - z * other.y, 
				 z * other.x - x * other.z, 
				 x * other.y - y * other.x };
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

	color operator*(const float other) const
	{
		return { static_cast<unsigned char>(r * other),
				 static_cast<unsigned char>(g * other),
				 static_cast<unsigned char>(b * other)};
	}

	color operator+(const color& other) const
	{
		return { static_cast<unsigned char>(r + other.r),
				 static_cast<unsigned char>(g + other.g),
				 static_cast<unsigned char>(b + other.b)};
	}

	friend std::ostream& operator<<(std::ostream& os, const color& obj)
	{
		os << "(" << obj.r << ", " << obj.g << ", " << obj.b << ")";
		return os;
	}
};

struct float4
{
	float x, y, z, w;

	float4()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}
	float4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	float4 operator+(const float4& other) const
	{
		return { x + other.x,
				 y + other.y,
				 z + other.z,
				 w + other.w };
	}

	float4 operator*(const float other) const
	{
		return { x * other,
				 y * other,
				 z * other,
				 w * other };
	}

	float4 operator/(const float other) const
	{
		return
		{
			x / other,
			y / other,
			z / other,
			w / other
		};
	}

	friend std::ostream& operator<<(std::ostream& os, const float4& obj)
	{
		os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ", " << obj.w << ")";
		return os;
	}

	float& operator[](int index)
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;
		default:
			return x;
		}
	}
};

struct float4x4
{
	float4 columns[4];

	float4x4()
	{
		for (int n = 0; n < 4; n++)
		{
			for (int m = 0; m < 4; m++)
			{
				if (m == n)
				{
					columns[n][m] = 1.0f;
				}
				else
				{
					columns[n][m] = 0.0f;
				}
			}
		}
	}

	float4x4(float a11, float a21, float a31, float a41,
			 float a12, float a22, float a32, float a42,
			 float a13, float a23, float a33, float a43,
			 float a14, float a24, float a34, float a44)
	{
		columns[0] = { a11, a21, a31, a41 };
		columns[1] = { a12, a22, a32, a42 };
		columns[2] = { a13, a23, a33, a43 };
		columns[3] = { a14, a24, a34, a44 };
	}

	float4x4(float4 n1, float4 n2, float4 n3, float4 n4)
	{
		columns[0] = n1;
		columns[1] = n2;
		columns[2] = n3;
		columns[3] = n4;
	}

	float4 operator*(float4& vec)
	{
		return 
		{ 
			columns[0][0] * vec[0] + columns[1][0] * vec[1] + columns[2][0] * vec[2] + columns[3][0] * vec[3],
			columns[0][1] * vec[0] + columns[1][1] * vec[1] + columns[2][1] * vec[2] + columns[3][1] * vec[3],
			columns[0][2] * vec[0] + columns[1][2] * vec[1] + columns[2][2] * vec[2] + columns[3][2] * vec[3],
			columns[0][3] * vec[0] + columns[1][3] * vec[1] + columns[2][3] * vec[2] + columns[3][3] * vec[3]
		};
	}

	float4x4 operator*(float4x4& other)
	{
		return
		{
			columns[0][0] * other.columns[0][0] + columns[1][0] * other.columns[0][1] + columns[2][0] * other.columns[0][2] + columns[3][0] * other.columns[0][3],
			columns[0][1] * other.columns[0][0] + columns[1][1] * other.columns[0][1] + columns[2][1] * other.columns[0][2] + columns[3][1] * other.columns[0][3],
			columns[0][2] * other.columns[0][0] + columns[1][2] * other.columns[0][1] + columns[2][2] * other.columns[0][2] + columns[3][2] * other.columns[0][3],
			columns[0][3] * other.columns[0][0] + columns[1][3] * other.columns[0][1] + columns[2][3] * other.columns[0][2] + columns[3][3] * other.columns[0][3],

			columns[0][0] * other.columns[1][0] + columns[1][0] * other.columns[1][1] + columns[2][0] * other.columns[1][2] + columns[3][0] * other.columns[1][3],
			columns[0][1] * other.columns[1][0] + columns[1][1] * other.columns[1][1] + columns[2][1] * other.columns[1][2] + columns[3][1] * other.columns[1][3],
			columns[0][2] * other.columns[1][0] + columns[1][2] * other.columns[1][1] + columns[2][2] * other.columns[1][2] + columns[3][2] * other.columns[1][3],
			columns[0][3] * other.columns[1][0] + columns[1][3] * other.columns[1][1] + columns[2][3] * other.columns[1][2] + columns[3][3] * other.columns[1][3],

			columns[0][0] * other.columns[2][0] + columns[1][0] * other.columns[2][1] + columns[2][0] * other.columns[2][2] + columns[3][0] * other.columns[2][3],
			columns[0][1] * other.columns[2][0] + columns[1][1] * other.columns[2][1] + columns[2][1] * other.columns[2][2] + columns[3][1] * other.columns[2][3],
			columns[0][2] * other.columns[2][0] + columns[1][2] * other.columns[2][1] + columns[2][2] * other.columns[2][2] + columns[3][2] * other.columns[2][3],
			columns[0][3] * other.columns[2][0] + columns[1][3] * other.columns[2][1] + columns[2][3] * other.columns[2][2] + columns[3][3] * other.columns[2][3],

			columns[0][0] * other.columns[3][0] + columns[1][0] * other.columns[3][1] + columns[2][0] * other.columns[3][2] + columns[3][0] * other.columns[3][3],
			columns[0][1] * other.columns[3][0] + columns[1][1] * other.columns[3][1] + columns[2][1] * other.columns[3][2] + columns[3][1] * other.columns[3][3],
			columns[0][2] * other.columns[3][0] + columns[1][2] * other.columns[3][1] + columns[2][2] * other.columns[3][2] + columns[3][2] * other.columns[3][3],
			columns[0][3] * other.columns[3][0] + columns[1][3] * other.columns[3][1] + columns[2][3] * other.columns[3][2] + columns[3][3] * other.columns[3][3],
		};
	}

	float4& operator[](int columnIndex)
	{
		return columns[columnIndex];
	}
};