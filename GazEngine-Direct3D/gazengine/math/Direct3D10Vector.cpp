#include "Direct3D10Vector.h"

namespace Direct3D10Vector
{
	D3DXCOLOR toD3DXCOLOR(const Vector4& original)
	{
		return D3DXCOLOR(original.R(), original.G(), original.B(), original.A());
	}

	D3DXVECTOR2 toD3DXVECTOR2(const Vector2& original)
	{
		return D3DXVECTOR2(original.X(), original.Y());
	}

	D3DXVECTOR3 toD3DXVECTOR3(const Vector3& original)
	{
		return D3DXVECTOR3(original.X(), original.Y(), original.Z());
	}

	Vector2 toVector2(const D3DXVECTOR2& original)
	{
		return Vector2(original.x, original.y);
	}

	Vector3 toVector3(const D3DXVECTOR3& original)
	{
		return Vector3(original.x, original.y, original.z);
	}

	Vector4 toVector4(const D3DXCOLOR& original)
	{
		return Vector4(original.r, original.g, original.b, original.a);
	}
}
