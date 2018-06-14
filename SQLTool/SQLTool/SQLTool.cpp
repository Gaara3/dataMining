﻿#include "stdafx.h"
#include "SqlTool.h"


SqlTool::SqlTool()
{
}


SqlTool::~SqlTool()
{
}

bool SqlTool::connectDB() {
	mysql_init(&this->mysql);
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "bigdata", 3306, NULL, 0)) {
		printf("Something wrong when connecting to the Database:%s\n", mysql_error(&mysql));
		return false;
	}
	printf("Connected to the database!\n");
	return true;
}

bool SqlTool::operationExcutor(const char* operation, MYSQL_RES* &res) {
	printf("SQL:%s\n", operation);
	if (mysql_query(&this->mysql, operation))        //执行SQL语句  
	{
		printf("operation failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	res = mysql_store_result(&mysql);
	return true;
}