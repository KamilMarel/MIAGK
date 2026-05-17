#include "Cylinder.h"

Cylinder::Cylinder(float radius, float height, unsigned int horizontalDetailLevel, unsigned int verticalDetailLevel)
{
	float horizontalStep = (2.0f * M_PI) / (3.0f + horizontalDetailLevel * 1.0f);
	float verticalStep = height * 1.0f / (1.0f + verticalDetailLevel * 1.0f);
	int verticalLevelsIncludingBases = 2 + verticalDetailLevel;
	int amountOfVerticesPerVerticalLevel = 3 + horizontalDetailLevel;

	float currentHeight = 0;
	for (int verticalLevel = 0; verticalLevel < verticalLevelsIncludingBases; verticalLevel++)
	{
		float t = 0;
		for (int vertexOfVerticalLevel = 0; vertexOfVerticalLevel < amountOfVerticesPerVerticalLevel; vertexOfVerticalLevel++)
		{
			float offsetX = radius * cos(t);
			float offsetZ = radius * sin(t);
			vertices.push_back(Vertex(float3(offsetX, currentHeight, offsetZ)));
			t += horizontalStep;
		}
		currentHeight += verticalStep;
	}
	vertices.push_back(Vertex(float3(0, 0, 0)));
	vertices.push_back(Vertex(float3(0, height, 0)));

	int topVertexIndex = vertices.size() - 1;
	int bottomMiddleVertexIndex = vertices.size() - 2;
	for (int verticalLevel = 0; verticalLevel < verticalLevelsIncludingBases; verticalLevel++)
	{
		for (int levelVertex = 0; levelVertex < amountOfVerticesPerVerticalLevel - 1; levelVertex++)
		{
			int currentLevelVertexIndex = verticalLevel * amountOfVerticesPerVerticalLevel + levelVertex;
			int levelBelowVertexIndex = currentLevelVertexIndex - amountOfVerticesPerVerticalLevel + 1;
			int upperLevelVertexIndex = currentLevelVertexIndex + amountOfVerticesPerVerticalLevel;
			if (verticalLevel == 0)
			{
				levelBelowVertexIndex = bottomMiddleVertexIndex;
			}
			if (verticalLevel == verticalLevelsIncludingBases - 1)
			{
				upperLevelVertexIndex = topVertexIndex;
			}
			indices.push_back(int3(currentLevelVertexIndex, currentLevelVertexIndex + 1, upperLevelVertexIndex));
			indices.push_back(int3(currentLevelVertexIndex, levelBelowVertexIndex, currentLevelVertexIndex + 1));
		}

		int firstVertexIndexOnThisLevel = verticalLevel * amountOfVerticesPerVerticalLevel;
		int lastVertexIndexOnThisLevel = firstVertexIndexOnThisLevel + (amountOfVerticesPerVerticalLevel - 1);
		int levelBelowVertexIndex = firstVertexIndexOnThisLevel - amountOfVerticesPerVerticalLevel;
		int upperLevelVertexIndex = lastVertexIndexOnThisLevel + amountOfVerticesPerVerticalLevel;
		if (verticalLevel == 0)
		{
			levelBelowVertexIndex = bottomMiddleVertexIndex;
		}
		if (verticalLevel == verticalLevelsIncludingBases - 1)
		{
			upperLevelVertexIndex = topVertexIndex;
		}
		indices.push_back(int3(lastVertexIndexOnThisLevel, firstVertexIndexOnThisLevel, upperLevelVertexIndex));
		indices.push_back(int3(lastVertexIndexOnThisLevel, levelBelowVertexIndex, firstVertexIndexOnThisLevel));
	}
}

Cylinder::~Cylinder()
{}
