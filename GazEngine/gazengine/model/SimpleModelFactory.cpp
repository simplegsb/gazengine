#include "SimpleMesh.h"
#include "SimpleModelFactory.h"

using namespace std;

Mesh* SimpleModelFactory::createMesh(const vector<Vertex>& vertices)
{
	vector<int> indices;
	indices.reserve(vertices.size());
	for (unsigned int index = 0; index < vertices.size(); index++)
	{
		indices.push_back(index);
	}

	return createMesh(vertices, indices);
}

Mesh* SimpleModelFactory::createMesh(const vector<Vertex>& vertices, const vector<int>& indices)
{
	return new SimpleMesh(indices, vertices);
}
