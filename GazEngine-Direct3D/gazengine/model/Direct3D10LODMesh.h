#ifndef DIRECT3D10LODMESH_H_
#define DIRECT3D10LODMESH_H_

#include <map>
#include <vector>

#include <d3d10.h>

#include <gazengine/graph/SimpleTree.h>
#include <gazengine/model/Mesh.h>

#include "../rendering/Direct3D10Texture.h"
#include "Direct3D10Mesh.h"

class Direct3D10LODMesh : public Mesh
{
	public:
		Direct3D10LODMesh();

		void addLOD(Direct3D10Mesh* lod, float maxDistance);

		ID3DX10Mesh* getMesh() const;

		Texture* getNormalMap() const;

		PrimitiveType getPrimitiveType() const;

		Texture* getTexture() const;

		D3DXMATRIX getTransformation() const;

		void render(Renderer& renderer) const;

		void setCameraNode(SimpleTree* cameraNode);

		void setNode(SimpleTree* node);

		void setNormalMap(Texture* normalMap);

		void setTexture(Texture* texture);

		void setTransformation(const D3DXMATRIX& transformation);

	private:
		SimpleTree* cameraNode;

		std::vector<Direct3D10Mesh*> lods;

		SimpleTree* node;

		std::map<Direct3D10Mesh*, float> maxDistances;

		Texture* normalMap;

		D3DXMATRIX transformation;

		Direct3D10Mesh* getLOD() const;
};

#endif /* DIRECT3D10LODMESH_H_ */
