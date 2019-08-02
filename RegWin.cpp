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
		return 0;
	}

	std::string result = "not found";
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

	mysql_close(conn);
	return result;
}

std::string registerMember(LPSTR id, LPSTR FName, LPSTR LName, LPSTR Branch)
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
		return 0;
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
	return static_cast<std::string>(LName) + ", " + static_cast<std::string>(FName);
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
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
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
		char id[9], FName[20], LName[20], Branch[12];
		BOOL filled = FALSE;

		if (GetDlgItemTextA(hwnd, REG_ID_EDIT, id, 9) != 0
			&& GetDlgItemTextA(hwnd, REG_FNAME_EDIT, FName, 20) != 0
			&& GetDlgItemTextA(hwnd, REG_LNAME_EDIT, LName, 20) != 0)
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
			EnableWindow(GetDlgItem(hwnd, REG_OK), filled);
		}

		switch (wParam)
		{
		case REG_CANCEL:
		{
			DestroyWindow(hwnd);
			return 0;
		}
		case REG_OK:
		{
			std::string result = registerMember(id, FName, LName, Branch);

			time_t tm = time(NULL);
			char displayTime[26];
			ctime_s(displayTime, sizeof displayTime, &tm);
			std::string loginMessage = result + " signed in on " + displayTime;
			MessageBoxA(hwnd, loginMessage.c_str(), result.c_str(), MB_OK);

			DestroyWindow(hwnd);

			return 0;
		}
		}
	}
	}


	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
