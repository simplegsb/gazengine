#include "stdafx.h"

#include <windows.h> // Dependency of dxerr.h

#include <dxerr.h>

#include "Direct3D10Shader.h"

using namespace std;

Direct3D10Shader::Direct3D10Shader(ID3D10Device& device, const wstring& fileName, const string& techniqueName) :
	effect(NULL), device(device), inputLayout(NULL), technique(NULL)
{
	DWORD flags = D3D10_SHADER_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
    flags |= D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif
 
	ID3D10Blob* compilationErrors = NULL;
	HRESULT result = D3DX10CreateEffectFromFile(fileName.data(), NULL, NULL, "fx_4_0", flags, 0, &device, NULL, NULL,
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

	technique = effect->GetTechniqueByName(techniqueName.data());

	initInputLayout(device);
}

void Direct3D10Shader::apply()
{
	// It turns out ID3DXFont::DrawText() has no regard for the state of our rendering engine so lets try and restore
	// it...
    device.IASetInputLayout(inputLayout);

    technique->GetPassByIndex(0)->Apply(0);
}

Direct3D10Shader::~Direct3D10Shader()
{
	if (effect != NULL)
	{
		effect->Release();
	}

	if (inputLayout != NULL)
	{
		inputLayout->Release();
	}
}

void Direct3D10Shader::initInputLayout(ID3D10Device& device)
{
	D3D10_INPUT_ELEMENT_DESC vertexDescription[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};

    D3D10_PASS_DESC passDescription;
    technique->GetPassByIndex(0)->GetDesc(&passDescription);
    device.CreateInputLayout(vertexDescription, 3, passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize, &inputLayout);
}

void Direct3D10Shader::setVar(const string& name, D3DXCOLOR value)
{
	effect->GetVariableByName(name.data())->AsVector()->SetFloatVector(value);
}

void Direct3D10Shader::setVar(const string& name, D3DXMATRIX value)
{
	effect->GetVariableByName(name.data())->AsMatrix()->SetMatrix(value);
}

void Direct3D10Shader::setVar(const string& name, D3DXVECTOR3 value)
{
	effect->GetVariableByName(name.data())->AsVector()->SetFloatVector(value);
}

void Direct3D10Shader::setVar(const string& name, float value)
{
	effect->GetVariableByName(name.data())->AsScalar()->SetFloat(value);
}
