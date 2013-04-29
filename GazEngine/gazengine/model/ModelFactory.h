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

		void colorizeVertices(std::vector<Vertex>& vertices, const Vector4& color);

		Mesh* createBoxMesh(float length, float width, float height, const Vector4& color, bool doubleSided = false);

		Mesh* createCubeMesh(float size, const Vector4& color, bool doubleSided = false);

		virtual Mesh* createMesh(const std::vector<Vertex>& vertices) = 0;

		virtual Mesh* createMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices) = 0;

		Mesh* createPrismMesh(float size, const Vector4& color);

		Mesh* createSquareMesh(float size, const Vector4& color, bool doubleSided = false);

		static ModelFactory* getInstance();

		void scaleVertices(std::vector<Vertex>& vertices, float scale);

		static void setInstance(ModelFactory* instance);

	private:
		static ModelFactory* instance;
};

#endif /* MODELFACTORY_H_ */
