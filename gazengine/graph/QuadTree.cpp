#include "stdafx.h"

#include <algorithm>

#include "../math/Intersection.h"
#include "../model/Circle.h"
#include "QuadTree.h"

using namespace std;

QuadTree::QuadTree(unsigned int subdivideThreshold, const AABB2& boundary) :
	boundary(boundary), children(), models(), subdivideThreshold(subdivideThreshold)
{
	children.reserve(4);
}

QuadTree::~QuadTree()
{
	for (unsigned int index = 0; index < children.size(); index++)
	{
		delete children.at(index);
	}

	for (unsigned int index = 0; index < models.size(); index++)
	{
		delete models.at(index);
	}
}

void QuadTree::addModelFromChild()
{
	for (unsigned int index = 0; index < children.size(); index++)
	{
		if (!children.at(index)->getModels().empty())
		{
			Model* model = children.at(index)->getModels().at(0);
			children.at(index)->remove(*model);
			models.push_back(model);
			return;
		}
	}
}

bool QuadTree::contains(const Model& model) const
{
	const Circle* circle = dynamic_cast<const Circle*>(&model);
	if (circle == NULL)
	{
		return false;
	}

	return Intersection::contains(boundary, *circle);
}

const AABB2& QuadTree::getBoundary() const
{
	return boundary;
}

const vector<QuadTree*>& QuadTree::getChildren() const
{
	return children;
}

const vector<Model*>& QuadTree::getModels() const
{
	return models;
}

bool QuadTree::insert(Model* model)
{
	if (!contains(*model))
	{
		return false;
	}

	if (models.size() == subdivideThreshold && children.empty())
	{
		subdivide();
	}

	bool addedToChild = false;
	for (unsigned int index = 0; index < children.size(); index++)
	{
		if (children.at(index)->insert(model))
		{
			addedToChild = true;
			break;
		}
	}

	if (!addedToChild)
	{
		models.push_back(model);
	}

	return true;
}

vector<Model*> QuadTree::queryRange(const AABB2& range) const
{
	vector<Model*> queryResult;

	if (!Intersection::intersect(boundary, range))
	{
		return queryResult;
	}

	for (unsigned int index = 0; index < models.size(); index++)
	{
		Circle* circle = dynamic_cast<Circle*>(models.at(index));
		if (circle != NULL)
		{
			if (Intersection::intersect(range, *circle))
			{
				queryResult.push_back(circle);
			}
		}
	}

	for (unsigned int index = 0; index < children.size(); index++)
	{
		vector<Model*> childResult = children.at(index)->queryRange(range);
		queryResult.insert(queryResult.end(), childResult.begin(), childResult.end());
	}

	return queryResult;
}

bool QuadTree::remove(const Model& model)
{
	if (find(models.begin(), models.end(), &model) == models.end())
	{
		for (unsigned int index = 0; index < children.size(); index++)
		{
			if (children.at(index)->remove(model))
			{
				return true;
			}
		}

		return false;
	}

	models.erase(std::remove(models.begin(), models.end(), &model));

	if (models.size() < subdivideThreshold)
	{
		addModelFromChild();
	}

	if (models.size() < subdivideThreshold)
	{
		children.clear();
	}

	return true;
}

void QuadTree::subdivide()
{
	float childHalfDimension = boundary.halfDimension / 2.0f;

	AABB2 boundary0;
	boundary0.center = boundary.center;
	boundary0.halfDimension = childHalfDimension;
	boundary0.center.x -= childHalfDimension;
	boundary0.center.y += childHalfDimension;
	children.push_back(new QuadTree(subdivideThreshold, boundary0));

	AABB2 boundary1;
	boundary1.center = boundary.center;
	boundary1.halfDimension = childHalfDimension;
	boundary1.center.x += childHalfDimension;
	boundary1.center.y += childHalfDimension;
	children.push_back(new QuadTree(subdivideThreshold, boundary1));

	AABB2 boundary2;
	boundary2.center = boundary.center;
	boundary2.halfDimension = childHalfDimension;
	boundary2.center.x -= childHalfDimension;
	boundary2.center.y -= childHalfDimension;
	children.push_back(new QuadTree(subdivideThreshold, boundary2));

	AABB2 boundary3;
	boundary3.center = boundary.center;
	boundary3.halfDimension = childHalfDimension;
	boundary3.center.x += childHalfDimension;
	boundary3.center.y -= childHalfDimension;
	children.push_back(new QuadTree(subdivideThreshold, boundary3));
}

void QuadTree::update(Model& model)
{
	remove(model);
	insert(&model);
}
