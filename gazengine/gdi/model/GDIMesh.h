#ifndef GDIMESH_H_
#define GDIMESH_H_

#include <vector>

#include <windows.h>

#include "../../math/Vector2.h"
#include "../../model/Mesh.h"

class GDIMesh : public Mesh
{
	public:
		GDIMesh(std::vector<Vector2> vertices, COLORREF colour);

		virtual ~GDIMesh();

		COLORREF getColour() const;

		Texture* getNormalMap() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		std::vector<Vector2>& getVertices();

		const std::vector<Vector2>& getVertices() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setNormalMap(Texture* texture);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		COLORREF colour;

		PrimitiveType primitiveType;

		std::vector<Vector2> vertices;

		bool visible;
};

#endif /* GDIMESH_H_ */
