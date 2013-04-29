#ifndef RENDERINGENGINE_H_
#define RENDERINGENGINE_H_

#include "../engine/Engine.h"
#include "../graph/SimpleTree.h"
#include "../model/Model.h"
#include "../scene/Camera.h"
#include "../scene/Light.h"
#include "Renderer.h"

class RenderingEngine : public Engine
{
	public:
		virtual void addLight(Light* light) = 0;

		virtual void addModel(Model* model) = 0;

		virtual void addRenderer(Renderer* renderer) = 0;

		virtual const Camera* getCamera() const = 0;

		virtual const Vector4& getClearingColour() const = 0;

		virtual int getHeight() const = 0;

		virtual int getWidth() const = 0;

		virtual void removeModel(const Model& model) = 0;

		virtual void removeRenderer(const Renderer& renderer) = 0;

		virtual void setCamera(Camera* camera) = 0;

		virtual void setClearingColour(const Vector4& clearingColour) = 0;

		virtual void setHeight(int height) = 0;

		virtual void setRendererRoot(const Renderer& renderer, const SimpleTree& node) = 0;

		virtual void setWidth(int width) = 0;
};

#endif /* RENDERINGENGINE_H_ */
