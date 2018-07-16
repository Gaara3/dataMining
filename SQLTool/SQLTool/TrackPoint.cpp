#include "stdafx.h"
#include "TrackPoint.h"
#include <string>
#include "Track.h"
#include "SqlTool.h"

using std::to_string;


int TrackPoint::intervalThreshold = 3600*6;

TrackPoint::TrackPoint()
{
}

TrackPoint::TrackPoint(char* TARGETID,char* POSIXTIME,char* SOURCE,double LONGITUDE,double LATITUDE, double ALTITUDE,char* OPERATOR, char* RESERVE1,char* RESERVE2,double speed,double angle ) {
	this->TARGETID = TARGETID;
	this->TIME = atoi(POSIXTIME);
	this->SOURCE = SOURCE;
	this->ORDERNUMBER = 1;
	this->CONFIDENCELEVEL = 1;

	this->CENTERLONGITUDE = LONGITUDE;
	this->UPPERLEFTLONGITUDE = LONGITUDE;
	this->UPPERRIGHTLONGITUDE = LONGITUDE;
	this->LOWERLEFTLONGITUDE = LONGITUDE;
	this->LOWERRIGHTLONGITUDE = LONGITUDE;

	this->CENTERALTITUDE = ALTITUDE;
	this->UPPERLEFTALTITUDE = ALTITUDE;
	this->UPPERRIGHTALTITUDE = ALTITUDE;
	this->LOWERLEFTALTITUDE = ALTITUDE;
	this->LOWERRIGHTALTITUDE = ALTITUDE;

	this->CENTERLATITUDE = LATITUDE;
	this->UPPERLEFTLATITUDE = LATITUDE;
	this->UPPERRIGHTLATITUDE = LATITUDE;
	this->LOWERLEFTLATITUDE = LATITUDE;
	this->LOWERRIGHTLATITUDE = LATITUDE;

	this->OPERATOR = OPERATOR;
	this->RESERVE1 = RESERVE1;
	this->RESERVE2 = RESERVE2;
	this->speed = speed;
	this->angle = angle;
}

void TrackPoint::setGridX(int X)
{
	this->gridX = X;
}

void TrackPoint::setGridY(int Y)
{
	this->gridY = Y;
}

//HistoryTrackPoint::HistoryTrackPoint(string TRACKID,int ORDERNUMBER,string TARGETID,int TIME,string SOURCE,
//	double CENTERLONGITUDE,double CENTERLATITUDE,double CENTERALTITUDE,/*double LOWERRIGHTLONGITUDE,double LOWERRIGHTLATITUDE ,
//	double LOWERRIGHTALTITUDE,double CENTERLONGITUDE,double CENTERLATITUDE,double CENTERALTITUDE,*/double CONFIDENCELEVEL,
//	string OPERATOR,string RESERVE1,string RESERVE2)
//{
//	this->TRACKID = TRACKID;
//	this->ORDERNUMBER = ORDERNUMBER;
//	this->TARGETID = TARGETID;
//	this->TIME = TIME;
//	this->SOURCE = SOURCE;
//	this->CENTERALTITUDE = CENTERALTITUDE;
//	this->CENTERLATITUDE = CENTERLATITUDE;
//	this->CENTERLONGITUDE = CENTERLONGITUDE;
//
//	this->UPPERLEFTALTITUDE = CENTERALTITUDE;
//	this->UPPERLEFTLATITUDE = CENTERLATITUDE;
//	this->UPPERLEFTLONGITUDE = CENTERLONGITUDE;
//
//	this->LOWERRIGHTALTITUDE = CENTERALTITUDE;
//	this->LOWERRIGHTLATITUDE = CENTERLATITUDE;
//	this->LOWERRIGHTLONGITUDE = CENTERLONGITUDE;
//	this->CONFIDENCELEVEL = 1;
//	this->OPERATOR = OPERATOR;
//	this->RESERVE1 = RESERVE1;
//	this->RESERVE2 = RESERVE2;
//
//	this->CONFIDENCELEVEL = 1;
//}

TrackPoint::~TrackPoint()
{
}

TrackPoint::TrackPoint(int orderNumber, double Longitude, double Latitude):ORDERNUMBER(orderNumber),CENTERLONGITUDE(Longitude),CENTERLATITUDE(Latitude)
{
}

string TrackPoint::insertSQL() {
	string insertSql = "insert into m_historytrack_sub(GUID,TRACKID,ORDERNUMBER,POSIXTIME,TIME,SOURCE,UPPERLEFTLONGITUDE,\
UPPERLEFTLATITUDE,UPPERLEFTALTITUDE, UPPERRIGHTLONGITUDE,UPPERRIGHTLATITUDE,UPPERRIGHTALTITUDE,LOWERRIGHTLONGITUDE,LOWERRIGHTLATITUDE,LOWERRIGHTALTITUDE,\
LOWERLEFTLONGITUDE,LOWERLEFTLATITUDE,LOWERLEFTALTITUDE,CENTERLONGITUDE,CENTERLATITUDE,\
CENTERALTITUDE,SPEED,ANGLE,CONFIDENCELEVEL,RESERVE1,RESERVE2) values(";
	insertSql.append("UUID(),").append(to_string(this->TRACKID)).append(",").append(to_string(this->ORDERNUMBER)).append(",").append(to_string(this->TIME)).append(",'")
		.append(SqlTool::datetimeConvertor(this->TIME)).append("','").append(this->SOURCE).append("',")
		.append(to_string(this->UPPERLEFTLONGITUDE)).append(",").append(to_string(this->UPPERLEFTLATITUDE)).append(",").append(to_string(this->UPPERLEFTALTITUDE)).append(",")
		.append(to_string(this->UPPERLEFTLONGITUDE)).append(",").append(to_string(this->UPPERLEFTLATITUDE)).append(",").append(to_string(this->UPPERLEFTALTITUDE)).append(",")
		.append(to_string(this->UPPERLEFTLONGITUDE)).append(",").append(to_string(this->UPPERLEFTLATITUDE)).append(",").append(to_string(this->UPPERLEFTALTITUDE)).append(",")
		.append(to_string(this->LOWERRIGHTLONGITUDE)).append(",").append(to_string(this->LOWERRIGHTLATITUDE)).append(",").append(to_string(this->LOWERRIGHTALTITUDE)).append(",")
		.append(to_string(this->CENTERLONGITUDE)).append(",").append(to_string(this->CENTERLATITUDE)).append(",").append(to_string(this->CENTERALTITUDE)).append(",")
		.append(to_string(this->speed)).append(",").append(to_string(this->angle)).append(",").append("1,'").append(this->RESERVE1).append("','").append(this->RESERVE2).append("');");

	//char* res = new char[900];
	//char* dateTimestr = datetimeConvertor(this->TIME);
	/*sprintf(res, "insert into HISTORYTRACK_SUB_COPY1(ID,TRACKID,ORDERNUMBER,TARGETID,TIME,SOURCE,UPPERLEFTLONGITUDE,\
UPPERLEFTLATITUDE,UPPERLEFTALTITUDE,LOWERRIGHTLONGITUDE,LOWERRIGHTLATITUDE,LOWERRIGHTALTITUDE,CENTERLONGITUDE,CENTERLATITUDE,\
CENTERALTITUDE,CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2) values(UUID(),'%s',%d,'%s','%s','%s',%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,'%s','%s','%s');",TRACKID, ORDERNUMBER,TARGETID, dateTimestr,SOURCE,
UPPERLEFTLONGITUDE, UPPERLEFTLATITUDE, UPPERLEFTALTITUDE, LOWERRIGHTLONGITUDE, LOWERRIGHTLATITUDE, LOWERRIGHTALTITUDE, CENTERLONGITUDE, CENTERLATITUDE, CENTERALTITUDE, CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2);*/
//	res = const_cast<char*>("insert into HISTORYTRACK_SUB_COPY1(ID,TRACKID,ORDERNUMBER,TARGETID,TIME,SOURCE,UPPERLEFTLONGITUDE,UPPERLEFTLATITUDE,UPPERLEFTALTITUDE,LOWERRIGHTLONGITUDE,LOWERRIGHTLATITUDE,LOWERRIGHTALTITUDE,CENTERLONGITUDE,CENTERLATITUDE,CENTERALTITUDE,CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2) values\
//		(UUID(), '', 1488, 'James', '2016-12-7 17:48:27', '8292', 95.435830, 25.638330, -3.000000, 95.435830, 25.638330, -3.000000, 95.435830, 25.638330, -3.000000, 1, 'root', '6.7', '228'); ");
	/*string insertSql = "insert into HISTORYTRACK_SUB_COPY1(ID,TRACKID,ORDERNUMBER,TARGETID,TIME,SOURCE,UPPERLEFTLONGITUDE,UPPERLEFTLATITUDE,UPPERLEFTALTITUDE,LOWERRIGHTLONGITUDE,LOWERRIGHTLATITUDE,LOWERRIGHTALTITUDE,CENTERLONGITUDE,CENTERLATITUDE,CENTERALTITUDE,CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2) values\
		(UUID(), '', 1488, 'James', '2016-12-7 17:48:27', '8292', 95.435830, 25.638330, -3.000000, 95.435830, 25.638330, -3.000000, 95.435830, 25.638330, -3.000000, 1, 'root', '6.7', '228'); ";*/
	return insertSql;

}

void  TrackPoint::setOrderNumber(int orderNumber) {
	this->ORDERNUMBER = orderNumber;
}

int TrackPoint::getOrderNumber()
{
	return this->ORDERNUMBER;
}

void TrackPoint::setTrackID(int trackID) {
	this->TRACKID = trackID;
}

int TrackPoint::getTime() {
	return this->TIME;
}

char* TrackPoint::getTargetID() {
	return this->TARGETID;
}

void Track::setTargetID(char* targetid) {
	this->TARGETID = targetid;
}
char* TrackPoint::getSource() {
	return this->SOURCE;
}

char* TrackPoint::getOperator() {
	return this->OPERATOR;
}

double TrackPoint::getSpeed()
{
	return this->speed;
}

void TrackPoint::setSpeed(double speed)
{
	this->speed = speed;
}



//与上一点时间间隔大，视为起点
bool TrackPoint::headOfTrack(int lastPosixTime) {
	return this->TIME - lastPosixTime > intervalThreshold;
}
//int main() {
//	/*HistoryTrackPoint hisD = HistoryTrackPoint("trackID", 101, "targetID", "2018-05-03 12:00:00", "sensor", 180, 0, 26, 1, "Gaara", "test", "test2");
//	string res = hisD.insertSQL();
//	const char* reschar = res.c_str();
//	printf(reschar);
//	system("pause");*/
//
//	HistoryTrack hisT = HistoryTrack(const_cast<char*>("targetId"), const_cast<char*>("source"), const_cast<char*>("taskInfo"), const_cast<char*>("Gaara"), const_cast<char*>("1341234235"));
//
//	printf(hisT.insertSQL().c_str());
//
//	system("pause");
//	return 0;
//}


char* TrackPoint::datetimeConvertor(int input) {
	time_t t = input;
	tm *ltm = localtime(&t);
	char* res = new char[19];
	sprintf(res, "%4d-%02d-%02d %02d:%02d:%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
	return res;
}


int TrackPoint::getGridX(vector<double> edges,double prec) {
	return floor((this->CENTERLONGITUDE- edges[1]) / prec);
}

int TrackPoint::getGridY(vector<double> edges, double prec) {
	return floor((this->CENTERLATITUDE - edges[3]) / prec);
}


bool TrackPoint::inTheGrid(Grid grid,vector<double> edges,double prec) {
	return this->getGridX(edges,prec) == grid.gridX  &&  this->getGridY(edges, prec) == grid.gridY;
}