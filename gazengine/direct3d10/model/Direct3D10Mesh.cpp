#include "stdafx.h"

#include "Direct3D10Mesh.h"

using namespace std;

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices) :
	device(device), indexBuffer(NULL), indexCount(vertices.size()), vertexBuffer(NULL)
{
	vector<DWORD> indices;
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		indices.push_back(index);
	}

	init(vertices, indices);
}

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const vector<Vertex>& vertices, const vector<DWORD>& indices) :
	device(device), indexBuffer(NULL), indexCount(indices.size()), vertexBuffer(NULL)
{
	init(vertices, indices);
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

	device.IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
	device.IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	device.IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    device.DrawIndexed(indexCount, 0, 0);
}

Model::PrimitiveType Direct3D10Mesh::getPrimitiveType() const
{
	return Model::TRIANGLE_LIST;
}

void Direct3D10Mesh::init(const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices)
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
