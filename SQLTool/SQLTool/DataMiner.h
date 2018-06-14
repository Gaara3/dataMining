#pragma once

#include <WinSock.h>  //一定要包含这个，或者winsock2.h
#include <Windows.h>
#include "mysql.h"  
#include <mysql.h>
class DataMiner
{
private:
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW rowElement;
public:
	bool connectDatabase(const char* database);
	bool operateDatabase(const char* operation);
	DataMiner();
	~DataMiner();
	//void dataPreprocess();
};

