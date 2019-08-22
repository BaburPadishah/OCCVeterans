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
			char id[9], name[80], radio[12];
			BOOL valid = TRUE;

			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_MEMBERS_ID_EDIT, id, 9) != 0) // check if ID entered
			{
				//validate ID
				char* idp = &id[0];
				while (*idp != '\0')
				{
					++idp;
				}
				if (*idp != id[8])
				{
					valid = FALSE;
				}
			}
			else
			{
				id[0] = '\0';
			}
			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_MEMBERS_NAME_EDIT, name, 80) != 0) // check if name entered
			{
				//validate name
				char* pname = &name[0];
				while (*pname != '\0')
				{
					if (!isalpha(*pname) && *pname != ' ' && *pname != '-' && *pname != ',' && *pname != '\'')
					{
						valid = FALSE;
					}
					else if (*pname == '\'' && *(pname - 1) != '\'')
					{
						char* pap = pname;
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
					++pname;
				}
			}
			else
			{
				name[0] = '\0';
			}

			if (!valid)
			{
				MessageBox(hwnd, L"Input not recognized.", L"Error", MB_OK);
				break;
			}

			//check if button checked
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

				wchar_t* wrow = new wchar_t[80];
				size_t retval;
				rsize_t dstsz = strlen(row[0]) + 1;
				rsize_t len = strlen(row[0]) + 1;
				lvI.cchTextMax = len;
				mbstowcs_s(&retval, wrow, dstsz, row[0], len);
				LPWSTR ptr = wrow;
				lvI.pszText = ptr;
				ListView_InsertItem(GetDlgItem(hwnd, ADMIN_MEMBER_LIST), &lvI);

				for (int j = 1; j < 3; ++j)
				{
					++lvI.iSubItem;
					len = strlen(row[j]) + 1;
					dstsz = strlen(row[j]) + 1;
					lvI.cchTextMax = len;
					mbstowcs_s(&retval, wrow, dstsz, row[j], len);
					ptr = wrow;
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
			char id[9], name[80], date[16];
			BOOL valid = TRUE;

			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_LOGINS_ID_EDIT, id, 9) != 0) // check if ID is entered
			{
				// validate ID
				char* idp = &id[0];
				while (*idp != '\0')
				{
					++idp;
				}
				if (*idp != id[8])
				{
					valid = FALSE;
				}
			}
			else
			{
				id[0] = '\0';
			}
			if (GetDlgItemTextA(hwnd, ADMIN_SEARCH_LOGINS_NAME_EDIT, name, 80) != 0)
			{
				//validate name
				char* pname = &name[0];
				while (*pname != '\0')
				{
					if (!isalpha(*pname) && *pname != ' ' && *pname != '-' && *pname != ',' && *pname != '\'')
					{
						valid = FALSE;
					}
					else if (*pname == '\'' && *(pname - 1) != '\'')
					{
						char* pap = pname;
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
					++pname;
				}
			}
			else
			{
				name[0] = '\0';
			}

			if (!valid)
			{
				MessageBox(hwnd, L"Input not recognized.", L"Error", MB_OK);
				break;
			}


			SYSTEMTIME st = { 0 };

			DateTime_GetSystemtime(GetDlgItem(hwnd, DATE_PICKER), &st);

			sprintf_s(date,"%d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
			if (date[0] == '0')
			{
				date[0] = '\0';
			}

			std::string q = CreateQuery(id, name, date, ADMIN_SEARCH_LOGINS_BUTTON);
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

				wchar_t* wrow = new wchar_t[60];
				size_t retval;
				rsize_t dstsz = strlen(row[0]) + 1;
				mbstowcs_s(&retval, wrow, dstsz, row[0], strlen(row[0]) + 1);
				LPWSTR ptr = wrow;
				lvI.pszText = ptr;
				ListView_InsertItem(GetDlgItem(hwnd, ADMIN_LOGIN_LIST), &lvI);

				for (int j = 1; j < 3; ++j)
				{
					++lvI.iSubItem;
					rsize_t len = strlen(row[j]) + 1;
					rsize_t dstsz = strlen(row[j]) + 1;
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
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
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
				buttonVal = "date_time >= '" 
					+ static_cast<std::string>(buttontxt) 
					+ "'" " AND " 
					+ "date_time <= '" 
					+ static_cast<std::string>(buttontxt) 
					+ " 23:59:59'";
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

