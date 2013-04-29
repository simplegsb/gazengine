#include "BulletBody.h"
#include "BulletPhysicsFactory.h"

Body* BulletPhysicsFactory::createBody(Body::Material material, Model* model, Vector3 position, bool)
{
	return new BulletBody(material, model, position);
}
