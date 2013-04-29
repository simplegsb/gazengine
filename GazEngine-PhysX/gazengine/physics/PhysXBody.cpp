#include <gazengine/model/Mesh.h>
#include <gazengine/model/Plane.h>
#include <gazengine/model/shape/Cube.h>
#include <gazengine/model/shape/Sphere.h>

#include "../math/PhysXMatrix.h"
#include "../math/PhysXVector.h"
#include "PhysXBody.h"

using namespace physx;

PhysXBody::PhysXBody(PxPhysics& physics, PxCooking& cooking, const Material& material, const Model* model,
					 const Matrix44& transformation, bool dynamic) :
	actor(NULL),
	dynamic(dynamic),
	linearAcceleration(0.0f, 0.0f, 0.0f),
	linearVelocity(0.0f, 0.0f, 0.0f),
	material(material),
	model(model),
	physxMaterial(NULL),
	physxModel(NULL),
	transformation(transformation)
{
	physxMaterial = physics.createMaterial(material.friction, material.friction, material.restitution);

	const Plane* plane = dynamic_cast<const Plane*>(model);
	if (plane != NULL)
	{
		actor = PxCreatePlane(physics, PxPlane(PhysXVector::toPxVec3(plane->getPositionOnPlane()),
			PhysXVector::toPxVec3(plane->getNormal())), *physxMaterial);
		return;
	}

	const Cube* cube = dynamic_cast<const Cube*>(model);
	if (cube != NULL)
	{
		physxModel = new PxBoxGeometry(cube->getHalfEdgeLength(), cube->getHalfEdgeLength(),
			cube->getHalfEdgeLength());
	}
	const Mesh* mesh = dynamic_cast<const Mesh*>(model);
	if (mesh != NULL)
	{
		// Need a concurrent block of data...
		vector<int> indices = mesh->getIndices();
		vector<Vertex> vertices = mesh->getVertices();
		vector<PxVec3> convexMeshData;
		convexMeshData.reserve(indices.size());
		for (unsigned int index = 0; index < indices.size(); index++)
		{
			PxVec3 vertex;
			vertex.x = vertices[indices[index]].position.X();
			vertex.y = vertices[indices[index]].position.Y();
			vertex.z = vertices[indices[index]].position.Z();
			convexMeshData.push_back(vertex);
		}

		PxConvexMeshDesc convexMeshDesc;
		convexMeshDesc.points.count = convexMeshData.size();
		convexMeshDesc.points.stride = sizeof(PxVec3);
		convexMeshDesc.points.data = &convexMeshData[0];
		convexMeshDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

		// Roasting...
		PxDefaultMemoryOutputStream buffer;
		cooking.cookConvexMesh(convexMeshDesc, buffer);
		PxDefaultMemoryInputData input(buffer.getData(), buffer.getSize());

		physxModel = new PxConvexMeshGeometry(physics.createConvexMesh(input));
	}
	const Sphere* sphere = dynamic_cast<const Sphere*>(model);
	if (sphere != NULL)
	{
		physxModel = new PxSphereGeometry(sphere->getRadius());
	}

	if (dynamic)
	{
		actor = PxCreateDynamic(physics, PhysXMatrix::toPxTransform(transformation), *physxModel, *physxMaterial,
			material.density);
		PxRigidBodyExt::updateMassAndInertia(*static_cast<PxRigidBody*>(actor), &material.density, 1);
	}
	else
	{
		actor = PxCreateStatic(physics, PhysXMatrix::toPxTransform(transformation), *physxModel, *physxMaterial);
	}
}

PhysXBody::~PhysXBody()
{
	if (physxModel != NULL)
	{
		delete physxModel;
	}
}

void PhysXBody::applyForce(const Vector3& force, const Vector3&)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->addForce(PhysXVector::toPxVec3(force));
	}
}

void PhysXBody::applyTorque(const Vector3& torque)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->addTorque(PhysXVector::toPxVec3(torque));
	}
}

void PhysXBody::clearForces()
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->clearForce();
	}
}

PxActor* PhysXBody::getActor()
{
	return actor;
}

const Vector3& PhysXBody::getLinearAcceleration() const
{
	return linearAcceleration; // ???
}

const Vector3& PhysXBody::getLinearVelocity() const
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		linearVelocity = PhysXVector::toVector3(rigidBody->getLinearVelocity());
	}

	return linearVelocity;
}

float PhysXBody::getMass() const
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		return rigidBody->getMass();
	}

	return 0.0f;
}

const Body::Material& PhysXBody::getMaterial() const
{
	return material;
}

const Model* PhysXBody::getModel() const
{
	return model;
}

physx::PxGeometry* PhysXBody::getPhysXModel()
{
	return physxModel;
}

Matrix44& PhysXBody::getTransformation()
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		transformation = PhysXMatrix::toMatrix44(rigidBody->getGlobalPose());
	}

	return transformation;
}

const Matrix44& PhysXBody::getTransformation() const
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		transformation = PhysXMatrix::toMatrix44(rigidBody->getGlobalPose());
	}

	return transformation;
}

bool PhysXBody::isDynamic()
{
	return dynamic;
}

void PhysXBody::setDynamic(bool)
{
	//assert(dynamic != this->dynamic && "PhysX bodys cannot be changed between dynamic and static...");
}

void PhysXBody::setLinearVelocity(const Vector3& linearVelocity)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->setLinearVelocity(PhysXVector::toPxVec3(linearVelocity));
	}
}

void PhysXBody::setMass(float mass)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->setMass(mass);
	}
}

void PhysXBody::setMaterial(const Material&)
{
}

void PhysXBody::setNode(SimpleTree* node)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		PxShape* shapes;
		rigidBody->getShapes(&shapes, 1);
		shapes->userData = node;
	}
}

void PhysXBody::setTransformation(const Matrix44& transformation)
{
	PxRigidBody* rigidBody = actor->isRigidBody();
	if (rigidBody != NULL)
	{
		rigidBody->setGlobalPose(PhysXMatrix::toPxTransform(transformation));
	}
}
