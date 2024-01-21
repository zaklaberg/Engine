#include "framework.h"
#include "Main.h"

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
    // WM_ACTIVATE is sent when the window is activated or deactivated.  
    // We pause the game when the window is deactivated and unpause it 
    // when it becomes active.  
    case WM_ACTIVATE:
        if (LOWORD(wParam) == WA_INACTIVE)
        {
            pThis->mIsAppPaused = true;
            pThis->mTimer.Stop();
        }
        else
        {
            pThis->mIsAppPaused = false;
            pThis->mTimer.Start();
        }
        return 0;
    case WM_ENTERSIZEMOVE:
        pThis->mIsAppPaused = true;
        pThis->mIsResizing = true;
        pThis->mTimer.Stop();
        return 0;

        // WM_EXITSIZEMOVE is sent when the user releases the resize bars.
        // Here we reset everything based on the new window dimensions.
    case WM_EXITSIZEMOVE:
        pThis->mIsAppPaused = false;
        pThis->mIsResizing = false;
        pThis->mTimer.Start();

        pThis->OnResize();
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_SIZE:
		// Save the new client area dimensions.
		pThis->mClientWidth = LOWORD(lParam);
		pThis->mClientHeight = HIWORD(lParam);

		if (wParam == SIZE_MINIMIZED)
		{
			pThis->mIsAppPaused = true;
			pThis->mIsMinimized = true;
			pThis->mIsMaximized = false;
		}
		else if (wParam == SIZE_MAXIMIZED)
		{
			pThis->mIsAppPaused = false;
			pThis->mIsMinimized = false;
			pThis->mIsMaximized = true;
			pThis->OnResize();
		}
		else if (wParam == SIZE_RESTORED)
		{

			// Restoring from minimized state?
			if (pThis->mIsMinimized)
			{
				pThis->mIsAppPaused = false;
				pThis->mIsMinimized = false;
				pThis->OnResize();
			}

			// Restoring from maximized state?
			else if (pThis->mIsMaximized)
			{
				pThis->mIsAppPaused = false;
				pThis->mIsMaximized = false;
				pThis->OnResize();
			}
			else if (pThis->mIsResizing)
			{
				// If user is dragging the resize bars, we do not resize 
				// the buffers here because as the user continuously 
				// drags the resize bars, a stream of WM_SIZE messages are
				// sent to the window, and it would be pointless (and slow)
				// to resize for each WM_SIZE message received from dragging
				// the resize bars.  So instead, we reset after the user is 
				// done resizing the window and releases the resize bars, which 
				// sends a WM_EXITSIZEMOVE message.
			}
			else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
			{
				pThis->OnResize();
			}
		}
		return 0;

	// The WM_MENUCHAR message is sent when a menu is active and the user presses 
	// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		// Don't beep when we alt-enter.
		return MAKELRESULT(0, MNC_CLOSE);

		// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		// OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		// OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		// OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_KEYUP:
		// OnKeyUp(wParam, lParam);
		return 0;
	case WM_KEYDOWN:
		// OnKeyDown(wParam, lParam);
		return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}