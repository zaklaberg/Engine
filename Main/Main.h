#pragma once

#include "resource.h"
#include <string>
#include "Timer.h"
#include <memory>
#include "D3Base.h"

class Main 
{
public:
	Main(HINSTANCE hInstance, std::wstring appTitle = L"Main", std::wstring wndClassName = L"Main");
	Main(Main const&) = delete;
	void operator=(Main const&) = delete;
	virtual ~Main();

	int Run();
	void OnResize();
	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	bool InitMainWindow();
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

	int clientWidth = 800;
	int clientHeight = 600;

	Timer timer;
	std::unique_ptr<D3Base> renderer;
};
