#include "stdafx.h"

#include "Direct3D10Text.h"

using namespace std;

Direct3D10Text::Direct3D10Text(ID3D10Device& device, const wstring text, const RECT& rectangle, const D3DXCOLOR colour) :
	colour(colour), device(device), font(NULL), rectangle(rectangle), text(text)
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

Direct3D10Text::~Direct3D10Text()
{
	if (font != NULL)
	{
		font->Release();
	}
}

void Direct3D10Text::draw()
{
	font->DrawText(NULL, text.data(), text.size(), &rectangle, DT_NOCLIP, colour);

	// It turns out ID3DXFont::DrawText() has no regard for the state of our rendering engine so lets try and restore
	// it... ideally we should query these states before hand and restore them to their previous values.
	device.OMSetDepthStencilState(0, 0);
	float blendFactors[] = {0.0f, 0.0f, 0.0f, 0.0f};
	device.OMSetBlendState(0, blendFactors, 0xffffffff);
}

Model::PrimitiveType Direct3D10Text::getPrimitiveType() const
{
	return Model::NA;
}
		
const wstring Direct3D10Text::getText() const
{
	return text;
}
		
void Direct3D10Text::setText(const wstring text)
{
	this->text = text;
}
