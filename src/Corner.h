//
//  Corner.h
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef Corner_h
#define Corner_h

#include "ArduinoSTL-master/vector.h"

struct Corner {
	enum relation {same = 0, adj = 1, opp = 2};

	enum direction {TL = 0, TR = 1, BR = 2, BL = 3, ALL = 4};
    
	
	static unsigned char getRelation(const direction a, const direction b) {
		if (a == b)
			return same;

		if (a - b == 2 || b - a == 2)
			return opp;
		else
			return adj;
	}
    
	Corner(int y=0, int x=0, direction dir=ALL): i(y), j(x), d(dir) {
	}
    
    bool isPossibleConnection(unsigned char ci, unsigned char cj, direction cd) {
        if (cd == Corner::ALL || d == Corner::ALL){
            return !(i == ci && j == cj);
        }
        
        switch (Corner::getRelation(d, cd))
        {
        case Corner::adj: //Looks right
            switch (d)
            {
            case Corner::TL:
                if (i == ci && cd == Corner::TR && j < cj)
                    return true;
                else 
                  return (j == cj && cd == Corner::BL && i < ci);
            case Corner::TR:
                if (i == ci && cd == Corner::TL && j > cj)
                    return true;
                else 
                  return (j == cj && cd == Corner::BR && i < ci);
            case Corner::BL:
                if (i == ci && cd == Corner::BR && j < cj)
                    return true;
                else 
                  return (j == cj && cd == Corner::TL && i > ci);
            case Corner::BR:
                if (i == ci && cd == Corner::BL && j > cj)
                    return true;
                else 
                  return (j == cj && cd == Corner::TR && i > ci);
            default:
                return false;
            }
        case Corner::same:  //Falls through, because the next check is the same.
            if(i == ci || j == cj){
                return false;
            }
        default:
            switch (d) //if opposite, search the adjacent directions for the block, kind of
            {
                case Corner::TL:
                    return (Corner::searchDirection(i, j, Corner::TR, ci, cj) || Corner::searchDirection(i, j, Corner::BL, ci, cj));
                case Corner::TR:
                    return (Corner::searchDirection(i, j, Corner::BR, ci, cj) || Corner::searchDirection(i, j, Corner::TL, ci, cj));
                case Corner::BL:
                    return (Corner::searchDirection(i, j, Corner::TL, ci, cj) || Corner::searchDirection(i, j, Corner::BR, ci, cj));
                case Corner::BR:
                    return (Corner::searchDirection(i, j, Corner::BL, ci, cj) || Corner::searchDirection(i, j, Corner::TR, ci, cj));
                default:
                    return false;
            }
        }
    }
	
	static bool searchDirection(int i, int j, direction d, int ci, int cj) {
		int iMult, jMult;
		if (d == ALL)
			return true;
        if (i == ci && j == cj)
         return false;

		iMult = (d == BL || d == BR) ? 1 : -1;
		jMult = (d == TR || d == BR) ? 1 : -1;

		bool found = (ci - i) * iMult >= 0 && (cj - j) * jMult >= 0;
		return found;
	}
	
	int i;
	int j;
	direction d;
};

#endif /* Corner_h */
