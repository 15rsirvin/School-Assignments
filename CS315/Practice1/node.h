#ifndef node_h
#define node_h
#include <string>

class Node 
{
    public: 
        Node();
        Node(char data);
        void setData(char data);
        void printNodeData();
        friend class BST;

    private: 
        char data;
        Node* left;
        Node* right;
        Node* parent;
};
#endif