#ifndef ODBCQUERY_H_
#define ODBCQUERY_H_

#include "ODBCStatement.h"

class ODBCQuery : public ODBCStatement
{
	public:
		ODBCQuery(SQLHANDLE _connection);

		bool Execute(SQLCHAR* _pQuery);

		unsigned int GetRowCount() const;

		tm GetDate(unsigned int _column) const;

		std::string GetString(unsigned int _column) const;

		unsigned int GetUnsignedInt(unsigned int _column) const;

		unsigned long GetUnsignedLong(unsigned int _column) const;

		bool HasMoreRows() const;

		void NextRow();

	private:
		bool m_bHasMoreRows;

		SQLLEN m_rowCount;
};

#endif /* ODBCQUERY_H_ */
