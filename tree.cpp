/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <queue>
#include <stack>
#include <iostream>
#include "complex"
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

    // Iterator methods
    class PreOrderIterator {
    private:
        stack<Node<T>*> stack;

    public:
        PreOrderIterator(Node<T>* root) {
            if (root)
                stack.push(root);
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        PreOrderIterator& operator++() {
            Node<T>* current = stack.top();
            stack.pop();

            // Push children in reverse order (right to left) to simulate pre-order traversal
            for (int i = K - 1; i >= 0; --i) {
                if (current->children[i])
                    stack.push(current->children[i]);
            }

            return *this;
        }

        bool operator!=(const PreOrderIterator& other) const {
            return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
        }
    };

    PreOrderIterator begin_pre_order() {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() {
        return PreOrderIterator(nullptr);
    }

    // Post-order iterator
    class PostOrderIterator {
    private:
        stack<pair<Node<T>*, bool>> stack;

    public:
        PostOrderIterator(Node<T>* root) {
            if (root)
                stack.push({ root, false });
            advance();
        }

        Node<T>& operator*() const {
            return *stack.top().first;
        }

        PostOrderIterator& operator++() {
            stack.pop();
            advance();
            return *this;
        }

        bool operator!=(const PostOrderIterator& other) const {
            return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top().first != other.stack.top().first);
        }

    private:
        void advance() {
            while (!stack.empty() && stack.top().second) {
                stack.pop();
            }
            if (!stack.empty()) {
                Node<T>* current = stack.top().first;
                stack.pop();
                stack.push({ current, true });

                // Push children in reverse order (right to left) to simulate post-order traversal
                for (int i = K - 1; i >= 0; --i) {
                    if (current->children[i])
                        stack.push({ current->children[i], false });
                }
            }
        }
    };

    PostOrderIterator begin_post_order() {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() {
        return PostOrderIterator(nullptr);
    }

    // In-order iterator (not applicable for k-ary trees, simulate using DFS)
    class InOrderIterator {
    private:
        stack<Node<T>*> stack;

    public:
        InOrderIterator(Node<T>* root) {
            if (root)
                stack.push(root);
            advance();
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        InOrderIterator& operator++() {
            stack.pop();
            advance();
            return *this;
        }

        bool operator!=(const InOrderIterator& other) const {
            return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
        }

    private:
        void advance() {
            while (!stack.empty()) {
                Node<T>* current = stack.top();
                stack.pop();

                // Push children in reverse order (right to left) to simulate in-order traversal
                for (int i = K - 1; i >= 0; --i) {
                    if (current->children[i])
                        stack.push(current->children[i]);
                }

                if (!stack.empty())
                    break;
            }
        }
    };

    InOrderIterator begin_in_order() {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() {
        return InOrderIterator(nullptr);
    }

    // BFS iterator
    class BFSIterator {
    private:
        queue<Node<T>*> queue;

    public:
        BFSIterator(Node<T>* root) {
            if (root)
                queue.push(root);
        }

        Node<T>& operator*() const {
            return *queue.front();
        }

        BFSIterator& operator++() {
            Node<T>* current = queue.front();
            queue.pop();

            // Enqueue children in order (left to right) for BFS traversal
            for (size_t i = 0; i < K; ++i) {
                if (current->children[i])
                    queue.push(current->children[i]);
            }

            return *this;
        }

        bool operator!=(const BFSIterator& other) const {
            return queue.size() != other.queue.size() || (queue.size() > 0 && queue.front() != other.queue.front());
        }
    };

    BFSIterator begin_bfs_scan() {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() {
        return BFSIterator(nullptr);
    }

    // DFS iterator (using recursive approach)
    class DFSIterator {
    private:
        stack<Node<T>*> stack;

    public:
        DFSIterator(Node<T>* root) {
            if (root)
                stack.push(root);
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        DFSIterator& operator++() {
            Node<T>* current = stack.top();
            stack.pop();

            // Push children in reverse order (right to left) for DFS traversal
            for (int i = K - 1; i >= 0; --i) {
                if (current->children[i])
                    stack.push(current->children[i]);
            }

            return *this;
        }

        bool operator!=(const DFSIterator& other) const {
            return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
        }
    };

    DFSIterator begin_dfs_scan() {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() {
        return DFSIterator(nullptr);
    }

     // Heap iterator
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

    public:
        HeapIterator(Node<T>* root) {
            if (root) {
                fillVector(root);
                heapify();
            }
        }

        Node<T>& operator*() const {
            return *heap[0];
        }

        HeapIterator& operator++() {
            if (!heap.empty()) {
                swap(heap[0], heap[heap.size() - 1]);
                heap.pop_back();
                siftDown(0, heap.size());
            }
            return *this;
        }

        bool operator!=(const HeapIterator& other) const {
            return heap.size() != other.heap.size();
        }

    private:
        void fillVector(Node<T>* node) {
            if (!node) return;
            heap.push_back(node);
            for (size_t i = 0; i < K; ++i) {
                fillVector(node->children[i]);
            }
        }
    };

    HeapIterator begin_heap() {
        return HeapIterator(root);
    }

    HeapIterator end_heap() {
        return HeapIterator(nullptr);
    }
};


