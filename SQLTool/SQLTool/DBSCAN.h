﻿#pragma once
#include <iostream>
#include <cmath>
#include "DataPoint.h"

using namespace std;

//聚类分析类型
class DBSCAN
{
private:
	vector<DataPoint> dataSets;        //数据集合
	//unsigned int dimNum;            //维度	直接传入距离矩阵，不再需要考虑数据维度   by lsx
	double radius;                    //半径
	unsigned int dataNum;            //数据数量
	unsigned int minPTs;            //邻域最小数据个数
	double **distMat;				//距离矩阵

	//double GetDistance(DataPoint& dp1, DataPoint& dp2);                    //距离函数
	void SetArrivalPoints(DataPoint& dp,int idx);                                //设置数据点的领域点列表
	void KeyPointCluster(unsigned long i, unsigned long clusterId);    //对数据点领域内的点执行聚类操作
public:

	DBSCAN() {}                    //默认构造函数
	bool Init(double** distMat,int size, double radius, int minPTs);    //初始化操作
	bool DoDBSCANRecursive();            //DBSCAN递归算法
};