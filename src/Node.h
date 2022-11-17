//
//  Node.h
//  AVL
//
//  Created by Preston Raab on 11/3/22.
//

#ifndef Node_h
#define Node_h
#include "MajorBlock.h"
#include "ArduinoSTL-master/vector.h"

class MajorBlock;

class Node{
public:
    MajorBlock* data;
    Node* left;
    Node* right;

    Node(MajorBlock* data):data(data) {
        left = nullptr;
        right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
    }

    /*
    * Returns the data stored in this node
    *
    * @return the data stored in this node.
    */
    MajorBlock* getData() const{
        return data;
    }
    
    const MajorBlock* operator->() const {
        return getData();
    }

    MajorBlock*& operator*() {
        return data;
    }

    /*
    * Returns the left child of this node or null if empty left child.
    *
    * @return the left child of this node or null if empty left child.
    */
    Node* getLeftChild() const{
        return left;
    }

    /*
    * Returns the right child of this node or null if empty right child.
    *
    * @return the right child of this node or null if empty right child.
    */
    Node* getRightChild() const{
        return right;
    }

    /*
    * Returns the height of this node. MajorBlock*he height is the number of nodes
    * along the longest path from this node to a leaf.  While a conventional
    * interface only gives information on the functionality of a class and does
    * not comment on how a class should be implemented, this function has been
    * provided to point you in the right direction for your solution.  For an
    * example on height, see page 448 of the text book.
    *
    * @return the height of this tree with this node as the local root.
    */
    int getHeight(){
        if(left == nullptr && right == nullptr){
            return 0;
        }
        if(left == nullptr){
            return 1 + right->getHeight();
        }
        if(right == nullptr){
            return 1 + left->getHeight();
        }
        int left_height = left->getHeight();
        int right_height = right->getHeight();
        int result = 1 + (left_height > right_height ? left_height : right_height);
        return result;
    }

    int getBalance(){
        int left_height = left == nullptr? -1 : left->getHeight();
        int right_height = right == nullptr? -1 : right->getHeight();
        return right_height - left_height;
    }
};

#endif /* Node_h */
