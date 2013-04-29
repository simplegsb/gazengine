#include "BulletBody.h"
#include "BulletPhysicsFactory.h"

Body* BulletPhysicsFactory::createBody(const Body::Material& material, Model* model, const Matrix44& transformation,
									   bool /*dynamic*/)
{
	return new BulletBody(material, model, transformation);
}
