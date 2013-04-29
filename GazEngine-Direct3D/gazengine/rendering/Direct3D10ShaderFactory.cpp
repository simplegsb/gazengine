#include <windows.h> // Dependency of dxerr.h

#include <dxerr.h>

#include "Direct3D10ShaderFactory.h"

using namespace std;

Direct3D10ShaderFactory::Direct3D10ShaderFactory(ID3D10Device& device) :
	device(device),
	effects()
{
}

Direct3D10ShaderFactory::~Direct3D10ShaderFactory()
{
	for (map<wstring, ID3D10Effect*>::iterator iterator = effects.begin(); iterator != effects.end(); iterator++)
	{
		iterator->second->Release();
	}
}

void Direct3D10ShaderFactory::addEffect(const wstring& fileName)
{
	DWORD flags = D3D10_SHADER_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
    flags |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	ID3D10Effect* effect = NULL;
	ID3D10Blob* compilationErrors = NULL;
	HRESULT result = D3DX10CreateEffectFromFile(fileName.c_str(), NULL, NULL, "fx_4_0", flags, 0, &device, NULL, NULL,
		&effect, &compilationErrors, NULL);

	if(FAILED(result))
	{
		if(compilationErrors != NULL)
		{
			MessageBoxA(0, (char*) compilationErrors->GetBufferPointer(), 0, 0);
			compilationErrors->Release();
		}
		DXTrace(__FILE__, (DWORD)__LINE__, result, L"D3DX10CreateEffectFromFile", true);
	}
	else
	{
		effects.insert(pair<wstring, ID3D10Effect*>(fileName, effect));
	}
}

Direct3D10Shader* Direct3D10ShaderFactory::createShader(const wstring& fileName, const string& techniqueName)
{
	if (effects.find(fileName) == effects.end())
	{
		addEffect(fileName);
	}

	return new Direct3D10Shader(device, effects[fileName],
		effects[fileName]->GetTechniqueByName(techniqueName.c_str()));
}
