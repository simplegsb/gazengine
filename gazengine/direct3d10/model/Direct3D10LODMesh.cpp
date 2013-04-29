#include "Direct3D10LODMesh.h"

using namespace std;

Direct3D10LODMesh::Direct3D10LODMesh() :
	cameraNode(NULL),
	lods(),
	node(NULL),
	normalMap(NULL),
	maxDistances()
{
}

void Direct3D10LODMesh::addLOD(Direct3D10Mesh* lod, float maxDistance)
{
	lods.push_back(lod);
	maxDistances.insert(pair<Direct3D10Mesh*, float>(lod, maxDistance));
}

Direct3D10Mesh* Direct3D10LODMesh::getLOD() const
{
	Direct3D10Mesh* lod = NULL;

	D3DXMATRIX absoluteCameraTransformation = cameraNode->getAbsoluteTransformation();
	D3DXVECTOR3 cameraPosition(
		absoluteCameraTransformation._41,
		absoluteCameraTransformation._42,
		absoluteCameraTransformation._43);
	D3DXMATRIX absoluteTransformation = node->getAbsoluteTransformation();
	D3DXVECTOR3 position(
		absoluteTransformation._41,
		absoluteTransformation._42,
		absoluteTransformation._43);
	D3DXVECTOR3 toCamera = cameraPosition - position;
	float distanceToCamera = D3DXVec3Length(&toCamera);

	for (unsigned int index = 0; index < lods.size(); index++)
	{
		if (lod != NULL)
		{
			if (maxDistances.find(lods[index])->second > distanceToCamera)
			{
				return lod;
			}
		}

		lod = lods[index];
	}

	return lod;
}

ID3DX10Mesh* Direct3D10LODMesh::getMesh() const
{
	return getLOD()->getMesh();
}

Model::PrimitiveType Direct3D10LODMesh::getPrimitiveType() const
{
	return getLOD()->getPrimitiveType();
}

Texture* Direct3D10LODMesh::getNormalMap() const
{
	return getLOD()->getNormalMap();
}

Texture* Direct3D10LODMesh::getTexture() const
{
	return getLOD()->getTexture();
}

D3DXMATRIX Direct3D10LODMesh::getTransformation() const
{
	return transformation;
}

void Direct3D10LODMesh::render(Renderer& renderer) const
{
	renderer.render(*getLOD());
}

void Direct3D10LODMesh::setCameraNode(SimpleTree* cameraNode)
{
	this->cameraNode = cameraNode;
}

void Direct3D10LODMesh::setNormalMap(Texture* normalMap)
{
	for (unsigned int index = 0; index < lods.size(); index++)
	{
		lods[index]->setNormalMap(normalMap);
	}
}

void Direct3D10LODMesh::setNode(SimpleTree* node)
{
	this->node = node;
}

void Direct3D10LODMesh::setTexture(Texture* texture)
{
	for (unsigned int index = 0; index < lods.size(); index++)
	{
		lods[index]->setTexture(texture);
	}
}

void Direct3D10LODMesh::setTransformation(const D3DXMATRIX& transformation)
{
	this->transformation = transformation;
}
