//
//  MajorBlock.h
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef MajorBlock_h
#define MajorBlock_h

#include "Corner.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;


class MajorBlock {
private:
    double distanceFromEnd;
    
public:
    vector<MajorBlock*> connections = {};
    MajorBlock* shorterConnection;
	int i;
	int j;
    long locale;
    int popularity;
    
    vector<Corner> associatedCorners = {};

    typedef vector<MajorBlock*>::iterator MBIterator;

	MajorBlock(Corner const &c) : popularity(0), distanceFromEnd(-1) {
        switch(c.d){
        case Corner::TL:
        case Corner::ALL:
            i = c.i;
            j = c.j;
            break;
        case Corner::TR:
            i = c.i;
            j = c.j + 1;
            break;
        case Corner::BL:
            i = c.i + 1;
            j = c.j;
            break;
        case Corner::BR:
            i = c.i + 1;
            j = c.j + 1;
            break;
        }
        if(i > 3000){
            ;
        }
        locale = long(i * mapWidth) + j;
        associatedCorners.push_back(c);
	}
    
    void addAssociatedCorner(Corner const &c){
        associatedCorners.push_back(c);
    }
    
    // We ask the question, is m1 < m2 with respect to the reference block
    struct MajorBlockDistanceComparator {
        const MajorBlock* const reference;
        MajorBlockDistanceComparator(const MajorBlock* const &reference) : reference(reference){}
        
        //Priority needs to be given to blocks that are closer to the end than the reference.
        //Of those, we sort the blocks on the shortest path first.

        bool operator ()(const MajorBlock* const &m1, const MajorBlock* const &m2) {
            if(m1->distanceFromEnd > reference->getDistanceFromEnd() && m2->getDistanceFromEnd() > reference->getDistanceFromEnd()){
                return m1->distanceFromEnd < m2->distanceFromEnd;
            }
            else if (m2->distanceFromEnd > reference->getDistanceFromEnd()){
                return true;
            }
            else if (m1->distanceFromEnd > reference->getDistanceFromEnd()){
                return false;
            }
            else{
                return m1->distanceFromEnd + reference->getDistance(m1) < m2->distanceFromEnd + reference->getDistance(m2);
            }
        }
    };
    
    struct MajorBlockPointerLocationComparator {
        MajorBlockPointerLocationComparator(){};
        
        bool operator ()(MajorBlock* const &m1, MajorBlock* const &m2) {
            return m1->locale < m2->locale;
        }
    };
    
    struct MajorBlockLocationComparator {
        MajorBlockLocationComparator(){};
        
        bool operator ()(MajorBlock* const &m1, MajorBlock const &m2) const {
            return m1->locale < m2.locale;
        }
    };
    
    void addConnection(MajorBlock* const &m){
        connections.push_back(m);
    }
    
    bool isConnectedToEnd(){
        return distanceFromEnd > -0.5;
    }
    
    double getDistance(const MajorBlock* const &other) const{
        return std::sqrt(double(pow(double(other->i - i), 2)) + double(pow(double(other->j - j), 2)));
    }
    
    size_t getConnectionsSize() const{
        return connections.size();
    }
    
    double getDistanceFromEnd() const{
        return distanceFromEnd;
    }
    
    void setDistanceFromEnd(double distance){
        distanceFromEnd = distance;
    }
    
    MajorBlock* const& getConnectionAt(size_t i) const{
        return connections.at(i);
    }
    
    void clearConnections(){
        connections.clear();
    }
    
    void replaceConnections(vector<MajorBlock*> &otherConnections){
        connections.clear();
        for(MajorBlock* connection : otherConnections){
            addConnection(connection);
        }
    }
    
    static MajorBlock* startBlockPtr;
    static MajorBlock* endBlockPtr;
    static long mapWidth;
	
	static vector<MajorBlock*> findMajorBlocks(vector<Corner> &corners, Corner &start, MajorBlock &finish) {
        static MajorBlockPointerLocationComparator comp;
		vector<MajorBlock*> blocks;
		startBlockPtr = new MajorBlock(start);
        endBlockPtr = new MajorBlock(finish);
        blocks.push_back(startBlockPtr);
        blocks.insert(lower_bound(blocks.begin(), blocks.end(), endBlockPtr, comp), endBlockPtr);
        
		startBlockPtr->connections.push_back(endBlockPtr);

		unsigned long size = corners.size();
		unsigned percentile = (unsigned)size / 50 + 1;

		for (size_t i = 0; i < size; ++i) {  //Loop through all corners
            MajorBlock* m = new MajorBlock(corners[i]); //Create a major block for each one
            MBIterator find = getBlock(blocks, m);
            if(binary_search(blocks.begin(), blocks.end(), m, comp)){  //Search for an equivalent block
                (*find)->addAssociatedCorner(corners[i]);  //If found, add this corner to that block.
                cout << "Assos corners size: " << (*find)->associatedCorners.size() << endl;
                delete m;
            }
            else{ //If not found
                startBlockPtr->addConnection(m);
                m->connections.push_back(endBlockPtr);
                blocks.insert(find, m); //Add this new block to blocks
            }
		}
		for (size_t i = 0; i < blocks.size(); ++i) { //Loop through all our new blocks
			MajorBlock*& m = blocks.at(i);
			formInitialConnections(blocks, m, corners);
            sort(m->connections.begin(), m->connections.end());

			if (i % percentile == 0){
				cout << std::fixed << std::setprecision(2) << i * 100.0 / size << "%" << endl;
			}
		}
		return blocks;
	}
	
    
    
	static void formInitialConnections(vector<MajorBlock*> &allBlocks, MajorBlock* &m, vector<Corner> const &corners)
	{
        for(Corner associatedCorner : m->associatedCorners){ //Loop through each corner of the block (1 or 2)
            if(m->associatedCorners.size() != 1){
                cout << m->associatedCorners.size() << endl;
            }
            
            for (Corner c : corners)
            {
                if(associatedCorner.isPossibleConnection(c)){
                    MajorBlock connectBlock = MajorBlock(c);
                    MBIterator location = getBlock(allBlocks, connectBlock);
                    m->addConnection(*location);
                }
            }
        }
	}
	
	
	static MBIterator getBlock(vector<MajorBlock*> &blocks, MajorBlock*& m) {
        static MajorBlockPointerLocationComparator comp;
        return lower_bound(blocks.begin(), blocks.end(), m, comp);
	}
    
    static MBIterator getBlock(vector<MajorBlock*> &blocks, MajorBlock& m) {
        static MajorBlockLocationComparator comp;
        return lower_bound(blocks.begin(), blocks.end(), m, comp);
    }

	bool operator==(MajorBlock& other) const {
		return other.i == i && other.j == j;
	}
	bool operator<(MajorBlock& other) const {
		return other.i < i || (other.i == i && other.j < j);
	}
	bool operator<(const MajorBlock& other) const {
		return other.i < i || (other.i == i && other.j < j);
	}
    std::string toString() const{
        return "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
    }
    friend std::ostream& operator<<(std::ostream &o, const MajorBlock &m){
        o << m.toString();
        return o;
    }
};


#endif /* MajorBlock_h */
