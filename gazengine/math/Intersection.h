#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "../graph/AABB2.h"
#include "../model/Circle.h"

namespace Intersection
{
	bool contains(const AABB2& aabb, const Circle& circle);

	bool intersect(const AABB2& a, const AABB2& b);

	bool intersect(const AABB2& aabb, const Circle& circle);

	bool intersect(const Circle& a, const Circle& b);
}

#endif /* INTERSECTION_H_ */
