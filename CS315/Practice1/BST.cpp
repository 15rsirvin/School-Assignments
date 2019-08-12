#include <iostream>
#include "bst.h"
#include <string>
#include <stdexcept> // for validate tree function
#include <iomanip>

using namespace std;

BST::BST()
{
    root = NULL;
}
int BST::insertNode(Node* node) // made referncing zybooks algorithm
{
    Node* curr = root;
    int depth = 0;
    if(curr == NULL) // if empty
    {
        root = node;
    }
    else
    {
        while(curr != NULL) // loop until end of tree
        {
            depth++;
            if(node->data < curr->data) // inserted data value < current data value 
            {
                if(curr->left == NULL) // insert in empty spot on left
                {
                    curr->left = node;
                    node->parent = curr;
                    curr = NULL;
                }
                else // keep looping
                {
                    curr = curr->left;
                }
            }

            else // inserted data value >= current data value
            {
                if(curr->right == NULL)
                {
                    curr->right = node;
                    node->parent = curr;
                    curr = NULL;
                }
                else
                {
                    curr = curr->right;
                }
            }

        }
    }
    return depth;
}

void BST::removeNode(Node* root, char data) // Made referencing zybooks algorithm. 
{

    Node* cur = root;
    while (cur != NULL)
    {
        if(cur->data == data) // if you found the data
        {
            if(!(cur->left) && !(cur->right)) // if there are no children of node
            {
                if(!(cur->parent)) // if there is no parent
                {
                    this->root = NULL;
                }
                else if(cur->parent->left == cur) 
                {
                    cur->parent->left = NULL;
                    cur->parent = NULL;
                    
                }
                else
                {
                    cur->parent->right = NULL;
                    cur->parent = NULL;
                }
            }
            else if(cur->left && !(cur->right)) // if there is a left child
            {
                if(!(cur->parent))
                {
                    this->root = cur->left; 
                    cur->left->parent = NULL; 
                    cur->left = NULL;
                }
                else if(cur->parent->left == cur)
                {
                    cur->parent->left = cur->left;
                    cur->left->parent = cur->parent;
                    cur->parent = NULL;
                }
                else
                {
                    cur->parent->right = cur->left;
                    cur->left->parent = cur->parent;
                    cur->parent = NULL;
                }
            }
            else if(!(cur->left) && cur->right) // if there is a right child
            {
              if(!(cur->parent))
                {
                    this->root = cur->right; 
                    cur->right->parent = NULL; 
                }
                else if(cur->parent->left == cur)
                {
                    cur->parent->left = cur->right;
                    cur->right->parent = cur->parent;
                    cur->parent = NULL;
                }
                else
                {
                    cur->parent->right = cur->right;
                    cur->right->parent = cur->parent;
                    cur->parent = NULL;
                }  
            }
            else // if there are two children
            {
                Node* suc = cur->right;
                while(suc->left != NULL)
                {
                    suc = suc->left;
                }
                cur->data = suc->data;
                removeNode(cur->right,suc->data);
            }
            return; // if you don't find value return to quit function
        }
        else if(cur->data < data) // if you havent found it and the current nodes data is less than what you are looing for
        {
            cur = cur->right;
        }
        else    // if you havent found the data but the value is greater than what you are looking for
        {
            cur = cur->left;
        }
    }
    return; // you didn't find anything, return to quit function


}
void BST::printInOrder(Node* root) const 
{
    if(root == NULL) //base case, there is no node
    {
        return;
    }
    else
    {
        printInOrder(root->left); // print all nodes to left recursivly
        cout << root->data << " ";  // print this node's data
        printInOrder(root->right); // print all nodes to the right recursively
    }
}
Node* BST::getRoot() const
{
    return root;
}
int BST::getSize(Node* root) const
{
    int count = 1;
    if(root == NULL) // if empty return 0
    {
        return 0;
    }
    else // else recursivly add 1 to count for every node found and return count
    {
        count += getSize(root->left) + getSize(root-> right);

        return count;
    }

}
int BST::findMin() const
{
    Node* curr = root;
    if(curr == NULL)
    {
        return -1; // if empty return -1 for error
    }
    else
    {
        while(curr->left != NULL) // loop to leftmost element of tree
        {
            curr = curr->left;
        } 
        
        return curr->data; // return data of leftmost element
    }
}
int BST::findMax() const
{
    Node* curr = root;
    if(curr == NULL) // if empty return -1 for error
    {
        return -1;
    }
    else
    {
        while(curr->right != NULL) // loop to right most element of tree
        {
            curr = curr->right;
        } 
        
        return curr->data; // return data of rightmost element
    }
}

// For validate tree function below
void assert(bool condition, string message) {
    if (!condition) {
        throw runtime_error(message);
    }
}

//For error testing, this function validates that the tree is linked properly and was used for testing/bug fixing after hours of frustration on BST remove. Not currently being called in program.
void BST::validateTree(Node* root)
{
    
    if(root == NULL) // if last node
    {
        return; 
    }
    // Notice that this doesn't check if the first nodes parent is NULL

    if (root->left) { // if there is a left child, call the function on the left child
        string message = "Node " + to_string(root->left->data) + " parent did not equal" + to_string(root->data) + "was " + to_string(root->left->parent->data);
        assert(root->left->parent == root, message);
        validateTree(root->left);
    }

    if (root->right) { //if there is a right child, call the function on the right child
        string message = "Node " + to_string(root->right->data) + " parent did not equal" + to_string(root->data) + "was " + to_string(root->right->parent->data);
        assert(root->right->parent == root, message);
        validateTree(root->right);
    }

}

void BST::Print2D(Node* node, int space)
{

    if(node == NULL)
    {
        // Base Case, Do nothing
    }
    else
    {
        Print2D(node->right, space +10);

        cout << endl;

        for(int i = 0; i < space; i++)
        {
            cout << " ";
        }

        cout << node->data << endl;

        Print2D(node->left, space + 10);


    }
}
