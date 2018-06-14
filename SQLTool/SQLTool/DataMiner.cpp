#include "stdafx.h"
#include "DataMiner.h"
#include "SqlTool.h"
#include "HistoryTrack.h"
#include "HistoryTrackDetail.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

MYSQL_RES *res;
SqlTool sqlTool;
MYSQL_ROW column;


int main() {
	vector<string> targets;
	vector<HistoryTrack> historyTrack;

	if (!sqlTool.connectDB()) {
		return 0;//连接数据库异常
	}
	if (!sqlTool.operationExcutor(HistoryTrack::getTargetsQuery.c_str(), res))
		return 0;//执行数据库操作异常,程序结束
	int targetNum = mysql_num_fields(res);  // 获取列数 
	while (column = mysql_fetch_row(res))//对每个目标进行操作
	{
		targets.push_back(column[0]);//column 0 是targetID      sqlTool.operationExcutor("SELECT ")
		printf(column[0]);
	}
	mysql_free_result(res);

	
	int targetsNum = targets.size();
	for (int counter = 0; counter < targetsNum; counter++) {	//对每个对象进行轨迹提取为了性能考虑暂时不用迭代器

		//分段开始
		int orderCounter = 1;
		int lastPosixTime = 0;
		if (sqlTool.operationExcutor(HistoryTrack::getTargetRecords(targets[counter]).c_str(),res)) {
			while (column = mysql_fetch_row(res)) {	
				HistoryTrackDetail tmp = HistoryTrackDetail(column[0], column[1], column[2], column[3], column[4], column[5], column[6], column[7], column[8]);
				if (!tmp.headOfTrack(lastPosixTime)) {	//当前点迹不是起点
					
				}
				else {		//当前点轨迹
					HistoryTrack tmpTrack = HistoryTrack(column[0],column[2],column[9],column[6],column[1]);//SELECT TARGETID 0,POSIXTIME 1,SOURCE 2,LONGITUDE 3,LATITUDE 4,ALTITUDE 5,OPERATOR 6,RESERVE1 7,RESERVE2 8,TASKINFO 9;
					orderCounter = 1;
					string trackI
				
				}
			}
			printf("result rows:%d", res->row_count);			
			//mysql_free_result(res);
		}
	}
	char *str_field[32];  //定义一个字符串数组存储字段信息  
	for (int i = 0; i<9; i++)   //在已知字段数量的情况下获取字段名  
	{
		str_field[i] = mysql_fetch_field(res)->name;
		printf("%10s\t", str_field[i]);
	}
	printf("result rows:%d", res->row_count);
 	while (column = mysql_fetch_row(res)) {
		printf("%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\t%10s\n", column[0], column[1], column[2], column[3], column[4], column[5],column[6],column[7],column[8]);  //column是列数组  
	}

	system("pause");
}
