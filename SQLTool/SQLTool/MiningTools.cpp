#include "stdafx.h"
#include "MiningTools.h"



MiningTools::MiningTools()
{
}


MiningTools::~MiningTools()
{
}

double MiningTools::distanceBetweenLines(Segment sg1, Segment sg2,double* weights) {
	return weights[0]*verticalDistBetweenLines(sg1, sg2) + weights[1]*horizontalDistBetweenLines(sg1, sg2) + weights[2]*angleDistBetweenLines(sg1, sg2);
}

double MiningTools::verticalDistBetweenLines(Segment sg1, Segment sg2)
{
	Point pro1 = projectionOfPoint(sg1, sg2.start);
	Point pro2 = projectionOfPoint(sg1, sg2.end);
	Vector2D s2pA = Vector2D(sg2.start, pro1);
	Vector2D s2pB = Vector2D(sg2.end, pro2);
	double disA = vectorMag(s2pA);
	double disB = vectorMag(s2pB);
	return (disA*disA + disB * disB) / (disA + disB);
}

double MiningTools::horizontalDistBetweenLines(Segment sg1, Segment sg2)
{
	Point pro1 = projectionOfPoint(sg1, sg2.start);
	Point pro2 = projectionOfPoint(sg1, sg2.end);
	Vector2D p12s = Vector2D(pro1, sg1.start);
	Vector2D p12e = Vector2D(pro1, sg1.end);
	Vector2D p22s = Vector2D(pro2, sg1.start);
	Vector2D p22e = Vector2D(pro2, sg1.end);
	double minP1 = vectorMag(p12e) < vectorMag(p12s) ? vectorMag(p12e) : vectorMag(p12s);
	double minP2 = vectorMag(p22e) < vectorMag(p22s) ? vectorMag(p22e) : vectorMag(p22s);
	return minP1<minP2?minP1:minP2;
}

double MiningTools::angleDistBetweenLines(Segment sg1, Segment sg2)//原程序使用acos，本实现中使用L*sin
{
	Vector2D v1 = Vector2D(sg1.start, sg1.end);
	Vector2D v2 = Vector2D(sg2.start, sg2.end);
	double cosTheta = (v1*v2) / (vectorMag(v1)*vectorMag(v2));
	double sinTheta = sqrt(1 - cosTheta * cosTheta);
	return vectorMag(v1)*sinTheta;
}

Point MiningTools::projectionOfPoint(Segment sg, Point p)
{
	Vector2D s = Vector2D(sg.start.x, sg.start.y);
	Vector2D sp = Vector2D(p.x - sg.start.x, p.y - sg.start.x);//start to p
	Vector2D se = Vector2D(sg.end.x - sg.start.x, sg.end.y - sg.start.y); //start to end
	double alph = (sp*se) / (vectorMag(se) *vectorMag(se));
	Vector2D pro = s + (se * alph);
	return Point{ pro.x, pro.y };
}
