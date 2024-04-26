/**
 * @file: node.h
 * @author: Johnathan Reilly and Hunter Smith
 * @date: 4/18/24
 * @brief: This is the header file for the node class for a binary tree. 
*/
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
    if(root==nullptr){
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