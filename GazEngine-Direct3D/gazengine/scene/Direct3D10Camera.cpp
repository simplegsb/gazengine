#include <d3dx10.h>

#include "Direct3D10Camera.h"

Direct3D10Camera::Direct3D10Camera() :
	farClippingDistance(1000.0f),
	frameHeight(0.0f),
	frameWidth(0.0f),
	nearClippingDistance(0.1f),
	node(NULL),
	projection(),
	translation(0.0f, 0.0f, 0.0f),
	view()
{
}

float Direct3D10Camera::getFarClippingDistance() const
{
	return farClippingDistance;
}

Matrix44 Direct3D10Camera::getFinalTransformation() const
{
	if (node != NULL)
	{
		Matrix44 nodeView = node->getAbsoluteTransformation();
		nodeView.invert();

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

Vector3 Direct3D10Camera::getTranslation() const
{
	return translation;
}

void Direct3D10Camera::lookAt(const Vector3& target, const Vector3& up)
{
	D3DXVECTOR3 d3dxTarget(target.getData());
	D3DXVECTOR3 d3dxTranslation(translation.getData());
	D3DXVECTOR3 d3dxUp(up.getData());
	D3DXMATRIX d3dxView;

	D3DXMatrixLookAtLH(&d3dxView, &d3dxTranslation, &d3dxTarget, &d3dxUp);

	view.setData((float*) d3dxView);
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
	D3DXMATRIX d3dxProjection;

	D3DXMatrixOrthoLH(&d3dxProjection, width, height, nearClippingDistance, farClippingDistance);

	projection.setData((float*) d3dxProjection);

	frameHeight = height;
	frameWidth = width;
}

void Direct3D10Camera::setPerspective(float yAxisFieldOfView, float aspectRatio)
{
	D3DXMATRIX d3dxProjection;

	D3DXMatrixPerspectiveFovLH(&d3dxProjection, yAxisFieldOfView, aspectRatio, nearClippingDistance, farClippingDistance);

	projection.setData((float*) d3dxProjection);

	float halfYAxisFieldOfView = yAxisFieldOfView / 2.0f;
	float unitCircleCos = 1 - pow(cos(halfYAxisFieldOfView), 2.0f);
	float unitCircleSin = 1 - pow(sin(halfYAxisFieldOfView), 2.0f);

	float sin = (nearClippingDistance / unitCircleCos) * unitCircleSin;

	frameHeight = sin * 2.0f;
	frameWidth = frameHeight * aspectRatio;
}

void Direct3D10Camera::setTranslation(const Vector3& translation)
{
	this->translation = translation;
}
