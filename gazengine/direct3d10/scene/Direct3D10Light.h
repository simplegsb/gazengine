#ifndef DIRECT3D10LIGHT_H_
#define DIRECT3D10LIGHT_H_

#include <string>

#include <d3dx10.h>

#include "../rendering/Direct3D10Shader.h"

class Direct3D10Light
{
	public:
		Direct3D10Light(const std::string& name);

		void activate();

		void apply(Direct3D10Shader& shader);

		void deactivate();

		const D3DXCOLOR& getAmbientComponent() const;

		const D3DXVECTOR3& getAttenuation() const;

		const D3DXCOLOR& getDiffuseComponent() const;

		const D3DXVECTOR3& getDirection() const;

		std::string getName() const;

		float getRange() const;

		const D3DXCOLOR& getSpecularComponent() const;

		float getStrength() const;

		const D3DXVECTOR3& getTranslation() const;

		bool isActive() const;

		void setAmbientComponent(const D3DXCOLOR& ambient);

		void setAttenuation(const D3DXVECTOR3& attenuation);

		void setDiffuseComponent(const D3DXCOLOR& diffuse);

		void setDirection(const D3DXVECTOR3& direction);

		void setRange(float range);

		void setSpecularComponent(const D3DXCOLOR& specular);

		void setStrength(float strength);

		void setTranslation(const D3DXVECTOR3& translation);

	private:
		bool active;

		D3DXCOLOR ambient;

		D3DXVECTOR3 attenuation;

		D3DXCOLOR diffuse;

		D3DXVECTOR3 direction;

		std::string name;

		float range;

		D3DXCOLOR specular;

		float strength;

		D3DXVECTOR3 translation;
};

#endif /* DIRECT3D10LIGHT_H_ */
