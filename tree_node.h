/**
 * @file: node.h
 * @author: Johnathan Reilly and Hunter Smith
 * @date: 4/18/24
 * @brief: This is the header file for the node class for a binary tree. 
*/
using namespace std;

class node{
    public:
        /**
         * node - constructor for the node class.
        */
        node();

        /**
         * left - accessor for the left node
         * @return - the left node
        */
        node* left(){return leftNode;}

        /**
         * right - accessor for the right node
         * @return - the right node
        */
        node* right(){return rightNode;}

        /**
         * setLeft - setting function for the left node
         * @param tmp - node to be set
        */
        void setLeft(node* tmp){leftNode = tmp;}

        /**
         * setRight - setting functioni for the right node
         * @param tmp - node to be set
        */
        void setRight(node* tmp){rightNode = tmp;}

        /**
         * isLeaf - returns true if the current node is a leaf node
         * @return - true if left and right nodes are nullptr
        */
        bool isLeaf(){return leftNode == nullptr && rightNode == nullptr;}
    
    private:
        node* leftNode;
        node* rightNode;
};

node::node(){
    leftNode = nullptr;
    rightNode = nullptr;
}