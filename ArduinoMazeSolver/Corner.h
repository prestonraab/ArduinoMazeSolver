//
//  Corner.h
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef Corner_h
#define Corner_h

#include <vector>
#include <iostream>

using std::vector;

using std::vector;
using std::cout;
using std::endl;

static double searchRange = 200;

struct Corner {
	enum relation {same = 0, adj = 1, opp = 2};
    inline const static char* relationNames[] {"same", "adj", "opp"};

	enum direction {TL = 0, TR = 1, BR = 2, BL = 3, ALL = 4};
    inline const static char* directionNames[] {"topLeft", "topRight", "BottomRight", "BottomLeft", "All" };
    
    enum quadrant {origin=-1, right=0, up=1, left=2, down=3, one=4, two=5, three=6, four=7};
    
	
	static relation getRelation(const direction a, const direction b) {
		if (a == b)
			return same;

		if (a - b == 2 || b - a == 2)
			return opp;
		else
			return adj;
	}
    
    static quadrant getQuadrant(Corner originCorner, Corner otherCorner){
        int deltai = otherCorner.i - originCorner.i;
        int deltaj = otherCorner.j - originCorner.j;
        
        if(deltai == 0){
            if(deltaj == 0)
                return origin;
            else if(deltaj > 0)
                return down;
            else
                return up;
        }
        else if(deltai > 0){
            if(deltaj == 0)
                return right;
            else if(deltaj > 0)
                return four;
            else
                return one;
        }
        else{
            if(deltaj == 0)
                return left;
            else if(deltaj > 0)
                return three;
            else
                return two;
        }
    }
    
    
	Corner(int y, int x, direction dir): i(y), j(x), d(dir) {
	}
	
    static void setSearchRange(double range) {
        searchRange = range;
    }
    
    bool isPossibleConnection(Corner const &c) {
//        cout << "(" << i << "," << j << ") c: (" << c.i << "," << c.j << ")";
//        cout << " d: " << Corner::directionNames[d];
//        cout << " c.d: " << Corner::directionNames[c.d];
//        cout << " Relation: " << Corner::relationNames[Corner::getRelation(d, c.d)] << " " << endl;
        if (c.d == Corner::ALL || d == Corner::ALL){
            if(i != c.i || j != c.j){
                return true;
            }
            else
                return false;
        }
        
        switch (Corner::getRelation(d, c.d))
        {
        case Corner::adj: //Looks right
            switch (d)
            {
            case Corner::TL:
                if (i == c.i && c.d == Corner::TR && j < c.j)
                    return true;
                else if (j == c.j && c.d == Corner::BL && i < c.i)
                    return true;
                else
                    return false;
            case Corner::TR:
                if (i == c.i && c.d == Corner::TL && j > c.j)
                    return true;
                else if (j == c.j && c.d == Corner::BR && i < c.i)
                    return true;
                else
                    return false;
            case Corner::BL:
                if (i == c.i && c.d == Corner::BR && j < c.j)
                    return true;
                else if (j == c.j && c.d == Corner::TL && i > c.i)
                    return true;
                else
                    return false;
            case Corner::BR:
                if (i == c.i && c.d == Corner::BL && j > c.j)
                    return true;
                else if (j == c.j && c.d == Corner::TR && i > c.i)
                    return true;
                else
                    return false;
            default:
                return false;
            }
        case Corner::same:  //Falls through, because the next check is the same.
            if(i == c.i || j == c.j){
                return false;
            }
        default:
            switch (d) //if opposite, search the adjacent directions for the block, kind of
            {
                case Corner::TL:
                    if (Corner::searchDirection(i, j, Corner::TR, c) || Corner::searchDirection(i, j, Corner::BL, c))
                        return true;
                    else
                        return false;
                case Corner::TR:
                    if (Corner::searchDirection(i, j, Corner::BR, c) || Corner::searchDirection(i, j, Corner::TL, c))
                        return true;
                    else
                        return false;
                case Corner::BL:
                    if (Corner::searchDirection(i, j, Corner::TL, c) || Corner::searchDirection(i, j, Corner::BR, c))
                        return true;
                    else
                        return false;
                case Corner::BR:
                    if (Corner::searchDirection(i, j, Corner::BL, c) || Corner::searchDirection(i, j, Corner::TR, c))
                        return true;
                    else
                        return false;
                default:
                    return false;
            }
        }
    }
	
	static bool searchDirection(int i, int j, direction d, Corner const &cornerToSearch) {
		if ( (i - cornerToSearch.i > searchRange) || (cornerToSearch.i - i > searchRange))
			return false;
		if ( (j - cornerToSearch.j > searchRange) || (cornerToSearch.j - j > searchRange))
			return false;


		int iMult, jMult;
		if (d == ALL)
			return true;
		if (d == BL || d == BR)
			iMult = 1;
		else
			iMult = -1;
		if (d == TR || d == BR)
			jMult = 1;
		else
			jMult = -1;

		bool found = (cornerToSearch.i - i) * iMult >= 0 && (cornerToSearch.j - j) * jMult >= 0;
		if (i == cornerToSearch.i && j == cornerToSearch.j)
			found = false;
		return found;
	}
	
	int i;
	int j;
	direction d;
};

#endif /* Corner_h */
