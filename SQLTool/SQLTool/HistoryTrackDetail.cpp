#include "stdafx.h"
#include "HistoryTrackDetail.h"
#include <string>

using std::to_string;


int HistoryTrackDetail::intervalThreshold = 6000;

HistoryTrackDetail::HistoryTrackDetail()
{
}

HistoryTrackDetail::HistoryTrackDetail(char* TARGETID, char* POSIXTIME, char* SOURCE, char* LONGITUDE,char* LATITUDE,char* ALTITUDE,char* OPERATOR,char* RESERVE1,char* RESERVE2 ) {
	this->TARGETID = TARGETID;
	this->TIME = atoi(POSIXTIME);
	this->SOURCE = SOURCE;

	this->CENTERLONGITUDE = atof(LONGITUDE);
	this->UPPERLEFTLONGITUDE = atof(LONGITUDE);
	this->UPPERRIGHTLONGITUDE = atof(LONGITUDE);
	this->LOWERLEFTLONGITUDE = atof(LONGITUDE);
	this->LOWERRIGHTLONGITUDE = atof(LONGITUDE);

	this->CENTERALTITUDE = atof(ALTITUDE);
	this->UPPERLEFTALTITUDE = atof(ALTITUDE);
	this->UPPERRIGHTALTITUDE = atof(ALTITUDE);
	this->LOWERLEFTALTITUDE = atof(ALTITUDE);
	this->LOWERRIGHTALTITUDE = atof(ALTITUDE);

	this->CENTERLATITUDE = atof(LATITUDE);
	this->UPPERLEFTLATITUDE = atof(LATITUDE);
	this->UPPERRIGHTLATITUDE = atof(LATITUDE);
	this->LOWERLEFTLATITUDE = atof(LATITUDE);
	this->LOWERRIGHTLATITUDE = atof(LATITUDE);

	this->OPERATOR = OPERATOR;
	this->RESERVE1 = RESERVE1;
	this->RESERVE2 = RESERVE2;
}

HistoryTrackDetail::HistoryTrackDetail(string TRACKID,int ORDERNUMBER,string TARGETID,int TIME,string SOURCE,
	double CENTERLONGITUDE,double CENTERLATITUDE,double CENTERALTITUDE,/*double LOWERRIGHTLONGITUDE,double LOWERRIGHTLATITUDE ,
	double LOWERRIGHTALTITUDE,double CENTERLONGITUDE,double CENTERLATITUDE,double CENTERALTITUDE,*/double CONFIDENCELEVEL,
	string OPERATOR,string RESERVE1,string RESERVE2)
{
	this->TRACKID = TRACKID;
	this->ORDERNUMBER = ORDERNUMBER;
	this->TARGETID = TARGETID;
	this->TIME = TIME;
	this->SOURCE = SOURCE;
	this->CENTERALTITUDE = CENTERALTITUDE;
	this->CENTERLATITUDE = CENTERLATITUDE;
	this->CENTERLONGITUDE = CENTERLONGITUDE;

	this->UPPERLEFTALTITUDE = CENTERALTITUDE;
	this->UPPERLEFTLATITUDE = CENTERLATITUDE;
	this->UPPERLEFTLONGITUDE = CENTERLONGITUDE;

	this->LOWERRIGHTALTITUDE = CENTERALTITUDE;
	this->LOWERRIGHTLATITUDE = CENTERLATITUDE;
	this->LOWERRIGHTLONGITUDE = CENTERLONGITUDE;
	this->CONFIDENCELEVEL = 1;
	this->OPERATOR = OPERATOR;
	this->RESERVE1 = RESERVE1;
	this->RESERVE2 = RESERVE2;
}

HistoryTrackDetail::~HistoryTrackDetail()
{
}

string HistoryTrackDetail::insertSQL() {
	string insertSql = "insert into HISTORYTRACK_SUB values(ID,TRACKID,ORDERNUMBER,TARGETID,TIME,SOURCE,UPPERLEFTLONGITUDE,\
UPPERLEFTLATITUDE,UPPERLEFTALTITUDE,LOWERRIGHTLONGITUDE,LOWERRIGHTLATITUDE,LOWERRIGHTALTITUDE,CENTERLONGITUDE,CENTERLATITUDE,\
CENTERALTITUDE,CONFIDENCELEVEL,OPERATOR,RESERVE1,RESERVE2) values(";
	insertSql.append("UUID(),'").append(this->TRACKID).append("',").append(to_string(this->ORDERNUMBER)).append(",'")
		.append(this->TARGETID).append("','").append(to_string(this->TIME)).append("','").append(this->SOURCE).append("',")
		.append(to_string(this->UPPERLEFTLONGITUDE)).append(",").append(to_string(this->UPPERLEFTLATITUDE)).append(",").append(to_string(this->UPPERLEFTALTITUDE)).append(",")
		.append(to_string(this->LOWERRIGHTLONGITUDE)).append(",").append(to_string(this->LOWERRIGHTLATITUDE)).append(",").append(to_string(this->LOWERRIGHTALTITUDE)).append(",")
		.append(to_string(this->CENTERLONGITUDE)).append(",").append(to_string(this->CENTERLATITUDE)).append(",").append(to_string(this->CENTERALTITUDE)).append(",")
		.append("1,'").append(this->OPERATOR).append("','").append(this->RESERVE1).append("','").append(this->RESERVE2).append("');");
	return insertSql;
}

void  HistoryTrackDetail::setOderNumber(int orderNumber) {
	this->ORDERNUMBER = orderNumber;
}

bool HistoryTrackDetail::headOfTrack(int lastPosixTime) {
	return this->TIME - lastPosixTime > intervalThreshold;
}
/*int main() {
	HistoryTrackDetail hisD = HistoryTrackDetail("trackID", 101, "targetID", "2018-05-03 12:00:00", "sensor", 180, 0, 26, 1, "Gaara", "test", "test2");
	string res = hisD.insertSQL();
	const char* reschar = res.c_str();
	printf(reschar);
	system("pause");
	return 0;
}*/
