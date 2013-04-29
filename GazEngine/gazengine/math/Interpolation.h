#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

#include <vector>

#include "../math/Vector.h"

namespace Interpolation
{
	std::vector<Vector3> interpolateBezier(const std::vector<Vector3>& points, unsigned int interpolationCount);

	Vector3 interpolateBezier(const std::vector<Vector3>::const_iterator& begin,
		const std::vector<Vector3>::const_iterator& end, float time);
}

#endif /* INTERPOLATION_H_ */
