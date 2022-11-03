#include "MazeRunner.h"

#define leftc ((unsigned int)upperColBound - 1) -
#define upc ((unsigned int)upperColBound - 1) -

/** Useful for tight mazes with dead ends*/
int MazeRunner::removeUnlikelies(vector<vector<bool> >& m) {
    int removedOne = 0;
    unsigned long height = m.size();
    unsigned long width = m[0].size();
    
    //Works fast in one direction, so alternate in a circle.
    enum direction {right=0, down=1, up=2, left=3};
    
    direction d = right;
    
    bool center = false;
    bool nextCenter = false;
    bool lastCenterWasFalse = false;
    
    unsigned long upperRowBound = 0;
    unsigned long upperColBound = 0;
    for(unsigned int circle = 0; circle < 4; ++circle){
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
        }
        for (unsigned int row = 1; row + 1 < upperRowBound; ++row) {
            switch(d){
                case right:
                    center = m[row][0];
                    nextCenter = m[row][1];
                    break;
                case left:
                    center = m[row][leftc 0];
                    nextCenter = m[row][leftc 1];
                    break;
                case down:
                    center = m[0][row];
                    nextCenter = m[1][row];
                    break;
                case up:
                    center = m[upc 0][row];
                    nextCenter = m[upc 1][row];
            }
            
            for (unsigned int col = 1; col + 1 < upperColBound; ++col) {
                unsigned int x = 0;
                unsigned int y = 0;
                lastCenterWasFalse = !center;
                center = nextCenter;
                switch(d){
                    case right:
                        y = row;
                        x = col;
                        nextCenter = m[row][col + 1];
                        break;
                    case left:
                        y = row;
                        x = leftc (col);
                        nextCenter = m[row][leftc (col+1)];
                        break;
                    case down:
                        y = col;
                        x = row;
                        nextCenter = m[col + 1][row];
                        break;
                    case up:
                        y = upc (col);
                        x = row;
                        nextCenter = m[upc (col + 1)][row];
                        break;
                }
                
                if (!center && !(y == start.i && x == start.j) && !(y == finish.i && x == finish.j)) {
                    int countFalse = 0;
                    
                    if (!m[y][x - 1])
                        ++countFalse;

                    if (!m[y][x + 1])
                        if (++countFalse == 2)
                            continue;

                    if (!m[y + 1][x])
                        if (++countFalse == 2)
                            continue;

                    if (!m[y - 1][x])
                        if (++countFalse == 2)
                            continue;
                    
                    m[y][x] = true;
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

/** Takes a boolean grid and identifies the corners of the maze*/
void MazeRunner::identifyCorners(vector<vector<bool> > m, vector<Corner>& c) {
    int percentile = height / 20 + 1;

    bool lastTopLeft = false;
    bool lastBottomLeft = false;

    for (int i = 0; i + 1 < height; ++i) {
        lastTopLeft = m[i][0];
        lastBottomLeft = m[i + 1][0];
        for (int j = 0; j + 1 < width; ++j) {
            int countTrue = 0;
            Corner::direction d = Corner::BR;
            if (lastTopLeft) {
                ++countTrue;
            }
            lastTopLeft = m[i][j + 1];

            if (lastBottomLeft) {
                lastBottomLeft = m[i + 1][j + 1];
                if (++countTrue == 2)
                    continue;
                d = Corner::TR;
            }

            lastBottomLeft = m[i + 1][j + 1];

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
                Corner corner = Corner(i, j, d);
                c.push_back(corner); //Add corner to the end of the list
            }
        }
        if (i % percentile == 0)
            cout << i * 100.0 / height << "%" << endl;
    }
}

static double verticalStates[2][2] = {{0,0},{0,0}};
static double horizontalStates[2][2] = {{0,0},{0,0}};
static double vCounter[2] = {0,0};
static double hCounter[2] = {0,0};


void MazeRunner::reduceConnections(vector<MajorBlock*>& blocks) {
	unsigned long size = blocks.size();
	unsigned percentile = (unsigned)(size / 100 + 1);
    
    MajorBlock::MajorBlockPointerLocationComparator comp;
    
	for (size_t x = 0; x < size; ++x) {
		MajorBlock* &m = blocks.at(x);
		
		vector<MajorBlock*> newConnections;
		
		for (size_t y = 0; y < m->getConnectionsSize(); ++y) {
			MajorBlock* const& t = m->getConnectionAt(y);
			
			if (canSee(m, t)) {
                if(!binary_search(t->connections.begin(), t->connections.end(), m, comp)){
                    vector<MajorBlock*>::iterator foundBlock = lower_bound(t->connections.begin(), t->connections.end(), m, comp);
                    t->connections.insert(foundBlock, m);
                }
				newConnections.push_back(t);
                //cout << "yes: (" << m->i << "," << m->j << ") (" << t->i << "," << t->j << ")" << endl;
			}
            else{
                //cout << "no: (" << m->i << "," << m->j << ") (" << t->i << "," << t->j << ")" << endl;
            }
		}
        
        
        m->replaceConnections(newConnections);
		
		if (x % percentile == 0) {
			cout << x * 100 / size << " %" << endl;
		}
	}
    
    cout << "LOOK AT THIS  LOOK AT THIS  LOOK AT THIS  LOOK AT THIS  " << endl;
    cout << "More Vertical" << endl;
    for(int h = 0; h < 2; h++){
        for(int k = 0; k < 2; k++){
            verticalStates[h][k] /= vCounter[h] ++;;
            cout << verticalStates[h][k] << " ";
        }
        cout << endl;
    }
    cout << "More Horizontal" << endl;
    for(int h = 0; h < 2; h++){
        for(int k = 0; k < 2; k++){
            horizontalStates[h][k] /= hCounter[h] ++;;
            cout << horizontalStates[h][k] << " ";
        }
        cout << endl;
    }
    cout << "LOOK AT THIS  LOOK AT THIS  LOOK AT THIS  LOOK AT THIS  " << endl;
}

bool MazeRunner::canSee(const MajorBlock* const &m, const MajorBlock* const &t){
    if (m->i == t->i && m->j == t->j) {
        return false;
    }
    else if (m->i == t->i) {  //horizontal
        int delJ = t->j - m->j;
        int sgnJ = sgn(delJ);
        for (int j = m->j + sgnJ; j != t->j; j += sgnJ) {
            if (map[m->i][j])
                return false;
        }
    }
    else if (m->j == t->j) {  //vertical
        int delI = t->i - m->i;
        int sgnI =  sgn(delI);
        for (int i = m->i + sgnI; i != t->i; i += sgnI) {
            if (map[i][m->j])
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

        if (map[i][j] || map[i + down][j - right]) { //collide near m
            return false;
        }
        else if (map[t->i][t->j - right] || map[t->i - down][t->j]) {  //collide near j
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
                    
                    if (map[i][j]) {  //if square hits
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
                    
                    if (map[i][j] || map[i + down][j - right]) {  //if diagonal hits
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
                    
                    if (map[i][j] || map[i + down][j - right]) {  //if diagonal hits
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
    do{
        numChangesMade = 0;
        for(MajorBlock*& block : blocks){
            for(int c = 0; c < block->getConnectionsSize(); ++c){
                
                MajorBlock* const& connection = block->getConnectionAt(c);
                
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
                    else if(newBlockDistance + 0.00000001 < block->getDistanceFromEnd()){
                        block->setDistanceFromEnd(newBlockDistance);
                        block->shorterConnection = connection;
                        ++numChangesMade;
                    }
                    else if(newConnectionDistance + 0.00000001 < connection->getDistanceFromEnd()){
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
        cout << "Num Changes: " << numChangesMade << " Num Discovered: " << numBlocksDiscovered << "/" << blocks.size() - 1 << endl;
    }while(numChangesMade > 0);
    
    for(MajorBlock*& block : blocks){
        MajorBlock::MajorBlockDistanceComparator comp(block);
        sort(block->connections.begin(), block->connections.end(), comp);
        
    }
}
