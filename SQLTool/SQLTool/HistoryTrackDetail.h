#pragma once
#include <string>

using std::string;

class HistoryTrackDetail
{
	private:
		string TRACKID;
		int ORDERNUMBER;
		string TARGETID;
		int TIME;
		string SOURCE;
		double UPPERLEFTLONGITUDE;
		double UPPERLEFTLATITUDE;
		double UPPERLEFTALTITUDE;
		double UPPERRIGHTLONGITUDE;
		double UPPERRIGHTLATITUDE;
		double UPPERRIGHTALTITUDE;
		double LOWERLEFTLONGITUDE;
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

		static int intervalThreshold;
	public:
		string insertSQL();
		HistoryTrackDetail();
		HistoryTrackDetail(const char* TARGET, const char* POSIXTIME, const char* SOURCE, const char* LONGITUDE, const char* LATITUDE, const char* ALTITUDE, const char* OPERATOR, const char* RESERVE1, const char* RESERVE2);
		
		//jUST FOR TEST
		HistoryTrackDetail(string TRACKID, int ORDERNUMBER, string TARGETID, int TIME, string SOURCE,
			double CENTERLONGITUDE, double CENTERLATITUDE, double CENTERALTITUDE,/*double LOWERRIGHTLONGITUDE, double LOWERRIGHTLATITUDE,
			double LOWERRIGHTALTITUDE, double CENTERLONGITUDE, double CENTERLATITUDE, double CENTERALTITUDE,*/double CONFIDENCELEVEL,
			string OPERATOR, string RESERVE1, string RESERVE2);

		void setOderNumber(int);
		void setTrackID(string trackID);
		bool headOfTrack(int lastPosixTime);
		~HistoryTrackDetail();

};

