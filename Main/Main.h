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
	HINSTANCE mAppInstance = nullptr;
	HWND mMainWnd = nullptr;
	std::wstring mWndClassName;
	std::wstring mAppTitle;

	bool mIsMaximized = false;
	bool mIsMinimized = false;
	bool mIsResizing = false;
	bool mIsFullScreen = false;
	bool mIsAppPaused = false;

	int mClientWidth = 800;
	int mClientHeight = 600;

	Timer mTimer;
	std::unique_ptr<D3Base> mRenderer;
};
