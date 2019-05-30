#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);

BOOL EnableCloseButton(const HWND hwnd, const BOOL bState)
{
	HMENU	hMenu;
	UINT	dwExtra;

	if (hwnd == NULL || (hMenu = GetSystemMenu(hwnd, FALSE)) == NULL)
	{
		return FALSE;
	}

	dwExtra = bState ? MF_ENABLED : (MF_DISABLED | MF_GRAYED);
	return EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | dwExtra) != -1;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	// Registration
	const wchar_t CLASS_NAME[] = L"OCC Veterans' Club Sign-In";

	WNDCLASS wc = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Window Creation
	HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"OCC Veterans' Club Sign-In", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	EnableCloseButton(hwnd, FALSE);

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
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
		}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}