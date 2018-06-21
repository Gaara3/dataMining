#include "stdafx.h"
#include "PreProcessor.h"
#include "SqlTool.h"


PreProcessor::PreProcessor()
{
}


PreProcessor::~PreProcessor()
{
}
/*
	对入参列表的所有target进行预处理
*/
void PreProcessor::targetsPreProcession(vector<char*> targets, vector<HistoryTrack> &HistoryTracks) {
	int targetsNum = targets.size();
	bool newTarget = true;
	for (int counter = 0; counter < targetsNum; counter++) {
		printf("********************************new Target********************************\n");
		oneTargetPreProcession(targets[counter], HistoryTracks, newTarget);
	}
}

/*
	对特定目标进行预处理
*/
void PreProcessor::oneTargetPreProcession(char* target, vector<HistoryTrack>&HistoryTracks,bool &newTarget) {

	HistoryTrack tmp;
	int lastPosixtime = 0;
	int trackID = 0;
	int orderNumber = 0;
	sqlTool.operationExcutor(HistoryTrack::getTargetRecords(target), res);
	MYSQL_RES *targetRecord = res;
	//HistoryTrack* curTrack;
	vector<HistoryTrackDetail> details;
	while (column = mysql_fetch_row(targetRecord)) {		
		pointPreprocession(details,column,HistoryTracks,trackID, lastPosixtime,orderNumber, newTarget);
		newTarget = false;//TODO   改进
	}
	//单目标最后一段轨迹需要专门处理一次
	HistoryTracks.back().trackEndProcession(lastPosixtime, orderNumber, details);
	newTarget = true;
	sqlTool.operationExcutor(HistoryTracks.back().insertSQL(), res);
}


void PreProcessor::pointPreprocession(vector<HistoryTrackDetail>&details,MYSQL_ROW column, vector<HistoryTrack>&HistoryTracks,/* HistoryTrack *&curTrack,*/int &trackID, int &lastPosixTime,int &orderNumber,bool &newTarget) {
	HistoryTrackDetail point = HistoryTrackDetail(column[0], column[1], column[2], column[3], column[4], column[5], column[6], column[7], column[8]);
	
	if (point.headOfTrack(lastPosixTime)) {//该点是一段新轨迹
		printf("===============================new track============================\n");
		trackID++;
		if (!newTarget) {
			HistoryTrack *lastTrack = &HistoryTracks.back();
			
			/*lastTrack->setEndTime(lastPosixTime);
			lastTrack->setPointAmount(orderNumber);
			lastTrack->historyTrackDetail.assign(details.begin(), details.end());*/
			lastTrack->trackEndProcession(lastPosixTime, orderNumber, details);
			sqlTool.operationExcutor(lastTrack->insertSQL(), res);
			lastPosixTime = 0;			
			orderNumber = 0;			
			details.clear();	
		}
		HistoryTracks.push_back(HistoryTrack(trackID,point.getTargetID(), point.getSource(),column[9], point.getOperator(), point.getTime()));	//轨迹数组加入新track

	}
	
	//该点本身所需的操作:确定trackID,确定orderNumber，更新lastPosixTime，插入数据库
	point.setTrackID(trackID);
	lastPosixTime = point.getTime();
	point.setOderNumber(++orderNumber);
	details.push_back(point);
	//sqlTool.operationExcutor(point.insertSQL(), res);	
	printf("                              new point%d                              \n", orderNumber);
}

