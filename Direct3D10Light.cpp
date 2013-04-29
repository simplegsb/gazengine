#include "stdafx.h"

#include "Direct3D10Light.h"

using namespace std;

Direct3D10Light::Direct3D10Light(const string& name) :
	ambient(), attenuation(), active(true), diffuse(), direction(), name(name), range(100.0f), specular(),
	strength(1.0f), translation()
{
}

void Direct3D10Light::activate()
{
	active = true;
}

void Direct3D10Light::apply(Direct3D10Shader& shader)
{
	shader.setVar(name + "LightAttenuation", attenuation);
	shader.setVar(name + "LightDirection", direction);
	shader.setVar(name + "LightRange", range);
	shader.setVar(name + "LightSpecular", specular);
	shader.setVar(name + "LightStrength", strength);
	shader.setVar(name + "LightTranslation", translation);

	if (active)
	{
		shader.setVar(name + "LightAmbient", ambient);
		shader.setVar(name + "LightDiffuse", diffuse);
		shader.setVar(name + "LightSpecular", specular);
	}
	else
	{
		shader.setVar(name + "LightAmbient", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		shader.setVar(name + "LightDiffuse", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		shader.setVar(name + "LightSpecular", D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	}
}

void Direct3D10Light::deactivate()
{
	active = false;
}

const D3DXCOLOR& Direct3D10Light::getAmbientComponent() const
{
	return ambient;
}

const D3DXVECTOR3& Direct3D10Light::getAttenuation() const
{
	return attenuation;
}

const D3DXCOLOR& Direct3D10Light::getDiffuseComponent() const
{
	return diffuse;
}

const D3DXVECTOR3& Direct3D10Light::getDirection() const
{
	return direction;
}

float Direct3D10Light::getRange() const
{
	return range;
}

const D3DXCOLOR& Direct3D10Light::getSpecularComponent() const
{
	return specular;
}

float Direct3D10Light::getStrength() const
{
	return strength;
}

const D3DXVECTOR3& Direct3D10Light::getTranslation() const
{
	return translation;
}

bool Direct3D10Light::isActive() const
{
	return active;
}

void Direct3D10Light::setAmbientComponent(const D3DXCOLOR& ambient)
{
	this->ambient = ambient;
}

void Direct3D10Light::setAttenuation(const D3DXVECTOR3& attenuation)
{
	this->attenuation = attenuation;
}

void Direct3D10Light::setDiffuseComponent(const D3DXCOLOR& diffuse)
{
	this->diffuse = diffuse;
}

void Direct3D10Light::setDirection(const D3DXVECTOR3& direction)
{
	this->direction = direction;
}

void Direct3D10Light::setRange(float range)
{
	this->range = range;
}

void Direct3D10Light::setSpecularComponent(const D3DXCOLOR& specular)
{
	this->specular = specular;
}

void Direct3D10Light::setStrength(float strength)
{
	this->strength = strength;
}

void Direct3D10Light::setTranslation(const D3DXVECTOR3& translation)
{
	this->translation = translation;
}
