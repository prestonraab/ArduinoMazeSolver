//
//  MajorBlock.cpp
//  ImageMazeSolver
//
//  Created by Preston Raab on 3/13/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#include "MajorBlock.h"


MajorBlock* MajorBlock::startBlockPtr = nullptr;
MajorBlock* MajorBlock::endBlockPtr = nullptr;

MajorBlock::MajorBlock(unsigned char i, unsigned char j, Corner::direction d) : distanceFromEnd(-1) {
    switch(d){
    case Corner::TL:
    case Corner::ALL:
        this->i = i;
        this->j = j;
        break;
    case Corner::TR:
        this->i = i;
        this->j = j + 1;
        break;
    case Corner::BL:
        this->i = i + 1;
        this->j = j;
        break;
    case Corner::BR:
        this->i = i + 1;
        this->j = j + 1;
        break;
    }
    locale = int(i * mapWidth) + j;
    associatedCorners.push_back(d);
}

void MajorBlock::formInitialConnections(vector<MajorBlock*> blocks, unsigned char myLocation){
  for(Corner::direction d : associatedCorners){ //Loop through each corner of the block (1 or 2)
    Corner associatedCorner = Corner(i, j, d);
    for (unsigned char s = 0; s < blocks.size(); s++)
    {
      MajorBlock* other = blocks[s];
      for(Corner::direction p : other->associatedCorners){
        if(associatedCorner.isPossibleConnection(other->i, other->j, p)){
            addConnection(s);
            other->addConnection(myLocation);
        }
      }
    }
  }
}

void MajorBlock::addAssociatedCorner(Corner::direction const d){
    associatedCorners.push_back(d);
}

void MajorBlock::addConnection(unsigned char index){
    connections->set(0, index, true);
}

void MajorBlock::removeConnection(unsigned char index){
    connections->set(0, index, false);
}

bool MajorBlock::isConnectedToEnd(){
    return distanceFromEnd > -0.5;
}

double MajorBlock::getDistance(const MajorBlock* const &other) const{
    int deltaI = other->i - i;
    int deltaJ = other->j - j;
    return deltaI * deltaI + deltaJ * deltaJ;
}

double MajorBlock::getDistanceFromEnd() const{
    return distanceFromEnd;
}

void MajorBlock::setDistanceFromEnd(double distance){
    distanceFromEnd = distance;
}

void MajorBlock::createConnectionArray(unsigned char size){
    connections = new BitArray(1, size);
}


bool MajorBlock::operator==(MajorBlock& other) const {
    return other.i == i && other.j == j;
}
bool MajorBlock::operator<(MajorBlock& other) const {
    return other.i < i || (other.i == i && other.j < j);
}
bool MajorBlock::operator<(const MajorBlock& other) const {
    return other.i < i || (other.i == i && other.j < j);
}

int MajorBlock::mapWidth = 0;
