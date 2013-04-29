#ifndef DIRECT3D10VERTEX_H_
#define DIRECT3D10VERTEX_H_

#include <d3d10.h>

struct Direct3D10Vertex
{
	D3DXCOLOR color;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 position;
	D3DXVECTOR2 texCoord;
};

#endif /* DIRECT3D10VERTEX_H_ */
