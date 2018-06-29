#include "stdafx.h"
#include "Main.h"


Main::Main()
{
}


Main::~Main()
{
}

int main() {
	PreProcessor preProcessor;
	preProcessor.sqlTool.connectDB();
	preProcessor.sqlTool.operationExcutor(Track::getTargetsQuery, preProcessor.res);
	vector<char*> targets;
	vector<Track> HistoryTracks;	
	double prec = 0.1;

	while (preProcessor.column = mysql_fetch_row(preProcessor.res)) {
		targets.push_back(preProcessor.column[0]);
	}

	double* edges = preProcessor.targetsPreProcession(targets, HistoryTracks);//初始轨迹分段(根据时间阈值)，并得出4条边界
	printf("%lf   %lf   %lf   %lf\n", edges[0], edges[1], edges[2], edges[3]);
	preProcessor.tracksExtract(HistoryTracks,edges,prec);
	mysql_free_result(preProcessor.res);
	system("pause");
	return 0;
}
