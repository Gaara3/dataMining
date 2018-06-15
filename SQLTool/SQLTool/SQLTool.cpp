#include "stdafx.h"
#include "SqlTool.h"
#include <string>
#include <time.h>

//using std::string;
//using std::to_string;

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

char* SqlTool::uuidGenerator(MYSQL_RES* &res)
{
	this->operationExcutor("select UUID()", res);
	MYSQL_ROW column = mysql_fetch_row(res);
	return column[0];
}

char* SqlTool::datetimeConvertor(int input) {
	time_t t = input;
	tm *ltm = localtime(&t);	
	char* res =new char[19];
	sprintf(res, "%4d-%02d-%02d %02d:%02d:%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	return res;
	/*return to_string(ltm->tm_year + 1900).append("-").append(to_string(ltm->tm_mon + 1)).append("-").append(to_string(ltm->tm_mday + 1)).append(" ").append(to_string(ltm->tm_hour))
		.append(":").append(to_string(ltm->tm_min)).append(":").append(to_string(ltm->tm_sec));*/

}


//int main() {
//	int t = 1511008795;
//	SqlTool tool;
//	printf(tool.timeStampConvertor(t));
//	system("pause");
//}