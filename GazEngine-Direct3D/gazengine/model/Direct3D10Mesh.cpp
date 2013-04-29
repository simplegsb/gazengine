#include "Direct3D10Mesh.h"

using namespace std;

Direct3D10Mesh::Direct3D10Mesh(const Direct3D10Mesh& original) :
	colour(0.0f, 0.0f, 0.0f, 1.0f),
	device(original.device),
	mesh(NULL),
	normalMap(NULL),
	texture(NULL),
	transformation(),
	visible(true)
{
	operator=(original);
}

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices) :
	colour(0.0f, 0.0f, 0.0f, 1.0f),
	device(device),
	mesh(NULL),
	normalMap(NULL),
	texture(NULL),
	transformation()
{
	vector<DWORD> indices;
	indices.reserve(vertices.size());
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		indices.push_back(index);
	}

	init(vertices, indices);
}

Direct3D10Mesh::Direct3D10Mesh(ID3D10Device& device, const vector<Vertex>& vertices, const vector<DWORD>& indices) :
	device(device),
	mesh(NULL),
	normalMap(NULL),
	texture(NULL),
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

	//mesh->GenerateAdjacencyAndPointReps(0.0001f);
	//mesh->Optimize(D3DX10_MESHOPT_ATTR_SORT | D3DX10_MESHOPT_VERTEX_CACHE, NULL, NULL);
	//mesh->GenerateGSAdjacency();

	mesh->CommitToDevice();
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
