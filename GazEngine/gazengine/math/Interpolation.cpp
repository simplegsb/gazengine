#include "Interpolation.h"

using namespace std;

namespace Interpolation
{
	float getLength(vector<Vector3>::const_iterator begin, vector<Vector3>::const_iterator end);

	float getLength(vector<Vector3>::const_iterator begin, vector<Vector3>::const_iterator end)
	{
		float length = 0.0f;

		while (begin + 1 < end)
		{
			Vector3 segment = *begin - *(begin + 1);
			length += segment.getMagnitude();
			begin++;
		}

		return length;
	}

	vector<Vector3> interpolateBezier(const vector<Vector3>& points, unsigned int interpolationCount)
	{
		vector<Vector3> interpolatedPoints;
		interpolatedPoints.reserve(interpolationCount);

		for (unsigned int interpolationIndex = 0; interpolationIndex < interpolationCount;
			interpolationIndex++)
		{
			float time = (float) interpolationIndex / (interpolationCount - 1);
			interpolatedPoints.push_back(interpolateBezier(points.begin(), points.end(), time));
		}

		return interpolatedPoints;
	}

	Vector3 interpolateBezier(const vector<Vector3>::const_iterator& begin,
		const vector<Vector3>::const_iterator& end, float time)
	{
		if (begin + 1 == end)
		{
			return *begin;
		}

		Vector3 p0 = interpolateBezier(begin, end - 1, time);
		p0 *= 1 - time;

		Vector3 p1 = interpolateBezier(begin + 1, end, time);
		p1 *= time;

		p0 += p1;

		return p0;
	}
}
