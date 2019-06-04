#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
HWND AddControls(HWND); // Creates the static and edit controls, returns the handle to the edit control.

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	// Window Class Registration
	const wchar_t CLASS_NAME[] = L"OCC Student Veterans Association Sign-In";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Window Creation
	HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"OCC Student Veterans Association Sign-In", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 200, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	// Remove menu and disable dragging
	SetWindowLongPtr(hwnd, GWL_STYLE, 0);

	// Display Window
	ShowWindow(hwnd, nCmdShow);

	// Message Loop
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		{
			// call functions to display static edit controls
			// store handle to edit control
			HWND hEdit = AddControls(hwnd);
			break;
		}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	/*case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
		}
		return 0;
		break;*/

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}
}

HWND AddControls(HWND hwnd)
{
	CreateWindow(L"STATIC", L"Please enter your ID below:", WS_VISIBLE | WS_CHILD | SS_CENTER, 155, 50, 190, 20, hwnd, NULL, NULL, NULL);
	return CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 90, 300, 20, hwnd, NULL, NULL, NULL);
}
