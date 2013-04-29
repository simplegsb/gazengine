#ifndef VERTEX_H_
#define VERTEX_H_

#include <d3dx10.h>

struct Vertex
{
	D3DXCOLOR color;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 position;
	D3DXVECTOR2 texCoord;
};

#endif /* VERTEX_H_ */
