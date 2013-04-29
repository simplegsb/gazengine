#ifndef DIRECT3D10TEXT_H_
#define DIRECT3D10TEXT_H_

#include <string>

#include <d3dx10.h>

#include "../../model/Model.h"

class Direct3D10Text : public Model
{
	public:
		Direct3D10Text(ID3D10Device& device, const std::wstring text, const RECT& rectangle, const D3DXCOLOR colour);

		virtual ~Direct3D10Text();
		
		void draw();
		
		const std::wstring getText() const;
		
		void setText(const std::wstring text);

	private:
		D3DXCOLOR colour;

		ID3D10Device& device;

		ID3DX10Font* font;

		RECT rectangle;

		std::wstring text;

		Direct3D10Text(const Direct3D10Text& original);

		Direct3D10Text& operator=(const Direct3D10Text& original);
};

#endif /* DIRECT3D10TEXT_H_ */
