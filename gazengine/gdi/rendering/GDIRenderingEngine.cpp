#include <algorithm>

#include "../model/GDIMesh.h"
#include "GDIRenderer.h"
#include "GDIRenderingEngine.h"

using namespace std;

GDIRenderingEngine::GDIRenderingEngine(HWND window) :
	backBitmap(NULL),
	backBitmapOld(NULL),
	backBuffer(NULL),
	frontBuffer(NULL),
	height(600),
	models(),
	quadTree(NULL),
	rendererRoots(),
	renderers(),
	width(800),
	window(window)
{
}

GDIRenderingEngine::~GDIRenderingEngine()
{
	if (quadTree != NULL)
	{
		delete quadTree;
	}

	for (unsigned int index = 0; index < renderers.size(); index++)
	{
		delete renderers.at(index);
	}
}

void GDIRenderingEngine::addEntity(Entity* entity)
{
	vector<Model*> entityModels = entity->getComponents<Model>();
	for (unsigned int index = 0; index < entityModels.size(); index++)
	{
		models.push_back(entityModels[index]);
	}
}

void GDIRenderingEngine::addModel(Model* model)
{
	models.push_back(model);
}

void GDIRenderingEngine::addRenderer(Renderer* renderer)
{
	renderers.push_back(renderer);
	static_cast<GDIRenderer*>(renderer)->setBuffer(backBuffer);

	if (quadTree != NULL)
	{
		rendererRoots[renderer] = quadTree;
	}
}

void GDIRenderingEngine::advance()
{
	RECT windowRect;
	GetClientRect(window, &windowRect);
	BitBlt(backBuffer, 0, 0, windowRect.right, windowRect.bottom, NULL, 0, 0, WHITENESS);

	for (unsigned int rendererIndex = 0; rendererIndex < renderers.size(); rendererIndex++)
	{
		for (unsigned int modelIndex = 0; modelIndex < models.size(); modelIndex++)
		{
			if (models[modelIndex]->isVisible())
			{
				models[modelIndex]->render(*renderers[rendererIndex]);
			}
		}

		if (quadTree != NULL)
		{
			const QuadTree& quadTree = static_cast<const QuadTree&>(*rendererRoots[renderers[rendererIndex]]);
			renderQuadTree(*renderers[rendererIndex], quadTree);
		}
	}

	BitBlt(frontBuffer, 0, 0, windowRect.right, windowRect.bottom, backBuffer, 0, 0, SRCCOPY);
	ValidateRect(window, &windowRect);
}

void GDIRenderingEngine::destroy()
{
	SelectObject(backBuffer, backBitmapOld);
	DeleteObject(backBitmap);
	ReleaseDC(window, backBuffer);
	ReleaseDC(window, frontBuffer);
}

HDC GDIRenderingEngine::getBuffer() const
{
	return backBuffer;
}

int GDIRenderingEngine::getHeight() const
{
	return height;
}

QuadTree* GDIRenderingEngine::getQuadTree() const
{
	return quadTree;
}

int GDIRenderingEngine::getWidth() const
{
	return width;
}

void GDIRenderingEngine::init()
{
	RECT windowRect;
	GetClientRect(window, &windowRect);

	frontBuffer = GetDC(window);
	backBuffer = CreateCompatibleDC(frontBuffer);
	backBitmap = CreateCompatibleBitmap(frontBuffer, windowRect.right, windowRect.bottom);
	backBitmapOld = (HBITMAP) SelectObject(backBuffer, backBitmap);

	for (unsigned int index = 0; index < renderers.size(); index++)
	{
		static_cast<GDIRenderer*>(renderers[index])->setBuffer(backBuffer);
	}
}

void GDIRenderingEngine::removeEntity(const Entity& entity)
{
	vector<Model*> entityModels = entity.getComponents<Model>();
	for (unsigned int index = 0; index < entityModels.size(); index++)
	{
		models.erase(remove(models.begin(), models.end(), entityModels[index]));
	}
}

void GDIRenderingEngine::removeModel(const Model& model)
{
	models.erase(remove(models.begin(), models.end(), &model));
}

void GDIRenderingEngine::removeRenderer(const Renderer& renderer)
{
	renderers.erase(remove(renderers.begin(), renderers.end(), &renderer));
	rendererRoots.erase(&renderer);
	delete &renderer;
}

void GDIRenderingEngine::renderQuadTree(Renderer& renderer, const QuadTree& quadTree) const
{
	for (unsigned int index = 0; index < quadTree.getModels().size(); index++)
	{
		if (quadTree.getModels()[index]->isVisible())
		{
			quadTree.getModels()[index]->render(renderer);
		}
	}

	for (unsigned int index = 0; index < quadTree.getChildren().size(); index++)
	{
		renderQuadTree(renderer, *quadTree.getChildren()[index]);
	}
}

void GDIRenderingEngine::setHeight(int height)
{
	this->height = height;
}

void GDIRenderingEngine::setQuadTree(QuadTree* quadTree)
{
	this->quadTree = quadTree;
}

void GDIRenderingEngine::setRendererRoot(const Renderer& renderer, const Tree& node)
{
	rendererRoots[&renderer] = &node;
}

void GDIRenderingEngine::setWidth(int width)
{
	this->width = width;
}
