/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <stack>
#include <iostream>
#include "node.hpp"
#include "tree.hpp"

using namespace std;

template<typename T, size_t K = 2> // Define the amount of children to be 2 as a default

class Tree {

    void Tree::add_root(Node<T>& node) {
        root = &node; // The root will point of the new node
    }

    void Tree::add_sub_node(Node<T>& parent, Node<T>& child) {
        if (parent.children.size() < K) { // If we have a "place" for the new kid
            parent.add_child(&child);
        } else {
            throw runtime_error("Maximum number of children reached");
        }
    }

    
    // Overload the output stream operator to print the tree
    friend ostream& operator<<(ostream& os, const Tree<T, K>& tree) {
        if (tree.root == nullptr) return os;
        queue<Node<T>*> q;
        q.push(tree.root);
        while (!q.empty()) {
            Node<T>* node = q.front();
            q.pop();
            os << node->get_value() << " ";
            for (auto& child : node->children) {
                q.push(child);
            }
        }
        return os;
    }
};

#endif // TREE_HPP