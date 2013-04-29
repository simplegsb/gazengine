#include "Direct3D10Renderer.h"

Direct3D10Renderer::Direct3D10Renderer() :
	shader(NULL)
{
}

Direct3D10Renderer::~Direct3D10Renderer()
{
	if (shader != NULL)
	{
		delete shader;
	}
}

Direct3D10Shader* Direct3D10Renderer::getShader() const
{
	return shader;
}

void Direct3D10Renderer::setShader(Direct3D10Shader* shader)
{
	this->shader = shader;
}
