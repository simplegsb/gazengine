#ifndef DIRECT3D10MESH_H_
#define DIRECT3D10MESH_H_

#include <vector>

#include <d3d10.h>

#include "../../model/Mesh.h"
#include "../../model/Vertex.h"
#include "../rendering/Direct3D10Texture.h"

class Direct3D10Mesh : public Mesh
{
	public:
		Direct3D10Mesh(const Direct3D10Mesh& original);

		Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices);

		Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices);

		virtual ~Direct3D10Mesh();

		ID3DX10Mesh* getMesh() const;

		Texture* getNormalMap() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		D3DXMATRIX getTransformation() const;

		bool isVisible() const;

		Direct3D10Mesh& operator=(const Direct3D10Mesh& original);

		void render(Renderer& renderer) const;

		void setNormalMap(Texture* normalMap);

		void setTexture(Texture* texture);

		void setTransformation(const D3DXMATRIX& transformation);

		void setVisible(bool visible);

	private:
		ID3D10Device& device;

		ID3DX10Mesh* mesh;

		Texture* normalMap;

		Texture* texture;

		D3DXMATRIX transformation;

		bool visible;

		void init(const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices);
};

#endif /* DIRECT3D10MESH_H_ */
