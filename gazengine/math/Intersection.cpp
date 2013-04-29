#include "stdafx.h"

#include "Intersection.h"

namespace Intersection
{
	bool contains(const AABB2& aabb, const Circle& circle)
	{
		float aabbMaxX = aabb.center.x + aabb.halfDimension;
		float aabbMinX = aabb.center.x - aabb.halfDimension;
		float aabbMaxY = aabb.center.y + aabb.halfDimension;
		float aabbMinY = aabb.center.y - aabb.halfDimension;

		float circleMaxX = circle.getPosition().x + circle.getRadius();
		float circleMinX = circle.getPosition().x - circle.getRadius();
		float circleMaxY = circle.getPosition().y + circle.getRadius();
		float circleMinY = circle.getPosition().y - circle.getRadius();

		if (circleMaxX <= aabbMaxX && circleMinX >= aabbMinX &&
			circleMaxY <= aabbMaxY && circleMinY >= aabbMinY)
		{
			return true;
		}

		return false;
	}

	bool intersect(const AABB2& a, const AABB2& b)
	{
		float aMaxX = a.center.x + a.halfDimension;
		float aMinX = a.center.x - a.halfDimension;
		float aMaxY = a.center.y + a.halfDimension;
		float aMinY = a.center.y - a.halfDimension;

		float bMaxX = b.center.x + b.halfDimension;
		float bMinX = b.center.x - b.halfDimension;
		float bMaxY = b.center.y + b.halfDimension;
		float bMinY = b.center.y - b.halfDimension;

		if (aMinX > bMaxX || bMinX > aMaxX || aMinY > bMaxY || bMinY > aMaxY)
		{
			return false;
		}
		
		return true;
	}

	bool intersect(const AABB2& aabb, const Circle& circle)
	{
		float aabbMaxX = aabb.center.x + aabb.halfDimension;
		float aabbMinX = aabb.center.x - aabb.halfDimension;
		float aabbMaxY = aabb.center.y + aabb.halfDimension;
		float aabbMinY = aabb.center.y - aabb.halfDimension;

		float circleMaxX = circle.getPosition().x + circle.getRadius();
		float circleMinX = circle.getPosition().x - circle.getRadius();
		float circleMaxY = circle.getPosition().y + circle.getRadius();
		float circleMinY = circle.getPosition().y - circle.getRadius();

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
		return (a.getPosition() - b.getPosition()).length() < a.getRadius() + b.getRadius();
	}
}
