#ifndef ODBC_H_
#define ODBC_H_

#include <string>

#include <windows.h>

#include <sql.h>
#include <sqlext.h>

#pragma comment(lib, "odbc32.lib")

class ConnectionException : public std::exception
{
	public:
		const char* what() const;
};

class InvalidCreateException : public std::exception
{
	public:
		const char* what() const;
};

class InvalidReadException : public std::exception
{
	public:
		const char* what() const;
};

class InvalidUpdateException : public std::exception
{
	public:
		const char* what() const;
};

namespace ODBC
{
	bool CheckConnection();

	bool Connect(std::string _dsnName, std::string _userName, std::string _password);

	void Disconnect();

	SQLHANDLE GetConnection();
}

#endif /* ODBC_H_ */
