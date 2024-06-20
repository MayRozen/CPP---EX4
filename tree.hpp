/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <stack>
#include <iostream>
#include "complex"
#include "node.hpp"

using namespace std;

template<typename T, size_t K = 2> // Define the amount of children to be 2 as a default
class Tree {
    private:
    // Helper function to delete all nodes in the tree recursively
    void deleteTree(TreeNode<Key>* node) {
        if (node == nullptr) return;
        for (TreeNode<Key>* child : node->children) {
            deleteTree(child);
        }
        delete node;
    }

public:
    Node<T>* root; // The tree is a vector of pointers to the nodes

    Tree() : root(nullptr) {} // Firsofall, the root will be null

    // Destructor to delete the entire tree
    ~KaryTree() {
        deleteTree(root);
    }

    void add_root(Node<T>& node); // Adding a new root
    void add_sub_node(Node<T>& parent, Node<T>& child); // Adding a new node

    Node<T>& begin_pre_order();
    Node<T>& end_pre_order();

    Node<T>& begin_post_order();
    Node<T>& end_post_order();

    Node<T>& begin_in_order();
    Node<T>& end_in_order();

    Node<T>& begin_bfs_scan();
    Node<T>& end_bfs_scan();

    Node<T>& begin_dfs_scan();
    Node<T>& end_dfs_scan();

    HeapIterator begin_heap();
    HeapIterator end_heap();

    // Overload the output stream operator to print the tree
    friend ostream& operator<<(ostream& os, const Tree<T, K>& tree);
};

#endif // TREE_HPP