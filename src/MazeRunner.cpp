#include "MazeRunner.h"

#define leftc ((unsigned int)upperColBound - 1) -
#define upc ((unsigned int)upperColBound - 1) -

MazeRunner::MazeRunner(BitArray* map, vector<unsigned char> startPos, vector<unsigned char> endPos):
									map(map),
									height((unsigned)map->height),
									width((unsigned)map->width)
	{
        
        startBlockPtr = new MajorBlock(startPos.at(0), startPos.at(1), Corner::ALL);
        finishBlockPtr = new MajorBlock(endPos.at(0), endPos.at(1), Corner::ALL);
	}

/** Useful for tight mazes with dead ends*/
int MazeRunner::removeUnlikelies(BitArray* m) {
    int removedOne = 0;
    unsigned char height = m->height;
    unsigned char width = m->width;
    
    //Works fast in one direction, so alternate in a circle.
    enum direction {right=0, down=1, up=2, left=3};
    
    direction d = right;
    
    bool center = false;
    bool nextCenter = false;
    
    unsigned char upperRowBound = 0;
    unsigned char upperColBound = 0;
    for(unsigned char circle = 0; circle < 4; ++circle){
        switch(circle) {
            case 0: d = right;
                break;
            case 1: d = down;
                break;
            case 2: d = left;
                break;
            case 3: d = up;
                break;
        }
        
        switch(d){
            case right:
            case left:
                upperRowBound = height;
                upperColBound = width;
                break;
            case down:
            case up:
                upperRowBound = width;
                upperColBound = height;
                break;
        }
        for (unsigned char row = 1; row + 1 < upperRowBound; ++row) {
            switch(d){
                case right:
                    center = m->get(row, 0);
                    nextCenter = m->get(row, 1);
                    break;
                case left:
                    center = m->get(row,leftc 0);
                    nextCenter = m->get(row,leftc 1);
                    break;
                case down:
                    center = m->get(0,row);
                    nextCenter = m->get(1,row);
                    break;
                case up:
                    center = m->get(upc 0, row);
                    nextCenter = m->get(upc 1, row);
                    break;
            }
            
            for (unsigned int col = 1; col + 1 < upperColBound; ++col) {
                unsigned int x = 0;
                unsigned int y = 0;
                center = nextCenter;
                switch(d){
                    case right:
                        y = row;
                        x = col;
                        nextCenter = m->get(row, col + 1);
                        break;
                    case left:
                        y = row;
                        x = leftc (col);
                        nextCenter = m->get(row, leftc (col+1));
                        break;
                    case down:
                        y = col;
                        x = row;
                        nextCenter = m->get(col + 1, row);
                        break;
                    case up:
                        y = upc (col);
                        x = row;
                        nextCenter = m->get(upc (col + 1), row);
                        break;
                }
                
                if (!center && !(y == startBlockPtr->i && x == startBlockPtr->j) && !(y == finishBlockPtr->i && x == finishBlockPtr->j)) {
                    int countFalse = 0;
                    
                    if (!m->get(y, x - 1))
                        ++countFalse;

                    if (!m->get(y, x + 1))
                        if (++countFalse == 2)
                            continue;

                    if (!m->get(y + 1, x))
                        if (++countFalse == 2)
                            continue;

                    if (!m->get(y - 1, x))
                        if (++countFalse == 2)
                            continue;
                    
                    m->set(y, x, true);
                    center = true;
                    ++removedOne;
                }
            }
        }
        if(removedOne == 0){
            return 0;
        }
    }
    return removedOne;
}

bool MazeRunner::insertBlockIntoVector(vector<MajorBlock*>& blocks, MajorBlock* block, MajorBlock* start){
    unsigned int blockDistanceSquared = (block->i - start->i) * (block->i - start->i) + (block->j - start->j) * (block->j - start->j);
    unsigned int currentBlockDistanceSquared = 0;
    for(unsigned int s = 0; s < blocks.size(); s++){
        int deltaI = blocks[s]->i - start->i;
        int deltaJ = blocks[s]->j - start->j;
        currentBlockDistanceSquared = deltaI * deltaI + deltaJ * deltaJ;
        if(currentBlockDistanceSquared > blockDistanceSquared){
            blocks.insert(blocks.begin(), s, block);
            return true;
        }
        else if(deltaI == block->i - start->i && deltaJ == block->j - start->j){
            blocks[s]->addAssociatedCorner(block->associatedCorners[0]);
            return false;
        }
    }
    blocks.push_back(block);
    return true;
}


/** Takes a boolean grid and identifies the corners of the maze, saves pointers in a vector*/
void MazeRunner::identifyMajorBlocks(BitArray* m) {
    allBlocks.push_back(startBlockPtr);
    allBlocks.push_back(finishBlockPtr);
    
    bool lastTopLeft = false;
    bool lastBottomLeft = false;

    for (unsigned int i = 0; i + 1 < height; ++i) {
        lastTopLeft = m->get(i,0);
        lastBottomLeft = m->get(i + 1,0);
        for (unsigned int j = 0; j + 1 < width; ++j) {
            int countTrue = 0;
            Corner::direction d = Corner::BR;
            if (lastTopLeft) {
                ++countTrue;
            }
            lastTopLeft = m->get(i,j + 1);

            if (lastBottomLeft) {
                lastBottomLeft = m->get(i + 1,j + 1);
                if (++countTrue == 2)
                    continue;
                d = Corner::TR;
            }
            else{
                lastBottomLeft = m->get(i + 1,j + 1);
            }

            if (lastTopLeft) {
                if (++countTrue == 2)
                    continue;
                d = Corner::BL;
            }
            if (lastBottomLeft) {
                if (++countTrue == 2)
                    continue;
                d = Corner::TL;
            }
            if (countTrue == 1) {
                MajorBlock* m = new MajorBlock(i, j, d); //Create a major block for each one
                if(!insertBlockIntoVector(allBlocks, m, startBlockPtr)){//Add this new block to blocks
                    delete m;
                }
            }
        }
    }
    
    while(allBlocks.size() > 36){
        allBlocks.pop_back();
    }
    
    for (unsigned char s = 0; s < allBlocks.size(); s++) { //Loop through all our new blocks
        MajorBlock* m = allBlocks[s];
        m->createConnectionArray(allBlocks.size());
        m->formInitialConnections(allBlocks, s);
    }
}


void MazeRunner::reduceConnections(vector<MajorBlock*>& blocks) {
	for (unsigned char first = 0; first < blocks.size(); ++first) {
    for (unsigned char second = first + 1; second < blocks.size(); ++second) {
      if(blocks.at(first)->connections->get(0, second) == 0){
        continue;
      }
      if (!canSee(blocks.at(first), blocks.at(second))) {
        blocks.at(second)->connections->set(0, first, false);
        blocks.at(first)->connections->set(0, second, false);
			}
		}
	}
}


bool MazeRunner::canSee(const MajorBlock* const &m, const MajorBlock* const &t){
    if (m->i == t->i && m->j == t->j) {
        return false;
    }
    else if (m->i == t->i) {  //horizontal
        int delJ = t->j - m->j;
        int sgnJ = sgn(delJ);
        for (int j = m->j + sgnJ; j != t->j; j += sgnJ) {
            if (map->get(m->i,j))
                return false;
        }
    }
    else if (m->j == t->j) {  //vertical
        int delI = t->i - m->i;
        int sgnI =  sgn(delI);
        for (int i = m->i + sgnI; i != t->i; i += sgnI) {
            if (map->get(i,m->j))
                return false;
        }
    }
    else {  //some diagonal
        Line line = Line(t->i, t->j, m->i, m->j);
        int down = (t->i > m->i) ? 1 : -1;
        int right = (t->j > m->j) ? 1 : -1;

        int i = m->i;
        int j = m->j + right;

        int originalPoint[] = { i,j };

        if (map->get(i,j) || map->get(i + down,j - right)) { //collide near m
            return false;
        }
        else if (map->get(t->i,t->j - right) || map->get(t->i - down,t->j)) {  //collide near j
            return false;
        }
        else { // m and j are far apart
            bool previousStateWasOn = false;
            string previousState = "unknown";
            
            while (i != (t->i - down) || j != (t->j)) { //diagonal doesn't match t's diagonal
                int rightPoint[] = { i       , j + right };
                int downPoint[]  = { i + down, j };
                
                if (!previousStateWasOn && line.onPoint(downPoint)) {
                    previousStateWasOn = true;
                    previousState = "on";
                    
                    
                    i += down;
                    
                    if (map->get(i,j)) {  //if square hits
                        return false;
                        break;
                    }
                }
                else if (!previousStateWasOn && line.onSameSide(downPoint, originalPoint)) {    //try down
                    if(line.moreVertical){
                        if(previousState == "down") verticalStates[0][0] ++;
                        if(previousState == "right") verticalStates[0][1] ++;
                        vCounter[0] ++;
                    }
                    else {
                        if(previousState == "down") horizontalStates[0][0] ++;
                        if(previousState == "right") horizontalStates[0][1] ++;
                        hCounter[0] ++;
                    }
                    previousState = "down";
                    previousStateWasOn = false;
                    
                    i += down;
                    
                    if (map->get(i,j) || map->get(i + down,j - right)) {  //if diagonal hits
                        return false;
                        break;
                    }
                }
                else if (line.onSameSide(rightPoint, originalPoint)) {   //try right
                    if(line.moreVertical){
                        if(previousState == "down") verticalStates[1][0] ++;
                        if(previousState == "right") verticalStates[1][1] ++;
                        vCounter[1] ++;
                    }
                    else {
                        if(previousState == "down") horizontalStates[1][0] ++;
                        if(previousState == "right") horizontalStates[1][1] ++;
                        hCounter[1] ++;
                    }
                    previousStateWasOn = false;
                    previousState = "right";
                    
                    j += right;
                    
                    if (map->get(i,j) || map->get(i + down,j - right)) {  //if diagonal hits
                        return false;
                        break;
                    }
                }
            }
        }
    }
    return true;
}


void MazeRunner::orderConnections(vector<MajorBlock*>& blocks){
    int numChangesMade;
    int numBlocksDiscovered = 0;
    MajorBlock::endBlockPtr->setDistanceFromEnd(0);

    for(unsigned char t = 0; t < blocks.size(); t++){
        MajorBlock*& block = blocks[t];
        for(unsigned char s = t + 1; s < blocks.size(); s++){
            if(block->connections->get(0,s) == false){
                continue;
            }
            
            MajorBlock* const& connection = blocks[s];
            
            ///This provides essential checking that the each block is doubly connected. Run this after any changes to a block's connections.
//                bool blockInConnection = false;
//                for(int x = 0; x < connection->getConnectionsSize(); ++x){
//                    if(connection->getConnectionAt(x)->locale == block->locale){
//                        blockInConnection = true;
//                        break;
//                    }
//                }
//                if(blockInConnection == false){
//                    cout << "Non-reciprocal connection " << endl;
//                    cout << "Block can see connection: " << canSee(block, connection) << endl;
//                    cout << "Connection can see block: " << canSee(connection, block) << endl;
//                    cout << "Block acorn size: " << block->associatedCorners.size() << endl;
//                    cout << "Connection acorn size: " << connection->associatedCorners.size() << endl;
//                }
            
            
            double interDistance = block->getDistance(connection);
            double newBlockDistance = connection->getDistanceFromEnd() + interDistance;
            double newConnectionDistance = block->getDistanceFromEnd() + interDistance;
            

            if(connection->isConnectedToEnd()){
                if(!block->isConnectedToEnd()){
                    block->setDistanceFromEnd(newBlockDistance);
                    block->shorterConnection = connection;
                    ++numChangesMade;
                    ++numBlocksDiscovered;
                }
                else if(newBlockDistance + 0.000001 < block->getDistanceFromEnd()){
                    block->setDistanceFromEnd(newBlockDistance);
                    block->shorterConnection = connection;
                    ++numChangesMade;
                }
                else if(newConnectionDistance + 0.000001 < connection->getDistanceFromEnd()){
                    connection->setDistanceFromEnd(newConnectionDistance);
                    connection->shorterConnection = block;
                    ++numChangesMade;
                }
            }
            else{ // if (!connection->isConnectedToEnd()){
                if(block->isConnectedToEnd()){
                    connection->setDistanceFromEnd(newConnectionDistance);
                    connection->shorterConnection = block;
                    ++numChangesMade;
                    ++numBlocksDiscovered;
                }
            }
        }
    }
}

double MazeRunner::verticalStates[2][2] = {{0,0},{0,0}};
double MazeRunner::horizontalStates[2][2] = {{0,0},{0,0}};
double MazeRunner::vCounter[2] = {0,0};
double MazeRunner::hCounter[2] = {0,0};

bool MazeRunner::solve(){
    int removed = -1;
		while (removed != 0) {
        removed = removeUnlikelies(map);
		}
        
		identifyMajorBlocks(map);
		reduceConnections(allBlocks);
    //debugfloatln("Number of Blocks: ", allBlocks.size());
    
    orderConnections(allBlocks);
    
    //debugfloatln("Start block connections size: ", startBlockPtr->getConnectionsSize());
//    if(startBlockPtr->getConnectionsSize() == 0){
//        //debugln("Start block has no connections, check output image");
//        return false;
//    }
    return true;
	}
