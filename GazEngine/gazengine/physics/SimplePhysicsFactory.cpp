#include "SimpleBody.h"
#include "SimplePhysicsFactory.h"

Body* SimplePhysicsFactory::createBody(const Body::Material& material, Model* model, const Matrix44& transformation,
									   bool dynamic)
{
	return new SimpleBody(material, model, transformation, dynamic);
}
