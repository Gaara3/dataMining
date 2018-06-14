#pragma once
#include <string>
#include <vector>
#include "HistoryTrackDetail.h"

using std::string;
using std::vector;

class HistoryTrack
{
private:
	string TRACKID;
	int POINTAMOUNT;
	string TARGETID;
	string TARGETMODELNUMBER;
	string TARGETNAME;
	string TARGETTYPE;
	string GB;
	int STARTTIME;
	int ENDTIME;
	double CONFIDENCELEVEL;
	string SOURCE;
	string TASKINFO;
	string OPERATOR;
	string RESERVE1;
	string RESERVE2;
	vector<HistoryTrackDetail> historyTrackDetail;

	
public:
	HistoryTrack();
	HistoryTrack(char* TARGETID, char* SOURCE, char* TASKINFO, char* OPERATOR,char* STARTTIME);
	~HistoryTrack();
	static string getTargetsQuery;
	static string getTargetRecords(string targetID);
};

