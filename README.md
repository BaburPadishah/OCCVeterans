# OCCVeterans
Digital sign-in for the Student Veterans Association at Orange Coast College

This program uses the Win32 API to display a window which prompts members of the SVA for their ID.
If their ID is detected, the user is signed in and the program records their information, including the current time, in a SQL server. 
If their ID is not detected, another window appears which prompts the user for their name and branch, and adds that information to the SQL server.

If a user enters in an administrator password, another window appears which allows the user to search for members by any or all of the following: name, ID, branch, arrival time.
