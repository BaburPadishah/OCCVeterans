#include "header.h"

std::string createQuery(LPSTR id, LPSTR name, LPSTR buttontxt, int CTRL_ID)
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
				buttonVal = "branch = '"
					+ static_cast<std::string>(buttontxt)
					+ "'";
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

MYSQL_RES* adminQueryDB(std::string query)
{
	MYSQL* conn;
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

	if (conn)
	{
		std::cout << "Connection success" << std::endl;
	}
	else
	{
		std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
		return NULL;
	}

	const char* q = query.c_str();
	MYSQL_RES* res;
	int qstate;

	qstate = mysql_query(conn, q);

	if (!qstate) // mysql_query functioned correctly
	{
		res = mysql_store_result(conn);
		mysql_close(conn);
		return res;
	}
	else
	{
		std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
		return NULL;
	}
}