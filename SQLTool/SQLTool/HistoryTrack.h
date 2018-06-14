#pragma once
#include "stdafx.h"
#include <stdio.h>	
#include <Windows.h>
#include <winsock.h>
#include <string>
#include "mysql.h"
#include <vector>
#include "HistoryTrackDetail.h"

using std::string;
using std::vector;

MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW column;
char query[150];

class HistoryTrack {
private:
	string TRACKID;
	int POINTAMOUNT;
	string TARGETID;
	string TARGETMODELNUMBER;
	string TARGETNAME;
	string TARGETTYPE;
	string GB;
	string STARTTIME;
	string ENDTIME;
	double CONFIDENCELEVEL;
	string SOURCE;
	string TASKINFO;
	string OPERATOR;
	string RESERVE1;
	string RESERVE2;


public:
	//插入历史轨迹
	void insertIntoDB() {
		if (!connectDatabase()) {	//连接失败
			return;
		}
		string insertQuery = "insert into historytrack_main(ID,TRACKID,POINTAMOUNT,TARGETID,TARGETMODELNUMBER,) values "
		sprintf(query, "insert into historytrack_main(TODO) values (NULL, 'Lilei', 'wyt2588zs','lilei23@sina.cn');");  //可以想办法实现手动在控制台手动输入指令  
		if (mysql_query(&mysql, query))        //执行SQL语句  
		{
			printf("Query failed (%s)\n", mysql_error(&mysql));
			return ;
		}
		else
		{
			printf("Insert success\n");
			return ;
		}
		
	}

	//连接数据库
	bool connectDatabase() {
		mysql_init(&mysql);//初始化mysql,连接mysql

		if (!(mysql_real_connect(&mysql, "localhost", "root", "root", "bigdata", 3306, NULL, 0))) {
			printf("Error connecting to datebase:%s\n", mysql_error(&mysql));
			return false;
		}
		else {
			printf("Connected...\n");
			return true;
		}
	}
};
