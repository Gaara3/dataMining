#include "stdafx.h"
#include "SqlTool.h"
#include <string>
#include <time.h>


SqlTool::SqlTool()
{
}


SqlTool::~SqlTool()
{
	mysql_free_result(res);
	mysql_close(&mysql);
}

bool SqlTool::connectDB() {//TODO   封装传入参数
	mysql_init(&this->mysql);
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", "new_bigdata", 3306, NULL, 0)) {
		printf("Something wrong when connecting to the Database:%s\n", mysql_error(&mysql));
		return false;
	}
	printf("Connected to the database!\n");
	return true;
}

bool SqlTool::operationExcutor(const char* operation, MYSQL_RES* &res) {
	//printf("SQL:%s\n", operation);
	if (mysql_query(&this->mysql, operation))        //执行SQL语句  
	{
		printf("operation failed (%s)\n", mysql_error(&mysql));
		printf("SQL:%s\n", operation);
		return false;
	}
	res = mysql_store_result(&mysql);
	return true;
}

bool SqlTool::insertExcutor(const char* operation) {
	if (mysql_query(&this->mysql, operation))        //执行SQL语句  
	{
		printf("operation failed (%s)\n", mysql_error(&mysql));
		printf("SQL:%s\n", operation);
		return false;
	}
	return true;
}

char* SqlTool::getVariableFromDB(const char* operation) {	//获取统计信息max、min或数据库信息version、char等   单一返回值
	mysql_query(&this->mysql, operation);
	res = mysql_store_result(&this->mysql);
	MYSQL_ROW column = mysql_fetch_row(res);
	return strlen(column[0]) > 0 ? column[0] : const_cast<char*>("None");
}

//char* SqlTool::uuidGenerator(MYSQL_RES* &res)	
//{
//	this->operationExcutor("select UUID()", res);
//	MYSQL_ROW column = mysql_fetch_row(res);
//	return column[0];
//}

char* SqlTool::datetimeConvertor(int input) {
	time_t t = input;
	tm *ltm = localtime(&t);	
	char* res =new char[19];
	sprintf(res, "%4d-%02d-%02d %02d:%02d:%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	return res;
}
