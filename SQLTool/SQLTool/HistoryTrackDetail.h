#pragma once
#include <string>

using std::string;

class HistoryTrackDetail
{
	private:
		string TRACKID;
		int ORDERNUMBER;
		string TARGETID;
		string TIME;
		string SOURCE;
		double UPPERLEFTLONGITUDE;
		double UPPERLEFTLATITUDE;
		double UPPERLEFTALTITUDE;
		double UPPERRIGHTLONGITUDE;
		double UPPERRIGHTLATITUDE;
		double UPPERRIGHTALTITUDE;
		double LOWERERLEFTLONGITUDE;
		double LOWERLEFTLATITUDE;
		double LOWERLEFTALTITUDE;
		double LOWERRIGHTLONGITUDE;
		double LOWERRIGHTLATITUDE;
		double LOWERRIGHTALTITUDE;
		double CENTERLONGITUDE;
		double CENTERLATITUDE;
		double CENTERALTITUDE;
		double CONFIDENCELEVEL;
		string OPERATOR;
		string RESERVE1;
		string RESERVE2;

	public:
		string insertSQL();
		HistoryTrackDetail();
		HistoryTrackDetail(string TRACKID, int ORDERNUMBER, string TARGETID, string TIME, string SOURCE,
			double CENTERLONGITUDE, double CENTERLATITUDE, double CENTERALTITUDE,/*double LOWERRIGHTLONGITUDE, double LOWERRIGHTLATITUDE,
			double LOWERRIGHTALTITUDE, double CENTERLONGITUDE, double CENTERLATITUDE, double CENTERALTITUDE,*/double CONFIDENCELEVEL,
			string OPERATOR, string RESERVE1, string RESERVE2);
		~HistoryTrackDetail();

};

