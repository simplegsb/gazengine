#ifndef DIRECT3D10SHADER_H_
#define DIRECT3D10SHADER_H_

#include <string>

#include <d3dx10.h>

class Direct3D10Shader
{
	public:
		Direct3D10Shader(ID3D10Device& device, const std::wstring fileName, const std::string techniqueName);

		~Direct3D10Shader();

		void apply();

		void initInputLayout(ID3D10Device& device);

		void setVar(const std::string name, D3DXCOLOR value);

		void setVar(const std::string name, D3DXMATRIX value);

		void setVar(const std::string name, D3DXVECTOR3 value);

		void setVar(const std::string name, float value);

	private:
		ID3D10Device& device;

		ID3D10Effect* effect;

		ID3D10InputLayout* inputLayout;

		ID3D10EffectTechnique* technique;

		Direct3D10Shader(const Direct3D10Shader& original);

		Direct3D10Shader& operator=(const Direct3D10Shader& original);
};

#endif /* DIRECT3D10SHADER_H_ */
