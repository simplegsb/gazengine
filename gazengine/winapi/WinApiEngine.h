#ifndef WINAPIENGINE_H_
#define WINAPIENGINE_H_

#include <string>
#include <windows.h>

#include "../engine/Engine.h"

class WinApiEngine : public Engine
{
	public:
		WinApiEngine(const std::wstring& title, HINSTANCE instance, int commandShow);

		virtual ~WinApiEngine();
			
		void advance();

		void destroy();

		int getHeight() const;

		const MSG& getMessage() const;

		int getWidth() const;

		HWND getWindow() const;

		void init();

		void setDialog(HWND dialog);

		void setHeight(int height);

		void setWidth(int width);

	private:
		int commandShow;

		HWND dialog;

		int height;

		HINSTANCE instance;

		MSG message;

		std::wstring title;

		int width;

		HWND window;

		RECT getAdjustedRectangle() const;

		void registerWindowClass();
};

#endif /* WINAPIENGINE_H_ */
