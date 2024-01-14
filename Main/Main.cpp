// Main.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"



Main::Main(HINSTANCE hInstance, std::wstring appTitle, std::wstring wndClassName) :
    mAppInstance(hInstance),
    mAppTitle(appTitle),
    mWndClassName(wndClassName)
{

}
Main::~Main() {

}
bool Main::InitMainWindow() {
    this->RegisterWndClass();
    return this->InitWndInstance();
}

BOOL Main::InitWndInstance() {
    HWND hWnd = CreateWindowW(mWndClassName.c_str(), mAppTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mAppInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return TRUE;
}

int Main::Run() {
    HACCEL hAccelTable = LoadAccelerators(mAppInstance, MAKEINTRESOURCE(IDC_MAIN));
    MSG msg = { 0 };

    // mTimer.Reset();

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
            //mTimer.Tick();

            /* if (!mAppPaused)
            {
                CalculateFrameStats();
                Update(mTimer);
                Draw(mTimer);
            }
            else
            {
                Sleep(100);
            } */
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
    main.InitMainWindow();
    // Init renderer
    // Init physics 
    

    // Run loop
    return main.Run();
}


LRESULT CALLBACK Main::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Main* pThis;

    if (message == WM_NCCREATE)
    {
        pThis = static_cast<Main*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);

        SetLastError(0);
        if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
        {
            if (GetLastError() != 0)
                return FALSE;
        }
    }
    else
    {
        pThis = reinterpret_cast<Main*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (!pThis)
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    
    switch (message)
    {
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    return 0;
}
