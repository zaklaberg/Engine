// Main.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"
#include <Utilities.h>

Main::Main(HINSTANCE hInstance, std::wstring appTitle, std::wstring wndClassName) :
    mAppInstance(hInstance),
    mAppTitle(appTitle),
    mWndClassName(wndClassName)
{
    this->InitMainWindow();
    this->mRenderer = std::make_unique<D3Base>(mMainWnd, mClientWidth, mClientHeight);
}
Main::~Main() {}
bool Main::InitMainWindow() {
    this->RegisterWndClass();
    return this->InitWndInstance();
}

BOOL Main::InitWndInstance() {
    // Compute window rectangle dimensions based on requested client area dimensions.
    RECT R = { 0L, 0L, (LONG)mClientWidth, (LONG)mClientHeight };

    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
    int width = R.right - R.left;
    int height = R.bottom - R.top;

    HWND hWnd = CreateWindowW(mWndClassName.c_str(), mAppTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, width, height, nullptr, nullptr, mAppInstance, this);

    if (!hWnd)
    {
        return FALSE;
    }
    mMainWnd = hWnd;
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return TRUE;
}

int Main::Run() {
    HACCEL hAccelTable = LoadAccelerators(mAppInstance, MAKEINTRESOURCE(IDC_MAIN));
    MSG msg = { 0 };

    mTimer.Reset();

    while (msg.message != WM_QUIT)
    {
        // If there are Window messages then process them.
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        // Otherwise, do engine stuff.
        else
        {
            mTimer.Tick();

            if (!mIsAppPaused)
            {
                // CalculateFrameStats();
                // Update(timer);
                // Draw(timer);
            }
            else
            {
                Sleep(100);
            }
        }
    }


    return (int)msg.wParam;
}

ATOM Main::RegisterWndClass() {
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = mAppInstance;
    wcex.hIcon = LoadIcon(mAppInstance, MAKEINTRESOURCE(IDI_MAIN));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = mWndClassName.c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    Main main(hInstance, L"Main", L"Main");

    // Run loop
    try {
        return main.Run();
    }
    catch(DxException& e) {
        MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
        return 0;
    }
}

void Main::OnResize()
{
    this->mRenderer->OnResize();
}



