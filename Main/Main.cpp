// Main.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"

Main::Main(HINSTANCE hInstance, std::wstring appTitle, std::wstring wndClassName) :
    appInstance(hInstance),
    appTitle(appTitle),
    wndClassName(wndClassName)
{

}
Main::~Main() {

}
bool Main::InitMainWindow() {
    this->RegisterWndClass();
    return this->InitWndInstance();
}

BOOL Main::InitWndInstance() {
    HWND hWnd = CreateWindowW(wndClassName.c_str(), appTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, appInstance, this);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return TRUE;
}

int Main::Run() {
    HACCEL hAccelTable = LoadAccelerators(appInstance, MAKEINTRESOURCE(IDC_MAIN));
    MSG msg = { 0 };

    timer.Reset();

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

            if (!isAppPaused)
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
    wcex.hInstance = appInstance;
    wcex.hIcon = LoadIcon(appInstance, MAKEINTRESOURCE(IDI_MAIN));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = wndClassName.c_str();
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

void Main::OnResize()
{
    
}



