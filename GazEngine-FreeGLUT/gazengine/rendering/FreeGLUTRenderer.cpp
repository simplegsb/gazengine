#include <windows.h>

#include <GL/gl.h>
#include <GL/glut.h>

#include <gazengine/model/shape/Capsule.h>
#include <gazengine/model/shape/Cylinder.h>
#include <gazengine/model/shape/Sphere.h>
#include <gazengine/model/shape/Torus.h>
#include <gazengine/model/Text.h>
#include <GL/glut.h>

#include "FreeGLUTRenderer.h"

using namespace std;

FreeGLUTRenderer::FreeGLUTRenderer(Renderer* renderer) :
	renderer(renderer)
{
}

FreeGLUTRenderer::~FreeGLUTRenderer()
{
	if (renderer != NULL)
	{
		delete renderer;
	}
}

void FreeGLUTRenderer::dispose()
{
	renderer->dispose();
}

void FreeGLUTRenderer::init()
{
	renderer->init();
}

void FreeGLUTRenderer::render(const Capsule& model)
{
	renderer->render(model);
}

void FreeGLUTRenderer::render(const Circle& model)
{
	renderer->render(model);
}

void FreeGLUTRenderer::render(const Cylinder& model)
{
	renderer->render(model);
}

void FreeGLUTRenderer::render(const Line2& model)
{
	renderer->render(model);
}

void FreeGLUTRenderer::render(const Mesh& model)
{
	renderer->render(model);
}

void FreeGLUTRenderer::render(const Sphere& model)
{
	renderer->render(model);
}

void FreeGLUTRenderer::render(const Text& model)
{
	glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());
	glRasterPos2f(model.getPosition().X(), model.getPosition().Y());

	const string& text = model.getText();

	for (unsigned int index = 0; index < text.length(); index++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[index]);
	}
}

void FreeGLUTRenderer::render(const Torus& model)
{
	glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());

	if (model.getPrimitiveType() == Model::LINE_LIST ||
		model.getPrimitiveType() == Model::LINE_STRIP)
	{
		glutWireTorus(model.getInnerRadius(), model.getOuterRadius(), model.getLevelOfDetail(),
			model.getLevelOfDetail());
	}
	else if (model.getPrimitiveType() == Model::TRIANGLE_LIST ||
		model.getPrimitiveType() == Model::TRIANGLE_STRIP)
	{
		glutSolidTorus(model.getInnerRadius(), model.getOuterRadius(), model.getLevelOfDetail(),
			model.getLevelOfDetail());
	}
}
