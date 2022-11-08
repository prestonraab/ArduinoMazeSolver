//
//  MajorBlock.h
//  MazeSolver
//
//  Created by Preston Raab on 2/10/20.
//  Copyright © 2020 Preston Raab. All rights reserved.
//

#ifndef MajorBlock_h
#define MajorBlock_h

#include "Corner.h"
#include "vector.h"
#include "AVL.h"


#ifndef AVL_h
#define AVL_h
#include "MajorBlock.h"
#include "Node.h"
#include "Stack.h"

class MajorBlock;

class AVL{
public:
    Node* root;
    int mySize;

    AVL();
    ~AVL();
    
    class iterator{
        stack<Node*> pile;
    public:
        iterator(Node* my_root){
            Node* current = my_root;
            while(current != nullptr){
                pile.push(current);
                current = current->left;
            }
        }
        
        Node* current(){
            return pile.top();
        }
        
        void next(){
            Node* curr = pile.top()->right;
            pile.pop();
            while(curr != NULL){
                pile.push(curr);
                curr = curr->left;
            }
        }
        
        bool isEnd(){
            return pile.size() != 0;
        }
    };
    
    iterator begin();
    
    
    /*
    * Returns the root node for this tree
    *
    * @return the root node for this tree.
    */
    Node* getRootNode() const;
    
    size_t size() const;


    /*
    * Attempts to add the given int to the AVL tree
    * Rebalances the tree if data is successfully added
    *
    * @return true if added
    * @return false if unsuccessful (i.e. the int is already in tree)
    */
    bool add(MajorBlock* data);

    /*
    * Attempts to remove the given int from the AVL tree
    * Rebalances the tree if data is successfully removed
    *
    * @return true if successfully removed
    * @return false if remove is unsuccessful(i.e. the int is not in the tree)
    */
    bool remove(MajorBlock* data);
    
    

    void rotate_right(Node*& local_root);

    void rotate_left(Node*& local_root);


    void restoreBalance(Node*& n);

    Node* find(Node* local_root, int data);
    
    Node* find(int data);

    bool edit(Node*& n, MajorBlock* data, bool insert);

    void RKO(Node*& n, MajorBlock* data);

    void sniperAttack(Node* local_root, Node*& rightmost, MajorBlock* data);

    /*
    * Removes all nodes from the tree, resulting in an empty tree.
    */
    void clear();
    
};



#endif /* AVL_h */


using std::cout;
using std::endl;

class AVL;

class MajorBlock: public HasLocale {
private:
    double distanceFromEnd;
    
public:
    AVL* connections;
    MajorBlock* shorterConnection;
	int i;
	int j;
    int locale;
    int popularity;
    
    
    
    vector<Corner> associatedCorners;

    typedef vector<MajorBlock*>::iterator MBIterator;

    MajorBlock(Corner const &c);
    
    void addAssociatedCorner(Corner const &c);
    
    // We ask the question, is m1 < m2 with respect to the reference block
    struct MajorBlockDistanceComparator {
        const MajorBlock* const reference;
        MajorBlockDistanceComparator(const MajorBlock* const &reference) : reference(reference){}
        
        //Priority needs to be given to blocks that are closer to the end than the reference.
        //Of those, we sort the blocks on the shortest path first.

        bool operator ()(const MajorBlock* const &m1, const MajorBlock* const &m2) {
            if(m1->distanceFromEnd > reference->getDistanceFromEnd() && m2->getDistanceFromEnd() > reference->getDistanceFromEnd()){
                return m1->distanceFromEnd < m2->distanceFromEnd;
            }
            else if (m2->distanceFromEnd > reference->getDistanceFromEnd()){
                return true;
            }
            else if (m1->distanceFromEnd > reference->getDistanceFromEnd()){
                return false;
            }
            else{
                return m1->distanceFromEnd + reference->getDistance(m1) < m2->distanceFromEnd + reference->getDistance(m2);
            }
        }
    };
    
    struct MajorBlockPointerLocationComparator {
        MajorBlockPointerLocationComparator(){};
        
        bool operator ()(MajorBlock* const &m1, MajorBlock* const &m2) {
            return m1->locale < m2->locale;
        }
    };
    
    struct MajorBlockLocationComparator {
        MajorBlockLocationComparator(){};
        
        bool operator ()(MajorBlock* const &m1, MajorBlock const &m2) const {
            return m1->locale < m2.locale;
        }
    };
    
    void addConnection(MajorBlock* const &m);
    
    bool isConnectedToEnd();
    
    double getDistance(const MajorBlock* const &other) const;
    
    size_t getConnectionsSize() const;
    
    double getDistanceFromEnd() const;
    
    void setDistanceFromEnd(double distance);
    
    void clearConnections();
    
    void replaceConnections(vector<MajorBlock*> &otherConnections);
    
    static MajorBlock* startBlockPtr;
    static MajorBlock* endBlockPtr;
    static long mapWidth;
	
    
    static vector<MajorBlock*> findMajorBlocks(vector<Corner> &corners, Corner &start, MajorBlock &finish) {
        static MajorBlockPointerLocationComparator comp;
        AVL blocks;
        vector<MajorBlock*> vectorBlocks;
        startBlockPtr = new MajorBlock(start);
        endBlockPtr = new MajorBlock(finish);
        blocks.add(startBlockPtr);
        blocks.add(endBlockPtr);
        vectorBlocks.push_back(startBlockPtr);
        vectorBlocks.push_back(endBlockPtr);
        
        startBlockPtr->connections->add(endBlockPtr);

        unsigned long size = corners.size();
        unsigned percentile = (unsigned)size / 50 + 1;

        for (size_t i = 0; i < size; ++i) {  //Loop through all corners
            MajorBlock* m = new MajorBlock(corners[i]); //Create a major block for each one
            auto find = blocks.find(m->locale);
            if(find != nullptr){  //Search for an equivalent block
                (*find).getData()->addAssociatedCorner(corners[i]);  //If found, add this corner to that block.
                cout << "Assos corners size: " << (*find).getData()->associatedCorners.size() << endl;
                delete m;
            }
            else{ //If not found
                startBlockPtr->addConnection(m);
                m->connections->add(endBlockPtr);
                blocks.add(m); //Add this new block to blocks
                vectorBlocks.push_back(m);
            }
        }
        
        for (AVL::iterator startIt = blocks.begin(); !startIt.isEnd(); startIt.next()) { //Loop through all our new blocks
            MajorBlock* m = **startIt.current();
            formInitialConnections(blocks, m, corners);
            //std::sort(m->connections.begin(), m->connections.end());
        }
        return vectorBlocks;
    }



    static void formInitialConnections(AVL &allBlocks, MajorBlock* &m, vector<Corner> const &corners)
    {
        for(Corner associatedCorner : m->associatedCorners){ //Loop through each corner of the block (1 or 2)
            if(m->associatedCorners.size() != 1){
                cout << m->associatedCorners.size() << endl;
            }
            
            for (Corner c : corners)
            {
                if(associatedCorner.isPossibleConnection(c)){
                    MajorBlock connectBlock = MajorBlock(c);
                    auto location = allBlocks.find(connectBlock.locale);
                    m->addConnection(**location);
                }
            }
        }
    }

    bool operator==(MajorBlock& other) const;
    bool operator<(MajorBlock& other) const;
    bool operator<(const MajorBlock& other) const;
    std::string toString() const;
    
    friend std::ostream& operator<<(std::ostream &o, const MajorBlock &m){
        o << m.toString();
        return o;
    }
};


#endif /* MajorBlock_h */
