#include "GDIMesh.h"
#include "GDIQuadTree.h"

using namespace std;

GDIQuadTree::GDIQuadTree(const QuadTree& quadTree) : GDIMesh(vector<Vector2>(), RGB(50, 50, 50)),
	quadTree(quadTree), vertices()
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

		vertices.at(0).x = quadTree.getBoundary().center.x - quadTree.getBoundary().halfDimension;
		vertices.at(0).y = quadTree.getBoundary().center.y + quadTree.getBoundary().halfDimension;
		vertices.at(1).x = quadTree.getBoundary().center.x + quadTree.getBoundary().halfDimension;
		vertices.at(1).y = quadTree.getBoundary().center.y + quadTree.getBoundary().halfDimension;
		vertices.at(2).x = quadTree.getBoundary().center.x + quadTree.getBoundary().halfDimension;
		vertices.at(2).y = quadTree.getBoundary().center.y - quadTree.getBoundary().halfDimension;
		vertices.at(3).x = quadTree.getBoundary().center.x - quadTree.getBoundary().halfDimension;
		vertices.at(3).y = quadTree.getBoundary().center.y - quadTree.getBoundary().halfDimension;
		vertices.at(4).x = quadTree.getBoundary().center.x - quadTree.getBoundary().halfDimension;
		vertices.at(4).y = quadTree.getBoundary().center.y + quadTree.getBoundary().halfDimension;

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
