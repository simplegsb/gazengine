#include <windows.h>

#include <sqlext.h>

#include "ODBCExec.h"

ODBCExec::ODBCExec(SQLHANDLE _connection) :
	ODBCStatement(_connection)
{
}

bool ODBCExec::Execute(SQLCHAR* _pExec)
{
	return SQL_SUCCEEDED(SQLExecDirectA(GetStatement(), _pExec, SQL_NTS));
}
