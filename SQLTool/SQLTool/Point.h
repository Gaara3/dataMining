#pragma once
#include <math.h>
typedef struct myPoint {
	double x;
	double y;

	void rotateAnticlockwise(double angle) {
		double cosA = cos(angle), sinA = sin(angle);
		x = cosA *x - sinA *y;
		y = sinA *x + cosA*y;
	}
}Point;