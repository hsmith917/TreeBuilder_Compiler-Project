#include "tree_node.h"

using namespace std;

int main(){

    node* root = nullptr;
    insert(root, "root", 0, "");
    insert(root, "A", 1, "root");
    insert(root, "B", 0, "root");

    printTree(root);

    return 0;
};