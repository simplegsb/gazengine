#include "SimpleMesh.h"

using namespace std;

SimpleMesh::SimpleMesh() :
	colour(0.0f, 0.0f, 0.0f, 1.0f),
	indices(),
	position(0.0f, 0.0f),
	primitiveType(TRIANGLE_LIST),
	vertices(),
	visible(true)
{
}

SimpleMesh::SimpleMesh(const vector<int>& indices, const vector<Vertex>& vertices) :
	colour(0.0f, 0.0f, 0.0f, 1.0f),
	indices(indices),
	position(0.0f, 0.0f),
	primitiveType(TRIANGLE_LIST),
	vertices(vertices),
	visible(true)
{
}

const Vector4& SimpleMesh::getColour() const
{
	return colour;
}

vector<int>& SimpleMesh::getIndices()
{
	return indices;
}

const vector<int>& SimpleMesh::getIndices() const
{
	return indices;
}

Texture* SimpleMesh::getNormalMap() const
{
	return NULL;
}

const Vector2& SimpleMesh::getPosition() const
{
	return position;
}

Model::PrimitiveType SimpleMesh::getPrimitiveType() const
{
	return primitiveType;
}

Texture* SimpleMesh::getTexture() const
{
	return NULL;
}

vector<Vertex>& SimpleMesh::getVertices()
{
	return vertices;
}

const vector<Vertex>& SimpleMesh::getVertices() const
{
	return vertices;
}

bool SimpleMesh::isVisible() const
{
	return visible;
}

void SimpleMesh::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void SimpleMesh::setColour(const Vector4& colour)
{
	this->colour = colour;
}

void SimpleMesh::setNormalMap(Texture*)
{
}

void SimpleMesh::setPosition(const Vector2& position)
{
	this->position = position;
}

void SimpleMesh::setPrimitiveType(PrimitiveType)
{
	this->primitiveType = primitiveType;
}

void SimpleMesh::setTexture(Texture*)
{
}

void SimpleMesh::setVisible(bool visible)
{
	this->visible = visible;
}
