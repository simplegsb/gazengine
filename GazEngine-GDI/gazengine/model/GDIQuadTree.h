#ifndef GDIQUADTREE_H_
#define GDIQUADTREE_H_

#include <windows.h>

#include <gazengine/graph/QuadTree.h>

#include "GDIMesh.h"

class GDIQuadTree : public GDIMesh
{
	public:
		GDIQuadTree(const QuadTree& quadTree);

		virtual ~GDIQuadTree();
		
		PrimitiveType getPrimitiveType() const;

		const std::vector<Vector2>& getVertices() const;

	private:
		const QuadTree& quadTree;

		mutable std::vector<Vector2> vertices;

		GDIQuadTree(const GDIQuadTree& original);

		std::vector<Vector2> getVertices(const QuadTree& quadTree) const;

		GDIQuadTree& operator=(const GDIQuadTree& original);
};

#endif /* GDIQUADTREE_H_ */
