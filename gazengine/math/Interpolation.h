#ifndef INTERPOLATION_H_
#define INTERPOLATION_H_

#include <vector>

#include <d3dx10.h>

namespace Interpolation
{
	std::vector<D3DXVECTOR3> interpolateBezier(const std::vector<D3DXVECTOR3>& points,
		unsigned int interpolationCount);

	D3DXVECTOR3 interpolateBezier(const std::vector<D3DXVECTOR3>::const_iterator& begin,
		const std::vector<D3DXVECTOR3>::const_iterator& end, float time);
}

#endif /* INTERPOLATION_H_ */
