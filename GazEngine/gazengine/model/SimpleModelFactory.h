#ifndef SIMPLEMODELFACTORY_H_
#define SIMPLEMODELFACTORY_H_

#include "ModelFactory.h"

class SimpleModelFactory : public ModelFactory
{
	public:
		Mesh* createMesh(const std::vector<Vertex>& vertices);

		Mesh* createMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices);
};

#endif /* SIMPLEMODELFACTORY_H_ */
