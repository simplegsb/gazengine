#ifndef SIMPLETREE_H_
#define SIMPLETREE_H_

#include <vector>

#include "d3dx10.h"

#include "../model/Model.h"

class SimpleTree
{
	public:
		SimpleTree();

		~SimpleTree();

		void addChild(SimpleTree* child);

		D3DXMATRIX getAbsoluteTransformation() const;

		const std::vector<SimpleTree*>& getChildren() const;

		Model* getModel();

		const Model* getModel() const;

		SimpleTree* getParent() const;

		const D3DXMATRIX& getTransformation() const;

		void setModel(Model* model);

		void setTransformation(const D3DXMATRIX& transformation);

	private:
		std::vector<SimpleTree*> children;

		Model* model;

		SimpleTree* parent;

		D3DXMATRIX transformation;
};

#endif /* SIMPLETREE_H_ */
