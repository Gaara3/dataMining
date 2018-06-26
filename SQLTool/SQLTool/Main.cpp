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

	while (preProcessor.column = mysql_fetch_row(preProcessor.res)) {
		targets.push_back(preProcessor.column[0]);
	}

	double* edges = preProcessor.targetsPreProcession(targets, HistoryTracks);//初始轨迹分段(根据时间阈值)，并得出4条边界
	

	mysql_free_result(preProcessor.res);
	system("pause");
	return 0;
}
