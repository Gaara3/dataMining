#include "stdafx.h"
#include "Main.h"


Main::Main()
{
}


Main::~Main()
{
}
void targetsCluster(vector<char*> targets, vector<Track> historyTracks);
void analyzeTargetTracks(vector<Track>targetTracks);

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

	double* edges = Processor::targetsPreProcession(targets, HistoryTracks);//初始轨迹分段(根据时间阈值)，并得出4条边界
	printf("%lf   %lf   %lf   %lf\n", edges[0], edges[1], edges[2], edges[3]);
	Processor::tracksExtract(HistoryTracks,edges,prec);
	Processor::tracksMDL(HistoryTracks);//轨迹提取特征点完成

	targetsCluster(targets,HistoryTracks);//分目标进行聚类

	/*vector<Segment> segments =Processor::tracks2Segment(HistoryTracks);
	double **disMat=Processor::disMatrice(segments);	//生成距离矩阵

	EpsiSolver epsiSolver = EpsiSolver(time(0),disMat, segments.size());
	epsiSolver.solve();
	double epsi = epsiSolver.getRes();
	int s = segments.size();
	DBSCAN dbscaner;
	dbscaner.Init(disMat, s, epsi, 2);
	vector<int>* clusterInfo = dbscaner.clusterGenerate();*/
	/*for (int counter1 = 0; counter1 < s; counter1++) {
		for (int counter2 = 0; counter2 < s; counter2++)
			printf("%lf\t", disMat[counter1][counter2]);
		printf("\n");
	}*/
	mysql_free_result(Processor::res);
	system("pause");
	return 0;
}

void targetsCluster(vector<char*> targets, vector<Track> historyTracks)
{
	int targetNum = targets.size();
	int trackNum = historyTracks.size();
	//vector<Track> *targetTracks = new vector<Track>[targetNum];
	int trackCounter = 0;
	//
	for (int counter = 0; counter < targetNum; counter++) {
		vector<Track> targetTracks ;
		printf("target %s:", targets[counter]);
		for (; trackCounter < trackNum; trackCounter++) {
			if (strcmp(targets[counter], historyTracks[trackCounter].getTargetID()) == 0) {
				targetTracks.push_back(historyTracks[trackCounter]);
			}
			else {
				break;
			}				
		}
		analyzeTargetTracks(targetTracks);
		printf("---------------------------------------\n");
	}
}

void analyzeTargetTracks(vector<Track>targetTracks) {
	vector<Segment> segments = Processor::tracks2Segment(targetTracks);
	double **disMat = Processor::disMatrice(segments);	//生成距离矩阵
	int s = segments.size();
	printf("size:%d\n", s);
	for (int counter1 = 0; counter1 < s; counter1++) {
		for (int counter2 = 0; counter2 < s; counter2++)
			printf("%lf\t", disMat[counter1][counter2]);
		printf("\n");
	}
	EpsiSolver epsiSolver = EpsiSolver(time(0), disMat, segments.size());
	epsiSolver.solve();
	double epsi = epsiSolver.getRes();
	DBSCAN dbscaner;
	dbscaner.Init(disMat, s, epsi, 2);
	vector<int>* clusterInfo = dbscaner.clusterGenerate();
}
