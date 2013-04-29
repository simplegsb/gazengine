#include "stdafx.h"

#include "GDIMesh.h"
#include "GDIQuadTree.h"

using namespace std;

GDIQuadTree::GDIQuadTree(HDC buffer, const QuadTree& quadTree) :
	buffer(buffer), quadTree(quadTree)
{
}

GDIQuadTree::~GDIQuadTree()
{
}

void GDIQuadTree::draw()
{
	draw(quadTree);
}

void GDIQuadTree::draw(const QuadTree& quadTree)
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

	GDIMesh mesh(buffer, vertices, RGB(50, 50, 50));
	mesh.draw();

	for (unsigned int index = 0; index < quadTree.getChildren().size(); index++)
	{
		draw(*quadTree.getChildren().at(index));
	}
}

Model::PrimitiveType GDIQuadTree::getPrimitiveType() const
{
	return Model::NA;
}
