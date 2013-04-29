#include "SimpleBody.h"

SimpleBody::SimpleBody(Material material, Model* model, Vector2 position) :
	dynamic(false),
	linearAcceleration(0.0f, 0.0f),
	linearVelocity(0.0f, 0.0f),
	mass(1.0f),
	material(material),
	model(model),
	position(position)
{
}

void SimpleBody::applyForce(const Vector2& force, const Vector2&) // Ignore position, no angular simulation yet...
{
	linearAcceleration += force;// / mass;
}

void SimpleBody::clearForces()
{
	linearAcceleration = Vector2(0.0f, 0.0f);
}

const Vector2& SimpleBody::getLinearAcceleration() const
{
	return linearAcceleration;
}

const Vector2& SimpleBody::getLinearVelocity() const
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

const Vector2& SimpleBody::getPosition() const
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

void SimpleBody::setLinearVelocity(const Vector2& linearVelocity)
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

void SimpleBody::setPosition(const Vector2& position)
{
	this->position = position;
}
