#include "stdafx.h"

#include "WinApiEngine.h"

using namespace std;

LRESULT CALLBACK handleEvent(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(window, message, wParam, lParam);
}

WinApiEngine::WinApiEngine(const wstring& title, HINSTANCE instance, int commandShow) :
		commandShow(commandShow), dialog(NULL), height(600), instance(instance), message(), title(title), width(800),
		window()
{
}

WinApiEngine::~WinApiEngine()
{
}

void WinApiEngine::advance()
{
	if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
    {
		// It's poorly named, but IsDialogMessage actually forwards the message to the dialog.
		if(dialog == NULL || !IsDialogMessage(dialog, &message))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
    }
}

void WinApiEngine::destroy()
{
}

RECT WinApiEngine::getAdjustedRectangle() const
{
	RECT windowRectangle;
	windowRectangle.bottom = height;
	windowRectangle.left = 0;
	windowRectangle.right = width;
	windowRectangle.top = 0;

    AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, false);
	
	return windowRectangle;
}

int WinApiEngine::getHeight() const
{
	return height;
}

const MSG& WinApiEngine::getMessage() const
{
	return message;
}

int WinApiEngine::getWidth() const
{
	return width;
}

HWND WinApiEngine::getWindow() const
{
	return window;
}

void WinApiEngine::init()
{
	registerWindowClass();

	RECT adjustedRectangle = getAdjustedRectangle();
	int adjustedWidth = adjustedRectangle.right - adjustedRectangle.left;
	int adjustedHeight = adjustedRectangle.bottom - adjustedRectangle.top;

	window = CreateWindowEx(NULL, L"WindowClass", title.data(), WS_OVERLAPPEDWINDOW, 0, 0, adjustedWidth,
		adjustedHeight, NULL, NULL, instance, NULL);

    ShowWindow(window, commandShow);
}

void WinApiEngine::registerWindowClass()
{
	WNDCLASSEX windowClass;
    ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hInstance = instance;
    windowClass.lpfnWndProc = handleEvent;
    windowClass.lpszClassName = L"WindowClass";
    windowClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClassEx(&windowClass);
}

void WinApiEngine::setDialog(HWND dialog)
{
	this->dialog = dialog;
}

void WinApiEngine::setHeight(int height)
{
	this->height = height;
}

void WinApiEngine::setWidth(int width)
{
	this->width = width;
}
