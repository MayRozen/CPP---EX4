/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <stack>
#include <iostream>
#include "node.hpp"

using namespace std;

template<typename T, size_t K = 2> // Define the amount of children to be 2 as a default

class Tree {
public:
    Node<T>* root; // The tree is a vector of pointers to the nodes

    Tree() : root(nullptr) {} // Firsofall, the root will be null

    void add_root(Node<T>& node);
    void add_sub_node(Node<T>& parent, Node<T>& child);

    

    // Overload the output stream operator to print the tree
    friend ostream& operator<<(ostream& os, const Tree<T, K>& tree);
};

#endif // TREE_HPP