#include <windows.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "OpenGLCamera.h"

using namespace std;

OpenGLCamera::OpenGLCamera() :
	farClippingDistance(1000.0f),
	frameHeight(0.0f),
	frameWidth(0.0f),
	nearClippingDistance(0.1f),
	node(NULL)
{
}

float OpenGLCamera::getFarClippingDistance() const
{
	return farClippingDistance;
}

float OpenGLCamera::getFrameHeight() const
{
	return frameHeight;
}

float OpenGLCamera::getFrameWidth() const
{
	return frameWidth;
}

float OpenGLCamera::getNearClippingDistance() const
{
	return nearClippingDistance;
}

SimpleTree* OpenGLCamera::getNode()
{
	return node;
}

Vector3 OpenGLCamera::getTranslation() const
{
	return Vector3();
}

void OpenGLCamera::lookAt(const Vector3& target, const Vector3& up)
{
	gluLookAt(0.0f, 0.0f, 0.0f, target.X(), target.Y(), target.Z(), up.X(), up.Y(), up.Z());
}

void OpenGLCamera::setFarClippingDistance(float farClippingDistance)
{
	this->farClippingDistance = farClippingDistance;
}

void OpenGLCamera::setFrameHeight(float frameHeight)
{
	this->frameHeight = frameHeight;
}

void OpenGLCamera::setFrameWidth(float frameWidth)
{
	this->frameWidth = frameWidth;
}

void OpenGLCamera::setNearClippingDistance(float nearClippingDistance)
{
	this->nearClippingDistance = nearClippingDistance;
}

void OpenGLCamera::setNode(SimpleTree* node)
{
	this->node = node;
}

void OpenGLCamera::setOrthogonal(float width, float height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-width / 2, width / 2, -height / 2, height / 2, nearClippingDistance, farClippingDistance);

	frameHeight = height;
	frameWidth = width;

	glMatrixMode(GL_MODELVIEW);
}

void OpenGLCamera::setPerspective(float yAxisFieldOfView, float aspectRatio)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float halfYAxisFieldOfView = yAxisFieldOfView / 2.0f;
	float unitCircleCos = 1 - pow(cos(halfYAxisFieldOfView), 2.0f);
	float unitCircleSin = 1 - pow(sin(halfYAxisFieldOfView), 2.0f);

	float sin = (nearClippingDistance / unitCircleCos) * unitCircleSin;

	frameHeight = sin * 2.0f;
	frameWidth = frameHeight * aspectRatio;

	glFrustum(-frameWidth / 2, frameWidth / 2, -frameHeight / 2, frameHeight / 2, nearClippingDistance,
		farClippingDistance);

	glMatrixMode(GL_MODELVIEW);
}

void OpenGLCamera::setTranslation(const Vector3&)
{
}
