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
	static SqlTool sqlTool;
	static MYSQL_RES *res;
	static MYSQL_ROW column;
	Processor();
	~Processor();
	static vector<vector<double>> targetsPreProcession(vector<char*> targets,vector<Track> &HistoryTracks);
	static vector<double> getTargetEdges(char* targetID);
	static void oneTargetPreProcession(char* target, vector<Track> &HistoryTracks,bool &sameTrack,int &trackID);
	static void pointPreprocession(vector<TrackPoint> &details, MYSQL_ROW column, vector<Track>&HistoryTracks,/*HistoryTrack *&curTrack,*/int &trackID,int &lastPosixTime,int &orderNumber,bool &newTrack,double &totalLength,double &lastLongitude,double &lastLatitude);
	static double distanceBetweenPoints(double& lastLongitude, double& lastLatitude, double longitude, double latitude);
	//static double* getEdges();
	static void tracksExtract(vector<Track>&tracks,vector<double> edges,double prec);
	static void tracksMDL(vector<Track> &tracks);
	static vector<Segment>tracks2Segment(vector<Track>&tracks,vector<Segment> &result);
	static double** disMatrice(vector<Segment>);
	static void processByTarget(vector <Track>);
	static void clusterAnalyze(vector<Segment> segs, vector<int>* clusterInfo,int clusterNum);
};

