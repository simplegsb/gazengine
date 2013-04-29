#include "Direct3D10Shader.h"

using namespace std;

Direct3D10Shader::Direct3D10Shader(ID3D10Device& device, ID3D10Effect* effect, ID3D10EffectTechnique* technique) :
	effect(effect),
	device(device),
	inputLayout(NULL),
	technique(technique)
{
	initInputLayout();
}

Direct3D10Shader::~Direct3D10Shader()
{
	if (inputLayout != NULL)
	{
		inputLayout->Release();
	}
}

void Direct3D10Shader::apply()
{
	// It turns out ID3DXFont::DrawText() has no regard for the state of our rendering engine so lets try and restore
	// it...
    device.IASetInputLayout(inputLayout);

    technique->GetPassByIndex(0)->Apply(0);
}

const ID3D10InputLayout& Direct3D10Shader::getInputLayout() const
{
	return *inputLayout;
}

void Direct3D10Shader::initInputLayout()
{
	D3D10_INPUT_ELEMENT_DESC vertexDescription[] =
	{
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 16, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D10_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D10_INPUT_PER_VERTEX_DATA, 0}
	};

    D3D10_PASS_DESC passDescription;
    technique->GetPassByIndex(0)->GetDesc(&passDescription);
    device.CreateInputLayout(vertexDescription, 4, passDescription.pIAInputSignature,
		passDescription.IAInputSignatureSize, &inputLayout);
}

void Direct3D10Shader::setVar(const string& name, const Matrix44& value)
{
	// I'm trusting Direct3D to not change the value here...
	effect->GetVariableByName(name.data())->AsMatrix()->SetMatrix(const_cast<float*>(value.getData()));
}

void Direct3D10Shader::setVar(const string& name, float value)
{
	effect->GetVariableByName(name.data())->AsScalar()->SetFloat(value);
}

void Direct3D10Shader::setVar(const string& name, const Vector3& value)
{
	// I'm trusting Direct3D to not change the value here...
	effect->GetVariableByName(name.data())->AsVector()->SetFloatVector(const_cast<float*>(value.getData()));
}

void Direct3D10Shader::setVar(const string& name, const Vector4& value)
{
	// I'm trusting Direct3D to not change the value here...
	effect->GetVariableByName(name.data())->AsVector()->SetFloatVector(const_cast<float*>(value.getData()));
}

void Direct3D10Shader::setVar(const string& name, ID3D10ShaderResourceView* value)
{
	effect->GetVariableByName(name.data())->AsShaderResource()->SetResource(value);
}

void Direct3D10Shader::setVar(const string& structName, const string& name, const Matrix44& value)
{
	// I'm trusting Direct3D to not change the value here...
	effect->GetVariableByName(structName.data())->GetMemberByName(name.data())->AsMatrix()
		->SetMatrix(const_cast<float*>(value.getData()));
}

void Direct3D10Shader::setVar(const string& structName, const string& name, float value)
{
	effect->GetVariableByName(structName.data())->GetMemberByName(name.data())->AsScalar()->SetFloat(value);
}

void Direct3D10Shader::setVar(const string& structName, const string& name, const Vector3& value)
{
	// I'm trusting Direct3D to not change the value here...
	effect->GetVariableByName(structName.data())->GetMemberByName(name.data())
		->AsVector()->SetFloatVector(const_cast<float*>(value.getData()));
}

void Direct3D10Shader::setVar(const string& structName, const string& name, const Vector4& value)
{
	// I'm trusting Direct3D to not change the value here...
	effect->GetVariableByName(structName.data())->GetMemberByName(name.data())
		->AsVector()->SetFloatVector(const_cast<float*>(value.getData()));
}
