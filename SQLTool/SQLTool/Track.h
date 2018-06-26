#pragma once

#include <vector>
#include<string>
#include "TrackPoint.h"

using std::vector;
using std::string;

class Track
{
private:
	int TRACKID;
	int POINTAMOUNT;
	char* TARGETID;
	char* TARGETMODELNUMBER;
	char* TARGETNAME;
	char* TARGETTYPE;
	int STARTTIME;
	int ENDTIME;
	double CONFIDENCELEVEL;
	char* SOURCE;
	char* TASKINFO;
	char* OPERATOR;
	char* RESERVE1;
	char* RESERVE2;
	double length;
	
	static char* datetimeConvertor(int input);
	
public:
	vector<TrackPoint> historyPoint;
	vector<TrackPoint> featurePoint;	

	Track();
	Track(int trackID, char* TARGETID, char* SOURCE, char* TASKINFO, char* OPERATOR,int STARTTIME);
	Track(int trackID, char* TARGETID, char* SOURCE, char* TASKINFO, char* OPERATOR,char* STARTTIME);

	~Track();
	const static char* getTargetsQuery;
	static char* getTargetRecords(char* targetID);

	void setPointAmount(int pointAmount);
	void setEndTime(int endTime);
	void setTrackID(int trackID);
	void setLength(double length);
	string insertSQL();
	void trackEndProcession(int endTime,int pointAmount,vector<TrackPoint>details,double totalLength);
};

