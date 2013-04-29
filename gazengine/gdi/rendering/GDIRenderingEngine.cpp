#include "stdafx.h"

#include <algorithm>

#include "../model/GDIMesh.h"
#include "GDIRenderingEngine.h"

using namespace std;

GDIRenderingEngine::GDIRenderingEngine(HWND window) :
	backBitmap(NULL), backBitmapOld(NULL), backBuffer(NULL), frontBuffer(NULL), height(600), models(), quadTree(NULL),
	width(800), window(window)
{
}

GDIRenderingEngine::~GDIRenderingEngine()
{
	for (unsigned int index = 0; index < models.size(); index++)
	{
		delete models.at(index);
	}

	if (quadTree != NULL)
	{
		delete quadTree;
	}
}

void GDIRenderingEngine::addModel(Model* model)
{
	models.push_back(model);
}

void GDIRenderingEngine::advance()
{
	RECT windowRect;
	GetClientRect(window, &windowRect);
	BitBlt(backBuffer, 0, 0, windowRect.right, windowRect.bottom, NULL, 0, 0, WHITENESS);

	for (unsigned int index = 0; index < models.size(); index++)
	{
		models.at(index)->draw();
	}

	if (quadTree != NULL)
	{
		drawQuadTree(*quadTree);
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

void GDIRenderingEngine::drawQuadTree(const QuadTree& quadTree) const
{
	for (unsigned int index = 0; index < quadTree.getModels().size(); index++)
	{
		quadTree.getModels().at(index)->draw();
	}

	for (unsigned int index = 0; index < quadTree.getChildren().size(); index++)
	{
		drawQuadTree(*quadTree.getChildren().at(index));
	}
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
}

void GDIRenderingEngine::removeModel(const Model& model)
{
	models.erase(remove(models.begin(), models.end(), &model));
}

void GDIRenderingEngine::setHeight(int height)
{
	this->height = height;
}

void GDIRenderingEngine::setQuadTree(QuadTree* quadTree)
{
	this->quadTree = quadTree;
}

void GDIRenderingEngine::setWidth(int width)
{
	this->width = width;
}
