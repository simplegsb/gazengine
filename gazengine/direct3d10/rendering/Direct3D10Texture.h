#ifndef DIRECT3D10TEXTURE_H_
#define DIRECT3D10TEXTURE_H_

#include "../../rendering/Texture.h"
#include "Direct3D10Shader.h"

class Direct3D10Texture : public Texture
{
	public:
		Direct3D10Texture(ID3D10Device& device, const std::wstring& fileName);

		Direct3D10Texture(ID3D10Device& device, const std::wstring& fileName, const std::string& shaderName);

		~Direct3D10Texture();

		void apply(Direct3D10Shader& shader);

	private:
		std::string shaderName;

		ID3D10ShaderResourceView* texture;
};

#endif /* DIRECT3D10TEXTURE_H_ */
