#include "ODBCStatement.h"

ODBCStatement::ODBCStatement(SQLHANDLE _connection) :
	m_connection(_connection),
	m_statement(NULL)
{
	SQLAllocHandle(SQL_HANDLE_STMT, _connection, &m_statement);
}

ODBCStatement::~ODBCStatement()
{
	if (m_statement != NULL)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_statement);
	}
}

SQLHANDLE ODBCStatement::GetStatement() const
{
	return m_statement;
}
