//*****************************************************************************************
// Filename: tree_node.h
// Authors: Hunter Smith and Johnathan Reilly
// Brief: contains the node struct
// ****************************************************************************************
#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct node{
	string name;
	vector<node*> children;
    int weight;
};

void insert(node*& root, string n, int w, string parent){
    if(root==nullptr || n == "root"){
        root = new node;
        root -> name = n;
        root -> weight = w;
        return;
    }
    if(root->name == parent){
        node* tmp = new node;
        tmp->name = n;
        tmp->weight = w;
        //need to add based on weight
        for(vector<node*>::iterator it = root->children.begin(); it < root->children.end(); ++it){
            if((*it)->weight > w){
                root->children.insert(it, tmp);
                return;
            }
        }
        root->children.push_back(tmp);
        return;
    }
    for(int i = 0; i < root->children.size(); i++){
        insert(root->children[i], n, w, parent);
    }
}

void printTree(node*& root){
    cout << "<" << root->name << "," << root->weight << ">";
    for(vector<node*>::iterator it = root->children.begin(); it < root->children.end(); ++it){
        printTree(*it);
    }
}