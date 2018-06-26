#include "stdafx.h"
#include "Track.h"
#include <string>
#include "SqlTool.h"

using std::string;
using std::to_string;



const char* Track::getTargetsQuery = "SELECT distinct TARGETID FROM m_preprocessing;";

char* Track::getTargetRecords(char* targetID) {
	char* res = new char[800];
	sprintf(res, "SELECT TARGETID,POSIXTIME,SOURCE,LONGITUDE,LATITUDE,ALTITUDE,OPERATOR,RESERVE1,RESERVE2,TASKINFO FROM m_preprocessing WHERE TARGETID = '%s' ORDER BY POSIXTIME; ", targetID);
	return res;
	//return string("SELECT TARGETID,POSIXTIME,SOURCE,LONGITUDE,LATITUDE,ALTITUDE,OPERATOR,RESERVE1,RESERVE2,TASKINFO FROM preprocessing_copy WHERE TARGETID = '").append(targetID).append("'ORDER BY POSIXTIME; ");
	}

Track::Track()
{
}

Track::Track(int trackID,char* TARGETID, char* SOURCE, char* TASKINFO, char* OPERATOR,int STARTTIME) {
	this->TRACKID = trackID;
	this->TARGETID = TARGETID;
	this->SOURCE = SOURCE;
	this->TASKINFO = TASKINFO;
	this->OPERATOR = OPERATOR;
	this->POINTAMOUNT = 1;
	this->STARTTIME = STARTTIME;
	this->CONFIDENCELEVEL = 1;
}

Track::Track(int trackID, char * TARGETID, char * SOURCE, char * TASKINFO, char * OPERATOR, char * STARTTIME)
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


void Track::setEndTime(int endTime) {
	this->ENDTIME = endTime;
}

void Track::setPointAmount(int pointAmount) {
	this->POINTAMOUNT = pointAmount;
}

void Track::setTrackID(int trackID) {
	this->TRACKID = trackID;
}

void Track::setLength(double length){
	this->length = length;
}

string Track::insertSQL() {
	
	string insertSql = "insert into m_historytrack_main (GUID,TRACKID,POINTAMOUNT,TARGETID,STARTTIME,ENDTIME,SOURCE,TASKINFO,CONFIDENCELEVEL,OPERATOR,LENGTH) values(";
	insertSql.append("UUID(),").append(to_string(this->TRACKID)).append(",").append(to_string(POINTAMOUNT)).append(",'").append(this->TARGETID).append("','")
		.append(SqlTool::datetimeConvertor(this->STARTTIME)).append("','").append(SqlTool::datetimeConvertor(this->ENDTIME)).append("','").append(this->SOURCE).append("','").append(this->TASKINFO)
		.append("',").append(to_string(this->CONFIDENCELEVEL)).append(",'").append(this->OPERATOR).append("',").append(to_string(this->length)).append(");");


	//char* res = new char[800];
	//sprintf(res, "insert into m_historytrack_main(GUID, TRACKID, POINTAMOUNT, TARGETID, STARTTIME, ENDTIME, SOURCE, TASKINFO, CONFIDENCELEVEL, OPERATOR, RESERVE1, RESERVE2) values(UUID(),\
	//	'%s',%d,'%s','%s','%s','%s','%s',%lf,'%s','%s','%s');",TRACKID,POINTAMOUNT,TARGETID,datetimeConvertor(STARTTIME),datetimeConvertor(ENDTIME),SOURCE,TASKINFO,
	//	CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2);

	//const char* res = "insert into M_HISTORYTRACK_MAIN(GUID, TRACKID, POINTAMOUNT, TARGETID, STARTTIME, ENDTIME, SOURCE, TASKINFO, CONFIDENCELEVEL, OPERATOR, RESERVE1, RESERVE2) values(UUID(), 1, 2,3, '2018-05-30 14:14:14', '2018-5-3', 'source', 'taskInfo', 0.000000, 'Gaara', '', '');";
	return insertSql;
}

char* Track::datetimeConvertor(int input) {
	time_t t = input;
	tm *ltm = localtime(&t);
	char* res = new char[19];
	sprintf(res, "%4d-%02d-%02d %02d:%02d:%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	return res;
}

void Track::trackEndProcession(int endTime, int pointAmount, vector<TrackPoint>details,double totallength) {
	this->setEndTime(endTime);
	this->setPointAmount(pointAmount);
	this->setLength(totallength);
	this->historyPoint.assign(details.begin(), details.end());
}

Track::~Track()
{
}

