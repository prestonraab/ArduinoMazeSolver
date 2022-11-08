
#ifndef MAZERUNNER_H
#define MAZERUNNER_H

#include<iostream> 
#include "vector.h"
#include<string>
#include "Maze.h"
#include "Line.hpp"
#include "MajorBlock.h"
#include "Path.hpp"
#include "Writer.h"


static unsigned char black = 0x00;
static unsigned char white = 0xFF;


class MazeRunner{
private:
	vector<vector<bool> > map;
	
	unsigned int height;
	unsigned int width;
	
	vector<vector<bool> > likelyMap;
	vector<vector<unsigned char> > finalMap;
	
	Corner start;// = Corner(1, 1, Corner::TL);
	Corner finish;// = Corner(3, 9, Corner::ALL);

	vector<Corner> allCorners;// = { start, finish };

	MajorBlock mfinish;// = Corner(finish);

    Writer* writer;
	Path* shortPath;
	vector<Path*> foundShortPaths = {};
	

	const char* fileIn;
	
	int removeUnlikelies(vector<vector<bool> >& m);
	
	void identifyCorners(vector<vector<bool> > m, vector<Corner>& c);
	
	void getPotentialCorners(int i, int j, Corner::direction d, vector<MajorBlock*> corners);
	
    bool canSee(const MajorBlock* const &m, const MajorBlock* const &t);
	
	void reduceConnections(vector<MajorBlock*>& blocks);
	
public:
	vector<MajorBlock*> allBlocks;
	
	MazeRunner(vector<vector<bool> > map, vector<int> startPos, vector<int> endPos):
									map(map),
									height((unsigned)map.size()),
									width((unsigned)map[0].size()),
									start(Corner(startPos.at(0), startPos.at(1), Corner::ALL)),
									shortPath(NULL),
									finish(Corner(endPos.at(0), endPos.at(1), Corner::ALL)),
									mfinish(finish),
									likelyMap(map)
	{
        Path::magnitude = log2(long(height) * width) + 2;
		//print(map);

		allCorners.push_back(start);
        allCorners.push_back(finish);
	}
    
    void orderConnections(vector<MajorBlock*>& blocks);
	
	Path* getShortestPath(){
		return shortPath;
	}
	
	unsigned int getWidth(){
		return width;
	}
	
	unsigned int getHeight(){
		return height;
	}
    
    void addWriter(Writer* pathWriter){
        writer = pathWriter;
    }
	
	bool solve(){
        if(width < 51){
            print(likelyMap);
        }
		
		while (true) {
            int removed = removeUnlikelies(likelyMap);
            cout << "Removed " << removed << " unlikelies, ";
            if(removed > 4) cout << endl;
            if(width < 51) {
                print(likelyMap);
            }
            if(removed == 0){
                cout << endl;
                break;
            }
		}
		
		if(width < 100) print(likelyMap);
		cout << "Identifying Corners" << endl;
		identifyCorners(likelyMap, allCorners);
		cout << "Corner size: " << allCorners.size() << endl;
		//print(allCorners);
		cout << "Finding Major Blocks" << endl;
		allBlocks = MajorBlock::findMajorBlocks(allCorners, start, mfinish);
        if(width < 100) print(allBlocks, likelyMap);
        cout << "Reducing Connections" << endl;
		reduceConnections(allBlocks);
		if(width < 100) print(allBlocks, likelyMap);
		cout << "Printed All Blocks" << endl;
        cout << "Number of Blocks: " << allBlocks.size() << endl;
		
        const MajorBlock* startBlock = MajorBlock::startBlockPtr;
		
        cout << "Ordering connections" << endl;
        orderConnections(allBlocks);
        
        cout << "Start block connections size: " << startBlock->getConnectionsSize() << endl;
        if(startBlock->getConnectionsSize() == 0){
            cout << "Start block has no connections, check output image \n";
            return 0;
        }
        auto startBlockFirstConnection = MajorBlock::startBlockPtr->connections->getLeftmost();
        cout << "Start block first connection: (" << startBlockFirstConnection->i << ", " << startBlockFirstConnection->j << ")" << endl;
        
        cout << "Theoretical min distance: " << startBlock->getDistanceFromEnd() << endl;
        cout << "Finding First Path" << endl;
        
        Path* trod = new Path(startBlock);
        
        while(trod->data->getDistanceFromEnd() > 1){
            trod = trod->add(trod->data->connections->getLeftmost());
            cout << " Distance from End" << trod->data->getDistanceFromEnd() << endl;
        }
        
		cout << "Finding Best Path" << endl;
		//Path* initialPath = NULL;
        shortPath = trod;
		//shortPath = findBestPath(startBlock, initialPath);//.add(startBlock).reverse();
		cout << shortPath->toString();
		cout << "Printed Shortest Path" << endl;
		//print(allBlocks);
		cout << "Printed All Blocks" << endl;

		return shortPath->distance < std::numeric_limits<double>().max();
	}
	
	


	const MajorBlock* maxBlock = new MajorBlock(Corner(INT_MAX, INT_MAX, Corner::ALL));
	Path* maxPath = new Path(maxBlock);

	Path* shortestPath(vector<Path*> paths) {
		double min = std::numeric_limits<double>().max();
		Path* shortest = maxPath;
		for (Path* p : paths) {
			if (p->distance < min && p->has(MajorBlock::endBlockPtr)) {
				shortest = p;
				min = p->distance;
			}
		}
		return shortest;
	}

	vector<Path*> alreadySolvedPaths = {};

	Path* findBestPath(const MajorBlock* const &m, Path* &p);



	void print(vector<vector<bool> > m) {
		for (unsigned int i = 0; i < m.size(); i++) {
			for (unsigned int j = 0; j < m.at(i).size(); j++) {
				std::cout << (m.at(i).at(j) ? "X" : " ");//(unsigned char)(219) : (unsigned char)(32));
				//std::cout << (m.at(i).at(j) ? (unsigned char)(219) : (unsigned char)(32));
			}
			std::cout << std::endl;
		}
		cout << endl;
	}

	void print(vector<Corner> corners, vector<vector<bool> > map) {
		for (unsigned int i = 0; i + 1 < map.size(); i++) {
			for (unsigned int j = 0; j + 1 < map.at(i).size(); j++) {
				bool isInCorners = false;
				for (unsigned int k = 0; k < corners.size(); k++) {
					if (i == corners[k].i && j == corners[k].j)
						isInCorners = true;
				}
				std::cout << (isInCorners ? "X" : " ");
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void print(vector<MajorBlock*> blocks, vector<vector<bool> > map) {
		int pathCount = 0;
		for (unsigned int i = 0; i < map.size(); i++) {
			for (unsigned int j = 0; j < map.at(i).size(); j++) {
				bool isInCorners = false;
				long size = 0;
				bool isInPath = false;
				for (unsigned int k = 0; k < blocks.size(); k++) {
					if (i == blocks[k]->i && j == blocks[k]->j) {
						isInCorners = true;
						if (shortPath != NULL && shortPath->has(blocks[k])) {
							isInPath = true;
							pathCount = 1; //shortPath->find(blocks[k]);
						}
						else
							size = blocks[k]->getConnectionsSize();
					}
				}
				if (isInPath) {
					if (i == start.i && j == start.j)
						cout << "SS";
					else if (i == finish.i && j == finish.j)
						cout << "FF";
					else {
						cout << pathCount % 100;
					}
					pathCount++;
				}
				else if (isInCorners) {
					std::cout << size;
				}
				else if (map[i][j]) {
					std::cout << "XX";//char(219) << char(219);
				}
				else {
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

};

#endif
