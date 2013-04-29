#include <windows.h>

#include <sqlext.h>

#include "ODBCQuery.h"

using namespace std;

ODBCQuery::ODBCQuery(SQLHANDLE _connection) :
	ODBCStatement(_connection),
	m_bHasMoreRows(false),
	m_rowCount(0)
{
}

bool ODBCQuery::Execute(SQLCHAR* _pQuery)
{
	if (SQL_SUCCEEDED(SQLExecDirectA(GetStatement(), _pQuery, SQL_NTS)))
	{
		if (SQL_SUCCEEDED(SQLFetch(GetStatement())))
		{
			m_bHasMoreRows = true; 
			return true;
		}
	}

	return false;
}

tm ODBCQuery::GetDate(unsigned int _column) const
{
	SQL_DATE_STRUCT value;
	SQLINTEGER length = 0;

	if (!SQL_SUCCEEDED(SQLGetData(GetStatement(), static_cast<SQLUSMALLINT>(_column), SQL_C_TYPE_DATE, &value, 1,
		&length)))
	{
		throw InvalidReadException();
	}

	tm date;
	date.tm_hour = -1;
	date.tm_isdst = 0;
	date.tm_mday = value.day;
	date.tm_min = -1;
	date.tm_mon = value.month - 1;
	date.tm_sec = -1;
	date.tm_wday = -1;
	date.tm_yday = -1;
	date.tm_year = value.year - 1900;

	return date;
}

unsigned int ODBCQuery::GetRowCount() const
{
	SQLLEN rowCount;

	if (!SQL_SUCCEEDED(SQLRowCount(GetStatement(), &rowCount)))
	{
		return 0;
	}

	return rowCount;
}

string ODBCQuery::GetString(unsigned int _column) const
{
	char buffer[256];
	SQLINTEGER length = 0;

	if (!SQL_SUCCEEDED(SQLGetData(GetStatement(), static_cast<SQLUSMALLINT>(_column), SQL_C_CHAR, buffer, 256,
		&length)))
	{
		throw InvalidReadException();
	}

	return string(buffer, length);
}

unsigned int ODBCQuery::GetUnsignedInt(unsigned int _column) const
{
	SQLUSMALLINT value;
	SQLINTEGER length = 0;

	if (!SQL_SUCCEEDED(SQLGetData(GetStatement(), static_cast<SQLUSMALLINT>(_column), SQL_C_USHORT, &value, 1,
		&length)))
	{
		throw InvalidReadException();
	}

	return (unsigned int) value;
}

unsigned long ODBCQuery::GetUnsignedLong(unsigned int _column) const
{
	SQLUINTEGER value;
	SQLINTEGER length = 0;

	if (!SQL_SUCCEEDED(SQLGetData(GetStatement(), static_cast<SQLUSMALLINT>(_column), SQL_C_ULONG, &value, 1,
		&length)))
	{
		throw InvalidReadException();
	}

	return (unsigned long) value;
}

bool ODBCQuery::HasMoreRows() const
{
	return m_bHasMoreRows;
}

void ODBCQuery::NextRow()
{
	if (!SQL_SUCCEEDED(SQLFetch(GetStatement())))
	{
		m_bHasMoreRows = false;
	}
}
