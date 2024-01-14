#pragma once

#include "resource.h"
#include <string>

class Main 
{
public:
	Main(HINSTANCE hInstance, std::wstring appTitle = L"Main", std::wstring wndClassName = L"Main");
	Main(Main const&) = delete;
	void operator=(Main const&) = delete;
	virtual ~Main();

	bool InitMainWindow();
	int Run();
	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
protected:
	ATOM RegisterWndClass();
	BOOL InitWndInstance();



protected:
	HINSTANCE mAppInstance = nullptr;
	HWND mMainWnd = nullptr;
	bool mIsMaximized = false;
	bool mIsMinimized = false;
	bool mIsResizing = false;
	bool mIsFullScreen = false;
	bool mIsAppPaused = false;
	std::wstring mWndClassName;
	std::wstring mAppTitle;
	// Timer mTimer;
};
