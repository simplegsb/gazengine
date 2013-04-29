#ifndef DIRECT3D10MESH_H_
#define DIRECT3D10MESH_H_

#include <vector>

#include <d3d10.h>

#include "Model.h"
#include "Vertex.h"

class Direct3D10Mesh : public Model
{
	public:
		Direct3D10Mesh(ID3D10Device& device, const std::vector<DWORD>& indices, const std::vector<Vertex>& vertices);

		virtual ~Direct3D10Mesh();
		
		void draw();

	private:
		Direct3D10Mesh(const Direct3D10Mesh& original);

		Direct3D10Mesh& operator=(const Direct3D10Mesh& original);

		ID3D10Device& device;

		ID3D10Buffer* indexBuffer;

		unsigned int indexCount;

		ID3D10Buffer* vertexBuffer;
};

#endif /* DIRECT3D10MESH_H_ */
