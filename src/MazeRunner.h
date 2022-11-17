
#ifndef MAZERUNNER_H
#define MAZERUNNER_H

#include "Line.h"
#include "MajorBlock.h"
#include "BitArray.h"
#include "ArduinoSTL-master/vector.h"
#include "ArduinoSTL-master/string.h"
using std::string;


class MazeRunner{
private:
	BitArray* map;
	
	unsigned int height;
	unsigned int width;
	
	MajorBlock* startBlockPtr;
	MajorBlock* finishBlockPtr;
	

	const char* fileIn;
	
	int removeUnlikelies(BitArray* m);
	
	void identifyMajorBlocks(BitArray* m);
	
	void getPotentialCorners(int i, int j, Corner::direction d, vector<MajorBlock*> corners);
	
    bool canSee(const MajorBlock* const &m, const MajorBlock* const &t);
	
	void reduceConnections(vector<MajorBlock*>& blocks);
	
public:
	vector<MajorBlock*> allBlocks;


	bool solve();
	
	MazeRunner(BitArray* map, vector<unsigned char> startPos, vector<unsigned char> endPos);
    
  void orderConnections(vector<MajorBlock*>& blocks);
  bool insertBlockIntoVector(vector<MajorBlock*>& blocks, MajorBlock* block, MajorBlock* start);
	
	
	unsigned int getWidth(){
		return width;
	}
	
	unsigned int getHeight(){
		return height;
	}
    

  vector<unsigned char> getNextPosition(){
    auto startBlockFirstConnection = startBlockPtr->shorterConnection;
    vector<unsigned char> result;
      if(startBlockFirstConnection == nullptr){
          result = {1, 1};
      }
      else{
          result = {startBlockFirstConnection->j, startBlockFirstConnection->i};
      }
    return result;
  }
	
    static double verticalStates[2][2];
    static double horizontalStates[2][2];
    static double vCounter[2];
    static double hCounter[2];


	//const MajorBlock* maxBlock = new MajorBlock(Corner(INT_MAX, INT_MAX, Corner::ALL));


//	void print(vector<vector<bool> > m) {
//		for (unsigned int i = 0; i < m.size(); i++) {
//			for (unsigned int j = 0; j < m.at(i).size(); j++) {
//				debug(m.at(i).at(j) ? "X" : " ");//(unsigned char)(219) : (unsigned char)(32));
//				//std::cout << (m.at(i).at(j) ? (unsigned char)(219) : (unsigned char)(32));
//			}
//		}
//	}


	// void print(vector<MajorBlock*> blocks, vector<vector<bool> > map) {
	// 	int pathCount = 0;
	// 	for (unsigned int i = 0; i < map.size(); i++) {
	// 		for (unsigned int j = 0; j < map.at(i).size(); j++) {
	// 			bool isInCorners = false;
	// 			long size = 0;
	// 			bool isInPath = false;
	// 			for (unsigned int k = 0; k < blocks.size(); k++) {
	// 				if (i == blocks[k]->i && j == blocks[k]->j) {
	// 					isInCorners = true;
	// 					if (shortPath != NULL && shortPath->has(blocks[k])) {
	// 						isInPath = true;
	// 						pathCount = 1; //shortPath->find(blocks[k]);
	// 					}
	// 					else
	// 						size = blocks[k]->getConnectionsSize();
	// 				}
	// 			}
	// 			if (isInPath) {
	// 				if (i == start.i && j == start.j)
	// 					cout << "SS";
	// 				else if (i == finish.i && j == finish.j)
	// 					cout << "FF";
	// 				else {
	// 					cout << pathCount % 100;
	// 				}
	// 				pathCount++;
	// 			}
	// 			else if (isInCorners) {
	// 				std::cout << size;
	// 			}
	// 			else if (map[i][j]) {
	// 				std::cout << "XX";//char(219) << char(219);
	// 			}
	// 			else {
	// 				std::cout << "  ";
	// 			}
	// 		}
	// 		debugln("");
	// 	}
	// 	debugln("";)
	// }

};

#endif
