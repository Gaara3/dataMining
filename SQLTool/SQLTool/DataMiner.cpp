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
	vector<vector<HistoryTrack>> HistoryTracksOfAllTargets;    //轨迹集合的集合，即所有tar的轨迹集合

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
		string currentTrackID;
		vector<HistoryTrack> historyTracksOfOneTarget;
		
		if (sqlTool.operationExcutor(HistoryTrack::getTargetRecords(targets[counter]).c_str(),res)) {//单个target的所有记录
			MYSQL_RES *targetRecords = res;
			while (column = mysql_fetch_row(targetRecords)) {
				//无论是否为起点，先生成点记录
				HistoryTrackDetail tmp = HistoryTrackDetail(column[0], column[1], column[2], column[3], column[4], column[5], column[6], column[7], column[8]);
				if (!tmp.headOfTrack(lastPosixTime)) {	//当前点迹不是起点
					tmp.setOderNumber(++orderCounter);
					tmp.setTrackID(currentTrackID);
					historyTracksOfOneTarget.back().historyTrackDetail.push_back(tmp);//当前轨迹存入该点
					sqlTool.operationExcutor(tmp.insertSQL().c_str, res); //插入历史轨迹sub表	
				}
				else {		//当前点轨迹是起点
					if (!historyTracksOfOneTarget.empty()) {//此目标此前已有轨迹，则需更新上一轨迹的endTime,orderNumber,并将其记录入库
						historyTracksOfOneTarget.back().setPointAmount(orderCounter);
						historyTracksOfOneTarget.back().setEndTime(lastPosixTime);
						//存入数据库
						historyTracksOfOneTarget.back().insertSQL()
						orderCounter = 1;

					}
					HistoryTrack tmpTrack = HistoryTrack(column[0],column[2],column[9],column[6],column[1]);//SELECT TARGETID 0,POSIXTIME 1,SOURCE 2,LONGITUDE 3,LATITUDE 4,ALTITUDE 5,OPERATOR 6,RESERVE1 7,RESERVE2 8,TASKINFO 9;
					historyTracksOfOneTarget.push_back(tmpTrack);
					orderCounter = 1;					
					currentTrackID = tmpTrack.trackIDgenerator(32);
				}
				lastPosixTime = atoi(column[1]);//无论是否开启新段，都需要更新lastPosixTime
			}
			printf("result rows:%d", targetRecords->row_count);
			//mysql_free_result(res);
		}

		HistoryTracksOfAllTargets.push_back(historyTracksOfOneTarget);//将当前tar的所有轨迹放入总vector
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
