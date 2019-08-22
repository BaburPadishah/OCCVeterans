#include "header.h"


//connect to and query database
std::string checkMembers(LPSTR id)
{
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	int qstate;
	conn = mysql_init(0);

	conn = mysql_real_connect(
		conn,
		"localhost",
		"root",
		"Garamantes45!",
		"occ_veteran_club",
		3306,
		nullptr,
		0
	);

	if (!conn)
	{
		return "Bad Connection";
	}

	std::string result = "not found";

	//query admin table
	std::string query = "SELECT * FROM admin WHERE id = "
		+ static_cast<std::string>(id);
	const char* q = query.c_str();

	qstate = mysql_query(conn, q);

	if (!qstate) // mysql_query functioned correctly
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
			result = row[1];
		mysql_free_result(res);
	}
	else
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
	}

	if (result == "not found") // not an admin
	{
		//query members table
		std::string query = "SELECT * FROM members WHERE id = "
			+ static_cast<std::string>(id);
		const char* q = query.c_str();

		qstate = mysql_query(conn, q);

		if (!qstate) // mysql_query functioned correctly
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				result = row[1];
			mysql_free_result(res);
		}
		else
		{
			std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		}

		if (result != "not found")
		{
			std::string ins = "INSERT INTO logins (id, name, date_time) VALUES ("
				+ static_cast<std::string>(id)
				+ ", '" + result + "', NOW())";

			qstate = mysql_query(conn, ins.c_str());

			if (qstate)
			{
				std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
			}
		}

	}

	mysql_close(conn);
	return result;
}

BOOL registerMember(LPSTR id, LPSTR FName, LPSTR LName, LPSTR Branch)
{
	MYSQL* conn;
	int qstate;
	conn = mysql_init(0);

	conn = mysql_real_connect(
		conn,
		"localhost",
		"root",
		"Garamantes45!",
		"occ_veteran_club",
		3306,
		nullptr,
		0
	);

	if (!conn)
	{
		return FALSE;
	}

	std::string ins = "INSERT INTO members (id, name, branch) VALUES ("
		+ static_cast<std::string>(id)
		+ ", '" + static_cast<std::string>(LName) + ", " + static_cast<std::string>(FName) + "', '"
		+ static_cast<std::string>(Branch) + "')";

	qstate = mysql_query(conn, ins.c_str());

	if (qstate)
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
	}

	std::string insLog = "INSERT INTO logins (id, name, date_time) VALUES ("
		+ static_cast<std::string>(id) + ", '"
		+ static_cast<std::string>(LName) + ", " + static_cast<std::string>(FName)
		+ "', NOW())";

	qstate = mysql_query(conn, insLog.c_str());

	if (qstate)
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
	}

	mysql_close(conn);
	return TRUE;
}

int newMember(LPSTR data)
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
		char id[9], FName[40], LName[40], Branch[12];
		BOOL filled = FALSE;

		if (GetDlgItemTextA(hwnd, REG_ID_EDIT, id, 9) != 0
			&& GetDlgItemTextA(hwnd, REG_FNAME_EDIT, FName, 40) != 0
			&& GetDlgItemTextA(hwnd, REG_LNAME_EDIT, LName, 40) != 0)
		{
			if (IsDlgButtonChecked(hwnd, AIRFORCE_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, AIRFORCE_RADIO, Branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, ARMY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ARMY_RADIO, Branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, COASTGUARD_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, COASTGUARD_RADIO, Branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, NAVY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, NAVY_RADIO, Branch, 12);
				filled = TRUE;
			}
			else if (IsDlgButtonChecked(hwnd, MARINES_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, MARINES_RADIO, Branch, 12);
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
			char FName2[40], LName2[40];
			strcpy_s(FName2, sizeof(FName2), FName);
			strcpy_s(LName2, sizeof(LName2), LName);

			// validate first and last names
			char* fp = &FName[0];
			char* lp = &LName[0];
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
				if (registerMember(id, FName, LName, Branch))
				{
					std::string result = static_cast<std::string>(LName2) + ", " + static_cast<std::string>(FName2);
					time_t tm = time(NULL);
					char displayTime[26];
					ctime_s(displayTime, sizeof displayTime, &tm);
					std::string loginMessage = result + " signed in on " + displayTime;
					MessageBoxA(hwnd, loginMessage.c_str(), result.c_str(), MB_OK);

					DestroyWindow(hwnd);

					return 0;
				}
			}
			else
			{
				MessageBox(hwnd, L"Input not recognized.", L"Error", MB_OK);
			}
		}
		}
	}
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}