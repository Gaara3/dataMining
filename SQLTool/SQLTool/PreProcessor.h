#pragma once

#include "HistoryTrack.h"
#include <mysql.h>
#include <vector>
#include "SqlTool.h"
class PreProcessor
{
	
public:
	SqlTool sqlTool;
	MYSQL_RES *res;
	MYSQL_ROW column;
	PreProcessor();
	~PreProcessor();
	void targetsPreProcession(vector<char*> targets,vector<HistoryTrack> &HistoryTracks);
	void oneTargetPreProcession(char* target, vector<HistoryTrack> &HistoryTracks,bool &sameTrack);
	void pointPreprocession(vector<HistoryTrackDetail> &details, MYSQL_ROW column, vector<HistoryTrack>&HistoryTracks,/*HistoryTrack *&curTrack,*/int &trackID,int &lastPosixTime,int &orderNumber,bool &sameTrack);
};

