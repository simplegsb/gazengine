#include "stdafx.h"

#include "Direct3D10Camera.h"

Direct3D10Camera::Direct3D10Camera() :
	farClippingDistance(1000.0f), nearClippingDistance(1.0f), projection(), translation(), view()
{
}

float Direct3D10Camera::getFarClippingDistance() const
{
	return farClippingDistance;
}

D3DXMATRIX Direct3D10Camera::getFinalTransformation() const
{
	return view * projection;
}

float Direct3D10Camera::getNearClippingDistance() const
{
	return nearClippingDistance;
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

void Direct3D10Camera::setPerspective(float yAxisFieldOfView, float aspectRatio)
{
	D3DXMatrixPerspectiveFovLH(&projection, yAxisFieldOfView, aspectRatio, nearClippingDistance, farClippingDistance);
}

void Direct3D10Camera::setTranslation(const D3DXVECTOR3& translation)
{
	this->translation = translation;
}
