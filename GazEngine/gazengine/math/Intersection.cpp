#include "MathFunctions.h"
#include "Intersection.h"

using namespace std;

namespace Intersection
{
	bool contains(const AABB2& aabb, const Circle& circle)
	{
		float aabbMaxX = aabb.center.X() + aabb.halfDimension;
		float aabbMinX = aabb.center.X() - aabb.halfDimension;
		float aabbMaxY = aabb.center.Y() + aabb.halfDimension;
		float aabbMinY = aabb.center.Y() - aabb.halfDimension;

		float circleMaxX = circle.getPosition().X() + circle.getRadius();
		float circleMinX = circle.getPosition().X() - circle.getRadius();
		float circleMaxY = circle.getPosition().Y() + circle.getRadius();
		float circleMinY = circle.getPosition().Y() - circle.getRadius();

		if (circleMaxX <= aabbMaxX && circleMinX >= aabbMinX &&
			circleMaxY <= aabbMaxY && circleMinY >= aabbMinY)
		{
			return true;
		}

		return false;
	}

	float getIntersectionTime(const Vector3& lineSegmentStart, const Vector3& lineSegmentFinish,
			const Plane& plane)
	{
		return dotProduct(plane.getNormal(), plane.getPositionOnPlane() - lineSegmentStart) /
			dotProduct(plane.getNormal(), lineSegmentFinish - lineSegmentStart);
	}

	bool intersect(const AABB2& a, const AABB2& b)
	{
		float aMaxX = a.center.X() + a.halfDimension;
		float aMinX = a.center.X() - a.halfDimension;
		float aMaxY = a.center.Y() + a.halfDimension;
		float aMinY = a.center.Y() - a.halfDimension;

		float bMaxX = b.center.X() + b.halfDimension;
		float bMinX = b.center.X() - b.halfDimension;
		float bMaxY = b.center.Y() + b.halfDimension;
		float bMinY = b.center.Y() - b.halfDimension;

		if (aMinX > bMaxX || bMinX > aMaxX || aMinY > bMaxY || bMinY > aMaxY)
		{
			return false;
		}
		
		return true;
	}

	bool intersect(const AABB2& aabb, const Circle& circle)
	{
		float aabbMaxX = aabb.center.X() + aabb.halfDimension;
		float aabbMinX = aabb.center.X() - aabb.halfDimension;
		float aabbMaxY = aabb.center.Y() + aabb.halfDimension;
		float aabbMinY = aabb.center.Y() - aabb.halfDimension;

		float circleMaxX = circle.getPosition().X() + circle.getRadius();
		float circleMinX = circle.getPosition().X() - circle.getRadius();
		float circleMaxY = circle.getPosition().Y() + circle.getRadius();
		float circleMinY = circle.getPosition().Y() - circle.getRadius();

		if ((circleMaxX <= aabbMaxX && circleMaxX >= aabbMinX) ||
			(circleMinX <= aabbMaxX && circleMinX >= aabbMinX))
		{
			if ((circleMaxY <= aabbMaxY && circleMaxY >= aabbMinY) ||
				(circleMinY <= aabbMaxY && circleMinY >= aabbMinY))
			{
				return true;
			}
		}

		return false;
	}

	bool intersect(const Circle& a, const Circle& b)
	{
		return (a.getPosition() - b.getPosition()).getMagnitude() < a.getRadius() + b.getRadius();
	}

	bool intersect(const Plane& plane, const std::vector<Vector3>& triangle)
	{
		if (intersect(plane, triangle[0], triangle[1]))
		{
			return true;
		}

		if (intersect(plane, triangle[1], triangle[2]))
		{
			return true;
		}

		if (intersect(plane, triangle[2], triangle[0]))
		{
			return true;
		}

		return false;
	}

	RelativePosition intersect(const Plane& plane, const Vector3& point)
	{
		float referenceDistance = dotProduct(plane.getNormal(), plane.getPositionOnPlane());
		float result = dotProduct(plane.getNormal(), point) - referenceDistance;

		if (result < 0.0f)
		{
			return BEHIND;
		}
		else if (result > 0.0f)
		{
			return INFRONT;
		}
		else
		{
			return ON_PLANE;
		}
	}

	bool intersect(const Plane& plane, const Vector3& lineSegmentStart, const Vector3& lineSegmentFinish)
	{
		int startPosition = intersect(plane, lineSegmentStart);
		int finishPosition = intersect(plane, lineSegmentFinish);

		if (startPosition == BEHIND && finishPosition == INFRONT ||
			startPosition == INFRONT && finishPosition == BEHIND ||
			startPosition == ON_PLANE ||
			finishPosition == ON_PLANE)
		{
			return true;
		}

		return false;
	}
}
