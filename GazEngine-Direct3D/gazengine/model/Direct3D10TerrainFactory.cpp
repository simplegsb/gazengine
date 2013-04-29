#include <gazengine/math/Interpolation.h>
#include <gazengine/math/Math.h>

#include "Direct3D10Mesh.h"
#include "Direct3D10TerrainFactory.h"

using namespace std;

namespace Direct3D10TerrainFactory
{
	Model* create2DTerrainFromPoints(ID3D10Device& device, float floor, const vector<D3DXVECTOR3>& points,
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

	Model* create2DPerlinTerrain(ID3D10Device& device, float width, unsigned int pointCount, unsigned int octaves,
		float persistence, const D3DXCOLOR& color)
	{
		vector<D3DXVECTOR3> points;
		points.reserve(pointCount);

		float segmentWidth = width / (pointCount - 1);
		float x = width / 2.0f * -1.0f;

		for (unsigned int pointIndex = 0; pointIndex < pointCount; pointIndex++)
		{
			points.push_back(D3DXVECTOR3(x, perlinNoise(x, octaves, persistence), 0.0f));
			x += segmentWidth;
		}

		return create2DTerrainFromPoints(device, width / 2.0f * -1.0f, points, color);
	}

	Model* create2DTerrainFromPoints(ID3D10Device& device, float floor, const vector<D3DXVECTOR3>& points,
		const D3DXCOLOR& color)
	{
		vector<Vertex> vertices;
		vertices.reserve((points.size() - 1) * 4);
		for (unsigned int segmentIndex = 0; segmentIndex < points.size() - 1; segmentIndex++)
		{
			Vertex vertexA;
			vertexA.color = color;
			vertexA.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexA.position = points.at(segmentIndex);
			vertices.push_back(vertexA);

			Vertex vertexAFloor;
			vertexAFloor.color = color;
			vertexAFloor.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexAFloor.position = points.at(segmentIndex);
			vertexAFloor.position.y = floor;
			vertices.push_back(vertexAFloor);

			Vertex vertexB;
			vertexB.color = color;
			vertexB.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexB.position = points.at(segmentIndex + 1);
			vertices.push_back(vertexB);

			Vertex vertexBFloor;
			vertexBFloor.color = color;
			vertexBFloor.normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			vertexBFloor.position = points.at(segmentIndex + 1);
			vertexBFloor.position.y = floor;
			vertices.push_back(vertexBFloor);
		}

		vector<DWORD> indices;
		indices.reserve((points.size() - 1) * 6);
		for (unsigned int segmentIndex = 0; segmentIndex < points.size() - 1; segmentIndex++)
		{
			indices.push_back(segmentIndex * 4 + 0);
			indices.push_back(segmentIndex * 4 + 3);
			indices.push_back(segmentIndex * 4 + 1);
			indices.push_back(segmentIndex * 4 + 2);
			indices.push_back(segmentIndex * 4 + 3);
			indices.push_back(segmentIndex * 4 + 0);
		}

		return new Direct3D10Mesh(device, vertices, indices);
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
				v0.position = points.at(segmentCount * segmentXIndex + segmentZIndex);
				vertices.push_back(v0);
				
				Vertex v1;
				v1.color = color;
				v1.normal = createNormal(segmentXIndex, segmentZIndex + 1, segmentCount, points);
				v1.position = points.at(segmentCount * segmentXIndex + segmentZIndex + 1);
				vertices.push_back(v1);
				
				Vertex v2;
				v2.color = color;
				v2.normal = createNormal(segmentXIndex + 1, segmentZIndex, segmentCount, points);
				v2.position = points.at(segmentCount * (segmentXIndex + 1) + segmentZIndex);
				vertices.push_back(v2);
				
				Vertex v3;
				v3.color = color;
				v3.normal = createNormal(segmentXIndex + 1, segmentZIndex + 1, segmentCount, points);
				v3.position = points.at(segmentCount * (segmentXIndex + 1) + segmentZIndex + 1);
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

		return new Direct3D10Mesh(device, vertices, indices);
	}

	Model* createMidPointDisplacementTerrain(ID3D10Device& device, float width, unsigned int iterations,
		const D3DXCOLOR& color)
	{
		return createMidPointDisplacementTerrain(device, width, iterations, color, 0);
	}

	Model* createMidPointDisplacementTerrain(ID3D10Device& device, float width, unsigned int iterations,
		const D3DXCOLOR& color, unsigned int interpolationCount)
	{
		vector<Vector3> points;
		points.push_back(Vector3(width / 2.0f * -1.0f, 0.0f, 0.0f));
		points.push_back(Vector3(width / 2.0f, 0.0f, 0.0f));

		for (unsigned int iteration = 0; iteration < iterations; iteration++)
		{
			vector<Vector3> subdividedPoints;
			float randomRange = width / (2.0f * pow((float) iterations, 1.75f));

			for (unsigned int segmentIndex = 0; segmentIndex < points.size() - 1; segmentIndex++)
			{
				Vector3 difference = points.at(segmentIndex + 1) - points.at(segmentIndex);
				Vector3 halfDifference = difference / 2.0f;
				Vector3 midpoint = points.at(segmentIndex) + halfDifference;

				midpoint.Y() += Math::getRandomFloat(-randomRange, randomRange);

				subdividedPoints.push_back(points.at(segmentIndex));
				subdividedPoints.push_back(midpoint);
				subdividedPoints.push_back(points.at(segmentIndex + 1));
			}

			points = subdividedPoints;
		}

		if (interpolationCount > 0)
		{
			points = Interpolation::interpolateBezier(points, interpolationCount);
		}

		vector<D3DXVECTOR3> d3dxPoints;
		d3dxPoints.reserve(points.size());
		for (unsigned int pointIndex = 0; pointIndex < points.size(); pointIndex++)
		{
			d3dxPoints.push_back(D3DXVECTOR3(points[pointIndex].getData()));
		}

		return create2DTerrainFromPoints(device, width / 2.0f * -1.0f, d3dxPoints, color);
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
