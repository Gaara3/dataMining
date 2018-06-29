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
	return 0.0;
}

double MiningTools::horizontalDistBetweenLines(Segment sg1, Segment sg2)
{
	return 0.0;
}

double MiningTools::angleDistBetweenLines(Segment sg1, Segment sg2)
{
	return 0.0;
}

Point MiningTools::projectionOfPoint(Segment sg, Point p)
{
	Vector2D s = Vector2D(sg.start.x, sg.start.y);
	Vector2D sp = Vector2D(p.x - sg.start.x, p.y - sg.start.x);//start to p
	Vector2D se = Vector2D(sg.end.x - sg.start.x, sg.end.y - sg.start.y); //start to end
	double alph = (sp*se) / (vectorMag(se) *vectorMag(se));
	
}
