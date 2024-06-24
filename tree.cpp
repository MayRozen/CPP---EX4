/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <queue>
#include <stack>
#include <iostream>
#include "complex"
#include "tree.hpp"

using namespace std;

template<typename T, int K>
void Tree<T, K>::add_root(Node<T>& node) {
    this->root = &node; // The root will point of the new node
}

template<typename T, int K>
void Tree<T, K>::add_sub_node(Node<T>& parent, Node<T>& child) {
    if (parent.children.size() <= getK()) { // If we have a "place" for the new kid
        parent.add_child(&child);
    } else {
        throw runtime_error("Maximum number of children reached");
    }
}


// Overload the output stream operator to print the tree
// Definition of operator<< for Tree class
template<typename T, int K>
ostream& Tree<T ,K>::operator<<(ostream& os) {
    if (this->root == nullptr) return os;
    queue<Node<T>*> q;
    q.push(this->root);
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

// Iterator methods
template<typename T, int K>
Tree<T, K>::PreOrderIterator::PreOrderIterator(Node<T>* root) {
    if (root) {
        stack.push(root);
    }
}

template<typename T, int K>
Node<T>& Tree<T, K>::PreOrderIterator::operator*() const {
    return *stack.top();
}

template<typename T, int K>
typename Tree<T, K>::PreOrderIterator& Tree<T, K>::PreOrderIterator::operator++() {
    Node<T>* current = stack.top();
    stack.pop();

    // Push children in reverse order (right to left) to simulate pre-order traversal
    for (int i = K - 1; i >= 0; --i) {
        if (current->children[i])
            stack.push(current->children[i]);
    }

    return *this;
}

template<typename T, int K>
bool Tree<T, K>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
}

// Implementation of PreOrderIterator::operator->()
template<typename T, int K>
Node<T>* Tree<T, K>::PreOrderIterator::operator->() const {
    return stack.top();
}

template<typename T, int K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::begin_pre_order() const {
    return PreOrderIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::PreOrderIterator Tree<T, K>::end_pre_order() const {
    return PreOrderIterator(nullptr);
}

// Post-order iterator
template<typename T, int K>
Tree<T, K>::PostOrderIterator::PostOrderIterator(Node<T>* root) {
    if (this->root) {
        stack.push({ this->root, false });
    }
    advance();
}

template<typename T, int K>
Node<T>& Tree<T, K>::PostOrderIterator::operator*() const {
    return *stack.top().first;
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator& Tree<T, K>::PostOrderIterator::operator++() {
    stack.pop();
    advance();
    return *this;
}

template<typename T, int K>
bool Tree<T, K>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top().first != other.stack.top().first);
}

template<typename T, int K>
Node<T>* Tree<T, K>::PostOrderIterator::operator->() const {
    return stack.top().first;
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::begin_post_order() const {
    return PostOrderIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::PostOrderIterator Tree<T, K>::end_post_order() const {
    return PostOrderIterator(nullptr);
}

// In-order iterator (not applicable for k-ary trees, simulate using DFS)
template<typename T, int K>
Tree<T, K>::InOrderIterator::InOrderIterator(Node<T>* root) {
    if (this->root) {
        stack.push(this->root);
    }
    advance();
}

template<typename T, int K>
Node<T>& Tree<T, K>::InOrderIterator::operator*() const {
    return *stack.top();
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator& Tree<T, K>::InOrderIterator::operator++() {
    stack.pop();
    advance();
    return *this;
}

template<typename T, int K>
bool Tree<T, K>::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
}


template<typename T, int K>
Node<T>* Tree<T, K>::InOrderIterator::operator->() const {
    return stack.top();
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator Tree<T, K>::begin_in_order() const {
    return InOrderIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::InOrderIterator Tree<T, K>::end_in_order() const {
    return InOrderIterator(nullptr);
}

// BFS iterator 
template<typename T, int K>
Tree<T, K>::BFSIterator::BFSIterator(Node<T>* root) {
    if (this->root) {
        queue.push(this->root);
    }
}

template<typename T, int K>
Node<T>&  Tree<T, K>::BFSIterator::operator*() const {
    return *queue.front();
}

template<typename T, int K>
typename Tree<T, K>::BFSIterator&  Tree<T, K>::BFSIterator::operator++() {
    Node<T>* current = queue.front();
    queue.pop();

    // Enqueue children in order (left to right) for BFS traversal
    for (size_t i = 0; i < (size_t)this->getK(); ++i) {
        if (current->children[i]) {
            queue.push(current->children[i]);
        }
    }

    return *this;
}

template<typename T, int K>
bool Tree<T, K>::BFSIterator::operator!=(const BFSIterator& other) const {
    return queue.size() != other.queue.size() || (queue.size() > 0 && queue.front() != other.queue.front());
}


template<typename T, int K>
Node<T>* Tree<T, K>::BFSIterator::operator->() const {
    return queue.front();
}

template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::begin_bfs_scan() const {
    return BFSIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::BFSIterator Tree<T, K>::end_bfs_scan() const {
    return BFSIterator(nullptr);
}

// DFS iterator (using recursive approach)
template<typename T, int K>
Tree<T, K>::DFSIterator::DFSIterator(Node<T>* root) {
    if (this->root) {
        stack.push(this->root);
    }
}

template<typename T, int K>
Node<T>& Tree<T, K>::DFSIterator::operator*() const {
    return *stack.top();
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator& Tree<T, K>::DFSIterator::operator++() {
    Node<T>* current = stack.top();
    stack.pop();

    // Push children in reverse order (right to left) for DFS traversal
    for (int i = this->getK() - 1; i >= 0; --i) {
        if (current->children[i])
            stack.push(current->children[i]);
    }

    return *this;
}

template<typename T, int K>
    bool Tree<T, K>::DFSIterator::operator!=(const DFSIterator& other) const {
        return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
    }

template<typename T, int K>
Node<T>* Tree<T, K>::DFSIterator::operator->() const {
    return stack.top();
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator Tree<T, K>::begin_dfs_scan() const {
    return DFSIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::DFSIterator Tree<T, K>::end_dfs_scan() const {
    return DFSIterator(nullptr);
}

// Heap iterator
template<typename T, int K>
Tree<T, K>::HeapIterator::HeapIterator(Node<T>* root) {
    if (this->root && this->getK()==2) {
        fillVector(this->root);
        heapify();
    }
}

template<typename T, int K>
Node<T>& Tree<T, K>::HeapIterator::operator*() const {
    return *heap[0];
}

template<typename T, int K>
typename Tree<T, K>::HeapIterator& Tree<T, K>::HeapIterator::operator++() {
    if (!heap.empty()) {
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        siftDown(0, heap.size());
    }
    return *this;
}

template<typename T, int K>
bool Tree<T, K>::HeapIterator::operator!=(const HeapIterator& other) const {
    return heap.size() != other.heap.size();
}

template<typename T, int K>
Node<T>* Tree<T, K>::HeapIterator::operator->() const {
    return heap.front();
}

template<typename T, int K>
typename Tree<T, K>::HeapIterator Tree<T, K>::begin_heap() const {
    return HeapIterator(root);
}

template<typename T, int K>
typename Tree<T, K>::HeapIterator Tree<T, K>::end_heap() const {
    return HeapIterator(nullptr);
}