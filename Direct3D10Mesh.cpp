#include "stdafx.h"

#include "Direct3D10Mesh.h"

using namespace std;

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const vector<DWORD>& indices, const vector<Vertex>& vertices) :
	device(device), indexBuffer(NULL), indexCount(indices.size()), vertexBuffer(NULL)
{
	D3D10_BUFFER_DESC vertexBufferDescription;
    vertexBufferDescription.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vertexBufferDescription.ByteWidth = sizeof(Vertex) * vertices.size();
    vertexBufferDescription.CPUAccessFlags = 0;
    vertexBufferDescription.MiscFlags = 0;
    vertexBufferDescription.Usage = D3D10_USAGE_IMMUTABLE;

	D3D10_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = &vertices[0];

    device.CreateBuffer(&vertexBufferDescription, &vertexData, &vertexBuffer);

	D3D10_BUFFER_DESC indexBufferDescription;
    indexBufferDescription.BindFlags = D3D10_BIND_INDEX_BUFFER;
    indexBufferDescription.ByteWidth = sizeof(DWORD) * indexCount;
    indexBufferDescription.CPUAccessFlags = 0;
    indexBufferDescription.MiscFlags = 0;
    indexBufferDescription.Usage = D3D10_USAGE_IMMUTABLE;

    D3D10_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = &indices[0];

    device.CreateBuffer(&indexBufferDescription, &indexData, &indexBuffer);
}

Direct3D10Mesh::~Direct3D10Mesh()
{
	if (indexBuffer != NULL)
	{
		indexBuffer->Release();
	}

	if (vertexBuffer != NULL)
	{
		vertexBuffer->Release();
	}
}

void Direct3D10Mesh::draw()
{
	UINT offset = 0;
	UINT stride = sizeof(Vertex);

	device.IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	device.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	device.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    device.DrawIndexed(indexCount, 0, 0);
}
