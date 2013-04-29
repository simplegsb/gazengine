#ifndef RENDERINGENGINE_H_
#define RENDERINGENGINE_H_

#include "../engine/Engine.h"
#include "../model/Model.h"

class RenderingEngine : public Engine
{
	public:
		virtual void addModel(Model* model) = 0;

		virtual void addRenderer(Renderer* renderer) = 0;

		virtual int getHeight() const = 0;

		virtual int getWidth() const = 0;

		virtual void removeModel(const Model& model) = 0;

		virtual void removeRenderer(const Renderer& renderer) = 0;

		virtual void setHeight(int height) = 0;

		virtual void setRendererRoot(const Renderer& renderer, const Tree& node) = 0;

		virtual void setWidth(int width) = 0;
};

#endif /* RENDERINGENGINE_H_ */
