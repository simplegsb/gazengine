#include <gazengine/input/KeyboardButtonEvent.h>
#include <gazengine/input/MouseButtonEvent.h>
#include <gazengine/input/MouseMoveEvent.h>
#include <gazengine/Events.h>
#include <gazengine/GazEngine.h>
#include <gazengine/Messages.h>

#include "WinApiEngine.h"

using namespace std;

map<unsigned char, Keyboard::Button> winapiAsciiKeyboardButtonMap = createAsciiKeyboardButtonMap();

LRESULT CALLBACK handleEvent(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_DESTROY)
    {
		GazEngine::stop();
        return 0;
    }
	else if (message == WM_KEYDOWN)
	{
		KeyboardButtonEvent keyboardButtonEvent;
		keyboardButtonEvent.buttonState = Button::DOWN;

		if (wParam == VK_ADD)
		{
			keyboardButtonEvent.button = Keyboard::PLUS;
		}
		else if (wParam == VK_DOWN)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_DOWN;
		}
		else if (wParam == VK_F1)
		{
			keyboardButtonEvent.button = Keyboard::F1;
		}
		else if (wParam == VK_F2)
		{
			keyboardButtonEvent.button = Keyboard::F2;
		}
		else if (wParam == VK_F3)
		{
			keyboardButtonEvent.button = Keyboard::F3;
		}
		else if (wParam == VK_F4)
		{
			keyboardButtonEvent.button = Keyboard::F4;
		}
		else if (wParam == VK_F5)
		{
			keyboardButtonEvent.button = Keyboard::F5;
		}
		else if (wParam == VK_F6)
		{
			keyboardButtonEvent.button = Keyboard::F6;
		}
		else if (wParam == VK_F7)
		{
			keyboardButtonEvent.button = Keyboard::F7;
		}
		else if (wParam == VK_F8)
		{
			keyboardButtonEvent.button = Keyboard::F8;
		}
		else if (wParam == VK_F9)
		{
			keyboardButtonEvent.button = Keyboard::F9;
		}
		else if (wParam == VK_F10)
		{
			keyboardButtonEvent.button = Keyboard::F10;
		}
		else if (wParam == VK_F11)
		{
			keyboardButtonEvent.button = Keyboard::F11;
		}
		else if (wParam == VK_F12)
		{
			keyboardButtonEvent.button = Keyboard::F12;
		}
		else if (wParam == VK_LEFT)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_LEFT;
		}
		else if (wParam == VK_RIGHT)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_RIGHT;
		}
		else if (wParam == VK_SUBTRACT)
		{
			keyboardButtonEvent.button = Keyboard::MINUS;
		}
		else if (wParam == VK_TAB)
		{
			keyboardButtonEvent.button = Keyboard::TAB;
		}
		else if (wParam == VK_UP)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_UP;
		}
		else if (winapiAsciiKeyboardButtonMap.find(static_cast<unsigned char>(wParam)) != winapiAsciiKeyboardButtonMap.end())
		{
			keyboardButtonEvent.button = winapiAsciiKeyboardButtonMap[static_cast<unsigned char>(wParam)];
			keyboardButtonEvent.character = static_cast<unsigned char>(wParam);
		}

		Messages::send(Events::KEYBOARD_BUTTON, &keyboardButtonEvent);
	}
	else if (message == WM_KEYUP)
	{
		KeyboardButtonEvent keyboardButtonEvent;
		keyboardButtonEvent.buttonState = Button::UP;

		if (wParam == VK_ADD)
		{
			keyboardButtonEvent.button = Keyboard::PLUS;
		}
		else if (wParam == VK_DOWN)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_DOWN;
		}
		else if (wParam == VK_F1)
		{
			keyboardButtonEvent.button = Keyboard::F1;
		}
		else if (wParam == VK_F2)
		{
			keyboardButtonEvent.button = Keyboard::F2;
		}
		else if (wParam == VK_F3)
		{
			keyboardButtonEvent.button = Keyboard::F3;
		}
		else if (wParam == VK_F4)
		{
			keyboardButtonEvent.button = Keyboard::F4;
		}
		else if (wParam == VK_F5)
		{
			keyboardButtonEvent.button = Keyboard::F5;
		}
		else if (wParam == VK_F6)
		{
			keyboardButtonEvent.button = Keyboard::F6;
		}
		else if (wParam == VK_F7)
		{
			keyboardButtonEvent.button = Keyboard::F7;
		}
		else if (wParam == VK_F8)
		{
			keyboardButtonEvent.button = Keyboard::F8;
		}
		else if (wParam == VK_F9)
		{
			keyboardButtonEvent.button = Keyboard::F9;
		}
		else if (wParam == VK_F10)
		{
			keyboardButtonEvent.button = Keyboard::F10;
		}
		else if (wParam == VK_F11)
		{
			keyboardButtonEvent.button = Keyboard::F11;
		}
		else if (wParam == VK_F12)
		{
			keyboardButtonEvent.button = Keyboard::F12;
		}
		else if (wParam == VK_LEFT)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_LEFT;
		}
		else if (wParam == VK_RIGHT)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_RIGHT;
		}
		else if (wParam == VK_SUBTRACT)
		{
			keyboardButtonEvent.button = Keyboard::MINUS;
		}
		else if (wParam == VK_UP)
		{
			keyboardButtonEvent.button = Keyboard::ARROW_UP;
		}
		else if (winapiAsciiKeyboardButtonMap.find(static_cast<unsigned char>(wParam)) != winapiAsciiKeyboardButtonMap.end())
		{
			keyboardButtonEvent.button = winapiAsciiKeyboardButtonMap[static_cast<unsigned char>(wParam)];
			keyboardButtonEvent.character = static_cast<unsigned char>(wParam);
		}

		Messages::send(Events::KEYBOARD_BUTTON, &keyboardButtonEvent);
	}
	else if (message == WM_LBUTTONDOWN)
	{
		MouseButtonEvent mouseButtonEvent;
		mouseButtonEvent.button = Mouse::LEFT;
		mouseButtonEvent.buttonState = Button::DOWN;
		mouseButtonEvent.x = static_cast<int>(LOWORD(lParam));
		mouseButtonEvent.y = static_cast<int>(HIWORD(lParam));

		Messages::send(Events::MOUSE_BUTTON, &mouseButtonEvent);
	}
	else if (message == WM_LBUTTONUP)
	{
		MouseButtonEvent mouseButtonEvent;
		mouseButtonEvent.button = Mouse::LEFT;
		mouseButtonEvent.buttonState = Button::UP;
		mouseButtonEvent.x = static_cast<int>(LOWORD(lParam));
		mouseButtonEvent.y = static_cast<int>(HIWORD(lParam));

		Messages::send(Events::MOUSE_BUTTON, &mouseButtonEvent);
	}
	else if (message == WM_MOUSEMOVE)
	{
		MouseMoveEvent mouseMoveEvent;
		mouseMoveEvent.x = static_cast<int>(LOWORD(lParam));
		mouseMoveEvent.y = static_cast<int>(HIWORD(lParam));

		Messages::send(Events::MOUSE_MOVE, &mouseMoveEvent);
	}
	else if (message == WM_RBUTTONDOWN)
	{
		MouseButtonEvent mouseButtonEvent;
		mouseButtonEvent.button = Mouse::RIGHT;
		mouseButtonEvent.buttonState = Button::DOWN;
		mouseButtonEvent.x = static_cast<int>(LOWORD(lParam));
		mouseButtonEvent.y = static_cast<int>(HIWORD(lParam));

		Messages::send(Events::MOUSE_BUTTON, &mouseButtonEvent);
	}
	else if (message == WM_RBUTTONUP)
	{
		MouseButtonEvent mouseButtonEvent;
		mouseButtonEvent.button = Mouse::RIGHT;
		mouseButtonEvent.buttonState = Button::UP;
		mouseButtonEvent.x = static_cast<int>(LOWORD(lParam));
		mouseButtonEvent.y = static_cast<int>(HIWORD(lParam));

		Messages::send(Events::MOUSE_BUTTON, &mouseButtonEvent);
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

void WinApiEngine::addEntity(Entity*)
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

void WinApiEngine::createWindow()
{
	registerWindowClass();

	RECT adjustedRectangle = getAdjustedRectangle();
	int adjustedWidth = adjustedRectangle.right - adjustedRectangle.left;
	int adjustedHeight = adjustedRectangle.bottom - adjustedRectangle.top;

	window = CreateWindowEx(NULL, L"WindowClass", title.data(), WS_OVERLAPPEDWINDOW, 0, 0, adjustedWidth,
		adjustedHeight, NULL, NULL, instance, NULL);
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

void WinApiEngine::grabFocus()
{
	SetFocus(window);
}

void WinApiEngine::init()
{
    ShowWindow(window, commandShow);

	if (dialog != NULL)
	{
		ShowWindow(dialog, commandShow);
	}
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

void WinApiEngine::removeEntity(const Entity&)
{
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
