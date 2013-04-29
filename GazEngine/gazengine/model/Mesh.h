#ifndef MESH_H_
#define MESH_H_

#include "Model.h"
#include "Vertex.h"

class Mesh : public Model
{
	public:
		virtual ~Mesh()
		{
		}

		virtual std::vector<int>& getIndices() = 0;

		virtual const std::vector<int>& getIndices() const = 0;

		virtual std::vector<Vertex>& getVertices() = 0;

		virtual const std::vector<Vertex>& getVertices() const = 0;
};

#endif /* MESH_H_ */
