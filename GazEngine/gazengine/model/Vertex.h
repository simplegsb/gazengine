#ifndef VERTEX_H_
#define VERTEX_H_

#include "../math/Vector.h"

struct Vertex
{
	Vector4 color;
	Vector3 normal;
	Vector3 position;
	Vector2 texCoord;
};

#endif /* VERTEX_H_ */
