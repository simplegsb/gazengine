#ifndef DIRECT3D10SHADERFACTORY_H_
#define DIRECT3D10SHADERFACTORY_H_

#include <map>

#include "Direct3D10Shader.h"

class Direct3D10ShaderFactory
{
	public:
		Direct3D10ShaderFactory(ID3D10Device& device);

		~Direct3D10ShaderFactory();

		Direct3D10Shader* createShader(const std::wstring& fileName, const std::string& techniqueName);

	private:
		ID3D10Device& device;

		std::map<std::wstring, ID3D10Effect*> effects;

		Direct3D10ShaderFactory(const Direct3D10ShaderFactory& original);

		void addEffect(const std::wstring& fileName);

		Direct3D10ShaderFactory& operator=(const Direct3D10ShaderFactory& original);
};

#endif /* DIRECT3D10SHADERFACTORY_H_ */
