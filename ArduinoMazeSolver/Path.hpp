//
//  Path.hpp
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <iostream>
#include "MajorBlock.h"
#include "Line.hpp"

using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::pow;

class Path {
public:
    static int magnitude;
    
    double distance;
	const Path* previous;
	const MajorBlock* data;
    
    std::unordered_set<const MajorBlock*> previousSet;
	
	Path(const MajorBlock* block) : previous(NULL), data(block), distance(0.0){
	}
	
	Path(const MajorBlock* const &block, const Path* previous) : previous(previous), data(block), distance(0.0){
    }

	Path(const MajorBlock* &block, int d) : previous(NULL), data(block), distance(d) {
	}
    
    void initializePrevious(){
        if(previous){
            previousSet = previous->previousSet;
        }
        previousSet.emplace(data);
    }
    
	
	Path* add(const MajorBlock* const &m) const{
		Path* next = new Path(m, this);
		next->distance = distance + std::sqrt(double(pow(double(data->i - m->i), 2)) + double(pow(double(data->j - m->j), 2)));
		return next;
	}
    
    const Path* match(const Path* const &m, int limit, int smallerMatch) const{
        size_t loc = data->locale;
        size_t mLoc = m->data->locale;
        
        switch(smallerMatch){
        case true:
            if(mLoc - loc >= limit) return this;
            break;
        case false:
            if(loc - mLoc >= limit) return this;
            break;
        }
        
        if(!previous) return nullptr;
        
        return previous->match(m, limit, smallerMatch);
    }
    
    bool has (const MajorBlock* const &m) const {
        return previousSet.count(m) > 0;
    }
    
    long distanceTo(const MajorBlock* const &m) const{
        return m->locale - data->locale;
    }
    
    struct PathPointerMajorBlockComparator {
        PathPointerMajorBlockComparator(){};
        
        bool operator ()(Path* const &p1, Path* const &p2) {
            const MajorBlock* &m1 = p1->data;
            const MajorBlock* &m2 = p2->data;
            return m1->i < m2->i || ((m1->i == m2->i) && (m1->j < m2->j));
        }
    };
            
    struct PathPointerMajorBlockPointerComparator {
        PathPointerMajorBlockPointerComparator(){};
        
        bool operator ()(Path* const &p1, const MajorBlock* const &m2) {
            const MajorBlock* &m1 = p1->data;
            return m1->i < m2->i || ((m1->i == m2->i) && (m1->j < m2->j));
        }
            
        bool operator ()(const MajorBlock* const &m1, Path* const &p2) {
            const MajorBlock* &m2 = p2->data;
            return m1->i < m2->i || ((m1->i == m2->i) && (m1->j < m2->j));
        }
    };

//	Path reverse() {
//		Path rev = {};
//		for (unsigned i = (unsigned)steps.size() - 1; i != -1; i--) {
//			rev.add(steps.at(i));
//		}
//		return rev;
//	}

	string toString() const{
        string output = "";
		output += "(" + to_string(data->i) + ", " + to_string(data->j) + ")" + "\t";
		
		if(previous == NULL){
			output += "\n\n";
		}
		else{
			output += previous->toString();
		}
        return output;
	}
    
    friend std::ostream& operator<<(std::ostream& o, Path p){
        o << p.toString();
        return o;
    }

	void drawOnMap(vector<vector<unsigned char>>& map, int thickness, int numSteps, double distance) const{
		if(previous != NULL){
			Line l = Line(data->j, data->i, previous->data->j, previous->data->i);
			//l.print();
			l.drawOn(map, thickness);
			previous->drawOnMap(map, thickness, ++numSteps, distance);
		}
		else{
			cout << "NumSteps: " << numSteps << "  Distance: " << distance << endl;
		}
	}
};

#endif /* Path_hpp */
