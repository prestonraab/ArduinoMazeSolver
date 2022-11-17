//
//  Line.cpp
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//

#include "Line.h"

Line::Line(int fx, int fy, int sx, int sy) : x1(fx), y1(fy), x2(sx), y2(sy), slope(0), isZero(y1 == y2), isInfinite(x1 == x2) {
    
	if (!isZero && !isInfinite) {
		slope = (1.0 * y2 - 1.0 * y1) / (double)(1.0 * x2 - 1.0 * x1);
        if(slope > 1 || slope < -1)
            moreVertical = true;
        else
            moreVertical = false;
	}
}

bool Line::onPoint(int point[2])
{
	int& x = point[0];
	int& y = point[1];
	if (isZero) {
		return y == y1;
	}
	if (isInfinite) {
		return x == x1;
	}
	return (y1 - y2) * (x1 - x) == (y1 - y) * (x1 - x2);
}

bool Line::onSameSide(int point3[2], int point4[2])
{
	int& x3 = point3[0];
	int& y3 = point3[1];
	int& x4 = point4[0];
	int& y4 = point4[1];
	if (isZero) {
		return (y3 > y1) == (y4 > y1);
	}
	if (isInfinite) {
		return (x3 > x1) == (x4 > x1);
	}
  float deltaX1 = static_cast<float>(x3) - static_cast<float>(x1);
  float deltaX2 = static_cast<float>(x4) - static_cast<float>(x1);
	return	(slope * deltaX1 > y3 - y1) ==
		(slope * deltaX2 > y4 - y1);
}
