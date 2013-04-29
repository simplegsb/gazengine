#ifndef DIRECT3D10MODELFACTORY_H_
#define DIRECT3D10MODELFACTORY_H_

#include <d3dx10.h>

#include "Model.h"

namespace Direct3D10ModelFactory
{
	Model* createCube(ID3D10Device& device, float size, D3DXCOLOR color);

	Model* createHills(ID3D10Device& device, DWORD rows, DWORD columns, float dx, D3DXCOLOR color);
};

#endif /* DIRECT3D10MODELFACTORY_H_ */
