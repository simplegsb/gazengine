#include <algorithm>

#include <windows.h>

#include <GL/gl.h>

#include "OpenGLRenderingEngine.h"

using namespace std;

OpenGLRenderingEngine::OpenGLRenderingEngine() :
	camera(NULL),
	clearingColour(0.0f, 0.0f, 0.0f, 1.0f),
	height(600),
	lights(),
	rendererRoots(),
	renderers(),
	tree(NULL),
	width(800)
{
}

OpenGLRenderingEngine::~OpenGLRenderingEngine()
{
	if (camera != NULL)
	{
		delete camera;
	}

	for (unsigned int index = 0; index < lights.size(); index++)
	{
		delete lights.at(index);
	}

	for (unsigned int index = 0; index < renderers.size(); index++)
	{
		delete renderers.at(index);
	}
}

void OpenGLRenderingEngine::addEntity(Entity* /*entity*/)
{
}

void OpenGLRenderingEngine::addLight(Light* light)
{
	lights.push_back(light);
}

void OpenGLRenderingEngine::addModel(Model* /*model*/)
{
}

void OpenGLRenderingEngine::addRenderer(Renderer* renderer)
{
	renderers.push_back(renderer);

	if (tree != NULL)
	{
		rendererRoots[renderer] = tree;
	}
}

void OpenGLRenderingEngine::advance()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	if (tree == NULL)
	{
		return;
	}

	glPushMatrix();
	{
		if (camera->getNode() != NULL)
		{
			Matrix44 cameraView = camera->getNode()->getAbsoluteTransformation();
			cameraView.invert();

			glMultMatrixf(cameraView.getData());
		}

		for (unsigned int index = 0; index < lights.size(); index++)
		{
			lights[index]->apply();
		}

		for (unsigned int index = 0; index < renderers.size(); index++)
		{
			Renderer& renderer = *renderers[index];
			renderer.init();

			renderTree(renderer, *rendererRoots[&renderer]);

			renderer.dispose();
		}
	}
	glPopMatrix();
}

void OpenGLRenderingEngine::destroy()
{
	// Revert depth test settings.
	glDepthFunc(GL_LESS);
	glDisable(GL_DEPTH_TEST);

	// Revert face culling settings.
	glDisable(GL_CULL_FACE);

	// Revert client state settings.
	glDisableClientState(GL_VERTEX_ARRAY);

	// Revert clearing settings.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

Camera* OpenGLRenderingEngine::getCamera() const
{
	return camera;
}

const Vector4& OpenGLRenderingEngine::getClearingColour() const
{
	return clearingColour;
}

int OpenGLRenderingEngine::getHeight() const
{
	return height;
}

const SimpleTree* OpenGLRenderingEngine::getTree() const
{
	return tree;
}

int OpenGLRenderingEngine::getWidth() const
{
	return width;
}

void OpenGLRenderingEngine::init()
{
	// Ensure objects further from the viewpoint are not drawn over the top of closer objects. To assist multi
	// pass rendering, objects at the exact same distance can be rendered over (i.e. the object will be rendered
	// using the result of the last Renderer executed).
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	// Only render the front (counter-clockwise) side of a polygon.
	//glEnable(GL_CULL_FACE);

	// Enable model data arrays.
	glEnableClientState(GL_VERTEX_ARRAY);

	// Set the colour buffer clearing colour.
	glClearColor(clearingColour.X(), clearingColour.Y(), clearingColour.Z(), clearingColour.W());

	// Initialise the viewport size.
	glViewport(0, 0, width, height);
}

void OpenGLRenderingEngine::removeEntity(const Entity& /*entity*/)
{
}

void OpenGLRenderingEngine::removeModel(const Model& /*model*/)
{
}

void OpenGLRenderingEngine::removeRenderer(const Renderer& renderer)
{
	renderers.erase(remove(renderers.begin(), renderers.end(), &renderer));
	rendererRoots.erase(&renderer);
	delete &renderer;
}

void OpenGLRenderingEngine::renderTree(Renderer& renderer, const SimpleTree& root)
{
	glPushMatrix();
	{
		glMultMatrixf(root.getTransformation().getData());

		if (root.getModel() != NULL)
		{
			root.getModel()->render(renderer);
		}

		for (unsigned int index = 0; index < root.getChildren().size(); index++)
		{
			renderTree(renderer, *root.getChildren()[index]);
		}
	}
	glPopMatrix();
}

void OpenGLRenderingEngine::setCamera(Camera* camera)
{
	this->camera = camera;
}

void OpenGLRenderingEngine::setClearingColour(const Vector4& clearingColour)
{
	this->clearingColour = clearingColour;
}

void OpenGLRenderingEngine::setHeight(int height)
{
	this->height = height;
}

void OpenGLRenderingEngine::setRendererRoot(const Renderer& renderer, const SimpleTree& node)
{
	rendererRoots[&renderer] = &node;
}

void OpenGLRenderingEngine::setTree(SimpleTree* tree)
{
	this->tree = tree;

	for (unsigned int index = 0; index < renderers.size(); index++)
	{
		if (rendererRoots.find(renderers[index]) == rendererRoots.end())
		{
			rendererRoots[renderers[index]] = tree;
		}
	}
}

void OpenGLRenderingEngine::setWidth(int width)
{
	this->width = width;
}
