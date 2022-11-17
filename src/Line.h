
//
//  Line.hpp
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef Line_h
#define Line_h

#include "ArduinoSTL-master/vector.h"

using std::vector;

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

class Line {
private:
	int x1;
	int y1;
	int x2;
	int y2;
	double slope = 0.0;

	bool isZero;
	bool isInfinite;
    
    void paintPixel(vector<vector<unsigned char>>& map, int x, int y, char c);
public:
	Line(int fx, int fy, int sx, int sy);
    
    bool moreVertical;

	bool onPoint(int point[2]);

	bool onSameSide(int point3[2], int point4[2]);

	void drawOn(vector<vector<unsigned char>>& map, int thickness);
};

#endif /* Line_hpp */
