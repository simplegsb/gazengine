#ifndef SIMPLETREE_H_
#define SIMPLETREE_H_

#include <vector>

#include "../math/Matrix.h"
#include "../model/Model.h"
#include "Tree.h"

class SimpleTree : public Tree
{
	public:
		SimpleTree();

		~SimpleTree();

		void addChild(SimpleTree* child);

		Matrix44 getAbsoluteTransformation() const;

		const std::vector<SimpleTree*>& getChildren() const;

		Model* getModel();

		const Model* getModel() const;

		SimpleTree* getParent() const;

		Matrix44& getTransformation();

		const Matrix44& getTransformation() const;

		void setModel(Model* model);

		void setTransformation(const Matrix44& transformation);

	private:
		std::vector<SimpleTree*> children;

		Model* model;

		SimpleTree* parent;

		Matrix44 transformation;
};

#endif /* SIMPLETREE_H_ */
