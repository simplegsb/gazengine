#ifndef OPENGLLIGHT_H_
#define OPENGLLIGHT_H_

#include <gazengine/scene/Light.h>

class OpenGLLight : public Light
{
	public:
		OpenGLLight(const std::string& name);

		virtual void activate() = 0;

		void apply();

		virtual void deactivate() = 0;

		const Vector4& getAmbientComponent() const;

		virtual const Vector3& getAttenuation() const = 0;

		const Vector4& getDiffuseComponent() const;

		virtual const Vector3& getDirection() const = 0;

		virtual const std::string& getName() const = 0;

		virtual float getRange() const = 0;

		const Vector4& getSpecularComponent() const;

		virtual float getStrength() const = 0;

		virtual const Vector3& getTranslation() const = 0;

		virtual bool isActive() const = 0;

		void setAmbientComponent(const Vector4& ambient);

		virtual void setAttenuation(const Vector3& attenuation) = 0;

		void setDiffuseComponent(const Vector4& diffuse);

		virtual void setDirection(const Vector3& direction) = 0;

		virtual void setRange(float range) = 0;

		void setSpecularComponent(const Vector4& specular);

		virtual void setStrength(float strength) = 0;

		virtual void setTranslation(const Vector3& translation) = 0;

	private:
		bool active;

		Vector4 ambient;

		Vector3 attenuation;

		Vector4 diffuse;

		Vector3 direction;

		std::string name;

		float range;

		Vector4 specular;

		float strength;

		Vector3 translation;
};

#endif /* OPENGLLIGHT_H_ */
