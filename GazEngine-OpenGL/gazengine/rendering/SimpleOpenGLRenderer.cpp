#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <gazengine/math/Math.h>
#include <gazengine/math/MathFunctions.h>
#include <gazengine/math/Matrix.h>
#include <gazengine/model/shape/Capsule.h>
#include <gazengine/model/shape/Cylinder.h>
#include <gazengine/model/shape/Sphere.h>
#include <gazengine/model/shape/Torus.h>

#include "SimpleOpenGLRenderer.h"

using namespace std;

void SimpleOpenGLRenderer::dispose()
{
	glPointSize(1.0f);
}

int SimpleOpenGLRenderer::getOpenGLDrawingMode(Model::PrimitiveType primitiveType)
{
	if (primitiveType == Model::POINTS)
	{
		return GL_POINTS;
	}
	else if (primitiveType == Model::LINE_LIST)
	{
		return GL_LINE;
	}
	else if (primitiveType == Model::LINE_STRIP)
	{
		return GL_LINE_STRIP;
	}
	else if (primitiveType == Model::TRIANGLE_LIST)
	{
		return GL_TRIANGLES;
	}
	else if (primitiveType == Model::TRIANGLE_STRIP)
	{
		return GL_TRIANGLE_STRIP;
	}

	return -1;
}

void SimpleOpenGLRenderer::init()
{
	glPointSize(2.0f);
}

void SimpleOpenGLRenderer::render(const Capsule& model)
{
	glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());

	gluCylinder(gluNewQuadric(), model.getRadius(), model.getRadius(), model.getLength(),
		model.getLevelOfDetail(), model.getLevelOfDetail());

	glPushMatrix();
	{
		gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());

		Matrix44 transformation;
		getTranslation3(transformation).Z() = model.getLength();

		glMultMatrixf(transformation.getData());

		gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());
	}
	glPopMatrix();
}

void SimpleOpenGLRenderer::render(const Circle&)
{
}

void SimpleOpenGLRenderer::render(const Cube&)
{
}

void SimpleOpenGLRenderer::render(const Cylinder& model)
{
	glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());

	gluCylinder(gluNewQuadric(), model.getRadius(), model.getRadius(), model.getLength(),
		model.getLevelOfDetail(), model.getLevelOfDetail());

	glPushMatrix();
	{
		Matrix44 transformation;
		Vector4 rotationAxis;
		rotationAxis.Y() = 1.0f;
		rotate(transformation, Math::PI, rotationAxis);

		glMultMatrixf(transformation.getData());

		gluDisk(gluNewQuadric(), 0.0f, model.getRadius(), model.getLevelOfDetail(), 1);
	}
	glPopMatrix();

	glPushMatrix();
	{
		Matrix44 transformation;
		getTranslation3(transformation).Z() = model.getLength();

		glMultMatrixf(transformation.getData());

		gluDisk(gluNewQuadric(), 0.0f, model.getRadius(), model.getLevelOfDetail(), 1);
	}
	glPopMatrix();
}

void SimpleOpenGLRenderer::render(const Line2&)
{
}

void SimpleOpenGLRenderer::render(const Mesh&)
{
}

void SimpleOpenGLRenderer::render(const Sphere& model)
{
	glColor4f(model.getColour().R(), model.getColour().G(), model.getColour().B(), model.getColour().A());

	gluSphere(gluNewQuadric(), model.getRadius(), model.getLevelOfDetail(), model.getLevelOfDetail());
}

void SimpleOpenGLRenderer::render(const Text&)
{
}

void SimpleOpenGLRenderer::render(const Torus&)
{
}
