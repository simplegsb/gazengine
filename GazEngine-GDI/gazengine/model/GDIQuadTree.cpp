#include "GDIMesh.h"
#include "GDIQuadTree.h"

using namespace std;

GDIQuadTree::GDIQuadTree(const QuadTree& quadTree) :
	GDIMesh(vector<Vector2>(), Vector4(0.2f, 0.2f, 0.2f, 1.0f)),
	quadTree(quadTree),
	vertices()
{
}

GDIQuadTree::~GDIQuadTree()
{
}

const vector<Vector2>& GDIQuadTree::getVertices() const
{
	vertices = getVertices(quadTree);
	return vertices;
}

vector<Vector2> GDIQuadTree::getVertices(const QuadTree& quadTree) const
{
	if (quadTree.getChildren().empty())
	{
		vector<Vector2> vertices(5, Vector2());

		vertices.at(0).X() = quadTree.getBoundary().center.X() - quadTree.getBoundary().halfDimension;
		vertices.at(0).Y() = quadTree.getBoundary().center.Y() + quadTree.getBoundary().halfDimension;
		vertices.at(1).X() = quadTree.getBoundary().center.X() + quadTree.getBoundary().halfDimension;
		vertices.at(1).Y() = quadTree.getBoundary().center.Y() + quadTree.getBoundary().halfDimension;
		vertices.at(2).X() = quadTree.getBoundary().center.X() + quadTree.getBoundary().halfDimension;
		vertices.at(2).Y() = quadTree.getBoundary().center.Y() - quadTree.getBoundary().halfDimension;
		vertices.at(3).X() = quadTree.getBoundary().center.X() - quadTree.getBoundary().halfDimension;
		vertices.at(3).Y() = quadTree.getBoundary().center.Y() - quadTree.getBoundary().halfDimension;
		vertices.at(4).X() = quadTree.getBoundary().center.X() - quadTree.getBoundary().halfDimension;
		vertices.at(4).Y() = quadTree.getBoundary().center.Y() + quadTree.getBoundary().halfDimension;

		return vertices;
	}

	vector<Vector2> vertices;

	for (unsigned int index = 0; index < quadTree.getChildren().size(); index++)
	{
		vector<Vector2> childVertices = getVertices(*quadTree.getChildren().at(index));
		vertices.insert(vertices.end(), childVertices.begin(), childVertices.end());
	}

	return vertices;
}

Model::PrimitiveType GDIQuadTree::getPrimitiveType() const
{
	return Model::NA;
}
