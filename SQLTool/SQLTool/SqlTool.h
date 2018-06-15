#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <WinSock.h>  //一定要包含这个，或者winsock2.h
#include <Windows.h>
#include <string>
#include "mysql.h"

using std::string;

class SqlTool
{
private:
	MYSQL mysql;
	MYSQL_RES *res;
	//MYSQL_ROW column;

public:	
	bool connectDB();
	bool operationExcutor(const char* operation,MYSQL_RES* &res);
	string uuidGenerator(MYSQL_RES* &res);
	static string datetimeConvertor(int input);
	SqlTool();
	~SqlTool();
};

