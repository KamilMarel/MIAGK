#include "Torus.h"

Torus::Torus(float torusRadius, float cylinderRadius, unsigned int torusDetailLevel, unsigned int cylinderDetailLevel)
{
	float torusCircleStep = (2.0f * M_PI) / (3.0f + torusDetailLevel * 1.0f);
	float cylinderCircleStep = (2.0f * M_PI) / (3.0f + cylinderDetailLevel * 1.0f);
	int torusMaxLevel = 3 + torusDetailLevel;
	int cylinderMaxLevel = 3 + cylinderDetailLevel;

	float torusCircleStage = 0;
	for (int torusLevel = 0; torusLevel < torusMaxLevel; torusLevel++)
	{
		float torusOffsetX = torusRadius * cos(torusCircleStage);
		float torusOffsetZ = torusRadius * sin(torusCircleStage);
		float3 directionFromTorusCenterToThePoint = float3(torusOffsetX, 0, torusOffsetZ).normalized();

		float cylinderCircleStage = 0;
		for (int cylinderLevel = 0; cylinderLevel < cylinderMaxLevel; cylinderLevel++)
		{
			float cylinderOffsetX = torusOffsetX + (cylinderRadius * cos(cylinderCircleStage) * directionFromTorusCenterToThePoint.x);
			float cylinderOffsetY = cylinderRadius * sin(cylinderCircleStage);
			float cylinderOffsetZ = torusOffsetZ + (cylinderRadius * cos(cylinderCircleStage) * directionFromTorusCenterToThePoint.z);

			vertices.push_back(Vertex(float3(cylinderOffsetX, cylinderOffsetY, cylinderOffsetZ)));

			cylinderCircleStage += cylinderCircleStep;
		}
		torusCircleStage += torusCircleStep;
	}

	for (int torusLevel = 0; torusLevel < torusMaxLevel; torusLevel++)
	{
		for (int cylinderLevel = 0; cylinderLevel < cylinderMaxLevel - 1; cylinderLevel++)
		{
			int currentLevelVertexIndex = torusLevel * cylinderMaxLevel + cylinderLevel;
			int levelBelowVertexIndex = currentLevelVertexIndex - cylinderMaxLevel + 1;
			int upperLevelVertexIndex = currentLevelVertexIndex + cylinderMaxLevel;
			if (torusLevel == 0)
			{
				levelBelowVertexIndex = (torusMaxLevel - 1) * cylinderMaxLevel + cylinderLevel + 1;
			}
			if (torusLevel == torusMaxLevel - 1)
			{
				upperLevelVertexIndex = 0 + cylinderLevel;
			}
			indices.push_back(int3(upperLevelVertexIndex, currentLevelVertexIndex + 1, currentLevelVertexIndex));
			indices.push_back(int3(currentLevelVertexIndex + 1, levelBelowVertexIndex, currentLevelVertexIndex));
		}

		int firstVertexIndexOnThisLevel = torusLevel * cylinderMaxLevel;
		int lastVertexIndexOnThisLevel = firstVertexIndexOnThisLevel + (cylinderMaxLevel - 1);
		int levelBelowVertexIndex = firstVertexIndexOnThisLevel - cylinderMaxLevel;
		int upperLevelVertexIndex = lastVertexIndexOnThisLevel + cylinderMaxLevel;
		if (torusLevel == 0)
		{
			levelBelowVertexIndex = (torusMaxLevel - 1) * cylinderMaxLevel;
		}
		if (torusLevel == torusMaxLevel - 1)
		{
			upperLevelVertexIndex = cylinderMaxLevel - 1;
		}
		indices.push_back(int3(upperLevelVertexIndex, firstVertexIndexOnThisLevel, lastVertexIndexOnThisLevel));
		indices.push_back(int3(firstVertexIndexOnThisLevel, levelBelowVertexIndex, lastVertexIndexOnThisLevel));
	}
}

Torus::~Torus()
{}
