#pragma once

#include "resource.h"
#include <string>
#include "Timer.h"

class Main 
{
public:
	Main(HINSTANCE hInstance, std::wstring appTitle = L"Main", std::wstring wndClassName = L"Main");
	Main(Main const&) = delete;
	void operator=(Main const&) = delete;
	virtual ~Main();

	bool InitMainWindow();
	int Run();
	void OnResize();
	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	ATOM RegisterWndClass();
	BOOL InitWndInstance();

protected:
	HINSTANCE appInstance = nullptr;
	HWND mainWnd = nullptr;
	std::wstring wndClassName;
	std::wstring appTitle;

	bool isMaximized = false;
	bool isMinimized = false;
	bool isResizing = false;
	bool isFullScreen = false;
	bool isAppPaused = false;

	int clientWidth = 0;
	int clientHeight = 0;

	Timer timer;
};
