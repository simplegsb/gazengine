#ifndef DIRECT3D10MODELFACTORY_H_
#define DIRECT3D10MODELFACTORY_H_

#include <d3dx10.h>

#include "../../model/Model.h"

namespace Direct3D10ModelFactory
{
	Model* createCube(ID3D10Device& device, float size, const D3DXCOLOR& color);

	Model* loadObjModel(ID3D10Device& device, const std::string& fileName, const D3DXCOLOR& color);
};

#endif /* DIRECT3D10MODELFACTORY_H_ */
