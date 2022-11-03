//  main.cpp: This file contains the 'main' function. Program execution begins and ends there.
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#include <stdio.h>

#include "Campus.h"
#include "MazeRunner.h"
#include "PathWriter.hpp"
#include "MajorBlock.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

int main(int numFiles, char** files)
{
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
    
    if(useFileIn){
        string stringFileIn = string(fileIn);
        if(stringFileIn.back() == 'g'){
            int xres = 0, yres = 0;
            int channels;  // RGB
            
            unsigned char *img = stbi_load(fileIn, &xres, &yres, &channels, 0);
            if(xres > 500) { thickness = 3; showCornersinPink = true; searchRange = 400;}
            if(xres > 1000) {thickness = 5; searchRange = 700;}
            if(xres > 1500) {scaleBy = 1.0 / 2.0; searchRange = 800;}
            if(xres > 2500) {scaleBy = 1.0 / 4.0;}
            if(xres > 4000) {scaleBy = 1.0 / (xres / 1000);}
            
            Corner::setSearchRange(searchRange);
            
            cout << channels;
            
            int newXres = xres * scaleBy;
            int newYres = yres * scaleBy;
            unsigned char *compressedImage = new unsigned char[newXres*newYres*channels];
            cout << compressedImage[0];
            
            stbir_resize_uint8(img,                xres,    yres, 0,
                               compressedImage, newXres, newYres, 0, channels);
            
            stbi_write_bmp("/Users/prestonraab/Desktop/interim.bmp", newXres, newYres, channels, compressedImage);
            
            stbi_image_free(img);
            
            fileIn = "/Users/prestonraab/Desktop/interim.bmp";
        }
        Campus campus(fileIn);
        greyMap = campus.greyMap;
        MajorBlock::mapWidth = greyMap.at(0).size();
        runner = new MazeRunner(campus);
        start = vector<int>{campus.start[0], campus.start[1]};
        end = vector<int>{campus.end[0], campus.end[1]};
        map = campus.getMap();
    }
    else{
        int mazeSize = 20;
        Maze maze = Maze(mazeSize, mazeSize);
        
        map = maze.getMap();
        vector<vector<int> > startEnd = maze.getStartEnd();
        
        start = startEnd.at(0);
        end = startEnd.at(1);
        
        MajorBlock::mapWidth = map.at(0).size();
        
        runner = new MazeRunner(map, start, end);
        
        greyMap.reserve(map.size());
    
        for(int row = 0; row < map.size(); ++row){
            greyMap.push_back(vector<unsigned char>() );
            for(int col = 0; col < map[0].size(); ++col){
                greyMap.at(row).push_back( (unsigned char)(map[row][col]) - 1);
            }
        }
        
    }
    
    cout << "Start: (" << start.at(0) << ", " << start.at(1) << ")" << endl;
    cout << "End: (" << end.at(0) << ", " << end.at(1) << ")" << endl;
    
    PathWriter* writer = new PathWriter(runner, fileOut, greyMap, start, end, thickness, runner->getHeight(), runner->getWidth());
    
    runner->addWriter((Writer*) writer);
    
    PathWriter* blackWhiteWriter = new PathWriter(runner, fileOut, map, start, end, thickness, runner->getHeight(), runner->getWidth());
    
    
    if(useFileIn){
        Path* startEndConnector = (new Path(new MajorBlock( Corner(start[0],start[1], Corner::TL))))->add(new MajorBlock( Corner(end[0],end[1], Corner::TL)));
        blackWhiteWriter->drawOnMap(startEndConnector, showCornersinPink);
    }
    blackWhiteWriter->encodeOneStep();
    
    bool solved = runner->solve();
    
    if(solved){
        writer->drawOnMap(runner->getShortestPath(), showCornersinPink);
        writer->encodeOneStep();
        
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
    

    return 0;
}
