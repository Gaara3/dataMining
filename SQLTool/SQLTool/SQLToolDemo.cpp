// SQLTool.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock.h>  //一定要包含这个，或者winsock2.h
#include <Windows.h>
#include "mysql.h"    //引入mysql头文件(一种方式是在vc目录里面设置，一种是文件夹拷到工程目录，然后这样包含)
#include "TrackPoint.h"
#include "Track.h"


#pragma comment(lib,"wsock32.lib")
#pragma comment(lib,"libmysql.lib")
//
//using namespace std;
//
//MYSQL mysql;//mysql连接
//MYSQL_FIELD *fd;//字段列数组
//char field[32][32];  //存字段名二维数组
//MYSQL_RES *res;//表示返回行的一个查询结果集
//MYSQL_ROW column;//表示数据行的列
//char query[150];
//
//bool connectDatabase();
//void freeConnect();
////bool queryDatabase1();
//bool QueryDatabase2();
//bool insertData();
////bool modifyData();
//bool deleteData();

/*int main()
{
	connectDatabase();
	//queryDatabase1();
	//insertData();
	QueryDatabase2();
	//modifyData();
	//queryDataBase2();
	//deleteData();
	//queryDataBase2();
	freeConnect();
	system("pause");
	return 0;
}*/

/*bool connectDatabase() {
	mysql_init(&mysql);//初始化mysql,连接mysql

	//返回false则连接失败，返回true则连接成功
	if (!(mysql_real_connect(&mysql, "localhost", "root", "root", "bigdata", 3306, NULL, 0))) {
		printf("Error connecting to datebase:%s\n", mysql_error(&mysql));
		return false;
	}
	else {
		printf("Connected...\n");
		return true;
	}
}

void  freeConnect() {
	mysql_free_result(res);
	mysql_close(&mysql);
}*/

/*bool queryDatabase1() {
	sprintf_s(query, "select * from zjall limit 10");//执行查询语句，这里是查询所有，user是表名，不用加引号，用strcpy也可以
	mysql_query(&mysql, "set username gbk");//设置编码格式（SET NAMES GBK也行），否则cmd下中文乱码
	//返回0 查询成功，返回1查询失败
	if (mysql_query(&mysql, query)) {//执行SQL语句
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	if (!(res = mysql_store_result(&mysql)))    //获得sql语句结束后返回的结果集  
	{
		printf("Couldn't get result from %s\n", mysql_error(&mysql));
		return false;
	}

	//打印数据行数  
	printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));

	//获取字段的信息  
	char *str_field[32];  //定义一个字符串数组存储字段信息  
	for (int i = 0; i<6; i++)   //在已知字段数量的情况下获取字段名  
	{
		str_field[i] = mysql_fetch_field(res)->name;
	}
	for (int i = 0; i<6; i++)   //打印字段  
		printf("%8s\t", str_field[i]);
	printf("\n");
	//打印获取的数据  
	while (column = mysql_fetch_row(res))   //在已知字段数量情况下，获取并打印下一行  
	{
		printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n", column[0], column[1], column[2], column[3],column[4],column[5]);  //column是列数组  
	}
	return true;
}*/

/*bool QueryDatabase2()
{
	mysql_query(&mysql, "set username gbk");
	//返回0 查询成功，返回1查询失败  
	if (mysql_query(&mysql, "select * from preprocessing"))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("query success\n");
	}
	res = mysql_store_result(&mysql);
	//打印数据行数  
	printf("number of dataline returned: %d\n", mysql_affected_rows(&mysql));
	for (int i = 0; fd = mysql_fetch_field(res); i++)  //获取字段名  
		strcpy_s(field[i], fd->name);
	int j = mysql_num_fields(res);  // 获取列数  
	for (int i = 0; i<j; i++)  //打印字段  
		printf("%10s\t", field[i]);
	printf("\n");
	while (column = mysql_fetch_row(res))
	{
		for (int i = 0; i<j; i++)
			printf("%10s\t", column[i]);
		printf("\n");
	}
	return true;
}*/

//插入数据  
/*bool InsertData()
{
	sprintf(query, "insert into user values (NULL, 'Lilei', 'wyt2588zs','lilei23@sina.cn');");  //可以想办法实现手动在控制台手动输入指令  
	if (mysql_query(&mysql, query))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}
//修改数据  
bool ModifyData()
{
	sprintf(query, "update user set email='lilei325@163.com' where name='Lilei'");
	if (mysql_query(&mysql, query))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}
//删除数据  
bool DeleteData()
{
	/*sprintf(query, "delete from user where id=6");
	char query[100];
	printf("please input the sql:\n");
	gets(query);  //这里手动输入sql语句  
	if (mysql_query(&mysql, query))        //执行SQL语句  
	{
		printf("Query failed (%s)\n", mysql_error(&mysql));
		return false;
	}
	else
	{
		printf("Insert success\n");
		return true;
	}
}**/

//int main() {
//	HistoryTrackDetail hisd = HistoryTrackDetail("trackid", 101, "targetid", "2018-05-03 12:00:00", "sensor", 180, 0, 26, 1, "gaara", "test", "test2");
//	string res = hisd.insertSQL();
//	const char* reschar = res.c_str();
//	printf(reschar);
//	connectdatabase();
//
//	if (mysql_query(&mysql, reschar)) {
//		printf("insert succeed!!!");
//	}
//	else {
//		printf(mysql_error(&mysql));
//	}
//
//	system("pause");
//	return 0;
//}
