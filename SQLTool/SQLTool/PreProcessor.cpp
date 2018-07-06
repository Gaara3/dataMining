#include "stdafx.h"
#include "Processor.h"
#include "SqlTool.h"


Processor::Processor()
{
}


Processor::~Processor()
{
}
/*
	对入参列表的所有target进行预处理
*/
double* Processor::targetsPreProcession(vector<char*> targets, vector<Track> &HistoryTracks) {
	int targetsNum = targets.size();
	bool newTarget = true;
	int trackID = 0;
	double* edges = getEdges();//直接利用mysql找出经纬极值
	printf("%lf  %lf   %lf  %lf\n", edges[0], edges[1], edges[2], edges[3]);
	for (int counter = 0; counter < targetsNum; counter++) {
		//printf("********************************new Target********************************\n");
		oneTargetPreProcession(targets[counter], HistoryTracks, newTarget,trackID);
		newTarget = true;
	}
	return edges;
}

/*
	对特定目标进行预处理
*/
void Processor::oneTargetPreProcession(char* target, vector<Track>&HistoryTracks,bool &newTarget,int &trackID) {

	Track tmp;
	int lastPosixtime = 0;
	int orderNumber = 0;
	double totalLength = 0;
	double lastLongitude = 181, lastLatitude = 91;
	//Grid grid = { true,-1,-1,0,0 };  //newGrid,gridX,gridY,startIndex,endIndex
	sqlTool.operationExcutor(Track::getTargetRecords(target), res);
	mysql_autocommit(&sqlTool.mysql, 0);
	MYSQL_RES *targetRecord = res;
	vector<TrackPoint> details;
	//int *featurePoint = new int[];//特征点指针
	//vector<int>featurePoint;
	while (column = mysql_fetch_row(targetRecord)) {		
		pointPreprocession(details,column, HistoryTracks,trackID, lastPosixtime,orderNumber, newTarget,totalLength,lastLongitude,lastLatitude);
		newTarget = false;//TODO   改进
	}
	//单目标最后一段轨迹需要专门处理一次
	HistoryTracks.back().trackEndProcession(lastPosixtime, orderNumber, details,totalLength);
	sqlTool.insertExcutor(HistoryTracks.back().insertSQL().data());
	mysql_commit(&sqlTool.mysql);
}


void Processor::pointPreprocession(vector<TrackPoint>&details,MYSQL_ROW column, vector<Track>&HistoryTracks,int &trackID, int &lastPosixTime,int &orderNumber,bool &newTarget,double &totalLength,double &lastLongitude,double& lastLatitude) {
	
	double longitude = atof(column[3]), latitude = atof(column[4]), altitude = atof(column[5]);
	TrackPoint point = TrackPoint(column[0], column[1], column[2], longitude, latitude, altitude, column[6], column[7], column[8]);
	
	if (point.headOfTrack(lastPosixTime)) {//该点是一段新轨迹
		//printf("===============================new track============================\n");
		trackID++;
		if (!newTarget) {//newTarget 已涵盖队列为空的情况，不再另行判断
			Track *lastTrack = &HistoryTracks.back();
			lastTrack->trackEndProcession(lastPosixTime, orderNumber, details,totalLength);
			sqlTool.insertExcutor(lastTrack->insertSQL().data());	//为了不传类别无关变量res，暂不加入封装
			mysql_commit(&sqlTool.mysql);
			//引用值重置，考虑封装
			lastPosixTime = 0;			
			orderNumber = 0;			
			totalLength = 0; lastLatitude = 91; lastLongitude = 181;	//新轨迹开始，设置异常值以便于判断
			details.clear();	
		}
		HistoryTracks.push_back(Track(trackID,point.getTargetID(), point.getSource(),column[9], point.getOperator(), point.getTime()));	//轨迹数组加入新track
		//details.clear();
	}
	
	//该点本身所需的操作:确定trackID,确定orderNumber，更新lastPosixTime，插入数据库
	point.setTrackID(trackID);
	lastPosixTime = point.getTime();
	point.setOderNumber(++orderNumber);
	details.push_back(point);

	totalLength += distanceBetweenPoints(lastLongitude, lastLatitude,longitude,latitude);//计算两地点距离，并更新last坐标
	
	sqlTool.insertExcutor(point.insertSQL().data());	
	//printf("                              new point%d                              \n", orderNumber);
}

double Processor::distanceBetweenPoints(double &lastLongitude, double &lastLatitude, double longitude, double latitude) {
	double res = 0;
	if (lastLatitude <= 90 && lastLongitude <= 180) {	//当一段轨迹完结，设置异常值以便于新一段计算
		double p = 0.017453292519943295;    // Math.PI / 180
		double a = 0.5 - cos((latitude - lastLatitude) * p) / 2 +cos(latitude * p) * cos(lastLatitude * p) *(0.5 - cos((longitude - lastLongitude) * p)/2);

		res= 12742 * asin(sqrt(a)); // 2 * R; R = 6371 km
	}
	lastLatitude = latitude;
	lastLongitude = longitude;
	return res;
}


double* Processor::getEdges() {
	double edges[4];
	edges[0] = atof(sqlTool.getVariableFromDB("SELECT max(LONGITUDE)from m_preprocessing;"));
	edges[1] = atof(sqlTool.getVariableFromDB("SELECT min(LONGITUDE)from m_preprocessing;"));
	edges[2] = atof(sqlTool.getVariableFromDB("SELECT max(LATITUDE)from m_preprocessing;"));
	edges[3] = atof(sqlTool.getVariableFromDB("SELECT min(LATITUDE)from m_preprocessing;"));
	return edges;
}




void Processor::tracksExtract(vector<Track> &tracks,double* edges,double prec){
	int trackNum = tracks.size();
	for (int counter = 0; counter < trackNum; counter++) {
		tracks[counter].extractNnPoint(edges,prec);
	}
}

void Processor::tracksMDL(vector<Track> &tracks) {
	int trackNum = tracks.size();
	for (int counter = 0; counter < trackNum; counter++) {
		tracks[counter].MDLExtract();
	}
}

