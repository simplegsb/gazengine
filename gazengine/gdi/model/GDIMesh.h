#ifndef GDIMESH_H_
#define GDIMESH_H_

#include <vector>

#include <windows.h>

#include "../../math/Vector2.h"
#include "../../model/Model.h"

class GDIMesh : public Model
{
	public:
		GDIMesh(HDC buffer, std::vector<Vector2> vertices, COLORREF colour);

		virtual ~GDIMesh();
		
		void draw();
		
		PrimitiveType getPrimitiveType() const;

	private:
		HDC buffer;

		COLORREF colour;

		std::vector<Vector2> vertices;
};

#endif /* GDIMESH_H_ */
