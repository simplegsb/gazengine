#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <vector>

#include "../model/Model.h"
#include "AABB2.h"

class QuadTree
{
	public:
		QuadTree(unsigned int subdivideThreshold, const AABB2& boundary);

		~QuadTree();

		const AABB2& getBoundary() const;

		const std::vector<QuadTree*>& getChildren() const;

		const std::vector<Model*>& getModels() const;

		bool insert(Model* model);

		std::vector<Model*> queryRange(const AABB2& range) const;

		bool remove(const Model& model);

		void update(Model& model);

	private:
		AABB2 boundary;

		std::vector<QuadTree*> children;

		std::vector<Model*> models;

		unsigned int subdivideThreshold;

		void addModelFromChild();

		bool contains(const Model& model) const;

		void shiftModelsUpward();

		void subdivide();
};

#endif /* QUADTREE_H_ */
