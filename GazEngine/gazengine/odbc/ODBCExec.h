#ifndef ODBCEXEC_H_
#define ODBCEXEC_H_

#include "ODBCStatement.h"

class ODBCExec : public ODBCStatement
{
	public:
		ODBCExec(SQLHANDLE _connection);

		bool Execute(SQLCHAR* _pExec);
};

#endif /* ODBCEXEC_H_ */
