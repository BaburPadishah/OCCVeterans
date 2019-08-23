#include "header.h"

// Global Variables
HWND hEdit;
WNDPROC wpOrigEditProc;

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

	// Window Creation
	HWND hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"OCC Student Veterans Association Sign-In",
		NULL,
		SCREEN_W / 2 - WIN_WIDTH / 2,
		SCREEN_H / 2 - WIN_HEIGHT / 2,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		return 0;
	}

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
		addControls(hwnd);
		break;
	}

	//disables dragging
	case WM_NCLBUTTONDOWN:
		if (wParam == HTCAPTION)
		{
			return 0;
		}
		break;

	case WM_KEYDOWN:
		checkIdNum(hwnd, wParam);
		return 0;
		break;

	case WM_COMMAND:
		if (wParam == BUTTON)
		{
			ShowWindow(hwnd, SW_HIDE);
			checkIdNum(hwnd, wParam);
			ShowWindow(hwnd, SW_SHOW);
		}
		return 0;
		break;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Are you sure you want to quit?",
			L"Sign-in", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		// Else: User canceled. Do nothing.
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_MENU + 1));
		EndPaint(hwnd, &ps);
	}
	return 0;
	break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Adds button and static/edit controls
void addControls(HWND hwnd)
{
	CreateWindow(L"STATIC",
		L"Please enter your ID (8 numbers, no 'C'):",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		WIN_WIDTH / 2 - STATIC_WIDTH / 2,
		WIN_HEIGHT / 10,
		STATIC_WIDTH,
		STATIC_HEIGHT * 2,
		hwnd,
		(HMENU)STATIC,
		NULL,
		NULL
	);

	CreateWindow(
		L"BUTTON",
		L"Sign In",
		WS_VISIBLE | WS_BORDER | WS_CHILD,
		WIN_WIDTH / 2 - BUTTON_WIDTH / 2,
		WIN_HEIGHT / 2,
		BUTTON_WIDTH,
		BUTTON_HEIGHT,
		hwnd,
		(HMENU)BUTTON,
		NULL,
		NULL
	);

	hEdit = CreateWindow(
		L"EDIT",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
		WIN_WIDTH / 2 - EDIT_WIDTH / 2,
		WIN_HEIGHT / 3,
		EDIT_WIDTH,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)EDIT,
		NULL,
		NULL
	);

	wpOrigEditProc = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC,
		(LONG_PTR)EditSubclassProc);
}

//Verifies that the ID number given is a valid one
void checkIdNum(HWND hwnd, WPARAM wParam)
{
	if (wParam == BUTTON || wParam == VK_RETURN)
	{
		size_t len = GetWindowTextLength(hEdit);
		LPSTR buffer = new char[len + 1];

		if (GetWindowTextA(hEdit, buffer, len + 1))
		{
			size_t len = strlen(buffer);
			bool allDigit = true;
			for (size_t i = 0; i < len; ++i)
			{
				if (!isdigit(buffer[i]))
				{
					allDigit = false;
				}
			}

			//If the user enters Close into the text field it will end the program
			if (!strcmp("close", buffer) 
				|| !strcmp("Close", buffer) 
				|| !strcmp("CLOSE", buffer))
			{
				//checks if the current handle window is the main, then destroys it
				if (GetParent(hwnd) == NULL)
					DestroyWindow(hwnd);
				else
					DestroyWindow(GetParent(hwnd));
			}
			else if (checkAdmin(buffer) == "ADMIN")
			{
				adminWin();
			}
			else if (len == 8 && allDigit) // user has entered an ID number
			{
				std::string result = checkMembers(buffer);
				if (result == "not found")
				{
					if (MessageBox(hwnd,
						L"ID not found. Would you like to register as a new member?",
						L"New Member", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					{
						regWin(buffer);
					}
				}
				else
				{
					time_t tm = time(NULL);
					char displayTime[26];
					ctime_s(displayTime, sizeof displayTime, &tm);
					std::string loginMessage = result 
						+ " signed in on " + displayTime;
					MessageBoxA(hwnd, loginMessage.c_str(), 
						result.c_str(), MB_OK);
				}
			}
			else
			{
				MessageBox(hwnd, L"Incorrect ID format.", L"Error", MB_OK);
			}
		}

		delete[] buffer;
	}
}

// Subclass the edit control
LRESULT APIENTRY EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == VK_RETURN)
		{
			checkIdNum(hwnd, wParam);
		}
	}
	else if (uMsg == WM_CHAR)//stops the noise when pressing enter
	{
		if (wParam == VK_RETURN)
		{
			return 0;
		}
	}
	return CallWindowProc(wpOrigEditProc, hwnd, uMsg, wParam, lParam);
}