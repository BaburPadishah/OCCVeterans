#include "header.h"

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