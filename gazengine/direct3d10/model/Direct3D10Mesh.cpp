#include "stdafx.h"

#include "Direct3D10Mesh.h"

using namespace std;

Direct3D10Mesh::Direct3D10Mesh(const Direct3D10Mesh& original) :
	device(original.device),
	mesh(NULL),
	shader(NULL),
	transformation()
{
	operator=(original);
}

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices) :
	device(device),
	mesh(NULL),
	shader(NULL),
	transformation()
{
	vector<DWORD> indices;
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		indices.push_back(index);
	}

	init(vertices, indices);
}

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const vector<Vertex>& vertices, const vector<DWORD>& indices) :
	device(device),
	mesh(NULL),
	shader(NULL),
	transformation()
{
	init(vertices, indices);
}

Direct3D10Mesh::~Direct3D10Mesh()
{
	if (mesh != NULL)
	{
		mesh->Release();
	}

	if (shader != NULL)
	{
		delete shader;
	}
}

void Direct3D10Mesh::draw()
{
	mesh->DrawSubset(0);
}

Model::PrimitiveType Direct3D10Mesh::getPrimitiveType() const
{
	return Model::TRIANGLE_LIST;
}

Direct3D10Shader* Direct3D10Mesh::getShader() const
{
	return shader;
}
		
D3DXMATRIX Direct3D10Mesh::getTransformation() const
{
	return transformation;
}

void Direct3D10Mesh::init(const vector<Vertex>& vertices, const vector<DWORD>& indices)
{
	D3D10_INPUT_ELEMENT_DESC vertexDescription[] =
	{
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};

	D3DX10CreateMesh(&device, vertexDescription, 4, "POSITION", vertices.size(), vertices.size() / 3,
		D3DX10_MESH_32_BIT, &mesh);
	
	mesh->SetVertexData(0, &vertices[0]);
	mesh->SetIndexData(&indices[0], indices.size());

	mesh->CommitToDevice();
}

Direct3D10Mesh& Direct3D10Mesh::operator=(const Direct3D10Mesh& original)
{
	D3D10_INPUT_ELEMENT_DESC vertexDescription[] =
	{
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};

	if (mesh != NULL)
	{
		mesh->Release();
	}

	original.mesh->CloneMesh(original.mesh->GetFlags(), "POSITION", vertexDescription, 4, &mesh);

	return *this;
}

void Direct3D10Mesh::setTransformation(const D3DXMATRIX& transformation)
{
	this->transformation = transformation;
}

void Direct3D10Mesh::setShader(Direct3D10Shader* shader)
{
	this->shader = shader;
}
