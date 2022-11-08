//
//  AVL.h
//  AVL
//
//  Created by Preston Raab on 11/3/22.
//

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
    
    MajorBlock* getLeftmost();
    
    size_t size() const;
    
    void resort();


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
