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
long MajorBlock::mapWidth = 0;

MajorBlock::MajorBlock(Corner const &c) : popularity(0), distanceFromEnd(-1) {
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

void MajorBlock::addAssociatedCorner(Corner const &c){
    associatedCorners.push_back(c);
}

void MajorBlock::addConnection(MajorBlock* const &m){
    connections->add(m);
}

bool MajorBlock::isConnectedToEnd(){
    return distanceFromEnd > -0.5;
}

double MajorBlock::getDistance(const MajorBlock* const &other) const{
    return std::sqrt(double(pow(double(other->i - i), 2)) + double(pow(double(other->j - j), 2)));
}

size_t MajorBlock::getConnectionsSize() const{
    return connections->size();
}

double MajorBlock::getDistanceFromEnd() const{
    return distanceFromEnd;
}

void MajorBlock::setDistanceFromEnd(double distance){
    distanceFromEnd = distance;
}

void MajorBlock::clearConnections(){
    connections->clear();
}

void MajorBlock::replaceConnections(vector<MajorBlock*> &otherConnections){
    connections->clear();
    for(MajorBlock* connection : otherConnections){
        addConnection(connection);
    }
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
std::string MajorBlock::toString() const{
    return "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
}
