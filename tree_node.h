/**
 * @file: node.h
 * @author: Johnathan Reilly and Hunter Smith
 * @date: 4/18/24
 * @brief: This is the header file for the node class for a binary tree. 
*/
#include <string>
#include <climits>
using namespace std;

class node{
    public:
        /**
         * node - constructor for the node class.
        */
        node(string n = "", int w = INT_MAX, string p = "", node* pn = nullptr, node* l = nullptr, node* r = nullptr);

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

        /** weight - returns the value int contained in the node.
		 * @return - int in the weight field
		 */
		int weight()const {return weight_field;}

		/** set_weight - sets weight field to the int parameter.
		 * @param - int to be put in the weight field.
		 */
		void set_weight(int item) {weight_field = item;}

        /** name - accessor for name
         * @return - name of the node
        */
        string name()const {return node_name;}

        /** set_name - sets name
         * @param - string to be put in name
        */
        void set_name(string n) {node_name = n;}

        /** get_parent_name - accessor for parent name
         * @return - name of the node
        */
        string get_parent_name()const {return node_name;}

        /** set_parent_name - sets parent name
         * @param - string to be put in parent name
        */
        void set_parent_name(string pn) {parent_name = pn;}

        /** parent - accessor for parent node
         * @return - parent node
        */
        node* parent() {return parent_node;}

        /** set_parent - sets parent node
         * @param - parent node to be set
        */
        void set_parent(node* p) {parent_node = p;}
    
    private:
        string node_name;
        int weight_field;
        string parent_name;
        node* parent_node;
        node* leftNode;
        node* rightNode;
};

node::node(string n, int w, string p, node* pn, node* l, node* r){
    node_name = n;
    weight_field = w;
    parent_name = p;
    parent_node = pn;
    leftNode = l;
    rightNode = r;
}

void buildnode(string n, int w, string p){
    // n is node's name
    // w is node's weight
    // p is node's parent
};