#ifndef DIRECT3D10MESH_H_
#define DIRECT3D10MESH_H_

#include <vector>

#include <d3d10.h>

#include "../rendering/Direct3D10Shader.h"
#include "../../model/Model.h"
#include "../../model/Vertex.h"

class Direct3D10Mesh : public Model
{
	public:
		Direct3D10Mesh(const Direct3D10Mesh& original);

		Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices);

		Direct3D10Mesh(ID3D10Device& device, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices);

		virtual ~Direct3D10Mesh();
		
		void draw();
		
		PrimitiveType getPrimitiveType() const;

		Direct3D10Shader* getShader() const;
		
		D3DXMATRIX getTransformation() const;

		Direct3D10Mesh& operator=(const Direct3D10Mesh& original);

		void setShader(Direct3D10Shader* shader);

		void setTransformation(const D3DXMATRIX& transformation);

	private:
		ID3D10Device& device;

		ID3DX10Mesh* mesh;

		Direct3D10Shader* shader;

		D3DXMATRIX transformation;
		
		void init(const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices);
};

#endif /* DIRECT3D10MESH_H_ */
