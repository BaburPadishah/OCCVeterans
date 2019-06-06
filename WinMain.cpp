#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam); 
HWND AddControls(HWND); // Creates the static and edit controls


//constants
const int WIN_WIDTH = 400;
const int WIN_HEIGHT = 200;
const int STATIC_WIDTH = 190;
const int STATIC_HEIGHT = 20;
const int EDIT_WIDTH = 100;
const int EDIT_HEIGHT = 20;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, 
	_In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	// Window Class Registration
	const wchar_t CLASS_NAME[] = L"OCC Student Veterans Association Sign-In";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Get screen resolution
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Window Creation
	HWND hwnd = CreateWindowEx(0, CLASS_NAME, 
		L"OCC Student Veterans Association Sign-In", 0,
		nScreenWidth / 2 - WIN_WIDTH / 2, nScreenHeight / 2 - WIN_HEIGHT / 2,
		WIN_WIDTH, WIN_HEIGHT, HWND_DESKTOP, NULL, hInstance, NULL);

	// store handle to edit control
	HWND hEdit = AddControls(hwnd); 

	if (hwnd == NULL || hEdit == NULL)
	{
		return 0;
	}

	// Remove menu and disable dragging
	SetWindowLongPtr(hwnd, GWL_STYLE, WS_BORDER);

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
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			INT editid = 0;
			INT editlength = 0;

			HWND hEdit = GetDlgItem(hwnd, editid); 
			editlength = GetWindowTextLength(hEdit);
			TCHAR buff[1024];
			GetWindowText(hEdit, buff, 1024);
			MessageBox(hwnd, buff, L"edit text", 0);
		}
		return 0;
		break;

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
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Adds static and edit controls
HWND AddControls(HWND hwnd)
{
	CreateWindow(L"STATIC", L"Please enter your ID below:",
		WS_VISIBLE | WS_CHILD | SS_CENTER, WIN_WIDTH / 2 - STATIC_WIDTH / 2, 
		WIN_HEIGHT / 3, STATIC_WIDTH, STATIC_HEIGHT, hwnd, NULL, NULL, NULL);

	return CreateWindow(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 
		WIN_WIDTH / 2 - EDIT_WIDTH / 2, WIN_HEIGHT / 2, EDIT_WIDTH, 
		EDIT_HEIGHT, hwnd, NULL, NULL, NULL);
}
