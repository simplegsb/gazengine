#include "../math/Direct3D10Vector.h"
#include "Direct3D10Mesh.h"
#include "Direct3D10Vertex.h"

using namespace std;

Direct3D10Mesh::Direct3D10Mesh(const Direct3D10Mesh& original) :
	colour(),
	device(original.device),
	indices(),
	mesh(NULL),
	normalMap(NULL),
	texture(NULL),
	transformation(),
	vertices(),
	visible(true)
{
	operator=(original);
}

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const vector<Vertex>& vertices, const vector<int>& indices) :
	colour(0.0f, 0.0f, 0.0f, 1.0f),
	device(device),
	indices(indices),
	mesh(NULL),
	normalMap(NULL),
	texture(NULL),
	transformation(),
	vertices(vertices),
	visible(true)
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

	vector<Direct3D10Vertex> d3dVertices;
	d3dVertices.reserve(vertices.size());
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		Direct3D10Vertex d3dVertex;
		d3dVertex.color = Direct3D10Vector::toD3DXCOLOR(vertices[index].color);
		d3dVertex.normal = Direct3D10Vector::toD3DXVECTOR3(vertices[index].normal);
		d3dVertex.position = Direct3D10Vector::toD3DXVECTOR3(vertices[index].position);
		d3dVertex.texCoord = Direct3D10Vector::toD3DXVECTOR2(vertices[index].texCoord);
		d3dVertices.push_back(d3dVertex);
	}

	mesh->SetVertexData(0, &d3dVertices[0]);
	mesh->SetIndexData(&indices[0], indices.size());

	//mesh->GenerateAdjacencyAndPointReps(0.0001f);
	//mesh->Optimize(D3DX10_MESHOPT_ATTR_SORT | D3DX10_MESHOPT_VERTEX_CACHE, NULL, NULL);
	//mesh->GenerateGSAdjacency();

	mesh->CommitToDevice();
}

Direct3D10Mesh::~Direct3D10Mesh()
{
	if (mesh != NULL)
	{
		mesh->Release();
	}

	if (normalMap != NULL)
	{
		delete normalMap;
	}

	if (texture != NULL)
	{
		delete texture;
	}
}

const Vector4& Direct3D10Mesh::getColour() const
{
	return colour;
}

vector<int>& Direct3D10Mesh::getIndices()
{
	return indices;
}

const vector<int>& Direct3D10Mesh::getIndices() const
{
	return indices;
}

ID3DX10Mesh* Direct3D10Mesh::getMesh() const
{
	return mesh;
}

Texture* Direct3D10Mesh::getNormalMap() const
{
	return normalMap;
}

Model::PrimitiveType Direct3D10Mesh::getPrimitiveType() const
{
	return Model::TRIANGLE_LIST;
}

Texture* Direct3D10Mesh::getTexture() const
{
	return texture;
}

D3DXMATRIX Direct3D10Mesh::getTransformation() const
{
	return transformation;
}

vector<Vertex>& Direct3D10Mesh::getVertices()
{
	return vertices;
}

const vector<Vertex>& Direct3D10Mesh::getVertices() const
{
	return vertices;
}

bool Direct3D10Mesh::isVisible() const
{
	return visible;
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

void Direct3D10Mesh::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Direct3D10Mesh::setColour(const Vector4& colour)
{
	this->colour = colour;
}

void Direct3D10Mesh::setNormalMap(Texture* normalMap)
{
	this->normalMap = normalMap;
}

void Direct3D10Mesh::setPrimitiveType(PrimitiveType)
{
}

void Direct3D10Mesh::setTexture(Texture* texture)
{
	this->texture = texture;
}

void Direct3D10Mesh::setTransformation(const D3DXMATRIX& transformation)
{
	this->transformation = transformation;
}

void Direct3D10Mesh::setVisible(bool visible)
{
	this->visible = visible;
}
