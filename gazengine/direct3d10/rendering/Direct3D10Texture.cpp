#include "Direct3D10Texture.h"

using namespace std;

Direct3D10Texture::Direct3D10Texture(ID3D10Device& device, const wstring& fileName) :
	shaderName("texture2d"),
	texture(NULL)
{
	HRESULT result = D3DX10CreateShaderResourceViewFromFile(&device, fileName.c_str(), NULL, NULL, &texture, NULL);

	if (FAILED(result))
	{
		  // TODO
	}
}

Direct3D10Texture::Direct3D10Texture(ID3D10Device& device, const wstring& fileName, const string& shaderName) :
	shaderName(shaderName),
	texture(NULL)
{
	HRESULT result = D3DX10CreateShaderResourceViewFromFile(&device, fileName.c_str(), NULL, NULL, &texture, NULL);

	if (FAILED(result))
	{
		  // TODO
	}
}

Direct3D10Texture::~Direct3D10Texture()
{
	if (texture != NULL)
	{
		texture->Release();
	}
}

void Direct3D10Texture::apply(Direct3D10Shader& shader)
{
	shader.setVar(shaderName, texture);
}
