#pragma once

#include <vector>
#include "HistoryTrackDetail.h"

using std::vector;

class HistoryTrack
{
private:
	char* TRACKID;
	int POINTAMOUNT;
	char* TARGETID;
	char* TARGETMODELNUMBER;
	char* TARGETNAME;
	char* TARGETTYPE;
	char* GB;
	int STARTTIME;
	int ENDTIME;
	double CONFIDENCELEVEL;
	char* SOURCE;
	char* TASKINFO;
	char* OPERATOR;
	char* RESERVE1;
	char* RESERVE2;
	
	static char* datetimeConvertor(int input);
	
public:
	vector<HistoryTrackDetail> historyTrackDetail;

	HistoryTrack();
	HistoryTrack(char* TARGETID, char* SOURCE, char* TASKINFO, char* OPERATOR,char* STARTTIME);

	~HistoryTrack();
	const static char* getTargetsQuery;
	static char* getTargetRecords(char* targetID);

	void setPointAmount(int pointAmount);
	void setEndTime(int endTime);
	void setTrackID(char* trackID);
	char* insertSQL();
};

