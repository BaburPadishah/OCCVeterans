#include "header.h"

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
		WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER | SS_LEFT,
		ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 30,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_MEMBERS_ID_EDIT,
		NULL,
		NULL
	);

	PostMessage(GetDlgItem(hwnd, ADMIN_SEARCH_MEMBERS_ID_EDIT), EM_LIMITTEXT, 8, 0);

	CreateWindow(L"EDIT",
		L"",
		WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL | SS_LEFT,
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
		WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER | SS_LEFT,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 30,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_LOGINS_ID_EDIT,
		NULL,
		NULL
	);

	PostMessage(GetDlgItem(hwnd, ADMIN_SEARCH_LOGINS_ID_EDIT), EM_LIMITTEXT, 8, 0);

	CreateWindow(L"EDIT",
		L"",
		WS_VISIBLE | WS_BORDER | WS_CHILD | ES_AUTOHSCROLL | SS_LEFT,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 60,
		STATIC_WIDTH,
		STATIC_HEIGHT,
		hwnd,
		(HMENU)ADMIN_SEARCH_LOGINS_NAME_EDIT,
		NULL,
		NULL
	);

	// List-View Controls

	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(icex);
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

	// date and time picker control
	icex.dwICC = ICC_DATE_CLASSES;
	InitCommonControlsEx(&icex);

	CreateWindowEx(
		0,
		DATETIMEPICK_CLASS,
		TEXT("DateTime"),
		WS_BORDER | WS_CHILD | WS_VISIBLE | DTS_APPCANPARSE | DTS_SHOWNONE,
		3 * ADMIN_WIDTH / 4 + 5,
		ADMIN_HEIGHT / 60 + 90,
		120,
		EDIT_HEIGHT + 10,
		hwnd,
		(HMENU)DATE_PICKER,
		NULL,
		NULL
	);

	//DateTime_SetFormat(GetDlgItem(hwnd, DATE_PICKER), L"yyyy - MM - dd");


	DateTime_SetMonthCalStyle(
		GetDlgItem(hwnd, DATE_PICKER),
		MCS_MULTISELECT | MCS_NOTODAYCIRCLE
	); // doesn't work?

}
