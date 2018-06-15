﻿#include "stdafx.h"
#include "HistoryTrack.h"
#include <string>
#include "SqlTool.h"

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
	this->CONFIDENCELEVEL = 1;
}

//TODO improvement is need
string HistoryTrack::trackIDgenerator(int length) {
	return string("testtestteeesttest");
}

void HistoryTrack::setEndTime(int endTime) {
	this->ENDTIME = endTime;
}

void HistoryTrack::setPointAmount(int pointAmount) {
	this->POINTAMOUNT = pointAmount;
}

void HistoryTrack::setTrackID(string trackID) {
	this->TRACKID = trackID;
}

string HistoryTrack::insertSQL() {
	
	string insertSql = "insert into HISTORYTRACK_MAIN_COPY1 (ID,TRACKID,POINTAMOUNT,TARGETID,STARTTIME,ENDTIME,SOURCE,TASKINFO,CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2) values(";
	insertSql.append("UUID(),'").append(this->TRACKID).append("',").append(to_string(POINTAMOUNT)).append(",'").append(this->TARGETID).append("','")
		.append(SqlTool::datetimeConvertor(this->STARTTIME)).append("','").append(SqlTool::datetimeConvertor(this->ENDTIME)).append("','").append(this->SOURCE).append("','").append(this->TASKINFO)
		.append("',").append(to_string(this->CONFIDENCELEVEL)).append(",'").append(this->OPERATOR).append("','").append(this->RESERVE1).append("','")
		.append(this->RESERVE2).append("');");

	return insertSql;
}

string HistoryTrack::datetimeConvertor(int input) {
	return "";
}

HistoryTrack::~HistoryTrack()
{
}

