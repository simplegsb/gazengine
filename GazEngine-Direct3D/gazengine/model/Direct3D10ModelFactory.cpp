#include "Direct3D10Mesh.h"
#include "Direct3D10ModelFactory.h"

using namespace std;

Direct3D10ModelFactory::Direct3D10ModelFactory(ID3D10Device& device) :
	device(device)
{
}

Mesh* Direct3D10ModelFactory::createMesh(const vector<Vertex>& vertices)
{
	vector<int> indices;
	indices.reserve(vertices.size());
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		indices.push_back(index);
	}

	return createMesh(vertices, indices);
}

Mesh* Direct3D10ModelFactory::createMesh(const vector<Vertex>& vertices, const vector<int>& indices)
{
	return new Direct3D10Mesh(device, vertices, indices);
}
