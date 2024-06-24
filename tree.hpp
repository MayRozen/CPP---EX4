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

    // Overload the output stream operator to print the tree
    ostream& operator<<(ostream& os);

    // PreOrderIterator class declaration
    class PreOrderIterator {
    private:
        stack<Node<T>*> stack;
    public:
        PreOrderIterator(Node<T>* root);
        Node<T>* operator->() const;
        Node<T>& operator*() const;
        PreOrderIterator& operator++();
        bool operator!=(const PreOrderIterator& other) const;
    };

    PreOrderIterator begin_pre_order() const;
    PreOrderIterator end_pre_order() const;

    // PostOrderIterator class declaration
    class PostOrderIterator {
    private:
        stack<pair<Node<T>*, bool>> stack;
        void advance() {
        while (!stack.empty() && stack.top().second) {
            stack.pop();
        }
        if (!stack.empty()) {
            Node<T>* current = stack.top().first;
            stack.pop();
            stack.push({ current, true });

            // Push children in reverse order (right to left) to simulate post-order traversal
            for (int i = this->getK() - 1; i >= 0; --i) {
                if (current->children[i]) {
                    stack.push({ current->children[i], false });
                }
            }
        }
    }
    public:
        PostOrderIterator(Node<T>* root);
        Node<T>* operator->() const;
        Node<T>& operator*() const;
        PostOrderIterator& operator++();
        bool operator!=(const PostOrderIterator& other) const;
    };

    PostOrderIterator begin_post_order() const;
    PostOrderIterator end_post_order() const;

    // InOrderIterator class declaration
    class InOrderIterator {
    private:
        stack<Node<T>*> stack;
        void advance() {
        while (!stack.empty()) {
            Node<T>* current = stack.top();
            stack.pop();

            // Push children in reverse order (right to left) to simulate in-order traversal
            for (int i = this->getK() - 1; i >= 0; --i) {
                if (current->children[i]) {
                    stack.push(current->children[i]);
                }
            }

            if (!stack.empty()) {
                break;
            }
        }
    }
    public:
        InOrderIterator(Node<T>* root);
        Node<T>* operator->() const;
        Node<T>& operator*() const;
        InOrderIterator& operator++();
        bool operator!=(const InOrderIterator& other) const;
    };

    InOrderIterator begin_in_order() const;
    InOrderIterator end_in_order() const;

    // BFSIterator class declaration
    class BFSIterator {
    private:
        queue<Node<T>*> queue;
    public:
        BFSIterator(Node<T>* root);
        Node<T>* operator->() const;
        Node<T>& operator*() const;
        BFSIterator& operator++();
        bool operator!=(const BFSIterator& other) const;
    };

    BFSIterator begin_bfs_scan() const;
    BFSIterator end_bfs_scan() const;

    // DFSIterator class declaration
    class DFSIterator {
    private:
        stack<Node<T>*> stack;
    public:
        DFSIterator(Node<T>* root);
        Node<T>* operator->() const;
        Node<T>& operator*() const;
        DFSIterator& operator++();
        bool operator!=(const DFSIterator& other) const;
    };

    DFSIterator begin_dfs_scan() const;
    DFSIterator end_dfs_scan() const;

    // HeapIterator class declaration
    class HeapIterator {
    private:
        vector<Node<T>*> heap;
        void heapify() {
            int n = heap.size();
            for (int i = n / 2 - 1; i >= 0; --i) {
                siftDown(i, n);
            }
        }
        
        void siftDown(int i, int n) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < n && heap[left]->data < heap[smallest]->data) {
                smallest = left;
            }

            if (right < n && heap[right]->data < heap[smallest]->data) {
                smallest = right;
            }

            if (smallest != i) {
                swap(heap[i], heap[smallest]);
                siftDown(smallest, n);
            }
        }
        
        void fillVector(Node<T>* node) {
            if (!node) return;
            heap.push_back(node);
            for (size_t i = 0; i < (size_t)K; ++i) {
                fillVector(node->children[i]);
            }
        }
    public:
        HeapIterator(Node<T>* root);
        Node<T>* operator->() const;
        Node<T>& operator*() const;
        HeapIterator& operator++();
        bool operator!=(const HeapIterator& other) const;
    };

    HeapIterator begin_heap() const;
    HeapIterator end_heap() const;
};


#endif // TREE_HPP