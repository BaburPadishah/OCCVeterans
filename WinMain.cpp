#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <mysql.h>
#include <string>
#include <iostream>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
LRESULT APIENTRY EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void checkIdNum(HWND hwnd, WPARAM wParam);
void AddControls(HWND);
std::string connAndQuery(LPSTR data);

// Global Variables
HWND hEdit, hBtn;
WNDPROC wpOrigEditProc;
int qstate;

// Global Constants
const int WIN_WIDTH = 300;
const int WIN_HEIGHT = 200;
const int STATIC_WIDTH = 140;
const int STATIC_HEIGHT = 20;
const int EDIT_WIDTH = 140;
const int EDIT_HEIGHT = 20;
const int BUTTON_WIDTH = 70;
const int BUTTON_HEIGHT = 40;

enum Controls { STATIC, EDIT, BUTTON };

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
	HWND hwnd = CreateWindowEx(
		0, 
		CLASS_NAME,
		L"OCC Student Veterans Association Sign-In", 
		NULL,
		nScreenWidth / 2 - WIN_WIDTH / 2, 
		nScreenHeight / 2 - WIN_HEIGHT / 2,
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
		AddControls(hwnd);
		wpOrigEditProc = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)EditSubclassProc);
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
		checkIdNum(hwnd, wParam);
		return 0;
		break;

	case WM_CLOSE:
		if (MessageBox(hwnd, L"Are you sure you want to quit?", L"Sign-in", MB_OKCANCEL) == IDOK)
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
void AddControls(HWND hwnd)
{
	CreateWindow(L"STATIC",
		L"Please enter your ID:",
		WS_VISIBLE | WS_CHILD | SS_CENTER, 
		WIN_WIDTH / 2 - STATIC_WIDTH / 2,
		WIN_HEIGHT / 10, STATIC_WIDTH, 
		STATIC_HEIGHT, 
		hwnd, 
		(HMENU)STATIC, 
		NULL, 
		NULL
	);

	hBtn = CreateWindow(
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
		WIN_HEIGHT / 4, EDIT_WIDTH,
		EDIT_HEIGHT, 
		hwnd, 
		(HMENU)EDIT, 
		NULL, 
		NULL
	);
}

//Verifys that the ID number given is a valid one
void checkIdNum(HWND hwnd, WPARAM wParam)
{
	if (wParam == BUTTON || wParam == VK_RETURN)
	{
		int len = GetWindowTextLength(hEdit);
		LPSTR buffer = new char[len + 1];

		if (GetWindowTextA(hEdit, buffer, len + 1))
		{
			int len = strlen(buffer);
			//If the user enters Close into the text field it will end the program
			if (!strcmp("close", buffer) || !strcmp("Close", buffer))
			{
				//checks if the current handle window is the main, then destroys it
				if (GetParent(hwnd) == NULL)
					DestroyWindow(hwnd);
				else
					DestroyWindow(GetParent(hwnd));
			}
			else if (len >= 7 && len <= 9) // user has entered an ID number
			{
				if (!isdigit(buffer[0]))
				{
					++buffer; // removes 'C' at beginning of input, if user enters it
				}
				std::string result = connAndQuery(buffer);
				MessageBoxA(hwnd, result.c_str(), result.c_str(), MB_OK);
			}
			else
			{
				MessageBoxA(hwnd, "Input not recognized.", "Error", MB_OK);
			}
		}
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
	return CallWindowProc(wpOrigEditProc, hwnd, uMsg, wParam, lParam);
}

//connect to and query database
std::string connAndQuery(LPSTR data)
{
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "Garamantes45!", "occ_veteran_club", 3306, nullptr, 0);

	if (!conn)
	{
		return 0;
	}

	std::string result = "not found";
	std::string query = "SELECT * FROM members WHERE id = " + static_cast<std::string>(data);
	const char* q = query.c_str();

	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
			result = row[1];
	}
	else
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
	}
	return result;
}
