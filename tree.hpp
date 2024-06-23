/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <queue>
#include <stack>
#include <iostream>
#include "node.cpp"

using namespace std;

template<typename T, int K = 2>
class Tree {
    private:
    // Helper function to delete all nodes in the tree recursively
    void deleteTree(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        for (Node<T>* child : node->children) {
            deleteTree(child);
        }
        delete node;
    }

public:
    Node<T>* root; // The tree is a vector of pointers to the nodes

    // Static assertion to ensure K is between 2 and 5
    //static_assert(K >= 2 && K <= 5, "K must be between 2 and 5");

    Tree() : root(nullptr) {} // Firsofall, the root will be null

    // Destructor to delete the entire tree
    ~Tree() {
        deleteTree(root);
    }

    int getK(){
        return K;
    }

    void add_root(Node<T>& node); // Adding a new root
    void add_sub_node(Node<T>& parent, Node<T>& child); // Adding a new node

    class PreOrderIterator;
    PreOrderIterator begin_pre_order() const;
    PreOrderIterator end_pre_order() const;

    class PostOrderIterator;
    PostOrderIterator begin_post_order() const;
    PostOrderIterator end_post_order() const;

    class InOrderIterator;
    InOrderIterator begin_in_order() const;
    InOrderIterator end_in_order() const;

    class BFSIterator;
    BFSIterator begin_bfs_scan() const;
    BFSIterator end_bfs_scan() const;

    class DFSIterator;
    DFSIterator begin_dfs_scan() const;
    DFSIterator end_dfs_scan() const;

    class HeapIterator;
    HeapIterator begin_heap() const;
    HeapIterator end_heap() const;

    // Overload the output stream operator to print the tree
    ostream& operator<<(ostream& os);
};


#endif // TREE_HPP