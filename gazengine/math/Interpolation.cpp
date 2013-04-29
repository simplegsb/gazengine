#include "stdafx.h"

#include "Interpolation.h"

using namespace std;

namespace Interpolation
{
	float getLength(vector<D3DXVECTOR3>::const_iterator begin, vector<D3DXVECTOR3>::const_iterator end);

	float getLength(vector<D3DXVECTOR3>::const_iterator begin, vector<D3DXVECTOR3>::const_iterator end)
	{
		float length = 0.0f;

		while (begin + 1 < end)
		{
			D3DXVECTOR3 segment = *begin - *(begin + 1);
			length += D3DXVec3Length(&segment);
			begin++;
		}

		return length;
	}

	vector<D3DXVECTOR3> interpolateBezier(const vector<D3DXVECTOR3>& points,
		unsigned int interpolationCount)
	{
		vector<D3DXVECTOR3> interpolatedPoints;
		interpolatedPoints.reserve(interpolationCount);

		for (unsigned int interpolationIndex = 0; interpolationIndex < interpolationCount;
			interpolationIndex++)
		{
			float time = (float) interpolationIndex / (interpolationCount - 1);
			interpolatedPoints.push_back(interpolateBezier(points.begin(), points.end(), time));
		}

		return interpolatedPoints;
	}

	D3DXVECTOR3 interpolateBezier(const vector<D3DXVECTOR3>::const_iterator& begin,
		const vector<D3DXVECTOR3>::const_iterator& end, float time)
	{
		if (begin + 1 == end)
		{
			return *begin;
		}

		D3DXVECTOR3 p0 = interpolateBezier(begin, end - 1, time);
		p0 *= 1 - time;

		D3DXVECTOR3 p1 = interpolateBezier(begin + 1, end, time);
		p1 *= time;

		p0 += p1;

		return p0;
	}
}
