#pragma once

#include "Track.h"
#include "TrackPoint.h"
#include <mysql.h>
#include <vector>
#include <math.h>
#include "SqlTool.h"

using std::vector;
class PreProcessor
{
	
public:
	SqlTool sqlTool;
	MYSQL_RES *res;
	MYSQL_ROW column;
	PreProcessor();
	~PreProcessor();
	double* targetsPreProcession(vector<char*> targets,vector<Track> &HistoryTracks);
	void oneTargetPreProcession(char* target, vector<Track> &HistoryTracks,bool &sameTrack,int &trackID,double edges[4]);
	void pointPreprocession(vector<TrackPoint> &details, MYSQL_ROW column, vector<Track>&HistoryTracks,/*HistoryTrack *&curTrack,*/int &trackID,int &lastPosixTime,int &orderNumber,bool &newTrack,double &totalLength,double &lastLongitude,double &lastLatitude,double edges[4]);
	double distanceBetweenPoints(double& lastLongitude, double& lastLatitude, double longitude, double latitude);
	void updateEdges(double longitude, double latitude, double edges[4]);
};

