#include "stdafx.h"
#include "Track.h"
#include <string>


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
		historyPoint[counter].gridY = tmpGridY;
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
	int len = this->featurePointIndex.size();
	while (star_index + length < len | star_index + length == len) {
		curr_index = star_index + length;
		double cost_par = MDL_par(star_index, curr_index);
		double cost_nopar = MDL_nopar(star_index, curr_index)+0.001;
		if (cost_par > cost_nopar) {
			count++;
			//TODO
			mdlPointIndex.push_back(featurePointIndex[curr_index - 1]);
			star_index = curr_index + 1;
			length = 1;
		}
		else {
			length++;
		}

	}
}

double Track::MDL_par(int star_index, int cur_index) {

}

double Track::MDL_nopar(int star_index, int cur_index) {

}

double Track::lth(int star_index, int cur_index) {

}

Track::~Track()
{
}

