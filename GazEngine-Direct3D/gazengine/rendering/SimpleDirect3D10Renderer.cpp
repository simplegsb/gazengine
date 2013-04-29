#include "SimpleDirect3D10Renderer.h"

#include <gazengine/model/Text.h>

#include "../model/Direct3D10Mesh.h"

SimpleDirect3D10Renderer::SimpleDirect3D10Renderer(ID3D10Device& device) :
	device(device),
	font(NULL)
{
	D3DX10_FONT_DESC fontDescription;
	fontDescription.Height = 24;
    fontDescription.Width = 0;
    fontDescription.Weight = 0;
    fontDescription.MipLevels = 1;
    fontDescription.Italic = false;
    fontDescription.CharSet = DEFAULT_CHARSET;
    fontDescription.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDescription.Quality = DEFAULT_QUALITY;
    fontDescription.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    wcscpy_s(fontDescription.FaceName, L"Times New Roman");

	D3DX10CreateFontIndirect(&device, &fontDescription, &font);
}

SimpleDirect3D10Renderer::~SimpleDirect3D10Renderer()
{
	if (font != NULL)
	{
		font->Release();
	}
}

void SimpleDirect3D10Renderer::dispose()
{
}

void SimpleDirect3D10Renderer::init()
{
}

void SimpleDirect3D10Renderer::render(const Capsule&)
{
}

void SimpleDirect3D10Renderer::render(const Circle&)
{
}

void SimpleDirect3D10Renderer::render(const Cylinder&)
{
}

void SimpleDirect3D10Renderer::render(const Line2&)
{
}

void SimpleDirect3D10Renderer::render(const Mesh& model)
{
	const Direct3D10Mesh* d3dMesh = dynamic_cast<const Direct3D10Mesh*>(&model);
	if (d3dMesh == NULL)
	{
		return;
	}

	d3dMesh->getMesh()->DrawSubset(0);
}

void SimpleDirect3D10Renderer::render(const Sphere&)
{
}

void SimpleDirect3D10Renderer::render(const Text& model)
{
	D3DXCOLOR d3dColor(model.getColour().getData());
	RECT rectangle;
	rectangle.left = static_cast<LONG>(model.getPosition().X());
	rectangle.top = static_cast<LONG>(model.getPosition().Y());
	wstring wtext(model.getText().begin(), model.getText().end());

	font->DrawText(NULL, wtext.data(), wtext.size(), &rectangle, DT_NOCLIP, d3dColor);

	// It turns out ID3DXFont::DrawText() has no regard for the state of our rendering engine so lets try and restore
	// it... ideally we should query these states before hand and restore them to their previous values.
	device.OMSetDepthStencilState(0, 0);
	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};
	device.OMSetBlendState(0, blendFactors, 0xffffffff);
}

void SimpleDirect3D10Renderer::render(const Torus&)
{
}
