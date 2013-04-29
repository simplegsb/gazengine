#ifndef SIMPLEMESH_H_
#define SIMPLEMESH_H_

#include "Mesh.h"

class SimpleMesh : public Mesh
{
	public:
		SimpleMesh();

		SimpleMesh(const std::vector<int>& indices, const std::vector<Vertex>& vertices);

		const Vector4& getColour() const;

		std::vector<int>& getIndices();

		const std::vector<int>& getIndices() const;

		Texture* getNormalMap() const;

		const Vector2& getPosition() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		std::vector<Vertex>& getVertices();

		const std::vector<Vertex>& getVertices() const;

		bool isVisible() const;

		void render(Renderer& renderer) const;

		void setColour(const Vector4& colour);

		void setNormalMap(Texture* texture);

		void setPosition(const Vector2& position);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setVisible(bool visible);

	private:
		Vector4 colour;

		std::vector<int> indices;

		Vector2 position;

		PrimitiveType primitiveType;

		std::vector<Vertex> vertices;

		bool visible;
};

#endif /* SIMPLEMESH_H_ */
