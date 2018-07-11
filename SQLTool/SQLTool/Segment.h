#pragma once
#include "Point.h"
struct Segment
{
	Point start;
	Point end;
	int trackPointLocator[4];

	/*Segment(Point a, Point b) {
		start = a; end = b;
		trackPointLocator = { 0,0,0,0 };
	}
	Segment(Point a, Point b, pair<int,int> startL, pair<int,int>endL) {
		start = a; end = b;
		startLocator = startL;
		endLocator = endL;
	}*/
}; 

