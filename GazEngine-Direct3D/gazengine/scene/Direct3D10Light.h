#ifndef DIRECT3D10LIGHT_H_
#define DIRECT3D10LIGHT_H_

#include <d3dx10.h>

#include <gazengine/graph/SimpleTree.h>
#include <gazengine/scene/Light.h>

#include "../rendering/Direct3D10Shader.h"

class Direct3D10Light : public Light
{
	public:
		Direct3D10Light(const std::string& name);

		void activate();

		void apply();

		void apply(Direct3D10Shader& shader);

		void deactivate();

		const Vector4& getAmbientComponent() const;

		const Vector3& getAttenuation() const;

		const Vector4& getDiffuseComponent() const;

		const Vector3& getDirection() const;

		float getInnerAngle() const;

		const std::string& getName() const;

		float getOuterAngle() const;

		float getRange() const;

		const Vector4& getSpecularComponent() const;

		float getStrengthAtOrigin() const;

		float getStrengthAtRange() const;

		const Vector3& getTranslation() const;

		bool isActive() const;

		void setAmbientComponent(const Vector4& ambient);

		void setAttenuation(const Vector3& attenuation);

		void setDiffuseComponent(const Vector4& diffuse);

		void setDirection(const Vector3& direction);

		void setInnerAngle(float innerAngle);

		void setNode(const SimpleTree* node);

		void setOuterAngle(float outerAngle);

		void setRange(float range);

		void setSpecularComponent(const Vector4& specular);

		void setStrengthAtOrigin(float strengthAtOrigin);

		void setStrengthAtRange(float strengthAtRange);

		void setTranslation(const Vector3& translation);

	private:
		bool active;

		Vector4 ambient;

		Vector3 attenuation;

		Vector4 diffuse;

		Vector3 direction;

		float innerAngle;

		std::string name;

		const SimpleTree* node;

		float outerAngle;

		float range;

		Vector4 specular;

		float strengthAtOrigin;

		float strengthAtRange;

		Vector3 translation;
};

#endif /* DIRECT3D10LIGHT_H_ */
