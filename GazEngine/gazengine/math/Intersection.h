#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "../graph/AABB2.h"
#include "../model/Plane.h"
#include "../model/shape/Circle.h"

namespace Intersection
{
	enum RelativePosition
	{
		BEHIND,
		INFRONT,
		ON_PLANE
	};

	bool contains(const AABB2& aabb, const Circle& circle);

	float getIntersectionTime(const Vector2& lineSegmentStart, const Vector2& lineSegmentFinish,
			const Plane& plane);

	bool intersect(const AABB2& a, const AABB2& b);

	bool intersect(const AABB2& aabb, const Circle& circle);

	bool intersect(const Circle& a, const Circle& b);

	bool intersect(const Plane& plane, const std::vector<Vector3>& triangle);

	RelativePosition intersect(const Plane& plane, const Vector3& point);

	bool intersect(const Plane& plane, const Vector3& lineSegmentStart, const Vector3& lineSegmentFinish);
}

#endif /* INTERSECTION_H_ */
