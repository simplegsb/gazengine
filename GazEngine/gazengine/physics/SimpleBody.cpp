#include "SimpleBody.h"

SimpleBody::SimpleBody(Material material, Model* model, Vector3 position, bool dynamic) :
	node(NULL),
	dynamic(dynamic),
	linearAcceleration(0.0f, 0.0f),
	linearVelocity(0.0f, 0.0f),
	mass(1.0f),
	material(material),
	model(model),
	position(position)
{
}

void SimpleBody::applyForce(const Vector3& force, const Vector3&) // Ignore position, no angular simulation yet...
{
	linearAcceleration += force;// / mass;
}

void SimpleBody::clearForces()
{
	linearAcceleration = Vector3(0.0f, 0.0f, 0.0f);
}

const Vector3& SimpleBody::getLinearAcceleration() const
{
	return linearAcceleration;
}

const Vector3& SimpleBody::getLinearVelocity() const
{
	return linearVelocity;
}

float SimpleBody::getMass() const
{
	return mass;
}

const Body::Material& SimpleBody::getMaterial() const
{
	return material;
}

const Model* SimpleBody::getModel() const
{
	return model;
}

const Vector3& SimpleBody::getPosition() const
{
	return position;
}

bool SimpleBody::isDynamic()
{
	return dynamic;
}

void SimpleBody::setDynamic(bool dynamic)
{
	this->dynamic = dynamic;
}

void SimpleBody::setLinearVelocity(const Vector3& linearVelocity)
{
	this->linearVelocity = linearVelocity;
}

void SimpleBody::setMass(float mass)
{
	this->mass = mass;
}

void SimpleBody::setMaterial(const Material& material)
{
	this->material = material;
}

void SimpleBody::setNode(SimpleTree* node)
{
	this->node = node;
}

void SimpleBody::setPosition(const Vector3& position)
{
	this->position = position;
}
