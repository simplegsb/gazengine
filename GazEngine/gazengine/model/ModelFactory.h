#ifndef MODELFACTORY_H_
#define MODELFACTORY_H_

#include <vector>

#include "Mesh.h"

class ModelFactory
{
	public:
		virtual ~ModelFactory()
		{
		}

		static void addRectangleIndexList(std::vector<int>& indices, unsigned int index, unsigned int vertexIndex,
			bool reverse = false);

		static void addRectangleVertexList(std::vector<Vertex>& vertices, unsigned int index, const Vector4& colour,
			const Vector3& topLeft, const Vector3& toTopRight, const Vector3& toBottomLeft);

		static void addTriangleIndexList(std::vector<int>& indices, unsigned int index, unsigned int vertexIndex,
			bool reverse = false);

		static void addTriangleVertexList(std::vector<Vertex>& vertices, unsigned int index, const Vector4& colour,
			const Vector3& top, const Vector3& toBottomLeft, const Vector3& toBottomRight);

		void colorizeVertices(std::vector<Vertex>& vertices, const Vector4& color);

		Mesh* createBoxMesh(const Vector3& halfExtents, const Vector4& color, bool doubleSided = false);

		Mesh* createCubeMesh(float halfExtent, const Vector4& color, bool doubleSided = false);

		virtual Mesh* createMesh(const std::vector<Vertex>& vertices) = 0;

		virtual Mesh* createMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices) = 0;

		Mesh* createPrismMesh(const Vector3& halfExtents, const Vector4& color);

		Mesh* createPyramidMesh(float halfBaseExtent, float height, const Vector4& color);

		Mesh* createSquareMesh(float halfExtent, const Vector4& color, bool doubleSided = false);

		static ModelFactory* getInstance();

		void scaleVertices(std::vector<Vertex>& vertices, float scale);

		static void setInstance(ModelFactory* instance);

	private:
		static ModelFactory* instance;
};

#endif /* MODELFACTORY_H_ */
