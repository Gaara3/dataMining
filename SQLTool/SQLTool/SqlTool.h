#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <WinSock.h>  //һ��Ҫ�������������winsock2.h
#include <Windows.h>
#include "mysql.h"
class SqlTool
{
private:
	MYSQL mysql;
	MYSQL_RES *res;
	//MYSQL_ROW column;

public:
	bool connectDB();
	bool operationExcutor(const char* operation,MYSQL_RES* &res);
	SqlTool();
	~SqlTool();
};

