//  main.cpp: This file contains the 'main' function. Program execution begins and ends there.
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;

#include "vector.h"

#include "MazeRunner.h"
#include "MajorBlock.h"


int main(int numFiles, char** files)
{
#if VECTOR
    vector<int> numbers;
    numbers.push_back(9);
    numbers.push_back(9);
    numbers.push_back(9);
    numbers.push_back(9);
    numbers.push_back(9);
    numbers.push_back(9);
    for(int i = 0; i < 25; i++){
        cout << numbers[i] << " ";
        cout << numbers.capacity << " ";
        cout << numbers.size() << endl;
        numbers.push_back(2);
    }
#else
    //const char* fileIn = "/Users/Preston/Downloads/maze.bmp";
    const char* fileIn;
    const char* fileOut;
    if(numFiles >= 2){
        fileIn = files[0];
        fileOut = files[1];
    }
    else{
        //fileIn = "/Users/prestonraab/Desktop/simpleMaze.bmp";
        fileIn = "/Users/prestonraab/Downloads/Fourth Maze.jpg";
        fileOut = "/Users/prestonraab/Desktop/new.bmp";
    }
    //"/Users/Preston/MazeSolver/MazeSolver/BigMaze.bmp";
    
    bool useFileIn = true;
    int thickness = 1;
    bool showCornersinPink = false;
    double searchRange = 200;
    float scaleBy = 1.0;
    
    MazeRunner* runner;
    
    vector<vector<unsigned char> > greyMap;
    vector<int> start;
    vector<int> end;

    vector<vector<bool> > map;

    int mazeSize = 20;
    Maze maze = Maze(mazeSize, mazeSize);
    
    map = maze.getMap();
    vector<vector<int> > startEnd = maze.getStartEnd();
    
    start = startEnd.at(0);
    end = startEnd.at(1);
    
    MajorBlock::mapWidth = map.at(0).size();
    
    runner = new MazeRunner(map, start, end);

    for(int row = 0; row < map.size(); ++row){
        greyMap.push_back(vector<unsigned char>() );
        for(int col = 0; col < map[0].size(); ++col){
            greyMap.at(row).push_back( (unsigned char)(map[row][col]) - 1);
        }
    }
    
    cout << "Start: (" << start.at(0) << ", " << start.at(1) << ")" << endl;
    cout << "End: (" << end.at(0) << ", " << end.at(1) << ")" << endl;
    
    
    if(useFileIn){
        Path* startEndConnector = (new Path(new MajorBlock( Corner(start[0],start[1], Corner::TL))))->add(new MajorBlock( Corner(end[0],end[1], Corner::TL)));
    }
    
    bool solved = runner->solve();
    
    if(solved){
        
        if(runner->getShortestPath()->distance < 1059.89){
            cout << "Good job, minimum solution found." << endl;
        }
        else{
            cout << "ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  ERROR  " << endl;
            cout << "You broke something" << endl;
            cout << "Go find it" << endl;
            cout << "Minimum solution not found." << endl;
        }
    }
    
#endif
    return 0;
}
