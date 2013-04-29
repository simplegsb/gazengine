#ifndef ODBCSTATEMENT_H_
#define ODBCSTATEMENT_H_

#include "ODBC.h"

class ODBCStatement
{
	public:
		ODBCStatement(SQLHANDLE _connection);

		virtual bool Execute(SQLCHAR* _pQuery) = 0;

		std::string GetMessage();

		virtual ~ODBCStatement();

	protected:
		SQLHANDLE GetStatement() const;

	private:
		SQLHANDLE m_connection;

		SQLHANDLE m_statement;
};

#endif /* ODBCSTATEMENT_H_ */
