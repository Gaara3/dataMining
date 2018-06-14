#include "stdafx.h"
#include "DataMiner.h"


DataMiner::DataMiner()
{
	mysql_init(&this->mysql);
}


DataMiner::~DataMiner()
{
	mysql_free_result(res);
	mysql_close(&mysql);
}

bool DataMiner::connectDatabase(const char* database) {	//还需评估init置于构造还是连接时
	if (!mysql_real_connect(&mysql, "localhost", "root", "root", database, 3306, NULL, 0)) {
		printf("Something wrong when connecting to database:%s", mysql_error(&this->mysql));
		return false;
	}		
	return true;
}

bool DataMiner::operateDatabase(const char* operation) {

}
