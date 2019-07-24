#include "functions.h"

//connect to and query database
std::string QueryDB(LPSTR data)
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
		+ static_cast<std::string>(data);
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
			+ static_cast<std::string>(data)
			+ ", '" + result + "', NOW())";

		qstate = mysql_query(conn, ins.c_str());

		if (qstate)
		{
			std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		}
	}

	return result;
}

int newMember(LPSTR data, HWND hwnd)
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
		WS_CAPTION | WS_POPUPWINDOW,
		SCREEN_W / 2 - REG_WIDTH / 2,
		SCREEN_H / 2 - REG_HEIGHT / 2,
		REG_WIDTH,
		REG_HEIGHT,
		NULL,
		NULL,
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
