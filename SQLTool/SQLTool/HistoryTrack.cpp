#include "stdafx.h"
#include "HistoryTrack.h"
#include <string>

using std::string;

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

HistoryTrack::~HistoryTrack()
{
}

