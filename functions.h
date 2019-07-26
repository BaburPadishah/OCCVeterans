#pragma once
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <mysql.h>
#include <string>
#include <iostream>
#include <chrono>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
LRESULT CALLBACK RegWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void checkIdNum(HWND hwnd, WPARAM wParam);
void AddControls(HWND);
void AddRegControls(HWND);
std::string QueryDB(LPSTR data);
int newMember(LPSTR data, HWND hwnd);
std::string addUserToRegistry(LPSTR data);


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

enum Controls { 
	STATIC, EDIT, BUTTON, 
	REG_ID_STATIC, REG_FNAME_STATIC, REG_LNAME_STATIC, REG_BRANCH_STATIC, REG_ID_EDIT, REG_FNAME_EDIT, REG_LNAME_EDIT, REG_OK, REG_CANCEL,
	AIRFORCE_RADIO, NAVY_RADIO, ARMY_RADIO, COASTGUARD_RADIO, MARINES_RADIO
};
