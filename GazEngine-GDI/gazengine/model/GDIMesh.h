#ifndef GDIMESH_H_
#define GDIMESH_H_

#include <vector>

#include <gazengine/model/Mesh.h>

class GDIMesh : public Mesh
{
	public:
		GDIMesh(std::vector<Vector2> vertices, const Vector4& colour);

		virtual ~GDIMesh();

		const Vector4& getColour() const;

		Texture* getNormalMap() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		std::vector<Vector2>& getVertices();

		const std::vector<Vector2>& getVertices() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setColour(const Vector4& colour);

		void setNormalMap(Texture* texture);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector4 colour;

		PrimitiveType primitiveType;

		std::vector<Vector2> vertices;

		bool visible;
};

#endif /* GDIMESH_H_ */
