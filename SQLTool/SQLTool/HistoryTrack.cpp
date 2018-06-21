#include "stdafx.h"
#include "HistoryTrack.h"
#include <string>
#include "SqlTool.h"

using std::string;
using std::to_string;



const char* HistoryTrack::getTargetsQuery = "SELECT distinct TARGETID FROM PREPROCESSING_copy;";

char* HistoryTrack::getTargetRecords(char* targetID) {
	char* res = new char[800];
	sprintf(res, "SELECT TARGETID,POSIXTIME,SOURCE,LONGITUDE,LATITUDE,ALTITUDE,OPERATOR,RESERVE1,RESERVE2,TASKINFO FROM preprocessing_copy WHERE TARGETID = '%s' ORDER BY POSIXTIME; ", targetID);
	return res;
	//return string("SELECT TARGETID,POSIXTIME,SOURCE,LONGITUDE,LATITUDE,ALTITUDE,OPERATOR,RESERVE1,RESERVE2,TASKINFO FROM preprocessing_copy WHERE TARGETID = '").append(targetID).append("'ORDER BY POSIXTIME; ");
	}

HistoryTrack::HistoryTrack()
{
}

HistoryTrack::HistoryTrack(int trackID,char* TARGETID, char* SOURCE, char* TASKINFO, char* OPERATOR,int STARTTIME) {
	this->TRACKID = trackID;
	this->TARGETID = TARGETID;
	this->SOURCE = SOURCE;
	this->TASKINFO = TASKINFO;
	this->OPERATOR = OPERATOR;
	this->POINTAMOUNT = 1;
	this->STARTTIME = STARTTIME;
	this->CONFIDENCELEVEL = 1;
}

HistoryTrack::HistoryTrack(int trackID, char * TARGETID, char * SOURCE, char * TASKINFO, char * OPERATOR, char * STARTTIME)
{
	this->TRACKID = trackID;
	this->TARGETID = TARGETID;
	this->SOURCE = SOURCE;
	this->TASKINFO = TASKINFO;
	this->OPERATOR = OPERATOR;
	this->POINTAMOUNT = 1;
	this->STARTTIME = atoi(STARTTIME);
	this->CONFIDENCELEVEL = 1;
}


void HistoryTrack::setEndTime(int endTime) {
	this->ENDTIME = endTime;
}

void HistoryTrack::setPointAmount(int pointAmount) {
	this->POINTAMOUNT = pointAmount;
}

void HistoryTrack::setTrackID(int trackID) {
	this->TRACKID = trackID;
}

char* HistoryTrack::insertSQL() {
	
	//string insertSql = "insert into HISTORYTRACK_MAIN_COPY1 (ID,TRACKID,POINTAMOUNT,TARGETID,STARTTIME,ENDTIME,SOURCE,TASKINFO,CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2) values(";
	/*insertSql.append("UUID(),'").append(this->TRACKID).append("',").append(to_string(POINTAMOUNT)).append(",'").append(this->TARGETID).append("','")
		.append(SqlTool::datetimeConvertor(this->STARTTIME)).append("','").append(SqlTool::datetimeConvertor(this->ENDTIME)).append("','").append(this->SOURCE).append("','").append(this->TASKINFO)
		.append("',").append(to_string(this->CONFIDENCELEVEL)).append(",'").append(this->OPERATOR).append("','").append(this->RESERVE1).append("','")
		.append(this->RESERVE2).append("');");*/


	/*char* res = new char[800];
	sprintf(res, "insert into HISTORYTRACK_MAIN_COPY1(ID, TRACKID, POINTAMOUNT, TARGETID, STARTTIME, ENDTIME, SOURCE, TASKINFO, CONFIDENCELEVEL, OPERATOR, RESERVE1, RESERVE2) values(UUID(),\
		'%s',%d,'%s','%s','%s','%s','%s',%lf,'%s','%s','%s');",TRACKID,POINTAMOUNT,TARGETID,datetimeConvertor(STARTTIME),datetimeConvertor(ENDTIME),SOURCE,TASKINFO,
		CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2);*/

	const char* res = "insert into HISTORYTRACK_MAIN_copy1(ID, TRACKID, POINTAMOUNT, TARGETID, STARTTIME, ENDTIME, SOURCE, TASKINFO, CONFIDENCELEVEL, OPERATOR, RESERVE1, RESERVE2) values(UUID(), '', 1, 'targetId', '2018-05-30 14:14:14', '2018-5-3', 'source', 'taskInfo', 0.000000, 'Gaara', '', '');";
	return const_cast<char*>(res);
}

char* HistoryTrack::datetimeConvertor(int input) {
	time_t t = input;
	tm *ltm = localtime(&t);
	char* res = new char[19];
	sprintf(res, "%4d-%02d-%02d %02d:%02d:%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	return res;
}

void HistoryTrack::trackEndProcession(int endTime, int pointAmount, vector<HistoryTrackDetail>details) {
	this->setEndTime(endTime);
	this->setPointAmount(pointAmount);
	this->historyTrackDetail.assign(details.begin(), details.end());
}

HistoryTrack::~HistoryTrack()
{
}

