﻿#include "stdafx.h"
#include "Main.h"


Main::Main()
{
}


Main::~Main()
{
}
void targetsFreqTracks(vector<char*> targets, vector<Track> historyTracks,vector<vector<double>>edges,double prec);
DBSCAN analyzeTargetTracks(vector<Track>&targetTracks,vector<double>,double prec, vector<Segment> &segments);
							

int main() {
	//Processor Processor;
	Processor::sqlTool.connectDB();
	Processor::sqlTool.operationExcutor(Track::getTargetsQuery, Processor::res);
	vector<char*> targets;
	vector<Track> HistoryTracks;	
	double prec = 0.1;

	while (Processor::column = mysql_fetch_row(Processor::res)) {
		targets.push_back(Processor::column[0]);
	}

	vector<vector<double>> edges = Processor::targetsPreProcession(targets, HistoryTracks);//初始轨迹分段(根据时间阈值)，并得出4条边界

	targetsFreqTracks(targets,HistoryTracks,edges,prec);//根据轨迹片段，进行:网格化、特征点提取、生成线段距离矩阵、DBSCAN、聚类结果解析
	mysql_free_result(Processor::res);
	system("pause");
	return 0;
}

void targetsFreqTracks(vector<char*> targets, vector<Track> historyTracks,vector<vector<double>>edges,double prec)
{
	int targetNum = (int)targets.size();
	int trackNum = (int)historyTracks.size();
	int trackCounter = 0;
	//对每一个目标，选出其轨迹段。以目标为单位进行分析
	for (int counter = 0; counter < targetNum; counter++) {
		vector<Track> targetTracks ;
		vector<Segment>targetSegs;
		printf("target %s:", targets[counter]);
		for (; trackCounter < trackNum; trackCounter++) {
			if (strcmp(targets[counter], historyTracks[trackCounter].getTargetID()) == 0) 
				targetTracks.push_back(historyTracks[trackCounter]);			
			else	//轨迹所属目标变化，则跳出，分析当前目标的情况
				break;								
		}
		DBSCAN targetDBSCANNER =analyzeTargetTracks(targetTracks,edges[counter],prec, targetSegs);
		vector<int>* clusterInfo = targetDBSCANNER.clusterGenerate();

		for (int counter = 0; counter < targetDBSCANNER.clusterNum; counter++) {
			printf("cluster %d:", counter);
			for (vector<int>::iterator i = clusterInfo[counter].begin(); i != clusterInfo[counter].end(); i++) {
				printf("%d\t", *i);
			}
			printf("\n");
		}
		printf("---------------------------------------\n");
	}
}

DBSCAN analyzeTargetTracks(vector<Track>&targetTracks,vector<double> edge,double prec, vector<Segment> &segments) {

	Processor::tracksExtract(targetTracks, edge, prec);	//轨迹网格化处理
	Processor::tracksMDL(targetTracks);	//轨迹提取特征点

	Processor::tracks2Segment(targetTracks, segments);//根据特征点生成子段
	double **disMat = Processor::disMatrice(segments);	//根据子段信息生成距离矩阵
	printf("size:%d\n", segments.size());
	EpsiSolver epsiSolver = EpsiSolver((int)time(0), disMat,(int) segments.size());	//模拟退火求解聚类epsi
	epsiSolver.solve();
	double epsi = epsiSolver.getRes();
	printf("DBSCAN epsi:%10g\n", epsi);
	return DBSCAN(disMat, segments.size(), epsi, 2);	//使用DBSCAN进行子段聚类
/*	vector<int>* clusterInfo = dbscaner.clusterGenerate();

	for (int counter = 0; counter < dbscaner.clusterNum; counter++) {
		printf("cluster %d:", counter);
		for (vector<int>::iterator i = clusterInfo[counter].begin(); i != clusterInfo[counter].end(); i++) {
			printf("%d\t", *i);
		}
		printf("\n");
	}
*/
}
