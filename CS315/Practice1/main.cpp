#include <iostream>
#include <vector>
#include "node.h"
#include "bst.h"

using namespace std;

int main()
{
    string preOrder;
    string postOrder;

    cin >> preOrder >> postOrder;


}

void buildTree(string preOrder, string postOrder, BST tree)
{
    if (preOrder.length() == 0 || postOrder.length() == 0)
        return ;

    else
    {
        char curr = preOrder[0];

        Node* node = new Node;
        node->setDate;
        tree.insertNode();


    }
    
}