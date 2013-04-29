#include "stdafx.h"

#include "Direct3D10Mesh.h"
#include "Direct3D10ModelFactory.h"

using namespace std;

namespace Direct3D10ModelFactory
{
	Model* createCube(ID3D10Device& device, float size, const D3DXCOLOR& color)
	{
		// Vertices
		vector<Vertex> vertices(24);
		D3DXVECTOR3 toFirst;
		D3DXVECTOR3 toSecond;

		vertices[0].pos = D3DXVECTOR3(-size, size, size);
		vertices[0].color = color;
		vertices[1].pos = D3DXVECTOR3(size, size, size);
		vertices[1].color = color;
		vertices[2].pos = D3DXVECTOR3(size, -size, size);
		vertices[2].color = color;
		vertices[3].pos = D3DXVECTOR3(-size, -size, size);
		vertices[3].color = color;

		toFirst = D3DXVECTOR3(vertices[2].pos - vertices[0].pos);
		toSecond = D3DXVECTOR3(vertices[1].pos - vertices[0].pos);
		D3DXVec3Cross(&vertices[0].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[0].normal, &vertices[0].normal);
		toFirst = D3DXVECTOR3(vertices[3].pos - vertices[1].pos);
		toSecond = D3DXVECTOR3(vertices[2].pos - vertices[1].pos);
		D3DXVec3Cross(&vertices[1].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[1].normal, &vertices[1].normal);
		toFirst = D3DXVECTOR3(vertices[1].pos - vertices[2].pos);
		toSecond = D3DXVECTOR3(vertices[3].pos - vertices[2].pos);
		D3DXVec3Cross(&vertices[2].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[2].normal, &vertices[2].normal);
		toFirst = D3DXVECTOR3(vertices[2].pos - vertices[3].pos);
		toSecond = D3DXVECTOR3(vertices[0].pos - vertices[3].pos);
		D3DXVec3Cross(&vertices[3].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[3].normal, &vertices[3].normal);
		
		vertices[4].pos = D3DXVECTOR3(-size, -size, -size);
		vertices[4].color = color;
		vertices[5].pos = D3DXVECTOR3(size, -size, -size);
		vertices[5].color = color;
		vertices[6].pos = D3DXVECTOR3(size, size, -size);
		vertices[6].color = color;
		vertices[7].pos = D3DXVECTOR3(-size, size, -size);
		vertices[7].color = color;

		toFirst = D3DXVECTOR3(vertices[7].pos - vertices[4].pos);
		toSecond = D3DXVECTOR3(vertices[5].pos - vertices[4].pos);
		D3DXVec3Cross(&vertices[4].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[4].normal, &vertices[4].normal);
		toFirst = D3DXVECTOR3(vertices[4].pos - vertices[5].pos);
		toSecond = D3DXVECTOR3(vertices[6].pos - vertices[5].pos);
		D3DXVec3Cross(&vertices[5].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[5].normal, &vertices[5].normal);
		toFirst = D3DXVECTOR3(vertices[5].pos - vertices[6].pos);
		toSecond = D3DXVECTOR3(vertices[7].pos - vertices[6].pos);
		D3DXVec3Cross(&vertices[6].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[6].normal, &vertices[6].normal);
		toFirst = D3DXVECTOR3(vertices[6].pos - vertices[7].pos);
		toSecond = D3DXVECTOR3(vertices[4].pos - vertices[7].pos);
		D3DXVec3Cross(&vertices[7].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[7].normal, &vertices[7].normal);

		vertices[8].pos = D3DXVECTOR3(-size, size, -size);
		vertices[8].color = color;
		vertices[9].pos = D3DXVECTOR3(size, size, -size);
		vertices[9].color = color;
		vertices[10].pos = D3DXVECTOR3(size, size, size);
		vertices[10].color = color;
		vertices[11].pos = D3DXVECTOR3(-size, size, size);
		vertices[11].color = color;

		toFirst = D3DXVECTOR3(vertices[11].pos - vertices[8].pos);
		toSecond = D3DXVECTOR3(vertices[9].pos - vertices[8].pos);
		D3DXVec3Cross(&vertices[8].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[8].normal, &vertices[8].normal);
		toFirst = D3DXVECTOR3(vertices[8].pos - vertices[9].pos);
		toSecond = D3DXVECTOR3(vertices[10].pos - vertices[9].pos);
		D3DXVec3Cross(&vertices[9].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[9].normal, &vertices[9].normal);
		toFirst = D3DXVECTOR3(vertices[9].pos - vertices[10].pos);
		toSecond = D3DXVECTOR3(vertices[11].pos - vertices[10].pos);
		D3DXVec3Cross(&vertices[10].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[10].normal, &vertices[10].normal);
		toFirst = D3DXVECTOR3(vertices[10].pos - vertices[11].pos);
		toSecond = D3DXVECTOR3(vertices[8].pos - vertices[11].pos);
		D3DXVec3Cross(&vertices[11].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[11].normal, &vertices[11].normal);

		vertices[12].pos = D3DXVECTOR3(-size, size, -size);
		vertices[12].color = color;
		vertices[13].pos = D3DXVECTOR3(-size, size, size);
		vertices[13].color = color;
		vertices[14].pos = D3DXVECTOR3(-size, -size, size);
		vertices[14].color = color;
		vertices[15].pos = D3DXVECTOR3(-size, -size, -size);
		vertices[15].color = color;

		toFirst = D3DXVECTOR3(vertices[15].pos - vertices[12].pos);
		toSecond = D3DXVECTOR3(vertices[13].pos - vertices[12].pos);
		D3DXVec3Cross(&vertices[12].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[12].normal, &vertices[12].normal);
		toFirst = D3DXVECTOR3(vertices[12].pos - vertices[13].pos);
		toSecond = D3DXVECTOR3(vertices[14].pos - vertices[13].pos);
		D3DXVec3Cross(&vertices[13].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[13].normal, &vertices[13].normal);
		toFirst = D3DXVECTOR3(vertices[13].pos - vertices[14].pos);
		toSecond = D3DXVECTOR3(vertices[15].pos - vertices[14].pos);
		D3DXVec3Cross(&vertices[14].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[14].normal, &vertices[14].normal);
		toFirst = D3DXVECTOR3(vertices[14].pos - vertices[15].pos);
		toSecond = D3DXVECTOR3(vertices[12].pos - vertices[15].pos);
		D3DXVec3Cross(&vertices[15].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[15].normal, &vertices[15].normal);

		vertices[16].pos = D3DXVECTOR3(size, size, size);
		vertices[16].color = color;
		vertices[17].pos = D3DXVECTOR3(size, size, -size);
		vertices[17].color = color;
		vertices[18].pos = D3DXVECTOR3(size, -size, -size);
		vertices[18].color = color;
		vertices[19].pos = D3DXVECTOR3(size, -size, size);
		vertices[19].color = color;

		toFirst = D3DXVECTOR3(vertices[19].pos - vertices[16].pos);
		toSecond = D3DXVECTOR3(vertices[17].pos - vertices[16].pos);
		D3DXVec3Cross(&vertices[16].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[16].normal, &vertices[16].normal);
		toFirst = D3DXVECTOR3(vertices[16].pos - vertices[17].pos);
		toSecond = D3DXVECTOR3(vertices[18].pos - vertices[17].pos);
		D3DXVec3Cross(&vertices[17].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[17].normal, &vertices[17].normal);
		toFirst = D3DXVECTOR3(vertices[17].pos - vertices[18].pos);
		toSecond = D3DXVECTOR3(vertices[19].pos - vertices[18].pos);
		D3DXVec3Cross(&vertices[18].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[18].normal, &vertices[18].normal);
		toFirst = D3DXVECTOR3(vertices[18].pos - vertices[19].pos);
		toSecond = D3DXVECTOR3(vertices[16].pos - vertices[19].pos);
		D3DXVec3Cross(&vertices[19].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[19].normal, &vertices[19].normal);

		vertices[20].pos = D3DXVECTOR3(-size, -size, size);
		vertices[20].color = color;
		vertices[21].pos = D3DXVECTOR3(size, -size, size);
		vertices[21].color = color;
		vertices[22].pos = D3DXVECTOR3(size, -size, -size);
		vertices[22].color = color;
		vertices[23].pos = D3DXVECTOR3(-size, -size, -size);
		vertices[23].color = color;

		toFirst = D3DXVECTOR3(vertices[23].pos - vertices[20].pos);
		toSecond = D3DXVECTOR3(vertices[21].pos - vertices[20].pos);
		D3DXVec3Cross(&vertices[20].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[20].normal, &vertices[20].normal);
		toFirst = D3DXVECTOR3(vertices[20].pos - vertices[21].pos);
		toSecond = D3DXVECTOR3(vertices[22].pos - vertices[21].pos);
		D3DXVec3Cross(&vertices[21].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[21].normal, &vertices[21].normal);
		toFirst = D3DXVECTOR3(vertices[21].pos - vertices[22].pos);
		toSecond = D3DXVECTOR3(vertices[23].pos - vertices[22].pos);
		D3DXVec3Cross(&vertices[22].normal, &toFirst, &toSecond);
		D3DXVec3Normalize(&vertices[22].normal, &vertices[22].normal);
		toFirst = D3DXVECTOR3(vertices[22].pos - vertices[23].pos);
		toSecond = D3DXVECTOR3(vertices[20].pos - vertices[23].pos);
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

		indices[30] = 18;
		indices[31] = 17;
		indices[32] = 16;
		indices[33] = 16;
		indices[34] = 19;
		indices[35] = 18;

		return new Direct3D10Mesh(device, indices, vertices);
	}
}