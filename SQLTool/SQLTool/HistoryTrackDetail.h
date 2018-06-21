#pragma once
#include <string>
#include <time.h>

using std::string;

class HistoryTrackDetail
{
	private:
		int TRACKID;
		int ORDERNUMBER;
		char* TARGETID;
		int TIME;
		char* SOURCE;
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
		char* OPERATOR;
		char* RESERVE1;
		char* RESERVE2;

		static int intervalThreshold;
	public:
		char* insertSQL();
		HistoryTrackDetail();
		HistoryTrackDetail(char* TARGET,char* POSIXTIME,char* SOURCE,char* LONGITUDE,char* LATITUDE,char* ALTITUDE, char* OPERATOR,char* RESERVE1,char* RESERVE2);
		
		//jUST FOR TEST
		//HistoryTrackDetail(string TRACKID, int ORDERNUMBER, string TARGETID, int TIME, string SOURCE,
		//	double CENTERLONGITUDE, double CENTERLATITUDE, double CENTERALTITUDE,/*double LOWERRIGHTLONGITUDE, double LOWERRIGHTLATITUDE,
		//	double LOWERRIGHTALTITUDE, double CENTERLONGITUDE, double CENTERLATITUDE, double CENTERALTITUDE,*/double CONFIDENCELEVEL,
		//	string OPERATOR, string RESERVE1, string RESERVE2);

		void setOderNumber(int);
		void setTrackID(int trackID);
		bool headOfTrack(int lastPosixTime);
		static char* datetimeConvertor(int input);
		~HistoryTrackDetail();
		int getTime();
		char* getTargetID();
		char* getSource();
		char* getOperator();
};

