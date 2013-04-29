#include "ODBC.h"

using namespace std;

const char* ConnectionException::what() const
{
	return "Connection failed or query attempted without established connection.";
}

const char* InvalidCreateException::what() const
{
	return "Invalid creation attempted.";
}

const char* InvalidReadException::what() const
{
	return "Invalid read attempted.";
}

const char* InvalidUpdateException::what() const
{
	return "Invalid update attempted.";
}

namespace ODBC
{
	SQLHANDLE g_connection = NULL;

	SQLHANDLE g_environment = NULL;

	bool CheckConnection()
	{
		return g_connection != NULL;
	}

	bool Connect(string _dsnName, string _userName, string _password)
	{
		// Get a handle to the SQL environment.
		if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &g_environment)))
		{
			return false;
		}

		// Use ODBC v3.
		if (!SQL_SUCCEEDED(SQLSetEnvAttr(g_environment, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3, 0)))
		{
			return false;
		}

		// Get a handle to an SQL connection.
		if (!SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_DBC, g_environment, &g_connection)))
		{
			return false;
		}

		// Connect!
		if (!SQL_SUCCEEDED(SQLConnectA(g_connection, (SQLCHAR*) _dsnName.c_str(), SQL_NTS,
			(SQLCHAR*) _userName.c_str(), SQL_NTS, (SQLCHAR*) _password.c_str(), SQL_NTS)))
		{
			return false;
		}

		return true;
	}

	void Disconnect()
	{
		SQLFreeHandle(SQL_HANDLE_DBC, g_connection);
		SQLFreeHandle(SQL_HANDLE_ENV, g_environment);

		g_connection = NULL;
		g_environment = NULL;
	}

	SQLHANDLE GetConnection()
	{
		return g_connection;
	}
}
