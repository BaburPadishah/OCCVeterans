#pragma once
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <chrono>
#include <commctrl.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
LRESULT CALLBACK RegWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AdminWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void checkIdNum(HWND hwnd, WPARAM wParam);
void AddControls(HWND);
std::string checkMembers(LPSTR id);

int newMember(LPSTR data);
void AddRegControls(HWND);
std::string registerMember(LPSTR id, LPSTR FName, LPSTR LName, LPSTR Branch);

int AdminWin();
void AddAdminControls(HWND hwnd);

// Screen resolution
const int SCREEN_W = GetSystemMetrics(SM_CXSCREEN);
const int SCREEN_H = GetSystemMetrics(SM_CYSCREEN);

// Global Constants - Main Window
const int WIN_WIDTH = 300;
const int WIN_HEIGHT = 200;
const int STATIC_WIDTH = 140;
const int STATIC_HEIGHT = 20;
const int EDIT_WIDTH = 140;
const int EDIT_HEIGHT = 20;
const int BUTTON_WIDTH = 70;
const int BUTTON_HEIGHT = 40;

// Global Constants - New Member Register Window
const int REG_WIDTH = 400;
const int REG_HEIGHT = 300;

// Global Constants - Admin Window 
const int ADMIN_WIDTH = 1000;
const int ADMIN_HEIGHT = 600;
const int LV_WIDTH = ADMIN_WIDTH / 2 - 50;
const int LV_HEIGHT = 2 * ADMIN_HEIGHT / 3;

enum Controls {
	STATIC, EDIT, BUTTON,
	REG_ID_STATIC, REG_FNAME_STATIC, REG_LNAME_STATIC, REG_BRANCH_STATIC, REG_ID_EDIT, REG_FNAME_EDIT, REG_LNAME_EDIT, REG_OK, REG_CANCEL,
	AIRFORCE_RADIO, NAVY_RADIO, ARMY_RADIO, COASTGUARD_RADIO, MARINES_RADIO,
	ADMIN_MEMBER_HEADER, ADMIN_LOGIN_HEADER, ADMIN_MEMBER_LIST, ADMIN_LOGIN_LIST, ADMIN_FINISH
};
