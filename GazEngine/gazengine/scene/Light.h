#ifndef LIGHT_H_
#define LIGHT_H_

#include <string>

#include "../math/Vector.h"

class Light
{
	public:
		virtual ~Light()
		{
		}

		virtual void activate() = 0;

		virtual void apply() = 0;

		virtual void deactivate() = 0;

		virtual const Vector4& getAmbientComponent() const = 0;

		virtual const Vector3& getAttenuation() const = 0;

		virtual const Vector4& getDiffuseComponent() const = 0;

		virtual const Vector3& getDirection() const = 0;

		virtual const std::string& getName() const = 0;

		virtual float getRange() const = 0;

		virtual const Vector4& getSpecularComponent() const = 0;

		virtual float getStrength() const = 0;

		virtual const Vector3& getTranslation() const = 0;

		virtual bool isActive() const = 0;

		virtual void setAmbientComponent(const Vector4& ambient) = 0;

		virtual void setAttenuation(const Vector3& attenuation) = 0;

		virtual void setDiffuseComponent(const Vector4& diffuse) = 0;

		virtual void setDirection(const Vector3& direction) = 0;

		virtual void setRange(float range) = 0;

		virtual void setSpecularComponent(const Vector4& specular) = 0;

		virtual void setStrength(float strength) = 0;

		virtual void setTranslation(const Vector3& translation) = 0;
};

#endif /* LIGHT_H_ */
