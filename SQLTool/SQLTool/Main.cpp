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
	preProcessor.sqlTool.operationExcutor(HistoryTrack::getTargetsQuery, preProcessor.res);
	vector<char*> targets;
	vector<HistoryTrack> HistoryTracks;

	while (preProcessor.column = mysql_fetch_row(preProcessor.res)) {
		targets.push_back(preProcessor.column[0]);
	}

	preProcessor.targetsPreProcession(targets, HistoryTracks);
	mysql_free_result(preProcessor.res);
	return 0;
}
