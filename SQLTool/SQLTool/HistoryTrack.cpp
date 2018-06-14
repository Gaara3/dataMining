#include "stdafx.h"
#include "HistoryTrack.h"
#include <string>
#include <cmath>

using std::string;
using std::to_string;

string HistoryTrack::getTargetsQuery = "SELECT distinct TARGETID FROM PREPROCESSING_copy;";

string HistoryTrack::getTargetRecords(string targetID) {
	return string("SELECT TARGETID,POSIXTIME,SOURCE,LONGITUDE,LATITUDE,ALTITUDE,OPERATOR,RESERVE1,RESERVE2,TASKINFO FROM preprocessing_copy WHERE TARGETID = '").append(targetID).append("'ORDER BY POSIXTIME; ");
	}

HistoryTrack::HistoryTrack()
{
}

HistoryTrack::HistoryTrack(char* TARGETID, char* SOURCE, char* TASKINFO, char* OPERATOR,char* STARTTIME) {
	this->TARGETID = TARGETID;
	this->SOURCE = SOURCE;
	this->TASKINFO = TASKINFO;
	this->OPERATOR = OPERATOR;
	this->POINTAMOUNT = 1;
	this->STARTTIME = atoi(STARTTIME);
}

//TODO improvement is need
string HistoryTrack::trackIDgenerator(int length) {
	char* res;
	for (int counter = 0; counter < length; counter++) {
		res[counter] = 'A' + rand() % 26;
	}
	return string(res);
}

void HistoryTrack::setEndTime(int endTime) {
	this->ENDTIME = endTime;
}

void HistoryTrack::setPointAmount(int pointAmount) {
	this->POINTAMOUNT = pointAmount;
}

string HistoryTrack::insertSQL() {
	string insertSql = "insert into HISTORYTRACK_MAIN values(ID,TRACKID,POINTAMOUNT,TARGETID,STARTTIME,ENDTIME,SOURCE,TASKINFO,CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2) values(";
	insertSql.append("UUID(),'").append(this->TRACKID).append("',").append(to_string(POINTAMOUNT))
}

HistoryTrack::~HistoryTrack()
{
}

