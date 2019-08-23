#include "header.h"

std::string checkAdmin(LPSTR id)
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
		return "Bad Connection";
	}

	std::string result = "not found";

	//query admin table
	std::string query = "SELECT * FROM admin WHERE id = '"
		+ static_cast<std::string>(id)
		+ "'";
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

	return result;
}

//connect to and query database
std::string checkMembers(LPSTR id)
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
		return "Bad Connection";
	}

	std::string result = "not found";


	//query members table
	std::string query = "SELECT * FROM members WHERE id = "
		+ static_cast<std::string>(id);
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

	if (result != "not found")  // match found
	{
		std::string ins = "INSERT INTO logins (id, name, date_time) VALUES ("
			+ static_cast<std::string>(id)
			+ ", '" + result + "', NOW())";

		qstate = mysql_query(conn, ins.c_str());

		if (qstate)
		{
			std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		}
	}

	mysql_close(conn);
	return result;
}

BOOL registerMember(LPSTR id, LPSTR FName, LPSTR LName, LPSTR Branch)
{
	MYSQL* conn;
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
		return FALSE;
	}

	std::string ins = "INSERT INTO members (id, name, branch) VALUES ("
		+ static_cast<std::string>(id)
		+ ", '"
		+ static_cast<std::string>(LName)
		+ ", "
		+ static_cast<std::string>(FName)
		+ "', '"
		+ static_cast<std::string>(Branch)
		+ "')";

	qstate = mysql_query(conn, ins.c_str());

	if (qstate)
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
	}

	std::string insLog = "INSERT INTO logins (id, name, date_time) VALUES ("
		+ static_cast<std::string>(id)
		+ ", '"
		+ static_cast<std::string>(LName)
		+ ", "
		+ static_cast<std::string>(FName)
		+ "', NOW())";

	qstate = mysql_query(conn, insLog.c_str());

	if (qstate)
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		return FALSE;
	}

	mysql_close(conn);
	return TRUE;
}