#include "functions.h"

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
		AddControls(hwnd);
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

LRESULT CALLBACK RegWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
		AddRegControls(hwnd);
		EnableWindow(GetDlgItem(hwnd, REG_OK), FALSE);
		return 0;
		break;

	//disables dragging
	case WM_NCLBUTTONDOWN:
		if (wParam == HTCAPTION)
		{
			return 0;
		}
		break;

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

	case WM_COMMAND:
	{
		switch (wParam)
		{
		case REG_CANCEL:
		{
			DestroyWindow(hwnd);
			return 0;
		}
		case AIRFORCE_RADIO:
		{
			EnableWindow(GetDlgItem(hwnd, REG_OK), TRUE);
			return 0;
		}
		case NAVY_RADIO:
		{
			EnableWindow(GetDlgItem(hwnd, REG_OK), TRUE);
			return 0;
		}
		case ARMY_RADIO:
		{
			EnableWindow(GetDlgItem(hwnd, REG_OK), TRUE);
			return 0;
		}
		case COASTGUARD_RADIO:
		{
			EnableWindow(GetDlgItem(hwnd, REG_OK), TRUE);
			return 0;
		}
		case MARINES_RADIO:
		{
			EnableWindow(GetDlgItem(hwnd, REG_OK), TRUE);
			return 0;
		}
		case REG_OK:
		{
			LPSTR id = new char[9];
			LPSTR FName = new char[20];
			LPSTR LName = new char[20];
			LPSTR Branch = new char[12];
			GetDlgItemTextA(hwnd, REG_ID_EDIT, id, 9);
			GetDlgItemTextA(hwnd, REG_FNAME_EDIT, FName, 20);
			GetDlgItemTextA(hwnd, REG_LNAME_EDIT, LName, 20);

			if (IsDlgButtonChecked(hwnd, AIRFORCE_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, AIRFORCE_RADIO, Branch, 12);
			}
			else if (IsDlgButtonChecked(hwnd, ARMY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ARMY_RADIO, Branch, 12);
			}
			else if (IsDlgButtonChecked(hwnd, COASTGUARD_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, COASTGUARD_RADIO, Branch, 12);
			}
			else if (IsDlgButtonChecked(hwnd, NAVY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, NAVY_RADIO, Branch, 12);
			}
			else if (IsDlgButtonChecked(hwnd, MARINES_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, MARINES_RADIO, Branch, 12);
			}
			
			QueryDB(id, FName, LName, Branch);

			DestroyWindow(hwnd);

			return 0;
		}
		}
	}
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
		WIN_HEIGHT / 10, 
		STATIC_WIDTH,
		STATIC_HEIGHT,
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
		WIN_HEIGHT / 4,
		EDIT_WIDTH,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)EDIT,
		NULL,
		NULL
	);

	wpOrigEditProc = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)EditSubclassProc);
}

void AddRegControls(HWND parent)
{
	// Three static fields: ID, name, branch
	CreateWindow(L"STATIC",
		L"Student ID:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		REG_WIDTH / 3 - STATIC_WIDTH - 5,
		REG_HEIGHT / 10, 
		STATIC_WIDTH,
		STATIC_HEIGHT,
		parent,
		(HMENU)REG_ID_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"First Name:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		REG_WIDTH / 3 - STATIC_WIDTH - 5,
		REG_HEIGHT / 5,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		parent,
		(HMENU)REG_FNAME_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Last Name:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		REG_WIDTH / 3 - STATIC_WIDTH - 5,
		3 * REG_HEIGHT / 10,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		parent,
		(HMENU)REG_LNAME_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Branch:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		REG_WIDTH / 3 - STATIC_WIDTH - 5,
		4 * REG_HEIGHT / 10,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		parent,
		(HMENU)REG_BRANCH_STATIC,
		NULL,
		NULL
	);

	// Three edit fields: ID (filled by buffer), first name, last name

	CreateWindow(
		L"EDIT",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
		REG_WIDTH / 3,
		REG_HEIGHT / 5,
		EDIT_WIDTH,
		EDIT_HEIGHT,
		parent,
		(HMENU)REG_FNAME_EDIT,
		NULL,
		NULL
	);

	CreateWindow(
		L"EDIT",
		L"",
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
		REG_WIDTH / 3,
		3 * REG_HEIGHT / 10,
		EDIT_WIDTH,
		EDIT_HEIGHT,
		parent,
		(HMENU)REG_LNAME_EDIT,
		NULL,
		NULL
	);

	// Five radio buttons: Army, Navy, Air Force, Marines, Coast Guard

	// Create Air Force radio button
	CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"BUTTON",
		L"Air Force",
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON
		| WS_TABSTOP | WS_GROUP,
		REG_WIDTH / 3,
		4 * REG_HEIGHT / 10,
		100,
		EDIT_HEIGHT,
		parent,
		(HMENU)AIRFORCE_RADIO,
		NULL,
		NULL
	);

	// Create Army radio button
	CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"BUTTON",
		L"Army",
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		REG_WIDTH / 3,
		4 * REG_HEIGHT / 10 + 20,
		100,
		EDIT_HEIGHT,
		parent,
		(HMENU)ARMY_RADIO,
		NULL,
		NULL
	);

	//Create Coast Guard radio button
	CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"BUTTON",
		L"Coast Guard",
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		REG_WIDTH / 3,
		4 * REG_HEIGHT / 10 + 40,
		100,
		EDIT_HEIGHT,
		parent,
		(HMENU)COASTGUARD_RADIO,
		NULL,
		NULL
	);

	// Create Marines radio button
	CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"BUTTON",
		L"Marines",
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		2 * REG_WIDTH / 3,
		4 * REG_HEIGHT / 10,
		100,
		EDIT_HEIGHT,
		parent,
		(HMENU)MARINES_RADIO,
		NULL,
		NULL
	);

	// Create Navy radio button
	CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"BUTTON",
		L"Navy",
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		2 * REG_WIDTH / 3,
		4 * REG_HEIGHT / 10 + 20,
		100,
		EDIT_HEIGHT,
		parent,
		(HMENU)NAVY_RADIO,
		NULL,
		NULL
	);

	// Two buttons: Register, Cancel

	CreateWindowEx(
		WS_EX_LEFT,
		L"BUTTON",
		L"Register",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
		REG_WIDTH / 2 - BUTTON_WIDTH - 10,
		2 * REG_HEIGHT / 3,
		BUTTON_WIDTH,
		BUTTON_HEIGHT,
		parent,
		(HMENU)REG_OK,
		(HINSTANCE)GetWindowLong(parent, GWLP_HINSTANCE),
		NULL
	);

	// Create button
	CreateWindowEx(
		WS_EX_LEFT,
		L"BUTTON",
		L"Cancel",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
		REG_WIDTH / 2 + 10,
		2 * REG_HEIGHT / 3,
		BUTTON_WIDTH,
		BUTTON_HEIGHT,
		parent,
		(HMENU)REG_CANCEL,
		(HINSTANCE)GetWindowLong(parent, GWLP_HINSTANCE),
		NULL
	);
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
			for (size_t i = 1; i < len; ++i)
			{
				if (!isdigit(buffer[i]))
				{
					allDigit = false;
				}
			}

			//If the user enters Close into the text field it will end the program
			if (!strcmp("close", buffer) || !strcmp("Close", buffer) || !strcmp("CLOSE", buffer))
			{
				//checks if the current handle window is the main, then destroys it
				if (GetParent(hwnd) == NULL)
					DestroyWindow(hwnd);
				else
					DestroyWindow(GetParent(hwnd));
			}
			else if ((len == 7 || (len == 8 && buffer[0] == '0') || (len == 9 && buffer[0] == 'C')) && allDigit) // user has entered an ID number
			{
				if (len == 9)
				{
					++buffer; // removes 'C' at beginning of input, if user enters it
				}
				time_t tm = time(NULL);
				char displayTime[26];
				ctime_s(displayTime, sizeof displayTime, &tm);

				std::string result = QueryDB(buffer);
				if (result == "not found")
				{
					if (MessageBox(hwnd,
						L"ID not found. Would you like to register as a new member?", 
						L"New Member", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					{
						newMember(buffer, hwnd);
					}
				}
				else // found a result
				{
					std::string loginMessage = result + " signed in on " + displayTime;
					MessageBoxA(hwnd, loginMessage.c_str(), result.c_str(), MB_OK);
				}
			}
			else
			{
				MessageBox(hwnd, L"Input not recognized.", L"Error", MB_OK);
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

