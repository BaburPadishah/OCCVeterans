#include "header.h"

MYSQL* AdminConn;

int AdminWin()
{
	// Window Class Registration
	const wchar_t ADMIN_CLASS_NAME[] = L"Search Records";

	WNDCLASS wc = { };

	wc.lpfnWndProc = AdminWindowProc;
	wc.lpszClassName = ADMIN_CLASS_NAME;

	RegisterClass(&wc);

	// Window Creation
	HWND hwnd = CreateWindowEx(
		0,
		ADMIN_CLASS_NAME,
		L"Search Records",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER,
		SCREEN_W / 2 - ADMIN_WIDTH / 2,
		SCREEN_H / 2 - ADMIN_HEIGHT / 2,
		ADMIN_WIDTH,
		ADMIN_HEIGHT,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (hwnd == NULL)
	{
		return 0;
	}

	AdminConn = mysql_init(0);
	AdminConn = mysql_real_connect(
		AdminConn,
		"localhost",
		"root",
		"Garamantes45!",
		"occ_veteran_club",
		3306,
		nullptr,
		0
	);

	if (AdminConn)
	{
		std::cout << "Connection success" << std::endl;
	}
	else
	{
		std::cerr << "Connection failed: " << mysql_error(AdminConn) << std::endl;
		return 0;
	}

	// Display Window
	ShowWindow(hwnd, SW_SHOW);

	// Message Loop
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK AdminWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		AddAdminControls(hwnd);
		break;
	}

	//disables dragging
	case WM_NCLBUTTONDOWN:
	{
		if (wParam == HTCAPTION)
		{
			return 0;
		}
		break;
	}

	case WM_KEYDOWN:
	{
		break;
	}

	case WM_COMMAND:
	{
		switch (wParam)
		{
		case ADMIN_SEARCH_MEMBERS_BUTTON:
		{
			ListView_DeleteAllItems(GetDlgItem(hwnd, ADMIN_MEMBER_LIST));
			char id[9], name[40], radio[12];

			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_MEMBERS_ID_EDIT, id, 9) == 0)
			{
				id[0] = '\0';
			}
			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_MEMBERS_NAME_EDIT, name, 40) == 0)
			{
				name[0] = '\0';
			}

			if (IsDlgButtonChecked(hwnd, AIRFORCE_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, AIRFORCE_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, ARMY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ARMY_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, COASTGUARD_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, COASTGUARD_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, NAVY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, NAVY_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, MARINES_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, MARINES_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, ALL_BRANCH_RADIO) == BST_CHECKED)
			{
				radio[0] = '\0';
			}
			else // no buttons checked
			{
				radio[0] = '\0';
			}

			std::string q = CreateQuery(id, name, radio, ADMIN_SEARCH_MEMBERS_BUTTON);
			MYSQL_RES* res = AdminQueryDB(q);
			MYSQL_ROW row;

			LVITEM lvI;
			memset(&lvI, 0, sizeof(LVITEM));

			lvI.mask = LVIF_TEXT | LVIF_STATE;
			lvI.pszText = LPSTR_TEXTCALLBACK;
			lvI.iItem = 0;
			lvI.iIndent = 0;
			lvI.iSubItem = 0;
			lvI.stateMask = 0;
			lvI.state = 0;

			while (row = mysql_fetch_row(res))
			{
				lvI.iSubItem = 0;

				wchar_t* wrow = new wchar_t;
				size_t retval;
				rsize_t dstsz = 20;
				rsize_t len = strlen(row[0]) + 1;
				mbstowcs_s(&retval, wrow, dstsz, row[0], len);
				LPWSTR ptr = wrow;
				lvI.cchTextMax = len;
				lvI.pszText = ptr;
				ListView_InsertItem(GetDlgItem(hwnd, ADMIN_MEMBER_LIST), &lvI);

				for (int j = 1; j < 3; ++j)
				{
					++lvI.iSubItem;
					rsize_t len = strlen(row[j]) + 1;
					mbstowcs_s(&retval, wrow, dstsz, row[j], len);
					ptr = wrow;
					lvI.cchTextMax = len;
					ListView_SetItemText(GetDlgItem(hwnd, ADMIN_MEMBER_LIST), lvI.iItem, j, ptr);
				}
				delete[] wrow;
				++lvI.iItem;
			}

			mysql_free_result(res);
			break;
		}
		case ADMIN_SEARCH_LOGINS_BUTTON:
		{
			ListView_DeleteAllItems(GetDlgItem(hwnd, ADMIN_LOGIN_LIST));
			char id[9], name[40], radio[12];

			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_LOGINS_ID_EDIT, id, 9) == 0)
			{
				id[0] = '\0';
			}
			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_LOGINS_NAME_EDIT, name, 40) == 0)
			{
				name[0] = '\0';
			}

			if (IsDlgButtonChecked(hwnd, ADMIN_PAST_DAY_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ADMIN_PAST_DAY_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, ADMIN_PAST_WEEK_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ADMIN_PAST_WEEK_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, ADMIN_PAST_MONTH_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ADMIN_PAST_MONTH_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, ADMIN_PAST_YEAR_RADIO) == BST_CHECKED)
			{
				GetDlgItemTextA(hwnd, ADMIN_PAST_YEAR_RADIO, radio, 12);
			}
			else if (IsDlgButtonChecked(hwnd, ADMIN_ALL_TIME_RADIO) == BST_CHECKED)
			{
				radio[0] = '\0';
			}
			else // no buttons checked
			{
				radio[0] = '\0';
			}

			std::string q = CreateQuery(id, name, radio, ADMIN_SEARCH_LOGINS_BUTTON);
			MYSQL_RES* res = AdminQueryDB(q);
			MYSQL_ROW row;

			LVITEM lvI;
			memset(&lvI, 0, sizeof(LVITEM));

			lvI.mask = LVIF_TEXT | LVIF_STATE;
			lvI.pszText = LPSTR_TEXTCALLBACK;
			lvI.iItem = 0;
			lvI.iIndent = 0;
			lvI.iSubItem = 0;
			lvI.stateMask = 0;
			lvI.state = 0;

			while (row = mysql_fetch_row(res))
			{
				lvI.iSubItem = 0;

				wchar_t* wrow = new wchar_t;
				size_t retval;
				rsize_t dstsz = 20;
				mbstowcs_s(&retval, wrow, dstsz, row[0], strlen(row[0]) + 1);
				LPWSTR ptr = wrow;
				lvI.pszText = ptr;
				ListView_InsertItem(GetDlgItem(hwnd, ADMIN_LOGIN_LIST), &lvI);

				for (int j = 1; j < 3; ++j)
				{
					++lvI.iSubItem;
					rsize_t len = strlen(row[j]) + 1;
					mbstowcs_s(&retval, wrow, dstsz, row[j], len);
					ptr = wrow;
					lvI.cchTextMax = len;
					ListView_SetItemText(GetDlgItem(hwnd, ADMIN_LOGIN_LIST), lvI.iItem, j, ptr);
				}
				delete[] wrow;
				++lvI.iItem;
			}

			mysql_free_result(res);
			break;
		}
		case ADMIN_FINISH:
		{
			DestroyWindow(hwnd);
			break;
		}
		}
		break;
	}

	case WM_DESTROY:
	{
		mysql_close(AdminConn);
		PostQuitMessage(0);
		return 0;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_MENU + 1));
		EndPaint(hwnd, &ps);
		break;
	}
	default:
	{
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
	return 0;
}

void AddAdminControls(HWND hwnd)
{
	CreateWindow(L"STATIC",
		L"Member List",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		ADMIN_WIDTH / 4 - STATIC_WIDTH / 2,
		ADMIN_HEIGHT / 60,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_MEMBER_HEADER,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Login List",
		WS_VISIBLE | WS_CHILD | SS_CENTER,
		3 * ADMIN_WIDTH / 4 - STATIC_WIDTH / 2,
		ADMIN_HEIGHT / 60,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_LOGIN_HEADER,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Search by ID:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		ADMIN_WIDTH / 4 - STATIC_WIDTH,
		ADMIN_HEIGHT / 60 + 30,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_ID_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Search by Name (Last, First):",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		ADMIN_WIDTH / 4 - STATIC_WIDTH * 2,
		ADMIN_HEIGHT / 60 + 60,
		STATIC_WIDTH * 2,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_NAME_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Search by Branch:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		ADMIN_WIDTH / 4 - STATIC_WIDTH,
		ADMIN_HEIGHT / 60 + 90,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_BRANCH_STATIC,
		NULL,
		NULL
	);

	CreateWindow(
		L"BUTTON",
		L"Finish",
		WS_VISIBLE | WS_BORDER | WS_CHILD,
		9 * ADMIN_WIDTH / 10 - BUTTON_WIDTH / 2,
		9 * ADMIN_HEIGHT / 10,
		BUTTON_WIDTH,
		BUTTON_HEIGHT,
		hwnd,
		(HMENU)ADMIN_FINISH,
		NULL,
		NULL
	);

	CreateWindow(L"EDIT",
		L"",
		WS_VISIBLE | WS_BORDER | WS_CHILD | SS_LEFT,
		ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 30,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_MEMBERS_ID_EDIT,
		NULL,
		NULL
	);

	CreateWindow(L"EDIT",
		L"",
		WS_VISIBLE | WS_BORDER | WS_CHILD | SS_LEFT,
		ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 60,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_MEMBERS_NAME_EDIT,
		NULL,
		NULL
	);

	CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"BUTTON",
		L"Air Force",
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON
		| WS_TABSTOP | WS_GROUP,
		ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 90,
		100,
		EDIT_HEIGHT,
		hwnd,
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
		ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 110,
		100,
		EDIT_HEIGHT,
		hwnd,
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
		ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 130,
		100,
		EDIT_HEIGHT,
		hwnd,
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
		ADMIN_WIDTH / 4 + 115,
		ADMIN_HEIGHT / 60 + 90,
		100,
		EDIT_HEIGHT,
		hwnd,
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
		ADMIN_WIDTH / 4 + 115,
		ADMIN_HEIGHT / 60 + 110,
		100,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)NAVY_RADIO,
		NULL,
		NULL
	);

	CreateWindowEx(
		WS_EX_WINDOWEDGE,
		L"BUTTON",
		L"All",
		WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
		ADMIN_WIDTH / 4 + 115,
		ADMIN_HEIGHT / 60 + 130,
		100,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)ALL_BRANCH_RADIO,
		NULL,
		NULL
	);

	CreateWindow(
		L"BUTTON",
		L"Search Members",
		WS_VISIBLE | WS_BORDER | WS_CHILD,
		ADMIN_WIDTH / 4 - LV_WIDTH / 2,
		ADMIN_HEIGHT / 5 - BUTTON_HEIGHT - 5,
		BUTTON_WIDTH * 2,
		BUTTON_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_MEMBERS_BUTTON,
		NULL,
		NULL
	);

	CreateWindow(
		L"BUTTON",
		L"Search Logins",
		WS_VISIBLE | WS_BORDER | WS_CHILD,
		3 * ADMIN_WIDTH / 4 - LV_WIDTH / 2,
		ADMIN_HEIGHT / 5 - BUTTON_HEIGHT - 5,
		BUTTON_WIDTH * 2,
		BUTTON_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_LOGINS_BUTTON,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Search by ID:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		3 * ADMIN_WIDTH / 4 - STATIC_WIDTH,
		ADMIN_HEIGHT / 60 + 30,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_ID_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Search by Name (Last, First):",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		3 * ADMIN_WIDTH / 4 - STATIC_WIDTH * 2,
		ADMIN_HEIGHT / 60 + 60,
		STATIC_WIDTH * 2,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_NAME_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"STATIC",
		L"Search by Date:",
		WS_VISIBLE | WS_CHILD | SS_RIGHT,
		3 * ADMIN_WIDTH / 4 - STATIC_WIDTH,
		ADMIN_HEIGHT / 60 + 90,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_BRANCH_STATIC,
		NULL,
		NULL
	);

	CreateWindow(L"EDIT",
		L"",
		WS_VISIBLE | WS_BORDER | WS_CHILD | SS_LEFT,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 30,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_LOGINS_ID_EDIT,
		NULL,
		NULL
	);

	CreateWindow(L"EDIT",
		L"",
		WS_VISIBLE | WS_BORDER | WS_CHILD | SS_LEFT,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 60,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_LOGINS_NAME_EDIT,
		NULL,
		NULL
	);

	CreateWindowEx(
		0,
		L"BUTTON",
		L"Past Day",
		WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_GROUP | BS_AUTORADIOBUTTON,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 90,
		100,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)ADMIN_PAST_DAY_RADIO,
		NULL,
		NULL
	);

	CreateWindowEx(
		0,
		L"BUTTON",
		L"Past Week",
		WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 110,
		100,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)ADMIN_PAST_WEEK_RADIO,
		NULL,
		NULL
	);

	CreateWindowEx(
		0,
		L"BUTTON",
		L"Past Month",
		WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 130,
		100,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)ADMIN_PAST_MONTH_RADIO,
		NULL,
		NULL
	);

	CreateWindowEx(
		0,
		L"BUTTON",
		L"Past Year",
		WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
		3 * ADMIN_WIDTH / 4 + 105,
		ADMIN_HEIGHT / 60 + 90,
		100,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)ADMIN_PAST_YEAR_RADIO,
		NULL,
		NULL
	);

	CreateWindowEx(
		0,
		L"BUTTON",
		L"All Time",
		WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_AUTORADIOBUTTON,
		3 * ADMIN_WIDTH / 4 + 105,
		ADMIN_HEIGHT / 60 + 110,
		100,
		EDIT_HEIGHT,
		hwnd,
		(HMENU)ADMIN_ALL_TIME_RADIO,
		NULL,
		NULL
	);

	// List-View Controls

	INITCOMMONCONTROLSEX icex;
	icex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex);

	HWND hWndMemberList = CreateWindow(
		WC_LISTVIEW,
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
		ADMIN_WIDTH / 4 - LV_WIDTH / 2,
		ADMIN_HEIGHT / 5,
		LV_WIDTH,
		LV_HEIGHT,
		hwnd,
		(HMENU)ADMIN_MEMBER_LIST,
		NULL,
		NULL
	);

	HWND hWndLoginList = CreateWindow(
		WC_LISTVIEW,
		L"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
		3 * ADMIN_WIDTH / 4 - LV_WIDTH / 2,
		ADMIN_HEIGHT / 5,
		LV_WIDTH,
		LV_HEIGHT,
		hwnd,
		(HMENU)ADMIN_LOGIN_LIST,
		NULL,
		NULL
	);

	WCHAR idHeader[3] = L"ID";
	WCHAR nameHeader[5] = L"Name";
	WCHAR branchHeader[7] = L"Branch";
	WCHAR dateHeader[5] = L"Date";

	LVCOLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;

	lvc.iSubItem = 0;
	lvc.pszText = idHeader;
	lvc.cx = LV_WIDTH / 4;
	ListView_InsertColumn(hWndMemberList, 0, &lvc);
	ListView_InsertColumn(hWndLoginList, 0, &lvc);

	lvc.iSubItem = 1;
	lvc.pszText = nameHeader;
	lvc.cx = 3 * LV_WIDTH / 8;
	ListView_InsertColumn(hWndMemberList, 1, &lvc);
	ListView_InsertColumn(hWndLoginList, 1, &lvc);

	lvc.iSubItem = 2;
	lvc.pszText = branchHeader;
	lvc.cx = 3 * LV_WIDTH / 8;
	ListView_InsertColumn(hWndMemberList, 2, &lvc);
	lvc.pszText = dateHeader;
	ListView_InsertColumn(hWndLoginList, 2, &lvc);
}

std::string CreateQuery(LPSTR id, LPSTR name, LPSTR buttontxt, int CTRL_ID)
{
	std::string table;
	if (CTRL_ID == ADMIN_SEARCH_MEMBERS_BUTTON)
	{
		table = "members";
	}
	else if (CTRL_ID == ADMIN_SEARCH_LOGINS_BUTTON)
	{
		table = "logins";
	}
	else
	{
		return "error";
	}

	bool idFilled = strcmp("", id);
	bool nameFilled = strcmp("", name);
	bool buttonFilled = strcmp("", buttontxt);

	std::string q = "SELECT * FROM " + table;
	std::string idVal;
	std::string nameVal;
	std::string buttonVal;

	if (idFilled || nameFilled || buttonFilled) // at least one input field is filled
	{
		q += " WHERE ";
		if (idFilled)
		{
			idVal = "id = " + static_cast<std::string>(id);
		}
		if (nameFilled)
		{
			nameVal = "name = '" + static_cast<std::string>(name) + "'";
		}	
		if (buttonFilled)	
		{
			if (table == "members")
			{
				buttonVal = "branch = '" + static_cast<std::string>(buttontxt) + "'";
			}
			else
			{
				buttonVal = "date_time >= DATE_SUB(NOW(), INTERVAL ";
				if (!strcmp("Past Day", buttontxt))
				{
					buttonVal += "1 DAY)";
				}
				else if (!strcmp("Past Week", buttontxt))
				{
					buttonVal += "7 DAY)";
				}
				else if (!strcmp("Past Month", buttontxt))
				{
					buttonVal += "1 MONTH)";
				}
				else if (!strcmp("Past Year", buttontxt))
				{
					buttonVal += "1 YEAR)";
				}
			}
		}

		if (!idFilled && !nameFilled && buttonFilled)
		{
			q += buttonVal;
		}
		else if (!idFilled && nameFilled && !buttonFilled)
		{
			q += nameVal;
		}
		else if (!idFilled && nameFilled && buttonFilled)
		{
			q += nameVal + " AND " + buttonVal;
		}
		else if (idFilled && !nameFilled && !buttonFilled)
		{
			q += idVal;
		}
		else if (idFilled && !nameFilled && buttonFilled)
		{
			q += idVal + " AND " + buttonVal;
		}
		else if (idFilled && nameFilled && !buttonFilled)
		{
			q += idVal + " AND " + nameVal;
		}
		else if (idFilled && nameFilled && buttonFilled)
		{
			q += idVal + " AND " + nameVal + " AND " + buttonVal;
		}
	}
	
	if (table == "logins")
	{
		q += " ORDER BY date_time DESC";
	}
	else
	{
		q += " ORDER BY name ASC";
	}
	
	return q;
}

MYSQL_RES* AdminQueryDB(std::string query)
{
	const char* q = query.c_str();
	MYSQL_RES* res;
	int qstate;

	qstate = mysql_query(AdminConn, q);

	if (!qstate) // mysql_query functioned correctly
	{
		res = mysql_store_result(AdminConn);
		return res;
	}
	else
	{
		std::cerr << "Query failed: " << mysql_error(AdminConn) << std::endl;
		return NULL;
	}
}

