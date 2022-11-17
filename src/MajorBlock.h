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
#include "ArduinoSTL-master/vector.h"
#include "BitArray.h"
using std::vector;


class MajorBlock {
private:
    double distanceFromEnd;
    
public:
    BitArray* connections;
    MajorBlock* shorterConnection;
    unsigned char i;
    unsigned char j;
    int locale;
    
    vector<Corner::direction> associatedCorners;
    
    ~MajorBlock(){
        delete connections;
    }

    MajorBlock(unsigned char i, unsigned char j, Corner::direction d);
    
    void addAssociatedCorner(Corner::direction const d);
    
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
    
    void addConnection(unsigned char index);
    void removeConnection(unsigned char index);
    
    bool isConnectedToEnd();
    
    double getDistance(const MajorBlock* const &other) const;
    
    size_t getConnectionsSize() const;
    
    double getDistanceFromEnd() const;
    
    void setDistanceFromEnd(double distance);
    
    static MajorBlock* startBlockPtr;
    static MajorBlock* endBlockPtr;
    static int mapWidth;
	

    void createConnectionArray(unsigned char size);


    void formInitialConnections(vector<MajorBlock*> blocks, unsigned char myLocation);

    bool operator==(MajorBlock& other) const;
    bool operator<(MajorBlock& other) const;
    bool operator<(const MajorBlock& other) const;
};


#endif /* MajorBlock_h */
