#include "Direct3D10Light.h"

using namespace std;

Direct3D10Light::Direct3D10Light(const string& name) :
	ambient(0.05f, 0.05f, 0.05f, 1.0f),
	attenuation(0.05f, 0.0005f, 0.00005f),
	active(true),
	diffuse(0.05f, 0.05f, 0.05f, 1.0f),
	direction(0.0f, 0.0f, -1.0f),
	name(name),
	range(1000.0f),
	specular(0.05f, 0.05f, 0.05f, 1.0f),
	strength(1.0f),
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
	shader.setVar(name + "Light", "attenuation", attenuation);
	shader.setVar(name + "Light", "direction", direction);
	shader.setVar(name + "Light", "range", range);
	shader.setVar(name + "Light", "specular", specular);
	shader.setVar(name + "Light", "strength", strength);
	shader.setVar(name + "Light", "position", translation);

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

const string& Direct3D10Light::getName() const
{
	return name;
}

float Direct3D10Light::getRange() const
{
	return range;
}

const Vector4& Direct3D10Light::getSpecularComponent() const
{
	return specular;
}

float Direct3D10Light::getStrength() const
{
	return strength;
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

void Direct3D10Light::setRange(float range)
{
	this->range = range;
}

void Direct3D10Light::setSpecularComponent(const Vector4& specular)
{
	this->specular = specular;
}

void Direct3D10Light::setStrength(float strength)
{
	this->strength = strength;
}

void Direct3D10Light::setTranslation(const Vector3& translation)
{
	this->translation = translation;
}
