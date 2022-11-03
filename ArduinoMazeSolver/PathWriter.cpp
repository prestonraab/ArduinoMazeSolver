//
//  PathWriter.cpp
//  MazeSolver
//
//  Created by Preston Raab on 2/11/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#include "PathWriter.hpp"


void PathWriter::drawOnMap(Path* p, bool useBlocks) {
    if(useBlocks){
        vector<MajorBlock*>& blocks = runner->allBlocks;
        for (unsigned int k = 0; k < blocks.size(); k++) {
            int i = blocks[k]->i;
            int j = blocks[k]->j;
            if(i == INT_MAX){
                continue;
            }
            mapToPaint[i][j] = 'C';
        }
        
        p->drawOnMap(mapToPaint, thickness, 0, p->distance);
        
        for (unsigned int k = 0; k < blocks.size(); k++) {
            int i = blocks[k]->i;
            int j = blocks[k]->j;
            if(i == INT_MAX){
                continue;
            }
            if (p->has(blocks[k])) {
                mapToPaint[i][j] = 'P';
            }
        }
        
        mapToPaint.at(end[0]).at(end[1]) = 'O';
        mapToPaint.at(start[0]).at(start[1]) = 'O';
    }
    else{
        //int pathCount = 0;
        p->drawOnMap(mapToPaint, thickness, 0, p->distance);

        for (Path path = *p; path.previous != NULL; path = *path.previous) {
            int i = path.data->i;
            int j = path.data->j;
            if(i == INT_MAX){
                continue;
            }
            mapToPaint[i][j] = 'P';
        }
    }
}

void PathWriter::encodeOneStep() {
    mapToPaint.at(end[0]).at(end[1]) = 'O';
    mapToPaint.at(start[0]).at(start[1]) = 'O';
    
    
    vector<vector<unsigned char>>& paintedMap = mapToPaint;
	vector<unsigned char> image;
	unsigned long height = runner->getHeight();
	unsigned long width = runner->getWidth();
	image.reserve(width * height);


	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
			switch (paintedMap[i][j])
			{
			case 'G':
				image.push_back(0);
				image.push_back(255);
				image.push_back(0);
				break;
			case 'P':
				image.push_back(0);
				image.push_back(0);
				image.push_back(255);
				break;
			case 'C':
				image.push_back(255);
				image.push_back(0);
				image.push_back(255);
				break;
			case 'O':
				image.push_back(255);
				image.push_back(165);
				image.push_back(0);
				break;
			default:
				char greyVal = greyMap[i][j];

				image.push_back(greyVal);
				image.push_back(greyVal);
				image.push_back(greyVal);
			}
            paintedMap[i][j] = 0;
			image.push_back(white);
		}
	}
	//Encode the image
	unsigned error = lodepng::encode(fileOut, image, (unsigned)width, (unsigned)height);
    

	//if there's an error, display it
	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}
