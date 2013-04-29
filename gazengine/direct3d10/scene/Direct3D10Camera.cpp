#include "Direct3D10Camera.h"

Direct3D10Camera::Direct3D10Camera() :
	farClippingDistance(1000.0f),
	frameHeight(0.0f),
	nearClippingDistance(0.1f),
	node(NULL),
	projection(),
	translation(),
	view(),
	frameWidth(0.0f)
{
}

float Direct3D10Camera::getFarClippingDistance() const
{
	return farClippingDistance;
}

D3DXMATRIX Direct3D10Camera::getFinalTransformation() const
{
	if (node != NULL)
	{
		D3DXMATRIX nodeView = node->getAbsoluteTransformation();
		D3DXMatrixInverse(&nodeView, NULL, &nodeView);

		return nodeView * projection;
	}

	return view * projection;
}

float Direct3D10Camera::getFrameHeight() const
{
	return frameHeight;
}

float Direct3D10Camera::getFrameWidth() const
{
	return frameWidth;
}

float Direct3D10Camera::getNearClippingDistance() const
{
	return nearClippingDistance;
}

SimpleTree* Direct3D10Camera::getNode()
{
	return node;
}

D3DXVECTOR3 Direct3D10Camera::getTranslation() const
{
	return translation;
}

void Direct3D10Camera::lookAt(const D3DXVECTOR3& target, const D3DXVECTOR3& up)
{
	D3DXMatrixLookAtLH(&view, &translation, &target, &up);
}

void Direct3D10Camera::setFarClippingDistance(float farClippingDistance)
{
	this->farClippingDistance = farClippingDistance;
}

void Direct3D10Camera::setNearClippingDistance(float nearClippingDistance)
{
	this->nearClippingDistance = nearClippingDistance;
}

void Direct3D10Camera::setNode(SimpleTree* node)
{
	this->node = node;
}

void Direct3D10Camera::setOrthogonal(float width, float height)
{
	D3DXMatrixOrthoLH(&projection, width, height, nearClippingDistance, farClippingDistance);

	frameHeight = height;
	frameWidth = width;
}

void Direct3D10Camera::setPerspective(float yAxisFieldOfView, float aspectRatio)
{
	D3DXMatrixPerspectiveFovLH(&projection, yAxisFieldOfView, aspectRatio, nearClippingDistance, farClippingDistance);

	float halfYAxisFieldOfView = yAxisFieldOfView / 2.0f;
	float unitCircleCos = 1 - pow(cos(halfYAxisFieldOfView), 2.0f);
	float unitCircleSin = 1 - pow(sin(halfYAxisFieldOfView), 2.0f);

	float sin = (nearClippingDistance / unitCircleCos) * unitCircleSin;

	frameHeight = sin * 2.0f;
	frameWidth = frameHeight * aspectRatio;
}

void Direct3D10Camera::setTranslation(const D3DXVECTOR3& translation)
{
	this->translation = translation;
}
