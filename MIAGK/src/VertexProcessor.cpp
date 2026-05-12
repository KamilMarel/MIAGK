#include "VertexProcessor.h"

VertexProcessor::VertexProcessor()
{
	setView2ProjMatrix(45.0f, 1.0f, 0.1f, 100.0f);
	setLookAt(float3(0, 0, 0), float3(0, 0, -1), float3(0, 1, 0));
	multByScale(float3(1.5f, 1.0f, 1.0f));
	multByRotation(-45.0f, float3(0.0f, 1.0f, 0.0f));
	multByTranslation(float3(0.0f, 0.0f, -5.0f));
}

void VertexProcessor::setView2ProjMatrix(float fovY, float aspect, float near, float far)
{
	fovY *= M_PI / 360;
	float f = cos(fovY) / sin(fovY);
	view2Proj[0] = {f / aspect, 0, 0, 0};
	view2Proj[1] = { 0, f, 0, 0 };
	view2Proj[2] = { 0, 0, (far + near) / (near - far), -1};
	view2Proj[3] = { 0, 0, 2 * far * near / (near - far), 0};
}

void VertexProcessor::setLookAt(const float3& eye, const float3& center, const float3& up)
{
	float3 f = center - eye;
	f = f.normalized();
	float3 upNormalized = up.normalized();
	float3 s = f.cross(up);
	float3 u = s.cross(f);
	world2View[0] = { s.x, u.x, -f.x, 0 };
	world2View[1] = { s.y, u.y, -f.y, 0 };
	world2View[2] = { s.z, u.z, -f.z, 0 };
	world2View[3] = { 0, 0, 0, 1 };
	float4x4 m;
	m[3] = {-eye.x, -eye.y, -eye.z, 1};
	world2View = world2View * m;
}

void VertexProcessor::multByTranslation(const float3& v)
{
	float4x4 m({1, 0, 0, 0}, 
			   {0, 1, 0, 0}, 
			   {0, 0, 1, 0}, 
			   {v.x, v.y, v.z, 1});
	obj2World = m * obj2World;
}

void VertexProcessor::multByScale(const float3& v)
{
	float4x4 m({ v.x, 0, 0, 0 },
			   { 0, v.y, 0, 0 },
			   { 0, 0, v.z, 0 },
			   { 0, 0, 0, 1 });
	obj2World = m * obj2World;
}

void VertexProcessor::multByRotation(const float a, const float3& v)
{
	float s = sin(a * M_PI / 180.0f);
	float c = cos(a * M_PI / 180.0f);
	float3 vNormalized = v.normalized();
	float4x4 m({ v.x * v.x * (1 - c) + c, v.y * v.x * (1 - c) + v.z * s, v.x * v.z * (1 - c) - v.y * s, 0},
			   { v.x * v.y * (1 - c) - v.z * s, v.y * v.y * (1 - c) + c, v.y * v.z * (1 - c) + v.x * s, 0},
			   { v.x * v.z * (1 - c) + v.y * s, v.y * v.z * (1 - c) - v.x * s, v.z * v.z * (1 - c) + c, 0},
			   { 0, 0, 0, 1 });
	obj2World = m * obj2World;
}

float4x4& VertexProcessor::getView2ProjMatrix()
{
	return view2Proj;
}

float4x4& VertexProcessor::getWorld2ViewMatrix()
{
	return world2View;
}

float4x4& VertexProcessor::getObj2WorldMatrix()
{
	return obj2World;
}
