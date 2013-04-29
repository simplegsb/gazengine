#ifndef DIRECT3D10RENDERER_H_
#define DIRECT3D10RENDERER_H_

#include <gazengine/rendering/Renderer.h>

#include "Direct3D10Shader.h"

class Direct3D10Renderer : public Renderer
{
	public:
		Direct3D10Renderer();

		virtual ~Direct3D10Renderer();

		Direct3D10Shader* getShader() const;

		void setShader(Direct3D10Shader* shader);

	private:
		Direct3D10Shader* shader;
};

#endif /* DIRECT3D10RENDERER_H_ */
