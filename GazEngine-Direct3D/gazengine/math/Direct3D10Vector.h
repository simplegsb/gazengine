#ifndef DIRECT3D10VECTOR_H_
#define DIRECT3D10VECTOR_H_

#include <d3dx10.h>

#include <gazengine/math/Vector.h>

namespace Direct3D10Vector
{
	D3DXCOLOR toD3DXCOLOR(const Vector4& original);

	D3DXVECTOR2 toD3DXVECTOR2(const Vector2& original);

	D3DXVECTOR3 toD3DXVECTOR3(const Vector3& original);

	Vector2 toVector2(const D3DXVECTOR2& original);

	Vector3 toVector3(const D3DXVECTOR3& original);

	Vector4 toVector4(const D3DXCOLOR& original);
}

#endif /* DIRECT3D10VECTOR_H_ */
