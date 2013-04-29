#include "SimpleTree.h"

using namespace std;

SimpleTree::SimpleTree() :
	children(),
	model(NULL),
	parent(NULL),
	transformation()
{
	transformation.setIdentity();
}

SimpleTree::~SimpleTree()
{
	for (unsigned int index = 0; index < children.size(); index++)
	{
		delete children.at(index);
	}
}

void SimpleTree::addChild(SimpleTree* child)
{
	children.push_back(child);
	child->parent = this;
}

Matrix44 SimpleTree::getAbsoluteTransformation() const
{
	Matrix44 absoluteMatrix;
	absoluteMatrix.setIdentity();
	const SimpleTree* currentNode = this;
	while (currentNode != NULL)
	{
		absoluteMatrix = currentNode->getTransformation() * absoluteMatrix;
		currentNode = currentNode->getParent();
	}

	return absoluteMatrix;
}

vector<SimpleTree*>& SimpleTree::getChildren()
{
	return children;
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

Matrix44& SimpleTree::getTransformation()
{
	return transformation;
}

const Matrix44& SimpleTree::getTransformation() const
{
	return transformation;
}

void SimpleTree::setModel(Model* model)
{
	this->model = model;
}

void SimpleTree::setTransformation(const Matrix44& transformation)
{
	this->transformation = transformation;
}
