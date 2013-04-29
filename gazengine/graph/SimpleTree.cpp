#include "stdafx.h"

#include <stack>

#include "SimpleTree.h"

using namespace std;

SimpleTree::SimpleTree() :
	children(),
	model(NULL),
	parent(NULL),
	transformation()
{
	D3DXMatrixIdentity(&transformation);
}

SimpleTree::~SimpleTree()
{
	for (unsigned int index = 0; index < children.size(); index++)
	{
		delete children.at(index);
	}

	if (model != NULL)
	{
		delete model;
	}
}

void SimpleTree::addChild(SimpleTree* child)
{
	children.push_back(child);
	child->parent = this;
}

D3DXMATRIX SimpleTree::getAbsoluteTransformation() const
{
	stack<D3DXMATRIX> matrices;

	const SimpleTree* currentNode = this;
	while (currentNode != NULL)
	{
		matrices.push(currentNode->getTransformation());
		currentNode = currentNode->getParent();
	}

	D3DXMATRIX absoluteMatrix;
	D3DXMatrixIdentity(&absoluteMatrix);
	while (!matrices.empty())
	{
		absoluteMatrix *= matrices.top();
		matrices.pop();
	}

	return absoluteMatrix;
}

const vector<SimpleTree*>& SimpleTree::getChildren() const
{
	return children;
}

Model* SimpleTree::getModel()
{
	return model;
}

const Model* SimpleTree::getModel() const
{
	return model;
}

SimpleTree* SimpleTree::getParent() const
{
	return parent;
}

const D3DXMATRIX& SimpleTree::getTransformation() const
{
	return transformation;
}

void SimpleTree::setModel(Model* model)
{
	this->model = model;
}

void SimpleTree::setTransformation(const D3DXMATRIX& transformation)
{
	this->transformation = transformation;
}
