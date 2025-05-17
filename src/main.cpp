#include "rbtreemap.h"

int main() {
    RBTreeMap<int> tree;
    /*tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(7);
    for(int i=0; i<100; i++) {
        tree.insert(i);
    }

    tree.remove(10);
    for(int i=0; i<100; i=i+2) {
        tree.remove(i);
    }

    std::cout<<(tree.search(11) ? "Found" : "Not found")<<std::endl;
    std::cout<<(tree.search(10000) ? "Found" : "Not found")<<std::endl;*/

    tree.insert(10);
    tree.insert(10);
    tree.insert(10);
    tree.insert(10);
    tree.insert(10);
    tree.remove(10);

    tree.navigate_tree();

}