#include "stdafx.h"

#include "Common.h"
#include "Direct3D10Mesh.h"
#include "Direct3D10ModelFactory.h"
#include "Line3D.h"

using namespace std;

namespace Direct3D10ModelFactory
{
	Model* create2DTerrainFromSegments(ID3D10Device& device, float floor, const vector<Line3D>& segments,
		const D3DXCOLOR& color);
	Model* create3DTerrainFromPoints(ID3D10Device& device, unsigned int segmentCount,
		const vector<D3DXVECTOR3>& points, const D3DXCOLOR& color);
	D3DXVECTOR3 createNormal(unsigned int segmentXIndex, unsigned int segmentYIndex, unsigned int segmentCount,
		const vector<D3DXVECTOR3>& points);
	float interpolateCosine(float a, float b, float x);
	float interpolateLinear(float a, float b, float x);
	float interpolateNoise(float x);
	float interpolateNoise(float x, float y);
	float noise(int x);
	float noise(int x, int y);
	float perlinNoise(float x, unsigned int octaves, float persistence);
	float perlinNoise(float x, float y, unsigned int octaves, float persistence);
	float smoothNoise(int x);
	float smoothNoise(int x, int y);

	Model* create2DPerlinTerrain(ID3D10Device& device, float width, unsigned int segmentCount, unsigned int octaves,
		float persistence, const D3DXCOLOR& color)
	{
		float segmentWidth = width / segmentCount;
		vector<Line3D> segments;
		float x = width / 2.0f * -1.0f;

		for (unsigned int segmentIndex = 0; segmentIndex < segmentCount; segmentIndex++)
		{
			Line3D segment;

			if (segmentIndex == 0)
			{
				segment.a = D3DXVECTOR3(x, perlinNoise(x, octaves, persistence), 0.0f);
			}
			else
			{
				segment.a = segments.back().b;
			}

			x += segmentWidth;

			segment.b = D3DXVECTOR3(x, perlinNoise(x, octaves, persistence), 0.0f);

			segments.push_back(segment);
		}

		return create2DTerrainFromSegments(device, width / 2.0f * -1.0f, segments, color);
	}

	Model* create2DTerrainFromSegments(ID3D10Device& device, float floor, const vector<Line3D>& segments,
		const D3DXCOLOR& color)
	{
		vector<Vertex> vertices;
		vertices.reserve(segments.size() * 4);
		for (unsigned int segmentIndex = 0; segmentIndex < segments.size(); segmentIndex++)
		{
			Vertex vertexA;
			vertexA.color = color;
			vertexA.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexA.pos = segments.at(segmentIndex).a;
			vertices.push_back(vertexA);

			Vertex vertexAFloor;
			vertexAFloor.color = color;
			vertexAFloor.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexAFloor.pos = segments.at(segmentIndex).a;
			vertexAFloor.pos.y = floor;
			vertices.push_back(vertexAFloor);

			Vertex vertexB;
			vertexB.color = color;
			vertexB.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexB.pos = segments.at(segmentIndex).b;
			vertices.push_back(vertexB);

			Vertex vertexBFloor;
			vertexBFloor.color = color;
			vertexBFloor.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexBFloor.pos = segments.at(segmentIndex).b;
			vertexBFloor.pos.y = floor;
			vertices.push_back(vertexBFloor);
		}

		vector<DWORD> indices;
		indices.reserve(segments.size() * 6);
		for (unsigned int segmentIndex = 0; segmentIndex < segments.size(); segmentIndex++)
		{
			indices.push_back(segmentIndex * 4 + 0);
			indices.push_back(segmentIndex * 4 + 3);
			indices.push_back(segmentIndex * 4 + 1);
			indices.push_back(segmentIndex * 4 + 2);
			indices.push_back(segmentIndex * 4 + 3);
			indices.push_back(segmentIndex * 4 + 0);
		}

		return new Direct3D10Mesh(device, indices, vertices);
	}

	Model* create3DPerlinTerrain(ID3D10Device& device, float width, float depth, float heightScalar,
		unsigned int segmentCount, unsigned int octaves, float persistence, const D3DXCOLOR& color)
	{
		float segmentWidth = width / segmentCount;
		float segmentDepth = depth / segmentCount;
		vector<D3DXVECTOR3> points;

		float x = width / 2.0f * -1.0f;
		for (unsigned int segmentXIndex = 0; segmentXIndex < segmentCount; segmentXIndex++)
		{
			float z = depth / 2.0f * -1.0f;
			for (unsigned int segmentZIndex = 0; segmentZIndex < segmentCount; segmentZIndex++)
			{
				points.push_back(D3DXVECTOR3(x, perlinNoise(x, z, octaves, persistence) * heightScalar, z));
				z += segmentDepth;
			}
			x += segmentWidth;
		}

		return create3DTerrainFromPoints(device, segmentCount, points, color);
	}

	Model* create3DTerrainFromPoints(ID3D10Device& device, unsigned int segmentCount,
		const vector<D3DXVECTOR3>& points, const D3DXCOLOR& color)
	{
		vector<Vertex> vertices;
		vertices.reserve((segmentCount - 1) * (segmentCount - 1) * 4);
		DWORD index = 0;
		vector<DWORD> indices;
		indices.reserve((segmentCount - 1) * (segmentCount - 1) * 6);

		for (unsigned int segmentXIndex = 0; segmentXIndex < segmentCount - 1; segmentXIndex++)
		{
			for (unsigned int segmentZIndex = 0; segmentZIndex < segmentCount - 1; segmentZIndex++)
			{
				Vertex v0;
				v0.color = color;
				v0.normal = createNormal(segmentXIndex, segmentZIndex, segmentCount, points);
				v0.pos = points.at(segmentCount * segmentXIndex + segmentZIndex);
				vertices.push_back(v0);
				
				Vertex v1;
				v1.color = color;
				v1.normal = createNormal(segmentXIndex, segmentZIndex + 1, segmentCount, points);
				v1.pos = points.at(segmentCount * segmentXIndex + segmentZIndex + 1);
				vertices.push_back(v1);
				
				Vertex v2;
				v2.color = color;
				v2.normal = createNormal(segmentXIndex + 1, segmentZIndex, segmentCount, points);
				v2.pos = points.at(segmentCount * (segmentXIndex + 1) + segmentZIndex);
				vertices.push_back(v2);
				
				Vertex v3;
				v3.color = color;
				v3.normal = createNormal(segmentXIndex + 1, segmentZIndex + 1, segmentCount, points);
				v3.pos = points.at(segmentCount * (segmentXIndex + 1) + segmentZIndex + 1);
				vertices.push_back(v3);

				indices.push_back(index);
				indices.push_back(index + 1);
				indices.push_back(index + 2);
				indices.push_back(index + 1);
				indices.push_back(index + 3);
				indices.push_back(index + 2);

				index += 4;
			}
		}

		return new Direct3D10Mesh(device, indices, vertices);
	}
	
	Model* createCube(ID3D10Device& device, float size, const D3DXCOLOR& color)
	{
		// Vertices
		vector<Vertex> vertices(24);

		vertices[0].pos = D3DXVECTOR3(-size, size, size);
		vertices[0].color = color;
		vertices[1].pos = D3DXVECTOR3(size, size, size);
		vertices[1].color = color;
		vertices[2].pos = D3DXVECTOR3(size, -size, size);
		vertices[2].color = color;
		vertices[3].pos = D3DXVECTOR3(-size, -size, size);
		vertices[3].color = color;

		D3DXVec3Cross(&vertices[0].normal, &D3DXVECTOR3(vertices[2].pos - vertices[0].pos), &D3DXVECTOR3(vertices[1].pos - vertices[0].pos));
		D3DXVec3Normalize(&vertices[0].normal, &vertices[0].normal);
		D3DXVec3Cross(&vertices[1].normal, &D3DXVECTOR3(vertices[3].pos - vertices[1].pos), &D3DXVECTOR3(vertices[2].pos - vertices[1].pos));
		D3DXVec3Normalize(&vertices[1].normal, &vertices[1].normal);
		D3DXVec3Cross(&vertices[2].normal, &D3DXVECTOR3(vertices[1].pos - vertices[2].pos), &D3DXVECTOR3(vertices[3].pos - vertices[2].pos));
		D3DXVec3Normalize(&vertices[2].normal, &vertices[2].normal);
		D3DXVec3Cross(&vertices[3].normal, &D3DXVECTOR3(vertices[2].pos - vertices[3].pos), &D3DXVECTOR3(vertices[0].pos - vertices[3].pos));
		D3DXVec3Normalize(&vertices[3].normal, &vertices[3].normal);
		
		vertices[4].pos = D3DXVECTOR3(-size, -size, -size);
		vertices[4].color = color;
		vertices[5].pos = D3DXVECTOR3(size, -size, -size);
		vertices[5].color = color;
		vertices[6].pos = D3DXVECTOR3(size, size, -size);
		vertices[6].color = color;
		vertices[7].pos = D3DXVECTOR3(-size, size, -size);
		vertices[7].color = color;

		D3DXVec3Cross(&vertices[4].normal, &D3DXVECTOR3(vertices[7].pos - vertices[4].pos), &D3DXVECTOR3(vertices[5].pos - vertices[4].pos));
		D3DXVec3Normalize(&vertices[4].normal, &vertices[4].normal);
		D3DXVec3Cross(&vertices[5].normal, &D3DXVECTOR3(vertices[4].pos - vertices[5].pos), &D3DXVECTOR3(vertices[6].pos - vertices[5].pos));
		D3DXVec3Normalize(&vertices[5].normal, &vertices[5].normal);
		D3DXVec3Cross(&vertices[6].normal, &D3DXVECTOR3(vertices[5].pos - vertices[6].pos), &D3DXVECTOR3(vertices[7].pos - vertices[6].pos));
		D3DXVec3Normalize(&vertices[6].normal, &vertices[6].normal);
		D3DXVec3Cross(&vertices[7].normal, &D3DXVECTOR3(vertices[6].pos - vertices[7].pos), &D3DXVECTOR3(vertices[4].pos - vertices[7].pos));
		D3DXVec3Normalize(&vertices[7].normal, &vertices[7].normal);

		vertices[8].pos = D3DXVECTOR3(-size, size, -size);
		vertices[8].color = color;
		vertices[9].pos = D3DXVECTOR3(size, size, -size);
		vertices[9].color = color;
		vertices[10].pos = D3DXVECTOR3(size, size, size);
		vertices[10].color = color;
		vertices[11].pos = D3DXVECTOR3(-size, size, size);
		vertices[11].color = color;

		D3DXVec3Cross(&vertices[8].normal, &D3DXVECTOR3(vertices[11].pos - vertices[8].pos), &D3DXVECTOR3(vertices[9].pos - vertices[8].pos));
		D3DXVec3Normalize(&vertices[8].normal, &vertices[8].normal);
		D3DXVec3Cross(&vertices[9].normal, &D3DXVECTOR3(vertices[8].pos - vertices[9].pos), &D3DXVECTOR3(vertices[10].pos - vertices[9].pos));
		D3DXVec3Normalize(&vertices[9].normal, &vertices[9].normal);
		D3DXVec3Cross(&vertices[10].normal, &D3DXVECTOR3(vertices[9].pos - vertices[10].pos), &D3DXVECTOR3(vertices[11].pos - vertices[10].pos));
		D3DXVec3Normalize(&vertices[10].normal, &vertices[10].normal);
		D3DXVec3Cross(&vertices[11].normal, &D3DXVECTOR3(vertices[10].pos - vertices[11].pos), &D3DXVECTOR3(vertices[8].pos - vertices[11].pos));
		D3DXVec3Normalize(&vertices[11].normal, &vertices[11].normal);

		vertices[12].pos = D3DXVECTOR3(-size, size, -size);
		vertices[12].color = color;
		vertices[13].pos = D3DXVECTOR3(-size, size, size);
		vertices[13].color = color;
		vertices[14].pos = D3DXVECTOR3(-size, -size, size);
		vertices[14].color = color;
		vertices[15].pos = D3DXVECTOR3(-size, -size, -size);
		vertices[15].color = color;

		D3DXVec3Cross(&vertices[12].normal, &D3DXVECTOR3(vertices[15].pos - vertices[12].pos), &D3DXVECTOR3(vertices[13].pos - vertices[12].pos));
		D3DXVec3Normalize(&vertices[12].normal, &vertices[12].normal);
		D3DXVec3Cross(&vertices[13].normal, &D3DXVECTOR3(vertices[12].pos - vertices[13].pos), &D3DXVECTOR3(vertices[14].pos - vertices[13].pos));
		D3DXVec3Normalize(&vertices[13].normal, &vertices[13].normal);
		D3DXVec3Cross(&vertices[14].normal, &D3DXVECTOR3(vertices[13].pos - vertices[14].pos), &D3DXVECTOR3(vertices[15].pos - vertices[14].pos));
		D3DXVec3Normalize(&vertices[14].normal, &vertices[14].normal);
		D3DXVec3Cross(&vertices[15].normal, &D3DXVECTOR3(vertices[14].pos - vertices[15].pos), &D3DXVECTOR3(vertices[12].pos - vertices[15].pos));
		D3DXVec3Normalize(&vertices[15].normal, &vertices[15].normal);

		vertices[16].pos = D3DXVECTOR3(size, size, size);
		vertices[16].color = color;
		vertices[17].pos = D3DXVECTOR3(size, size, -size);
		vertices[17].color = color;
		vertices[18].pos = D3DXVECTOR3(size, -size, -size);
		vertices[18].color = color;
		vertices[19].pos = D3DXVECTOR3(size, -size, size);
		vertices[19].color = color;

		D3DXVec3Cross(&vertices[16].normal, &D3DXVECTOR3(vertices[19].pos - vertices[16].pos), &D3DXVECTOR3(vertices[17].pos - vertices[16].pos));
		D3DXVec3Normalize(&vertices[16].normal, &vertices[16].normal);
		D3DXVec3Cross(&vertices[17].normal, &D3DXVECTOR3(vertices[16].pos - vertices[17].pos), &D3DXVECTOR3(vertices[18].pos - vertices[17].pos));
		D3DXVec3Normalize(&vertices[17].normal, &vertices[17].normal);
		D3DXVec3Cross(&vertices[18].normal, &D3DXVECTOR3(vertices[17].pos - vertices[18].pos), &D3DXVECTOR3(vertices[19].pos - vertices[18].pos));
		D3DXVec3Normalize(&vertices[18].normal, &vertices[18].normal);
		D3DXVec3Cross(&vertices[19].normal, &D3DXVECTOR3(vertices[18].pos - vertices[19].pos), &D3DXVECTOR3(vertices[16].pos - vertices[19].pos));
		D3DXVec3Normalize(&vertices[19].normal, &vertices[19].normal);

		vertices[20].pos = D3DXVECTOR3(-size, -size, size);
		vertices[20].color = color;
		vertices[21].pos = D3DXVECTOR3(size, -size, size);
		vertices[21].color = color;
		vertices[22].pos = D3DXVECTOR3(size, -size, -size);
		vertices[22].color = color;
		vertices[23].pos = D3DXVECTOR3(-size, -size, -size);
		vertices[23].color = color;

		D3DXVec3Cross(&vertices[20].normal, &D3DXVECTOR3(vertices[23].pos - vertices[20].pos), &D3DXVECTOR3(vertices[21].pos - vertices[20].pos));
		D3DXVec3Normalize(&vertices[20].normal, &vertices[20].normal);
		D3DXVec3Cross(&vertices[21].normal, &D3DXVECTOR3(vertices[20].pos - vertices[21].pos), &D3DXVECTOR3(vertices[22].pos - vertices[21].pos));
		D3DXVec3Normalize(&vertices[21].normal, &vertices[21].normal);
		D3DXVec3Cross(&vertices[22].normal, &D3DXVECTOR3(vertices[21].pos - vertices[22].pos), &D3DXVECTOR3(vertices[23].pos - vertices[22].pos));
		D3DXVec3Normalize(&vertices[22].normal, &vertices[22].normal);
		D3DXVec3Cross(&vertices[23].normal, &D3DXVECTOR3(vertices[22].pos - vertices[23].pos), &D3DXVECTOR3(vertices[20].pos - vertices[23].pos));
		D3DXVec3Normalize(&vertices[23].normal, &vertices[23].normal);
		
		// Indices
		vector<DWORD> indices(36);

		indices[0] = 2;
		indices[1] = 1;
		indices[2] = 0;
		indices[3] = 0;
		indices[4] = 3;
		indices[5] = 2;

		indices[6] = 6;
		indices[7] = 5;
		indices[8] = 4;
		indices[9] = 4;
		indices[10] = 7;
		indices[11] = 6;

		indices[12] = 10;
		indices[13] = 9;
		indices[14] = 8;
		indices[15] = 8;
		indices[16] = 11;
		indices[17] = 10;

		indices[18] = 14;
		indices[19] = 13;
		indices[20] = 12;
		indices[21] = 12;
		indices[22] = 15;
		indices[23] = 14;

		indices[24] = 18;
		indices[25] = 17;
		indices[26] = 16;
		indices[27] = 16;
		indices[28] = 19;
		indices[29] = 18;

		indices[30] = 18;
		indices[31] = 17;
		indices[32] = 16;
		indices[33] = 16;
		indices[34] = 19;
		indices[35] = 18;

		return new Direct3D10Mesh(device, indices, vertices);
	}

	Model* createMidPointDisplacementTerrain(ID3D10Device& device, float width, unsigned int iterations,
		const D3DXCOLOR& color)
	{
		vector<Line3D> segments;

		Line3D initialSegment;
		initialSegment.a = D3DXVECTOR3(width / 2.0f * -1.0f, 0.0f, 0.0f);
		initialSegment.b = D3DXVECTOR3(width / 2.0f, 0.0f, 0.0f);
		segments.push_back(initialSegment);

		for (unsigned int iteration = 0; iteration < iterations; iteration++)
		{
			vector<Line3D> subdividedSegments;
			float randomRange = width / (2.0f * pow((float) iterations, 1.75f));

			for (unsigned int segmentIndex = 0; segmentIndex < segments.size(); segmentIndex++)
			{
				D3DXVECTOR3 difference = segments.at(segmentIndex).b - segments.at(segmentIndex).a;
				D3DXVECTOR3 halfDifference = difference / 2.0f;
				D3DXVECTOR3 midpoint = segments.at(segmentIndex).a + halfDifference;

				midpoint.y += Common::getRandomFloat(-randomRange, randomRange);

				Line3D segment1;
				segment1.a = segments.at(segmentIndex).a;
				segment1.b = midpoint;
				subdividedSegments.push_back(segment1);

				Line3D segment2;
				segment2.a = midpoint;
				segment2.b = segments.at(segmentIndex).b;
				subdividedSegments.push_back(segment2);
			}

			segments = subdividedSegments;
		}

		return create2DTerrainFromSegments(device, width / 2.0f * -1.0f, segments, color);
	}

	D3DXVECTOR3 createNormal(unsigned int segmentXIndex, unsigned int segmentYIndex, unsigned int segmentCount,
		const vector<D3DXVECTOR3>& points)
	{
		D3DXVECTOR3 normal(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 normalTemp;

		if (segmentXIndex < segmentCount - 1 && segmentYIndex < segmentCount - 1)
		{
			D3DXVECTOR3 v0tov1 = points.at(segmentCount * segmentXIndex + segmentYIndex + 1) -
				points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVECTOR3 v0tov2 = points.at(segmentCount * (segmentXIndex + 1) + segmentYIndex) -
				points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVec3Cross(&normalTemp, &v0tov1, &v0tov2);

			normal += normalTemp;
		}

		if (segmentXIndex > 0 && segmentYIndex < segmentCount - 1)
		{
			D3DXVECTOR3 v0tov1 = points.at(segmentCount * (segmentXIndex - 1) + segmentYIndex) -
			points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVECTOR3 v0tov2 = points.at(segmentCount * segmentXIndex + segmentYIndex + 1) -
				points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVec3Cross(&normalTemp, &v0tov1, &v0tov2);

			normal += normalTemp;
		}

		if (segmentXIndex < segmentCount - 1 && segmentYIndex > 0)
		{
			D3DXVECTOR3 v0tov1 = points.at(segmentCount * (segmentXIndex + 1) + segmentYIndex) -
			points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVECTOR3 v0tov2 = points.at(segmentCount * segmentXIndex + segmentYIndex - 1) -
				points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVec3Cross(&normalTemp, &v0tov1, &v0tov2);

			normal += normalTemp;
		}

		if (segmentXIndex > 0 && segmentYIndex > 0)
		{
			D3DXVECTOR3 v0tov1 = points.at(segmentCount * (segmentXIndex - 1) + segmentYIndex) -
			points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVECTOR3 v0tov2 = points.at(segmentCount * segmentXIndex + segmentYIndex - 1) -
				points.at(segmentCount * segmentXIndex + segmentYIndex);
			D3DXVec3Cross(&normalTemp, &v0tov1, &v0tov2);

			normal += normalTemp;
		}

		D3DXVec3Normalize(&normal, &normal);
		return normal;
	}

	float interpolateCosine(float a, float b, float x)
	{
		float ft = x * 3.1415927f;
		float f = (1 - cos(ft)) * 0.5f;
		return a * (1 - f) + b * f;
	}

	float interpolateNoise(float x)
	{
		int intX = int(x);
		float remainderX = x - intX;

		//float v1 = noise(intX);
		//float v2 = noise(intX + 1);
		float v1 = smoothNoise(intX);
		float v2 = smoothNoise(intX + 1);

		//return interpolateLinear(v1, v2, remainderX);
		return interpolateCosine(v1, v2, remainderX);
	}

	float interpolateNoise(float x, float y)
	{
		int intX = int(x);
		float remainderX = x - intX;

		int intY = int(y);
		float remainderY = y - intY;

		//float v1 = noise(intX, intY);
		//float v2 = noise(intX + 1, intY);
		//float v3 = noise(intX, intY + 1);
		//float v4 = noise(intX + 1, intY + 1);
		float v1 = smoothNoise(intX, intY);
		float v2 = smoothNoise(intX + 1, intY);
		float v3 = smoothNoise(intX, intY + 1);
		float v4 = smoothNoise(intX + 1, intY + 1);

		//float i1 = interpolateLinear(v1, v2, remainderX);
		//float i2 = interpolateLinear(v3, v4, remainderX);
		float i1 = interpolateCosine(v1, v2, remainderX);
		float i2 = interpolateCosine(v3, v4, remainderX);

		//return interpolateLinear(i1, i2, remainderY);
		return interpolateCosine(i1, i2, remainderY);
	}

	float interpolateLinear(float a, float b, float x)
	{
		return a * (1 - x) + b * x;
	}

	float noise(int x)
	{
		x = (x<<13) ^ x;
		return 1.0f - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f;
	}
	
	float noise(int x, int y)
	{
		int n = x + y * 57;
		n = (n<<13) ^ n;
		return 1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f;
	}
	
	float perlinNoise(float x, unsigned int octaves, float persistence)
	{
		float y = 0;

		for(unsigned int octave = 0; octave < octaves - 1; octave++)
		{
			float frequency = pow(2.0f, (int) octave);
			float amplitude = pow(persistence, (int) octave);

			y += interpolateNoise(x * frequency) * amplitude;
		}

		return y;
	}
	
	float perlinNoise(float x, float y, unsigned int octaves, float persistence)
	{
		float z = 0;

		for(unsigned int octave = 0; octave < octaves - 1; octave++)
		{
			float frequency = pow(2.0f, (int) octave);
			float amplitude = pow(persistence, (int) octave);

			z += interpolateNoise(x * frequency, y * frequency) * amplitude;
		}

		return z;
	}
	
	float smoothNoise(int x)
	{
		return noise(x) / 2  +  noise(x - 1) / 4  +  noise(x + 1) / 4;
	}
	
	float smoothNoise(int x, int y)
	{
		float corners = (noise(x - 1, y - 1) + noise(x + 1, y - 1) + noise(x - 1, y + 1) + noise(x + 1, y + 1)) / 16;
		float sides = (noise(x - 1, y) + noise(x+1, y) + noise(x, y - 1) + noise(x, y + 1)) / 8;
		float center = noise(x, y) / 4;

		return corners + sides + center;
	}
}
