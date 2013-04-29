#ifndef GDIQUADTREE_H_
#define GDIQUADTREE_H_

#include <windows.h>

#include "../../graph/QuadTree.h"
#include "../../model/Model.h"

class GDIQuadTree : public Model
{
	public:
		GDIQuadTree(HDC buffer, const QuadTree& quadTree);

		virtual ~GDIQuadTree();
		
		void draw();
		
		PrimitiveType getPrimitiveType() const;

	private:
		HDC buffer;

		const QuadTree& quadTree;

		GDIQuadTree(const GDIQuadTree& original);

		void draw(const QuadTree& quadTree);

		GDIQuadTree& operator=(const GDIQuadTree& original);
};

#endif /* GDIQUADTREE_H_ */
