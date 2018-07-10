#include "stdafx.h"
#include "Main.h"


Main::Main()
{
}


Main::~Main()
{
}

int main() {
	Processor Processor;
	Processor.sqlTool.connectDB();
	Processor.sqlTool.operationExcutor(Track::getTargetsQuery, Processor.res);
	vector<char*> targets;
	vector<Track> HistoryTracks;	
	double prec = 0.1;

	while (Processor.column = mysql_fetch_row(Processor.res)) {
		targets.push_back(Processor.column[0]);
	}

	double* edges = Processor.targetsPreProcession(targets, HistoryTracks);//初始轨迹分段(根据时间阈值)，并得出4条边界
	printf("%lf   %lf   %lf   %lf\n", edges[0], edges[1], edges[2], edges[3]);
	Processor.tracksExtract(HistoryTracks,edges,prec);
	Processor.tracksMDL(HistoryTracks);
	vector<Segment> segments =Processor.tracks2Segment(HistoryTracks);
	double **disMat=Processor.disMatrice(segments);	//生成距离矩阵
	mysql_free_result(Processor.res);
	system("pause");
	return 0;
}
