#ifndef DIRECT3D10MESH_H_
#define DIRECT3D10MESH_H_

#include <vector>

#include <d3d10.h>

#include <gazengine/model/Mesh.h>

#include "../rendering/Direct3D10Texture.h"

class Direct3D10Mesh : public Mesh
{
	public:
		Direct3D10Mesh(const Direct3D10Mesh& original);

		Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices, const std::vector<int>& indices);

		~Direct3D10Mesh();

		const Vector4& getColour() const;

		std::vector<int>& getIndices();

		const std::vector<int>& getIndices() const;

		ID3DX10Mesh* getMesh() const;

		Texture* getNormalMap() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		D3DXMATRIX getTransformation() const;

		std::vector<Vertex>& getVertices();

		const std::vector<Vertex>& getVertices() const;

		bool isVisible() const;

		Direct3D10Mesh& operator=(const Direct3D10Mesh& original);

		void render(Renderer& renderer) const;

		void setColour(const Vector4& colour);

		void setNormalMap(Texture* normalMap);

		void setPrimitiveType(PrimitiveType primitiveType);

		void setTexture(Texture* texture);

		void setTransformation(const D3DXMATRIX& transformation);

		void setVisible(bool visible);

	private:
		Vector4 colour;

		ID3D10Device& device;

		std::vector<int> indices;

		ID3DX10Mesh* mesh;

		Texture* normalMap;

		Texture* texture;

		D3DXMATRIX transformation;

		std::vector<Vertex> vertices;

		bool visible;
};

#endif /* DIRECT3D10MESH_H_ */
