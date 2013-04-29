#include "SimpleBody.h"
#include "SimplePhysicsFactory.h"

Body* SimplePhysicsFactory::createBody(Body::Material material, Model* model, Vector3 position, bool dynamic)
{
	return new SimpleBody(material, model, position, dynamic);
}
