#pragma once
#include <math.h>
typedef struct myPoint {
	double x;
	double y;

	void rotateAnticlockwise(double angle) {
		x = cos(angle)*x - sin(angle)*y;
		y = sin(angle)*y + cos(angle)*y;
	}
}Point;