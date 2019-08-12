#include "node.h"
#include <iostream>

using namespace std;

Node::Node()
{
    this->data = NULL;
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
}

Node::Node(char data)
{
    this-> data = data;
}

void Node::setData(char data)
{
    this-> data = data;
}

void Node::printNodeData()
{
    cout << "Data = " << data << endl;
}