#ifndef DIRECT3D10MODELFACTORY_H_
#define DIRECT3D10MODELFACTORY_H_

#include <d3d10.h>

#include <gazengine/model/ModelFactory.h>

class Direct3D10ModelFactory : public ModelFactory
{
	public:
		Direct3D10ModelFactory(ID3D10Device& device);

		Mesh* createMesh(const std::vector<Vertex>& vertices);

		Mesh* createMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices);

	private:
		ID3D10Device& device;
};

#endif /* DIRECT3D10MODELFACTORY_H_ */
