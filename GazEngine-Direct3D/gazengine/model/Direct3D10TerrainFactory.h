#ifndef DIRECT3D10TERRAINFACTORY_H_
#define DIRECT3D10TERRAINFACTORY_H_

#include <d3dx10.h>

#include <gazengine/model/Model.h>

namespace Direct3D10TerrainFactory
{
	Model* create2DPerlinTerrain(ID3D10Device& device, float width, unsigned int segmentCount, unsigned int octaves,
		float persistence, const D3DXCOLOR& color);

	Model* create3DPerlinTerrain(ID3D10Device& device, float width, float depth, float heightScalar,
		unsigned int segmentCount, unsigned int octaves, float persistence, const D3DXCOLOR& color);

	Model* createMidPointDisplacementTerrain(ID3D10Device& device, float width, unsigned int iterations,
		const D3DXCOLOR& color);

	Model* createMidPointDisplacementTerrain(ID3D10Device& device, float width, unsigned int iterations,
		const D3DXCOLOR& color, unsigned int interpolationCount);
};

#endif /* DIRECT3D10TERRAINFACTORY_H_ */
