#include <gazengine/math/Math.h>
#include <gazengine/math/MathFunctions.h>

#include "Direct3D10Light.h"

using namespace std;

Direct3D10Light::Direct3D10Light(const string& name) :
	ambient(0.05f, 0.05f, 0.05f, 1.0f),
	attenuation(0.05f, 0.0005f, 0.00005f),
	active(true),
	diffuse(0.05f, 0.05f, 0.05f, 1.0f),
	direction(0.0f, 0.0f, -1.0f),
	innerAngle(0),
	name(name),
	node(NULL),
	outerAngle(Math::PI),
	range(1000.0f),
	specular(0.05f, 0.05f, 0.05f, 1.0f),
	strengthAtOrigin(1.0f),
	strengthAtRange(1.0f),
	translation(0.0f, 0.0f, 0.0f)
{
}

void Direct3D10Light::activate()
{
	active = true;
}

void Direct3D10Light::apply()
{
}

void Direct3D10Light::apply(Direct3D10Shader& shader)
{
	Vector3 position;
	if (node != NULL)
	{
		Matrix44 transformation = node->getAbsoluteTransformation();

		direction.X() = transformation[8];
		direction.Y() = transformation[9];
		direction.Z() = transformation[10];
		direction.normalize();

		position = getTranslation3(transformation);
	}
	else
	{
		position = translation;
	}

	shader.setVar(name + "Light", "attenuation", attenuation);
	shader.setVar(name + "Light", "direction", direction);
	shader.setVar(name + "Light", "innerAngle", innerAngle);
	shader.setVar(name + "Light", "position", position);
	shader.setVar(name + "Light", "outerAngle", outerAngle);
	shader.setVar(name + "Light", "range", range);
	shader.setVar(name + "Light", "strengthAtOrigin", strengthAtOrigin);
	shader.setVar(name + "Light", "strengthAtRange", strengthAtRange);

	if (active)
	{
		shader.setVar(name + "Light", "ambient", ambient);
		shader.setVar(name + "Light", "diffuse", diffuse);
		shader.setVar(name + "Light", "specular", specular);
	}
	else
	{
		shader.setVar(name + "Light", "ambient", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		shader.setVar(name + "Light", "diffuse", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
		shader.setVar(name + "Light", "specular", Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	}
}

void Direct3D10Light::deactivate()
{
	active = false;
}

const Vector4& Direct3D10Light::getAmbientComponent() const
{
	return ambient;
}

const Vector3& Direct3D10Light::getAttenuation() const
{
	return attenuation;
}

const Vector4& Direct3D10Light::getDiffuseComponent() const
{
	return diffuse;
}

const Vector3& Direct3D10Light::getDirection() const
{
	return direction;
}

float Direct3D10Light::getInnerAngle() const
{
	return innerAngle;
}

const string& Direct3D10Light::getName() const
{
	return name;
}

float Direct3D10Light::getOuterAngle() const
{
	return outerAngle;
}

float Direct3D10Light::getRange() const
{
	return range;
}

const Vector4& Direct3D10Light::getSpecularComponent() const
{
	return specular;
}

float Direct3D10Light::getStrengthAtOrigin() const
{
	return strengthAtOrigin;
}

float Direct3D10Light::getStrengthAtRange() const
{
	return strengthAtRange;
}

const Vector3& Direct3D10Light::getTranslation() const
{
	return translation;
}

bool Direct3D10Light::isActive() const
{
	return active;
}

void Direct3D10Light::setAmbientComponent(const Vector4& ambient)
{
	this->ambient = ambient;
}

void Direct3D10Light::setAttenuation(const Vector3& attenuation)
{
	this->attenuation = attenuation;
}

void Direct3D10Light::setDiffuseComponent(const Vector4& diffuse)
{
	this->diffuse = diffuse;
}

void Direct3D10Light::setDirection(const Vector3& direction)
{
	this->direction = direction;
}

void Direct3D10Light::setInnerAngle(float innerAngle)
{
	this->innerAngle = innerAngle;
}

void Direct3D10Light::setNode(const SimpleTree* node)
{
	this->node = node;
}

void Direct3D10Light::setOuterAngle(float outerAngle)
{
	this->outerAngle = outerAngle;
}

void Direct3D10Light::setRange(float range)
{
	this->range = range;
}

void Direct3D10Light::setSpecularComponent(const Vector4& specular)
{
	this->specular = specular;
}

void Direct3D10Light::setStrengthAtOrigin(float strengthAtOrigin)
{
	this->strengthAtOrigin = strengthAtOrigin;
}

void Direct3D10Light::setStrengthAtRange(float strengthAtRange)
{
	this->strengthAtRange = strengthAtRange;
}

void Direct3D10Light::setTranslation(const Vector3& translation)
{
	this->translation = translation;
}
