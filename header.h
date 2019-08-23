/**
	Orange Coast College Veterans' Association Sign-In
	Purpose: Maintain a database of club members are their sign-in times, 
		and allow an admin to search that database

	@author Hagen Atkeson
	@version 1.0 8/22/2019
*/

#pragma once
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <mysql.h>
#include <string.h>
#include <iostream>
#include <chrono>
#include <commctrl.h>

// window procedures
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);
LRESULT CALLBACK RegWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AdminWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// MAIN WINDOW FUNCTIONS
/**
	Adds the static, edit, and button controls to the main window

	@param hwnd a handle to the parent window
*/
void addControls(HWND hwnd);

/**
	Checks if the user's input is valid

	@param hwnd a handle to the parent window
	@param wParam a WORD denoting whether the button or the enter key is pressed
*/
void checkIdNum(HWND hwnd, WPARAM wParam);

/**
	Searches the members table for a matching ID string

	@param id a pointer to the user-provided ID
	@return the user's name if a match is found, otherwise "not found"
*/
std::string checkMembers(LPSTR id);

/**
	Searches the admin table for a matching ID string

	@param id a pointer to the user-provided ID
	@return "ADMIN" if a match is found, otherwise "not found"
*/
std::string checkAdmin(LPSTR id);

// NEW MEMBER REGISTRATION FUNCTIONS
/**
	Creates a New Member Registration window

	@param data a pointer to the user-provided ID number
	@return 0 on success
*/
int regWin(LPSTR data);

/**
	Adds static, edit, and button controls to New Member Registration window

	@param parent the New Member Registration window
*/
void addRegControls(HWND parent);

/**
	Adds a new member to the member table and records his or her sign-in

	@param id a pointer to the ID number string
	@param fName a pointer to the first name string
	@param lName a pointer to the last name string
	@param branch a pointer to the military branch string
	@return TRUE if successful connection and query, FALSE otherwise
*/
BOOL registerMember(LPSTR id, LPSTR fName, LPSTR lName, LPSTR branch);

// ADMIN SEARCH WINDOW FUNCTIONS
/**
	Creates an Admin Search window

	@return 0 on success
*/
int adminWin();

/**
	Adds static, edit, button, list view, and date-time-picker controls

	@param hwnd a handle to the parent window
*/
void addAdminControls(HWND hwnd);

/**
	Creates a query statement to be used in the Admin Search window

	@param id a pointer to the ID string
	@param name a pointer to the name string
	@param buttonTxt a pointer to either the military branch or date string
	@param CTRL_ID denotes whether the member or login table is being searched
	@return the query statement
*/
std::string createQuery(LPSTR id, LPSTR name, LPSTR buttonTxt, int CTRL_ID);

/*
	Queries the database to find any matches

	@param query the query statement
	@return a mySQL struct containing the results, NULL upon failure
*/
MYSQL_RES* adminQueryDB(std::string query);

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
const int RADIO_WIDTH = 100;

// Global Constants - New Member Register Window
const int REG_WIDTH = 400;
const int REG_HEIGHT = 300;

// Global Constants - Admin Window 
const int ADMIN_WIDTH = 1000;
const int ADMIN_HEIGHT = 900;
const int LV_WIDTH = ADMIN_WIDTH / 2 - 50;
const int LV_HEIGHT = 2 * ADMIN_HEIGHT / 3;

enum Controls {
	// Main window
	STATIC, EDIT, BUTTON,

	// Register window
	REG_ID_STATIC, REG_FNAME_STATIC, REG_LNAME_STATIC, REG_BRANCH_STATIC,
	REG_ID_EDIT, REG_FNAME_EDIT, REG_LNAME_EDIT, REG_OK, REG_CANCEL,
	AIRFORCE_RADIO, NAVY_RADIO, ARMY_RADIO, COASTGUARD_RADIO, MARINES_RADIO,

	// Admin window
	ADMIN_MEMBER_HEADER, ADMIN_LOGIN_HEADER, ADMIN_MEMBER_LIST, ADMIN_LOGIN_LIST,
	ADMIN_SEARCH_ID_STATIC, ADMIN_SEARCH_NAME_STATIC, ADMIN_SEARCH_BRANCH_STATIC,
	ADMIN_SEARCH_MEMBERS_ID_EDIT, ADMIN_SEARCH_MEMBERS_NAME_EDIT, 
	ADMIN_SEARCH_MEMBERS_BRANCH_EDIT,
	ADMIN_SEARCH_LOGINS_ID_EDIT, ADMIN_SEARCH_LOGINS_NAME_EDIT, 
	ALL_BRANCH_RADIO, DATE_PICKER,
	ADMIN_SEARCH_MEMBERS_BUTTON, ADMIN_SEARCH_LOGINS_BUTTON,
	ADMIN_FINISH
};