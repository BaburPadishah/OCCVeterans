#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	// Registration
	const wchar_t CLASS_NAME[] = L"OCC Veterans' Club Sign-In";
	HWND textBox;

	WNDCLASS wc = { };
	WNDCLASS wcChild = { };

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	wcChild.lpfnWndProc = WindowProc;
	wcChild.hInstance = hInstance;
	wcChild.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);
	RegisterClass(&wcChild);

	// Window Creation
	HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"OCC Veterans' Club Sign-In", WS_SYSMENU | !WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 500, 200, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	//Gray out Close button
	HMENU hMenu = GetSystemMenu(hwnd, FALSE);
	EnableMenuItem(hMenu, SC_CLOSE, MF_GRAYED);

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