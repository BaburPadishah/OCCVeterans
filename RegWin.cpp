#include "header.h"

int regWin(LPSTR data)
{
	// Window Class Registration
	const wchar_t CHILD_CLASS_NAME[] = L"New Member Registration";

	WNDCLASS wcReg = { };

	wcReg.lpfnWndProc = RegWinProc;
	wcReg.lpszClassName = CHILD_CLASS_NAME;

	RegisterClass(&wcReg);

	HWND regWin = CreateWindowEx(
		0,
		CHILD_CLASS_NAME,
		L"New Member Registration",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER,
		SCREEN_W / 2 - REG_WIDTH / 2,
		SCREEN_H / 2 - REG_HEIGHT / 2,
		REG_WIDTH,
		REG_HEIGHT,
		NULL,
		NULL,
		NULL,
		NULL
	);

	CreateWindowA(
		"EDIT",
		data,
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_AUTOHSCROLL,
		REG_WIDTH / 3,
		REG_HEIGHT / 10,
		EDIT_WIDTH,
		EDIT_HEIGHT,
		regWin,
		(HMENU)REG_ID_EDIT,
		NULL,
		NULL
	);

	EnableWindow(GetDlgItem(regWin, REG_ID_EDIT), FALSE);

	if (regWin == NULL)
	{
		return 0;
	}

	PostMessage(GetDlgItem(regWin, REG_ID_EDIT), EM_LIMITTEXT, 8, 0);

	// Display Window
	ShowWindow(regWin, SW_SHOW);

	// Message Loop
	MSG regMsg = { };
	while (GetMessage(&regMsg, NULL, 0, 0))
	{
		TranslateMessage(&regMsg);
		DispatchMessage(&regMsg);
	}

	return 0;
}

LRESULT CALLBACK RegWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_CREATE:
		addRegControls(hwnd);
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
		char id[9], fName[40], lName[40], branch[12];
		BOOL filled = FALSE;

		if (GetDlgItemTextA(hwnd, REG_ID_EDIT, id, 9) != 0
			&& GetDlgItemTextA(hwnd, REG_FNAME_EDIT, fName, 40) != 0
			&& GetDlgItemTextA(hwnd, REG_LNAME_EDIT, lName, 40) != 0)
		{
			if (IsDlgButtonChecked(hwnd, AIRFORCE_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, AIRFORCE_RADIO, branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, ARMY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ARMY_RADIO, branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, COASTGUARD_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, COASTGUARD_RADIO, branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, NAVY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, NAVY_RADIO, branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, MARINES_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, MARINES_RADIO, branch, 12);
				filled = TRUE;
			}
		}
		else
		{
			filled = FALSE;
		}

		EnableWindow(GetDlgItem(hwnd, REG_OK), filled);

		switch (wParam)
		{
		case REG_CANCEL:
		{
			DestroyWindow(hwnd);
			return 0;
		}
		case REG_OK:
		{
			// copy before validation to correctly display result
			char fNameCpy[40], lNameCpy[40];
			strcpy_s(fNameCpy, sizeof(fNameCpy), fName);
			strcpy_s(lNameCpy, sizeof(lNameCpy), lName);

			// validate first and last names
			char* fp = &fName[0];
			char* lp = &lName[0];
			BOOL valid = TRUE;

			while (*fp != '\0')
			{
				if (!isalpha(*fp) && *fp != '-' && *fp != '\'')
				{
					valid = FALSE;
				}
				else if (*fp == '\'' && *(fp - 1) != '\'')
				{
					char* pap = fp;
					char temp = *pap, temp2;
					*pap = '\'';
					++pap;
					temp2 = *pap;
					*pap = temp;
					temp = temp2;
					++pap;
					while (*(pap - 1) != '\0')
					{
						temp2 = *pap;
						*pap = temp;
						temp = temp2;
						++pap;
					}
				}
				++fp;
			}

			while (*lp != '\0')
			{
				if (!isalpha(*lp) && *lp != '-' && *lp != '\'')
				{
					valid = FALSE;
				}
				else if (*lp == '\'' && *(lp - 1) != '\'')
				{
					char* pap = lp;
					char temp = *pap, temp2;
					*pap = '\'';
					++pap;
					temp2 = *pap;
					*pap = temp;
					temp = temp2;
					++pap;
					while (*(pap - 1) != '\0')
					{
						temp2 = *pap;
						*pap = temp;
						temp = temp2;
						++pap;
					}
				}
				++lp;
			}

			if (valid)
			{
				if (registerMember(id, fName, lName, branch))
				{
					std::string result = static_cast<std::string>(lNameCpy)
						+ ", " 
						+ static_cast<std::string>(fNameCpy);
					time_t tm = time(NULL);
					char displayTime[26];
					ctime_s(displayTime, sizeof displayTime, &tm);
					std::string loginMessage = result 
						+ " signed in on " + displayTime;
					MessageBoxA(hwnd, loginMessage.c_str(),
						result.c_str(), MB_OK);

					DestroyWindow(hwnd);

					return 0;
				}
			}
			else
			{
				MessageBox(hwnd, L"Incorrect name format.", L"Error", MB_OK);
			}
		}
		}
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}