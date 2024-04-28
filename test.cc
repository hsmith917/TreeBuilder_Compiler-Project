#include "tree_node.h"
#include <string>

using namespace std;

int main(){

    node* root = nullptr;
    insert(root, "root", 0, "");
    insert(root, "A", 1, "root");
    //insert(root, "B", 0, "root");
    for(int i = 0; i<5; i++){
        insert(root, "A"+to_string(i), 1+i, "A");
    }
    insert(root, "C", 7, "root");

    printTree(root);

    return 0;
};