#include <gazengine/math/MathFunctions.h>
#include <gazengine/model/Mesh.h>
#include <gazengine/model/Plane.h>
#include <gazengine/model/shape/Cube.h>
#include <gazengine/model/shape/Sphere.h>

#include "../math/BulletMatrix.h"
#include "../math/BulletVector.h"
#include "BulletBody.h"

BulletBody::BulletBody(const Material& material, Model* model, const Matrix44& transformation) :
	body(NULL),
	bulletModel(NULL),
	linearAcceleration(0.0f, 0.0f, 0.0f),
	linearVelocity(0.0f, 0.0f, 0.0f),
	material(material),
	model(model),
	motionState(NULL),
	transformation(transformation)
{
	Cube* cube = dynamic_cast<Cube*>(model);
	if (cube != NULL)
	{
		bulletModel = new btBoxShape(btVector3(cube->getHalfEdgeLength(), cube->getHalfEdgeLength(),
			cube->getHalfEdgeLength()));
	}
	Mesh* mesh = dynamic_cast<Mesh*>(model);
	if (mesh != NULL)
	{
		btTriangleMesh* meshData = new btTriangleMesh;

		vector<int> indices = mesh->getIndices();
		vector<Vertex> vertices = mesh->getVertices();
		for (unsigned int index = 0; index < indices.size(); index += 3)
		{
			btVector3 vertex0(vertices[indices[index]].position.X(), vertices[indices[index]].position.Y(), vertices[indices[index]].position.Z());
			btVector3 vertex1(vertices[indices[index + 1]].position.X(), vertices[indices[index + 1]].position.Y(), vertices[indices[index + 1]].position.Z());
			btVector3 vertex2(vertices[indices[index + 2]].position.X(), vertices[indices[index + 2]].position.Y(), vertices[indices[index + 2]].position.Z());
			meshData->addTriangle(vertex0, vertex1, vertex2);
		}

		bulletModel = new btBvhTriangleMeshShape(meshData, true);
	}
	Plane* plane = dynamic_cast<Plane*>(model);
	if (plane != NULL)
	{
		bulletModel = new btStaticPlaneShape(BulletVector::toBtVector3(plane->getNormal()), 1.0f);
	}
	Sphere* sphere = dynamic_cast<Sphere*>(model);
	if (sphere != NULL)
	{
		bulletModel = new btSphereShape(sphere->getRadius());
	}

	if (mesh == NULL)
	{
		bulletModel->calculateLocalInertia(0.0f, btVector3(0.0f, 0.0f, 0.0f));
	}

	motionState = new btDefaultMotionState(BulletMatrix::toBtTransform(transformation));

	body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(0.0f, motionState, bulletModel));
	body->setFriction(material.friction);
	body->setRestitution(material.restitution);
	body->setRollingFriction(material.friction);
}

BulletBody::~BulletBody()
{
	if (motionState != NULL)
	{
		delete motionState;
	}

	if (body != NULL)
	{
		delete body;
	}

	if (bulletModel != NULL)
	{
		delete bulletModel;
	}
}

void BulletBody::applyForce(const Vector3& force, const Vector3& position)
{
	body->applyForce(BulletVector::toBtVector3(force), BulletVector::toBtVector3(position));
}

void BulletBody::applyTorque(const Vector3& torque)
{
	body->applyTorque(BulletVector::toBtVector3(torque));
}

void BulletBody::clearForces()
{
	body->clearForces();
}

btRigidBody* BulletBody::getBody()
{
	return body;
}

const Vector3& BulletBody::getLinearAcceleration() const
{
	return linearAcceleration; // ???
}

const Vector3& BulletBody::getLinearVelocity() const
{
	linearVelocity = BulletVector::toVector3(body->getLinearVelocity());
	return linearVelocity;
}

float BulletBody::getMass() const
{
	return body->getInvMass();
}

const Body::Material& BulletBody::getMaterial() const
{
	return material;
}

const Model* BulletBody::getModel() const
{
	return model;
}

Matrix44& BulletBody::getTransformation()
{
	transformation = BulletMatrix::toMatrix44(body->getWorldTransform());
	return transformation;
}

const Matrix44& BulletBody::getTransformation() const
{
	transformation = BulletMatrix::toMatrix44(body->getWorldTransform());
	return transformation;
}

bool BulletBody::isDynamic()
{
	return getMass() != 0.0f;
}

void BulletBody::setDynamic(bool dynamic)
{
	if (!dynamic)
	{
		setMass(0.0f);
	}
}

void BulletBody::setLinearVelocity(const Vector3& linearVelocity)
{
	body->setLinearVelocity(BulletVector::toBtVector3(linearVelocity));
}

void BulletBody::setMass(float mass)
{
	body->setMassProps(mass, body->getInvInertiaDiagLocal());
}

void BulletBody::setMaterial(const Material& material)
{
	this->material = material;

	body->setFriction(material.friction);
	body->setRestitution(material.restitution);
	body->setRollingFriction(material.friction);
}

void BulletBody::setNode(SimpleTree* node)
{
	body->setUserPointer(node);
}

void BulletBody::setTransformation(const Matrix44& transformation)
{
	body->setWorldTransform(BulletMatrix::toBtTransform(transformation));
}
