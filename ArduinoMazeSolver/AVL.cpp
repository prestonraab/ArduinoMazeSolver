//
//  AVL.cpp
//  ArduinoMazeSolver
//
//  Created by Preston Raab on 11/5/22.
//  Copyright © 2022 Preston Raab. All rights reserved.
//

#include "MajorBlock.h"

AVL::AVL(){
    root = nullptr;
    mySize = 0;
}
AVL::~AVL(){
    delete root;
}

AVL::iterator AVL::begin(){
    return iterator(root);
}


/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
Node* AVL::getRootNode() const{
    return root;
}

size_t AVL::size() const{
    return mySize;
}

MajorBlock* AVL::getLeftmost(){
    Node* local_root = root;
    while(local_root->left != nullptr){
        local_root = local_root->left;
    }
    return local_root->data;
}

void AVL::resort(){
    
}

/*
* Attempts to add the given int to the AVL tree
* Rebalances the tree if data is successfully added
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(MajorBlock* data){
    bool edited_it = edit(root, data, true);
    if(edited_it)
        mySize++;
    return edited_it;
}

/*
* Attempts to remove the given int from the AVL tree
* Rebalances the tree if data is successfully removed
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(MajorBlock* data){
    bool edited_it = edit(root, data, false);
    if(edited_it)
        mySize--;
    return edited_it;
}



void AVL::rotate_right(Node*& local_root) {
    Node* temp = local_root->left;
    local_root->left = temp->right;
    temp->right = local_root;
    local_root = temp;
}

void AVL::rotate_left(Node*& local_root) {
    Node* temp = local_root->right;
    local_root->right = temp->left;
    temp->left = local_root;
    local_root = temp;
}


void AVL::restoreBalance(Node*& n){
    int balance = n->getBalance();
    
    if(balance == -2){
        if(n->left != nullptr && n->left->getBalance() == 1){
            rotate_left(n->left);
            rotate_right(n);
        }
        else{
            rotate_right(n);
        }
    }
    else if(balance == 2){
        if(n->right != nullptr && n->right->getBalance() == -1){
            rotate_right(n->right);
            rotate_left(n);
        }
        else{
            rotate_left(n);
        }
    }
}


Node* AVL::find(int data){
    if(root == nullptr){
        return nullptr;
    }
    else if(root->data->locale == data){
        return root;
    }
    else{
        return find((data < root->data->locale)? root->left : root->right, data);
    }
}

bool AVL::edit(Node*& n, MajorBlock* data, bool insert){
    if(n == nullptr){
        if(insert){
            n = new Node(data);
            return true;
        }
        else
            return false;
    }
    else if(n->data->locale == data->locale){
        if(insert)
            return false;
        else{
            RKO(n, data);
            return true;
        }
    }
    else{
        bool edited_it = edit((data < n->data)? n->left : n->right, data, insert);
        if(edited_it)
            restoreBalance(n);
        return edited_it;
    }
}

void AVL::RKO(Node*& n, MajorBlock* data){
    Node** local_root = &n;
    if((*local_root)->left == nullptr && (*local_root)->right == nullptr){ //No children
        delete *local_root;
        *local_root = nullptr;
    }
    else if((*local_root)->left != nullptr && (*local_root)->right != nullptr){ //MajorBlock*he node we are trying to delete has both a left and right child
        sniperAttack(*local_root, (*local_root)->left, data);
        restoreBalance(*local_root);
    }
    else{
        Node* temp;
        if((*local_root)->left == nullptr){ //Node has only right child
            temp = (*local_root)->right;
            (*local_root)->right = nullptr;
        }
        else { //Node has only left child
            temp = (*local_root)->left;
            (*local_root)->left = nullptr;
        }
        delete *local_root;
        *local_root = temp;
    }
}

void AVL::sniperAttack(Node* local_root, Node*& rightmost, MajorBlock* data){
    if((rightmost)->right != nullptr){
        sniperAttack(local_root, (rightmost)->right, data);
        restoreBalance(rightmost);
        return;
    }
    
    local_root->data = (rightmost)->data;
    
    if((rightmost)->left == nullptr){
        delete rightmost;
        rightmost = nullptr;
    }
    else{
        Node* temp = (rightmost)->left;
        (rightmost)->left = nullptr;
        delete rightmost;
        rightmost = temp;
    }
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear(){
    delete root;
    root = nullptr;
    mySize = 0;
}


Node* AVL::find(Node* local_root, int data){
    if(local_root == nullptr){
        return nullptr;
    }
    else if(local_root->data->locale == data){
        return local_root;
    }
    else{
        return find((data < local_root->data->locale)? local_root->left : local_root->right, data);
    }
}
