//
//  PathWriter.hpp
//  MazeSolver
//
//  Created by Preston Raab on 2/11/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef PathWriter_hpp
#define PathWriter_hpp

#include <stdio.h>
#include "Path.hpp"
#include "MazeRunner.h"
#include "Writer.h"

class PathWriter : public Writer{
public:
	PathWriter(MazeRunner* runner, const char* fileOut, vector<vector<unsigned char>> greyMap, vector<int> start, vector<int> end, int thickness, size_t height, size_t width):runner(runner), fileOut(fileOut), greyMap(greyMap), start(start), end(end), thickness(thickness), height(height), width(width){
        
        mapToPaint.reserve(runner->getHeight());
        
        for(long row = 0; row < runner->getHeight(); ++row){
            mapToPaint.push_back(vector<unsigned char>(runner->getWidth()));
        }
	}
    
    PathWriter(MazeRunner* runner, const char* fileOut, vector<vector<bool>> map, vector<int> start, vector<int> end, int thickness, size_t height, size_t width):runner(runner), fileOut(fileOut), start(start), end(end), thickness(thickness), height(height), width(width){
        
        mapToPaint.reserve(runner->getHeight());
        greyMap.reserve(runner->getWidth());
        
        for(long row = 0; row < runner->getHeight(); ++row){
            greyMap.push_back(vector<unsigned char>(runner->getWidth()));
            mapToPaint.push_back(vector<unsigned char>(runner->getWidth()));
        }
        
        for(long row = 0; row < runner->getHeight(); ++row){
            for(long col = 0; col < runner->getWidth(); ++col){
                greyMap.at(row).at(col) = map.at(row).at(col) ? 0 : -1;
            }
        }
    }
	
	void drawOnMap(Path* p, bool useBlocks);
    
    virtual void write(Path* p){
        drawOnMap(p, true);
        encodeOneStep();
    }
	
	void encodeOneStep();
	
private:
	MazeRunner* runner;
	const char* fileOut;
    vector<int> start;
    vector<int> end;
    int thickness;
    vector<vector<unsigned char>> greyMap;
    size_t height;
    size_t width;
    vector<vector<unsigned char>> mapToPaint;
    
};

#endif /* PathWriter_hpp */
