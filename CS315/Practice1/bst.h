#ifndef BST_h
#define BST_h

#include "node.h"

class BST 
{
    public:
        // Part I 
        BST();
        int insertNode(Node* node);
        void removeNode(Node* root, char data);
        void printInOrder(Node* root) const;
        Node* getRoot() const;
        int getSize(Node* root) const;
        int findMin() const;
        int findMax() const;

        //Part II
        void Print2D(Node* node, int space);

    private: 
        Node* root;

        // My private helper function for checking BST Remove. 
        
        void validateTree(Node* root);             // used for testing, but not currently being called by anything


        


};

#endif