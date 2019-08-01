#include "header.h"

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
		NULL,
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
		if (wParam == HTCAPTION)
		{
			return 0;
		}
		break;

	case WM_KEYDOWN:
		return 0;
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case ADMIN_FINISH:
			DestroyWindow(hwnd);
			break;
		}
		return 0;
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
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
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

	CreateWindow(
		L"BUTTON",
		L"Finish",
		WS_VISIBLE | WS_BORDER | WS_CHILD,
		5 * ADMIN_WIDTH / 6 - BUTTON_WIDTH / 2,
		5 * ADMIN_HEIGHT / 6,
		BUTTON_WIDTH,
		BUTTON_HEIGHT,
		hwnd,
		(HMENU)ADMIN_FINISH,
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
		WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
		ADMIN_WIDTH / 4 - LV_WIDTH / 2,
		ADMIN_HEIGHT / 10,
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
		WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS,
		3 * ADMIN_WIDTH / 4 - LV_WIDTH / 2,
		ADMIN_HEIGHT / 10,
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
	lvc.cx = LV_WIDTH / 3;
	ListView_InsertColumn(hWndMemberList, 0, &lvc);
	ListView_InsertColumn(hWndLoginList, 0, &lvc);

	lvc.iSubItem = 1;
	lvc.pszText = nameHeader;
	ListView_InsertColumn(hWndMemberList, 1, &lvc);
	ListView_InsertColumn(hWndLoginList, 1, &lvc);

	lvc.iSubItem = 2;
	lvc.pszText = branchHeader;
	ListView_InsertColumn(hWndMemberList, 2, &lvc);
	lvc.pszText = dateHeader;
	ListView_InsertColumn(hWndLoginList, 2, &lvc);

	ShowWindow(hWndMemberList, SW_SHOW);
	ShowWindow(hWndLoginList, SW_SHOW);
}
