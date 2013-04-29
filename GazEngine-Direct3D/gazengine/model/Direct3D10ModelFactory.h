#ifndef DIRECT3D10MODELFACTORY_H_
#define DIRECT3D10MODELFACTORY_H_

#include <vector>

#include <d3dx10.h>

#include <gazengine/model/Model.h>

namespace Direct3D10ModelFactory
{
	void colorizeVertices(std::vector<Vertex>& vertices, const D3DXCOLOR& color);

	Direct3D10Mesh* createCube(ID3D10Device& device, float size, const D3DXCOLOR& color);

	/**
     * Loads a Model from the data in the OBJ format.
     * 
     * NOTE: The Model described in the .OBJ data must be constructed entirely from triangle polygons.
     * 
     * @param fileName The name of the file containing the OBJ data.
     * 
     * @return The Model created from the data in the OBJ format.
     */
	Direct3D10Mesh* loadObj(ID3D10Device& device, const std::string& fileName, const D3DXCOLOR& color);

	/**
     * Loads a Model from the data in the OBJ format.
     * 
     * NOTE: The Model described in the .OBJ data must be constructed entirely from triangle polygons.
     * 
     * @param fileName The name of the file containing the OBJ data.
     * 
     * @return The Model created from the data in the OBJ format.
     */
	Direct3D10Mesh* loadObj(ID3D10Device& device, const std::string& fileName, const D3DXCOLOR& color, float scale);
	
	void loadObj(const std::string& fileName, const D3DXCOLOR& color, float scale, std::vector<Vertex>& vertices,
		unsigned int normalCount, unsigned int positionCount, unsigned int texCoordCount, unsigned int vertexCount);

	void scaleVertices(std::vector<Vertex>& vertices, float scale);
};

#endif /* DIRECT3D10MODELFACTORY_H_ */
