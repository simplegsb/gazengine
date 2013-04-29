#include <fstream>
#include <sstream>
#include <string>

#include "Direct3D10Mesh.h"
#include "Direct3D10ModelFactory.h"

using namespace std;

namespace Direct3D10ModelFactory
{
	const unsigned int MAX_SPLIT_LENGTH = 256;

	vector<string> splitString(char* rawSplit, istream& source, char delimiter, unsigned int estimatedSplitCount);
	
	void colorizeVertices(vector<Vertex>& vertices, const D3DXCOLOR& color)
	{
		for (unsigned int index = 0; index < vertices.size(); index++)
		{
			vertices[index].color = color;
		}
	}

	Direct3D10Mesh* createCube(ID3D10Device& device, float size, const D3DXCOLOR& color)
	{
		// Vertices
		vector<Vertex> vertices(24);
		D3DXVECTOR3 toFirst;
		D3DXVECTOR3 toSecond;

		vertices[0].position = D3DXVECTOR3(-size, size, size);
		vertices[0].color = color;
		vertices[1].position = D3DXVECTOR3(size, size, size);
		vertices[1].color = color;
		vertices[2].position = D3DXVECTOR3(size, -size, size);
		vertices[2].color = color;
		vertices[3].position = D3DXVECTOR3(-size, -size, size);
		vertices[3].color = color;

		toFirst = D3DXVECTOR3(vertices[2].position - vertices[0].position);
		toSecond = D3DXVECTOR3(vertices[1].position - vertices[0].position);
		D3DXVec3Cross(&vertices[0].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[0].normal, &vertices[0].normal);
		toFirst = D3DXVECTOR3(vertices[3].position - vertices[1].position);
		toSecond = D3DXVECTOR3(vertices[2].position - vertices[1].position);
		D3DXVec3Cross(&vertices[1].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[1].normal, &vertices[1].normal);
		toFirst = D3DXVECTOR3(vertices[1].position - vertices[2].position);
		toSecond = D3DXVECTOR3(vertices[3].position - vertices[2].position);
		D3DXVec3Cross(&vertices[2].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[2].normal, &vertices[2].normal);
		toFirst = D3DXVECTOR3(vertices[2].position - vertices[3].position);
		toSecond = D3DXVECTOR3(vertices[0].position - vertices[3].position);
		D3DXVec3Cross(&vertices[3].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[3].normal, &vertices[3].normal);
		
		vertices[4].position = D3DXVECTOR3(-size, -size, -size);
		vertices[4].color = color;
		vertices[5].position = D3DXVECTOR3(size, -size, -size);
		vertices[5].color = color;
		vertices[6].position = D3DXVECTOR3(size, size, -size);
		vertices[6].color = color;
		vertices[7].position = D3DXVECTOR3(-size, size, -size);
		vertices[7].color = color;

		toFirst = D3DXVECTOR3(vertices[7].position - vertices[4].position);
		toSecond = D3DXVECTOR3(vertices[5].position - vertices[4].position);
		D3DXVec3Cross(&vertices[4].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[4].normal, &vertices[4].normal);
		toFirst = D3DXVECTOR3(vertices[4].position - vertices[5].position);
		toSecond = D3DXVECTOR3(vertices[6].position - vertices[5].position);
		D3DXVec3Cross(&vertices[5].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[5].normal, &vertices[5].normal);
		toFirst = D3DXVECTOR3(vertices[5].position - vertices[6].position);
		toSecond = D3DXVECTOR3(vertices[7].position - vertices[6].position);
		D3DXVec3Cross(&vertices[6].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[6].normal, &vertices[6].normal);
		toFirst = D3DXVECTOR3(vertices[6].position - vertices[7].position);
		toSecond = D3DXVECTOR3(vertices[4].position - vertices[7].position);
		D3DXVec3Cross(&vertices[7].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[7].normal, &vertices[7].normal);

		vertices[8].position = D3DXVECTOR3(-size, size, -size);
		vertices[8].color = color;
		vertices[9].position = D3DXVECTOR3(size, size, -size);
		vertices[9].color = color;
		vertices[10].position = D3DXVECTOR3(size, size, size);
		vertices[10].color = color;
		vertices[11].position = D3DXVECTOR3(-size, size, size);
		vertices[11].color = color;

		toFirst = D3DXVECTOR3(vertices[11].position - vertices[8].position);
		toSecond = D3DXVECTOR3(vertices[9].position - vertices[8].position);
		D3DXVec3Cross(&vertices[8].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[8].normal, &vertices[8].normal);
		toFirst = D3DXVECTOR3(vertices[8].position - vertices[9].position);
		toSecond = D3DXVECTOR3(vertices[10].position - vertices[9].position);
		D3DXVec3Cross(&vertices[9].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[9].normal, &vertices[9].normal);
		toFirst = D3DXVECTOR3(vertices[9].position - vertices[10].position);
		toSecond = D3DXVECTOR3(vertices[11].position - vertices[10].position);
		D3DXVec3Cross(&vertices[10].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[10].normal, &vertices[10].normal);
		toFirst = D3DXVECTOR3(vertices[10].position - vertices[11].position);
		toSecond = D3DXVECTOR3(vertices[8].position - vertices[11].position);
		D3DXVec3Cross(&vertices[11].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[11].normal, &vertices[11].normal);

		vertices[12].position = D3DXVECTOR3(-size, size, -size);
		vertices[12].color = color;
		vertices[13].position = D3DXVECTOR3(-size, size, size);
		vertices[13].color = color;
		vertices[14].position = D3DXVECTOR3(-size, -size, size);
		vertices[14].color = color;
		vertices[15].position = D3DXVECTOR3(-size, -size, -size);
		vertices[15].color = color;

		toFirst = D3DXVECTOR3(vertices[15].position - vertices[12].position);
		toSecond = D3DXVECTOR3(vertices[13].position - vertices[12].position);
		D3DXVec3Cross(&vertices[12].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[12].normal, &vertices[12].normal);
		toFirst = D3DXVECTOR3(vertices[12].position - vertices[13].position);
		toSecond = D3DXVECTOR3(vertices[14].position - vertices[13].position);
		D3DXVec3Cross(&vertices[13].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[13].normal, &vertices[13].normal);
		toFirst = D3DXVECTOR3(vertices[13].position - vertices[14].position);
		toSecond = D3DXVECTOR3(vertices[15].position - vertices[14].position);
		D3DXVec3Cross(&vertices[14].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[14].normal, &vertices[14].normal);
		toFirst = D3DXVECTOR3(vertices[14].position - vertices[15].position);
		toSecond = D3DXVECTOR3(vertices[12].position - vertices[15].position);
		D3DXVec3Cross(&vertices[15].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[15].normal, &vertices[15].normal);

		vertices[16].position = D3DXVECTOR3(size, size, size);
		vertices[16].color = color;
		vertices[17].position = D3DXVECTOR3(size, size, -size);
		vertices[17].color = color;
		vertices[18].position = D3DXVECTOR3(size, -size, -size);
		vertices[18].color = color;
		vertices[19].position = D3DXVECTOR3(size, -size, size);
		vertices[19].color = color;

		toFirst = D3DXVECTOR3(vertices[19].position - vertices[16].position);
		toSecond = D3DXVECTOR3(vertices[17].position - vertices[16].position);
		D3DXVec3Cross(&vertices[16].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[16].normal, &vertices[16].normal);
		toFirst = D3DXVECTOR3(vertices[16].position - vertices[17].position);
		toSecond = D3DXVECTOR3(vertices[18].position - vertices[17].position);
		D3DXVec3Cross(&vertices[17].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[17].normal, &vertices[17].normal);
		toFirst = D3DXVECTOR3(vertices[17].position - vertices[18].position);
		toSecond = D3DXVECTOR3(vertices[19].position - vertices[18].position);
		D3DXVec3Cross(&vertices[18].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[18].normal, &vertices[18].normal);
		toFirst = D3DXVECTOR3(vertices[18].position - vertices[19].position);
		toSecond = D3DXVECTOR3(vertices[16].position - vertices[19].position);
		D3DXVec3Cross(&vertices[19].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[19].normal, &vertices[19].normal);

		vertices[20].position = D3DXVECTOR3(-size, -size, size);
		vertices[20].color = color;
		vertices[21].position = D3DXVECTOR3(size, -size, size);
		vertices[21].color = color;
		vertices[22].position = D3DXVECTOR3(size, -size, -size);
		vertices[22].color = color;
		vertices[23].position = D3DXVECTOR3(-size, -size, -size);
		vertices[23].color = color;

		toFirst = D3DXVECTOR3(vertices[23].position - vertices[20].position);
		toSecond = D3DXVECTOR3(vertices[21].position - vertices[20].position);
		D3DXVec3Cross(&vertices[20].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[20].normal, &vertices[20].normal);
		toFirst = D3DXVECTOR3(vertices[20].position - vertices[21].position);
		toSecond = D3DXVECTOR3(vertices[22].position - vertices[21].position);
		D3DXVec3Cross(&vertices[21].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[21].normal, &vertices[21].normal);
		toFirst = D3DXVECTOR3(vertices[21].position - vertices[22].position);
		toSecond = D3DXVECTOR3(vertices[23].position - vertices[22].position);
		D3DXVec3Cross(&vertices[22].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[22].normal, &vertices[22].normal);
		toFirst = D3DXVECTOR3(vertices[22].position - vertices[23].position);
		toSecond = D3DXVECTOR3(vertices[20].position - vertices[23].position);
		D3DXVec3Cross(&vertices[23].normal, &toFirst, &toSecond);
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

		indices[30] = 22;
		indices[31] = 21;
		indices[32] = 20;
		indices[33] = 20;
		indices[34] = 23;
		indices[35] = 22;

		return new Direct3D10Mesh(device, vertices, indices);
	}

	Direct3D10Mesh* loadObj(ID3D10Device& device, const string& fileName, const D3DXCOLOR& color)
	{
		return loadObj(device, fileName, color, 1.0f);
	}

	Direct3D10Mesh* loadObj(ID3D10Device& device, const std::string& fileName, const D3DXCOLOR& color, float scale)
	{
		vector<Vertex> vertices;

		loadObj(fileName, color, scale, vertices, 0, 0, 0, 0);

		return new Direct3D10Mesh(device, vertices);
	}

	void loadObj(const string& fileName, const D3DXCOLOR& color, float scale, vector<Vertex>& vertices,
		unsigned int normalCount, unsigned int positionCount, unsigned int texCoordCount, unsigned int vertexCount)
	{
		vertices.reserve(vertexCount);

		ifstream inputFileStream(fileName.c_str());
		if (inputFileStream.fail())
		{
			throw exception();
		}

		char* rawSplit = new char[MAX_SPLIT_LENGTH];

        vector<string> lines = splitString(rawSplit, inputFileStream, '\n',
			normalCount + positionCount + texCoordCount + vertexCount / 3 + 50);

        vector<vector<string> > faces;
		faces.reserve(vertexCount / 3);
        vector<D3DXVECTOR3> normals;
		normals.reserve(normalCount);
        vector<D3DXVECTOR3> positions;
		positions.reserve(positionCount);
        vector<D3DXVECTOR2> texCoords;
		texCoords.reserve(texCoordCount);

        for (unsigned int lineIndex = 0; lineIndex < lines.size(); lineIndex++)
        {
			if (lines[lineIndex].empty())
			{
				continue;
			}

			istringstream inputLineStream(lines[lineIndex]);
			vector<string> splitLine = splitString(rawSplit, inputLineStream, ' ', 4);

            if (splitLine[0] == "v")
            {
				D3DXVECTOR3 position(
					(float) atof(splitLine[1].c_str()) * scale,
					(float) atof(splitLine[2].c_str()) * scale,
					(float) atof(splitLine[3].c_str()) * scale);
                positions.push_back(position);
            }
            else if (splitLine[0] == "vn")
            {
                D3DXVECTOR3 normal(
					(float) atof(splitLine[1].c_str()),
					(float) atof(splitLine[2].c_str()),
					(float) atof(splitLine[3].c_str()));
                normals.push_back(normal);
            }
            else if (splitLine[0] == "vt")
            {
                D3DXVECTOR2 texCoord(
					(float) atof(splitLine[1].c_str()),
					1.0f - (float) atof(splitLine[2].c_str()));
                texCoords.push_back(texCoord);
            }
            else if (splitLine[0] == "f")
            {
                faces.push_back(splitLine);
            }
        }

        // Read the faces from the file and populate the arrays.
        for (unsigned int faceIndex = 0; faceIndex < faces.size(); faceIndex++)
        {
			vector<string> face = faces[faceIndex];

            for (unsigned int vertexIndex = 1; vertexIndex < face.size() - 1; vertexIndex++)
            {
				istringstream inputFaceStream(face[vertexIndex]);
				vector<string> splitVertex = splitString(rawSplit, inputFaceStream, '/', 3);

				Vertex vertex;
				vertex.color = color;

				if (!normals.empty())
				{
					vertex.normal = normals[atoi(splitVertex[2].c_str()) - 1];
				}

                vertex.position = positions[atoi(splitVertex[0].c_str()) - 1];

				if (!texCoords.empty())
				{
					vertex.texCoord = texCoords[atoi(splitVertex[1].c_str()) - 1];
				}

				vertices.push_back(vertex);
            }

			// Create face normals if none were provided.
			if (normals.empty())
			{
				unsigned int vertexCount = vertices.size();

				D3DXVECTOR3 edge0 = vertices[vertexCount - 1].position - vertices[vertexCount - 2].position;
				D3DXVECTOR3 edge1 = vertices[vertexCount - 1].position - vertices[vertexCount - 3].position;
				D3DXVECTOR3 faceNormal;
				D3DXVec3Cross(&faceNormal, &edge0, &edge1);
				D3DXVec3Normalize(&faceNormal, &faceNormal);

				vertices[vertexCount - 1].normal = faceNormal;
				vertices[vertexCount - 2].normal = faceNormal;
				vertices[vertexCount - 3].normal = faceNormal;
			}
        }

		delete rawSplit;
	}
	
	void scaleVertices(vector<Vertex>& vertices, float scale)
	{
		for (unsigned int index = 0; index < vertices.size(); index++)
		{
			vertices[index].position *= scale;
		}
	}

	vector<string> splitString(char* rawSplit, istream& source, char delimiter, unsigned int estimatedSplitCount)
	{
		vector<string> splits;
		splits.reserve(estimatedSplitCount);

		while (!source.eof())
		{
			source.getline(rawSplit, MAX_SPLIT_LENGTH, delimiter);
			splits.push_back(rawSplit);
		}

		return splits;
	}
}
