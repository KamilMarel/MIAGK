#pragma once
#include "math_functions.h"

class VertexProcessor
{
public:
	VertexProcessor();
	void setView2ProjMatrix(float fovY, float aspect, float near, float far);
	void setLookAt(const float3& eye, const float3& center, const float3& up);
	void multByTranslation(const float3& v);
	void multByScale(const float3& v);
	void multByRotation(const float a, const float3& v);
	float4x4& getView2ProjMatrix();
	float4x4& getWorld2ViewMatrix();
	float4x4& getObj2WorldMatrix();
private:
	float4x4 view2Proj;
	float4x4 world2View;
	float4x4 obj2World;
};