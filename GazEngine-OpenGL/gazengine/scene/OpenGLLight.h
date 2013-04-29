#ifndef OPENGLLIGHT_H_
#define OPENGLLIGHT_H_

#include <gazengine/scene/Light.h>

class OpenGLLight : public Light
{
	public:
		OpenGLLight(const std::string& name);

		void activate();

		void apply();

		void deactivate();

		const Vector4& getAmbientComponent() const;

		const Vector3& getAttenuation() const;

		const Vector4& getDiffuseComponent() const;

		const Vector3& getDirection() const;

		const std::string& getName() const;

		float getRange() const;

		const Vector4& getSpecularComponent() const;

		float getStrength() const;

		const Vector3& getTranslation() const;

		bool isActive() const;

		void setAmbientComponent(const Vector4& ambient);

		void setAttenuation(const Vector3& attenuation);

		void setDiffuseComponent(const Vector4& diffuse);

		void setDirection(const Vector3& direction);

		void setRange(float range);

		void setSpecularComponent(const Vector4& specular);

		void setStrength(float strength);

		void setTranslation(const Vector3& translation);

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
