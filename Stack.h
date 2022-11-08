//
//  Stack.h
//  ArduinoMazeSolver
//
//  Created by Preston Raab on 11/5/22.
//  Copyright © 2022 Preston Raab. All rights reserved.
//

#ifndef Stack_h
#define Stack_h


template <typename T>
class stack{
    struct Node {
        Node(T data): data(data), next(nullptr){}
        ~Node() {
            if(next != nullptr)
                delete next;
        }
        T data;
        Node* next;
    };
    
public:
    
    stack(void): head(nullptr){
        
    }
    ~stack(void) {
        delete head;
    }
    
    bool contains(T value){
        for(Node* node = head; node != nullptr;){
            if(node->data == value){
                return true;
            }
            node = node->next;
        }
        return false;
    }

    /** Insert Node(value) at beginning of linked list */
     void push(T value) {
         if(contains(value)){
             return;
         }
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
    }
    
    /** Insert Node(value) at end of linked list */
     void insertTail(T value) {
         if(contains(value)){
             return;
         }
         Node* temp = head;
         if(temp == nullptr){
             head = new Node(value);
         }
         else{
             while(temp->next != nullptr){
                 temp = temp->next;
             }
             temp->next = new Node(value);
         }
    }
    
    T top(){
        return at(0);
    }
    
    void pop(){
        remove(head->data);
    }

    /*
    insertAfter

    A node with the given value should be inserted immediately after the
    node whose value is equal to insertionNode.

    A node should only be added if the node whose value is equal to
    insertionNode is in the list. Do not allow duplicate values in the list.
    */
     void insertAfter(T value, T insertionNode) {
         if(contains(value)){
             return;
         }
         for(Node* node = head; node != nullptr;){
             if(node->data == insertionNode){
                 if(node->next == nullptr){
                     node->next = new Node(value);
                 }
                 else{
                     Node* next = node->next;
                     node->next = new Node(value);
                     node->next->next = next;
                     return;
                 }
             }
             node = node->next;
         }
    }
    
    /*
    remove

    The node with the given value should be removed from the list.

    The list may or may not include a node with the given value.
    */
     void remove(T value) {
         if(contains(value) == false){
             return;
         }
        Node* previous = nullptr;
        for(Node* node = head; node != nullptr;){
            if(node->data == value){
                if(previous == nullptr){
                    head = node->next;
                    node->next = nullptr;
                    delete node;
                    node = head;
                    return;
                }
                previous->next = node->next;
                node->next = nullptr;
                delete node;
                return;
            }
            previous = node;
            node = node->next;
        }
    }
    
    T at(int index) {
        int count = 0;
        for(Node* node = head; node!=nullptr; node=node->next){
            count++;
        }
        if(index >= count || index < 0){
            std::out_of_range ex = std::out_of_range("out_of_range");
            throw ex;
        }
        
        Node* node = head;
        for(count = 0; count < index; count++){
            node = node->next;
        }
        return node->data;
    }


    /** Return true if linked list size == 0 */
     bool empty(void) const {
        return head == nullptr;
    }

    

    /** Remove all Nodes from linked list */
     void clear() {
        delete head;
        head = nullptr;
    }

    /** Return the number of nodes in the linked list */
     int size(){
        int numberOfNodes = 0;
         
         for(Node* node = head; node != nullptr; node = node->next){
             numberOfNodes++;
        }
        return numberOfNodes;
    }

private:
    Node* head;
};

#endif /* Stack_h */
