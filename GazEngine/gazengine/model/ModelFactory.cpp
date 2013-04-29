#include "ModelFactory.h"

using namespace std;

ModelFactory* ModelFactory::instance = NULL;

void ModelFactory::colorizeVertices(vector<Vertex>& vertices, const Vector4& color)
{
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		vertices[index].color = color;
	}
}

Mesh* ModelFactory::createCube(float size, const Vector4& color, bool doubleSided)
{
	// Vertices
	vector<Vertex> vertices(24);
	Vector3 normal;

	normal = Vector3(0.0f, 0.0f, 1.0f);
	vertices[0].position = Vector3(-size, size, size);
	vertices[0].color = color;
	vertices[0].normal = normal;
	vertices[1].position = Vector3(size, size, size);
	vertices[1].color = color;
	vertices[1].normal = normal;
	vertices[2].position = Vector3(size, -size, size);
	vertices[2].color = color;
	vertices[2].normal = normal;
	vertices[3].position = Vector3(-size, -size, size);
	vertices[3].color = color;
	vertices[3].normal = normal;

	normal = Vector3(0.0f, 0.0f, -1.0f);
	vertices[4].position = Vector3(-size, -size, -size);
	vertices[4].color = color;
	vertices[4].normal = normal;
	vertices[5].position = Vector3(size, -size, -size);
	vertices[5].color = color;
	vertices[5].normal = normal;
	vertices[6].position = Vector3(size, size, -size);
	vertices[6].color = color;
	vertices[6].normal = normal;
	vertices[7].position = Vector3(-size, size, -size);
	vertices[7].color = color;
	vertices[7].normal = normal;

	normal = Vector3(0.0f, 1.0f, 0.0f);
	vertices[8].position = Vector3(-size, size, -size);
	vertices[8].color = color;
	vertices[8].normal = normal;
	vertices[9].position = Vector3(size, size, -size);
	vertices[9].color = color;
	vertices[9].normal = normal;
	vertices[10].position = Vector3(size, size, size);
	vertices[10].color = color;
	vertices[10].normal = normal;
	vertices[11].position = Vector3(-size, size, size);
	vertices[11].color = color;
	vertices[11].normal = normal;

	normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertices[12].position = Vector3(-size, size, -size);
	vertices[12].color = color;
	vertices[12].normal = normal;
	vertices[13].position = Vector3(-size, size, size);
	vertices[13].color = color;
	vertices[13].normal = normal;
	vertices[14].position = Vector3(-size, -size, size);
	vertices[14].color = color;
	vertices[14].normal = normal;
	vertices[15].position = Vector3(-size, -size, -size);
	vertices[15].color = color;
	vertices[15].normal = normal;

	normal = Vector3(1.0f, 0.0f, 0.0f);
	vertices[16].position = Vector3(size, size, size);
	vertices[16].color = color;
	vertices[16].normal = normal;
	vertices[17].position = Vector3(size, size, -size);
	vertices[17].color = color;
	vertices[17].normal = normal;
	vertices[18].position = Vector3(size, -size, -size);
	vertices[18].color = color;
	vertices[18].normal = normal;
	vertices[19].position = Vector3(size, -size, size);
	vertices[19].color = color;
	vertices[19].normal = normal;

	normal = Vector3(0.0f, -1.0f, 0.0f);
	vertices[20].position = Vector3(-size, -size, size);
	vertices[20].color = color;
	vertices[20].normal = normal;
	vertices[21].position = Vector3(size, -size, size);
	vertices[21].color = color;
	vertices[21].normal = normal;
	vertices[22].position = Vector3(size, -size, -size);
	vertices[22].color = color;
	vertices[22].normal = normal;
	vertices[23].position = Vector3(-size, -size, -size);
	vertices[23].color = color;
	vertices[23].normal = normal;

	// Indices
	vector<int> indices;
	if (doubleSided)
	{
		indices.resize(72);
	}
	else
	{
		indices.resize(36);
	}

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

	indices[30] = 22;
	indices[31] = 21;
	indices[32] = 20;
	indices[33] = 20;
	indices[34] = 23;
	indices[35] = 22;

	if (doubleSided)
	{
		indices[36] = 0;
		indices[37] = 1;
		indices[38] = 2;
		indices[39] = 2;
		indices[40] = 3;
		indices[41] = 0;

		indices[42] = 4;
		indices[43] = 5;
		indices[44] = 6;
		indices[45] = 6;
		indices[46] = 7;
		indices[47] = 4;

		indices[48] = 8;
		indices[49] = 9;
		indices[50] = 10;
		indices[51] = 10;
		indices[52] = 11;
		indices[53] = 8;

		indices[54] = 12;
		indices[55] = 13;
		indices[56] = 14;
		indices[57] = 14;
		indices[58] = 15;
		indices[59] = 12;

		indices[60] = 16;
		indices[61] = 17;
		indices[62] = 18;
		indices[63] = 18;
		indices[64] = 19;
		indices[65] = 16;

		indices[66] = 20;
		indices[67] = 21;
		indices[68] = 22;
		indices[69] = 22;
		indices[70] = 23;
		indices[71] = 20;
	}

	return createMesh(vertices, indices);
}

Mesh* ModelFactory::createPrism(float size, const Vector4& color)
{
	// Vertices
	vector<Vertex> vertices(18);
	Vector3 normal;

	// Back
	normal = Vector3(0.0f, 0.0f, 1.0f);
	vertices[0].position = Vector3(-size, size, size);
	vertices[0].color = color;
	vertices[0].normal = normal;
	vertices[1].position = Vector3(size, size, size);
	vertices[1].color = color;
	vertices[1].normal = normal;
	vertices[2].position = Vector3(size, -size, size);
	vertices[2].color = color;
	vertices[2].normal = normal;
	vertices[3].position = Vector3(-size, -size, size);
	vertices[3].color = color;
	vertices[3].normal = normal;

	// Bottom
	normal = Vector3(0.0f, -1.0f, 0.0f);
	vertices[4].position = Vector3(-size, -size, size);
	vertices[4].color = color;
	vertices[4].normal = normal;
	vertices[5].position = Vector3(size, -size, size);
	vertices[5].color = color;
	vertices[5].normal = normal;
	vertices[6].position = Vector3(size, -size, -size);
	vertices[6].color = color;
	vertices[6].normal = normal;
	vertices[7].position = Vector3(-size, -size, -size);
	vertices[7].color = color;
	vertices[7].normal = normal;

	// Front
	normal = Vector3(0.0f, 1.0f, -1.0f);
	normal.normalize();
	vertices[8].position = Vector3(-size, -size, -size);
	vertices[8].color = color;
	vertices[8].normal = normal;
	vertices[9].position = Vector3(size, -size, -size);
	vertices[9].color = color;
	vertices[9].normal = normal;
	vertices[10].position = Vector3(size, size, size);
	vertices[10].color = color;
	vertices[10].normal = normal;
	vertices[11].position = Vector3(-size, size, size);
	vertices[11].color = color;
	vertices[11].normal = normal;

	// Left Side
	normal = Vector3(-1.0f, 0.0f, 0.0f);
	vertices[12].position = Vector3(-size, -size, -size);
	vertices[12].color = color;
	vertices[12].normal = normal;
	vertices[13].position = Vector3(-size, -size, size);
	vertices[13].color = color;
	vertices[13].normal = normal;
	vertices[14].position = Vector3(-size, size, size);
	vertices[14].color = color;
	vertices[14].normal = normal;

	// Right Side
	normal = Vector3(1.0f, 0.0f, 0.0f);
	vertices[15].position = Vector3(size, -size, -size);
	vertices[15].color = color;
	vertices[15].normal = normal;
	vertices[16].position = Vector3(size, size, size);
	vertices[16].color = color;
	vertices[16].normal = normal;
	vertices[17].position = Vector3(size, -size, size);
	vertices[17].color = color;
	vertices[17].normal = normal;

	// Indices
	vector<int> indices(24);

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

	indices[18] = 12;
	indices[19] = 13;
	indices[20] = 14;

	indices[21] = 15;
	indices[22] = 16;
	indices[23] = 17;

	return createMesh(vertices, indices);
}

Mesh* ModelFactory::createSquare(float size, const Vector4& color, bool doubleSided)
{
	// Vertices
	vector<Vertex> vertices(4);

	Vector3 normal(0.0f, 1.0f, 0.0f);
	vertices[0].position = Vector3(-size, 0.0f, size);
	vertices[0].color = color;
	vertices[0].normal = normal;
	vertices[1].position = Vector3(size, 0.0f, size);
	vertices[1].color = color;
	vertices[1].normal = normal;
	vertices[2].position = Vector3(size, 0.0f, -size);
	vertices[2].color = color;
	vertices[2].normal = normal;
	vertices[3].position = Vector3(-size, 0.0f, -size);
	vertices[3].color = color;
	vertices[3].normal = normal;

	// Indices
	vector<int> indices;
	if (doubleSided)
	{
		indices.resize(12);
	}
	else
	{
		indices.resize(6);
	}

	indices[0] = 2;
	indices[1] = 1;
	indices[2] = 0;
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;

	if (doubleSided)
	{
		indices[6] = 0;
		indices[7] = 1;
		indices[8] = 2;
		indices[9] = 2;
		indices[10] = 3;
		indices[11] = 0;
	}

	return createMesh(vertices, indices);
}

ModelFactory* ModelFactory::getInstance()
{
	return instance;
}

void ModelFactory::scaleVertices(vector<Vertex>& vertices, float scale)
{
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		vertices[index].position *= scale;
	}
}

void ModelFactory::setInstance(ModelFactory* instance)
{
	ModelFactory::instance = instance;
}
