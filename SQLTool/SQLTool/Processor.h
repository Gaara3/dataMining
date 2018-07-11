#pragma once

#include "Track.h"
#include "TrackPoint.h"
#include <mysql.h>
#include <vector>
#include <math.h>
#include "SqlTool.h"
#include "Grid.h"
#include "Segment.h"


using std::vector;
class Processor
{
	double prec = 0.1;
public:
	SqlTool sqlTool;
	MYSQL_RES *res;
	MYSQL_ROW column;
	Processor();
	~Processor();
	double* targetsPreProcession(vector<char*> targets,vector<Track> &HistoryTracks);
	void oneTargetPreProcession(char* target, vector<Track> &HistoryTracks,bool &sameTrack,int &trackID);
	void pointPreprocession(vector<TrackPoint> &details, MYSQL_ROW column, vector<Track>&HistoryTracks,/*HistoryTrack *&curTrack,*/int &trackID,int &lastPosixTime,int &orderNumber,bool &newTrack,double &totalLength,double &lastLongitude,double &lastLatitude);
	double distanceBetweenPoints(double& lastLongitude, double& lastLatitude, double longitude, double latitude);
	double* getEdges();
	void tracksExtract(vector<Track>&tracks,double* edges,double prec);
	void tracksMDL(vector<Track> &tracks);
	vector<Segment>tracks2Segment(vector<Track>&tracks);
	double** disMatrice(vector<Segment>);
	void processByTarget(vector <Track>);
	void clusterAnalyze(vector<int>* clusterInfo, vector<Segment> segments);
};

