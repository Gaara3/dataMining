﻿#include "stdafx.h"
#include "Track.h"
#include "MiningTools.h"
#include <string>


using std::string;
using std::to_string;



const char* Track::getTargetsQuery = "SELECT distinct TARGETID FROM m_preprocessing;";

//extern vector<Track> HistoryTracks;

char* Track::getTargetRecords(char* targetID) {
	char* res = new char[800];
	sprintf(res, "SELECT TARGETID,POSIXTIME,SOURCE,LONGITUDE,LATITUDE,ALTITUDE,OPERATOR,RESERVE1,RESERVE2,TASKINFO,SPEED,ANGLE FROM m_preprocessing WHERE TARGETID = '%s' ORDER BY POSIXTIME; ", targetID);
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

int Track::getEndTime()
{
	return this->ENDTIME;
}

int Track::getStartTime()
{
	return this->STARTTIME;
}

int Track::getPointAmount()
{
	return this->POINTAMOUNT;
}

void Track::setPointAmount(int pointAmount) {
	this->POINTAMOUNT = pointAmount;
}

void Track::setStartTime(int startTime)
{
	this->STARTTIME = startTime;
}

void Track::setTrackID(int trackID) {
	this->TRACKID = trackID;
}

void Track::setTrackIDofPoint(int trackID) {
	for (vector<TrackPoint>::iterator i = this->historyPoint.begin(); i!=historyPoint.end();i++) {
		(*i).setTrackID(trackID);
	}
}
void Track::setLength(double length){
	this->length = length;
}

void Track::setTargetID(char * id)
{
	this->TARGETID = id;
}

char * Track::getTargetID()
{
	return this->TARGETID;
}

string Track::insertHisSQL() {
	
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

char * Track::insertFreqSQL()
{
	char res[1000];
	sprintf(res, "insert into m_selectedfrequentlytrack_main (GUID,TRACKID,POINTAMOUNT,TARGETID,STARTTIME,ENDTIME,LENGTH,CONFIDENCELEVEL,OPERATOR) VALUES\
(UUID(),%d,%d,%s,'%s','%s',%lf,1,'%s')", TRACKID, POINTAMOUNT,TARGETID, SqlTool::datetimeConvertor(this->STARTTIME), SqlTool::datetimeConvertor(this->ENDTIME),length,OPERATOR);
	return res;
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

int Track::NnPointOfGrid(int index1, int index2) {//先算出网格平均坐标，再得出最近点
	if (index1 == index2)
		return index1;
	double tmpLongitude = 0, tmpLatitude = 0;
	for (int counter = index1; counter <= index2; counter++) {
		tmpLatitude += historyPoint[counter].CENTERLATITUDE;
		tmpLongitude += historyPoint[counter].CENTERLONGITUDE;
	}
	tmpLatitude /= (index2 - index1 + 1);
	tmpLongitude /= (index2 - index1 + 1);
	int resIndex = -1;
	double minBias = 800;//与网格均值点的最小偏移。处于计算量考虑，暂时用经纬度偏移量代替（若误差较大则改为实际距离）
	for (int counter = index1; counter <= index2; counter++) {
		double tmpBias = abs(historyPoint[counter].CENTERLATITUDE - tmpLatitude) + abs(historyPoint[counter].CENTERLONGITUDE - tmpLongitude);
		if (tmpBias < minBias) {
			minBias = tmpBias;
			resIndex = counter;
		}
	}
	return resIndex;
}

void Track::extractNnPoint(double* edges, double prec) {
	Grid curGrid = { true,-1,-1,0,-1 };
	for (int counter = 0; counter < this->POINTAMOUNT; counter++) {//TODO  考虑最后一个点！
		int tmpGridX = historyPoint[counter].getGridX(edges, prec), tmpGridY = historyPoint[counter].getGridY(edges, prec);
		historyPoint[counter].gridX = tmpGridX;
		historyPoint[counter].gridY = tmpGridY;		//出于聚类距离考虑，暂时不适用放大坐标，直接用经纬信息
		/*historyPoint[counter].gridX = historyPoint[counter].CENTERLONGITUDE;
		historyPoint[counter].gridY = historyPoint[counter].CENTERLATITUDE;*/
		//if 新格:计算目前的NnPoint,更新startIndex      旧格:更新endIndex
		if (curGrid.inTheGrid(tmpGridX,tmpGridY)) {	//仍处于curGrid，则更新endIndex
			curGrid.endIndex = counter;
		}
		else {
			if(counter!=0)
				this->featurePointIndex.push_back(NnPointOfGrid(curGrid.startIndex, curGrid.endIndex));
			curGrid.startIndex = counter;
			curGrid.endIndex = counter;
			curGrid.gridX = tmpGridX;
			curGrid.gridY = tmpGridY;
		}
	}
	this->featurePointIndex.push_back(NnPointOfGrid(curGrid.startIndex, curGrid.endIndex));
}

void Track::MDLExtract() {
	int star_index = 1, length = 1, count = 1,curr_index = 0;
	int len = (int)this->featurePointIndex.size();
	mdlPointIndex.push_back(featurePointIndex[0]);
	if (len > 1) {
		while (star_index + length < len) {
			curr_index = star_index + length;
			double cost_par = MDL_par(star_index, curr_index);
			double cost_nopar = MDL_nopar(star_index, curr_index) + 0.001;
			if (cost_par > cost_nopar) {
				count++;
				mdlPointIndex.push_back(featurePointIndex[curr_index - 1]);//TODO  待考察
				star_index = curr_index + 1;
				length = 1;
			}
			else {
				length++;
			}
		}
		mdlPointIndex.push_back(featurePointIndex[len - 1]);
	}	
}

double Track::MDL_par(int star_index, int cur_index) {
	double res = 0;
	int realStartIdx = featurePointIndex[star_index];
	int realEndIdx = featurePointIndex[cur_index];
	double x1 = historyPoint[realStartIdx].CENTERLONGITUDE;
	double y1 = historyPoint[realStartIdx].CENTERLATITUDE;
	double x2 = historyPoint[realEndIdx].CENTERLONGITUDE;
	double y2 = historyPoint[realEndIdx].CENTERLATITUDE;
	res += sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	double weights[3] = { 1,1,0 };//此时当做无水平分量
	Segment s2e = Segment{ Point{x1,y1 },Point{ x2,y2 } };

	for (int counter = star_index; counter < cur_index; counter++) {
		int tmpIdx1 = featurePointIndex[counter], tmpIdx2 = featurePointIndex[counter + 1];
		Segment temp = Segment{ Point{ historyPoint[tmpIdx1].CENTERLONGITUDE,historyPoint[tmpIdx1].CENTERLATITUDE },Point{ historyPoint[tmpIdx2].CENTERLONGITUDE,historyPoint[tmpIdx2].CENTERLATITUDE } };
		res += MiningTools::distanceBetweenLines(s2e,temp,weights);
	}
	return res;
}

double Track::MDL_nopar(int star_index, int cur_index) {
	return lth(star_index,cur_index);
}

double Track::lth(int star_index, int cur_index) {
	double res = 0;
	for (int counter1 = star_index; counter1 < cur_index; counter1++) {
		for (int counter2 = counter1+1; counter2 <= cur_index; counter2++) {
			int tmpIdx1 = featurePointIndex[counter1], tmpIdx2 = featurePointIndex[counter2];
			int x1 = historyPoint[tmpIdx1].CENTERLONGITUDE;
			int y1 = historyPoint[tmpIdx1].CENTERLATITUDE;
			int x2 = historyPoint[tmpIdx2].CENTERLONGITUDE;
			int y2 = historyPoint[tmpIdx2].CENTERLATITUDE;
			res += sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
		}
	}
	return res;
}

void Track::segGenerate(vector<Segment> &segs,int trackIdx) {
	int pointAmount = (int)this->mdlPointIndex.size();
	int segAmount = pointAmount - 1;
	for (int counter = 0; counter < segAmount; counter++) {
		int startIdx = this->mdlPointIndex[counter];
		int endIdx = this->mdlPointIndex[counter + 1];
		TrackPoint start = historyPoint[startIdx];
		TrackPoint end = historyPoint[endIdx ];
		segs.push_back({ Point{start.CENTERLONGITUDE,start.CENTERLATITUDE },Point{end.CENTERLONGITUDE,end.CENTERLATITUDE },trackIdx,startIdx ,trackIdx,endIdx });
	}
}

Track::~Track()
{
}

