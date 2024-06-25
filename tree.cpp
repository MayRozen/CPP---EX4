/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <queue>
#include <stack>
#include <iostream>
#include "node.cpp"
#include "complex"

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

    void add_root(Node<T>& node) { // Adding a new root
        root = &node; // The root will point of the new node
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) { // Adding a new node
        if (parent.children.size() < K) { // If we have a "place" for the new kid
            parent.add_child(&child);
        } else {
            throw runtime_error("Maximum number of children reached");
        }
    }

    // Overload the output stream operator to print the tree
    ostream& operator<<(ostream& os) {
        if (root == nullptr) return os;
        queue<Node<T>*> q;
        q.push(root);
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

    // PreOrderIterator class declaration
    class PreOrderIterator {
    private:
        stack<Node<T>*> stack;
    public:
        PreOrderIterator(Node<T>* root) {
            if (root) {
                stack.push(root);
            }
        }

        Node<T>* operator->() const {
            return stack.top();
        }

        Node<T>& operator*() const {
            return *stack.top();
        }
        
        PreOrderIterator& operator++() {
            if (!stack.empty()) {
                Node<T>* current = stack.top();
                stack.pop();
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                    stack.push(*it);
                }
            }
            return *this;
        }
                
        
        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator& other) const {
            if (stack.empty() && other.stack.empty()) {
                return true;
            }
            if (!stack.empty() && !other.stack.empty()) {
                return stack.top() == other.stack.top();
            }
            return false;
        }
    };

    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root);
    }

    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr);
    }

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
            for (size_t i = K - 1; i >= 0; --i) {
                if (current->children[i]) {
                    stack.push({ current->children[i], false });
                }
            }
        }
    }
    public:
        PostOrderIterator(Node<T>* root) {
            if (root) {
                stack.push({ root, false });
            }
            advance();
        }

        Node<T>* operator->() const {
            return stack.top().first;
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
    };

    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr);
    }

    // InOrderIterator class declaration
    class InOrderIterator {
    private:
        stack<Node<T>*> stack;
        void advance() {
        while (!stack.empty()) {
            Node<T>* current = stack.top();
            stack.pop();

            // Push children in reverse order (right to left) to simulate in-order traversal
            for (size_t i = K - 1; i >= 0; --i) {
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
        InOrderIterator(Node<T>* root) {
            if (root) {
                stack.push(root);
            }
            advance();
        }

        Node<T>* operator->() const {
            return stack.top();
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
    };

    InOrderIterator begin_in_order() const {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr);
    }

    // BFSIterator class declaration
    class BFSIterator {
    private:
        queue<Node<T>*> queue;
    public:
        BFSIterator(Node<T>* root) {
            if (root) {
                queue.push(root);
            }
        }

        Node<T>* operator->() const {
            return queue.front();
        }

        Node<T>&  operator*() const {
            return *queue.front();
        }

        BFSIterator&  operator++() {
            Node<T>* current = queue.front();
            queue.pop();

            // Enqueue children in order (left to right) for BFS traversal
            for (size_t i = 0; i < (size_t)K; ++i) {
                if (current->children[i]) {
                    queue.push(current->children[i]);
                }
            }

            return *this;
        }
        
        bool operator!=(const BFSIterator& other) const {
            return queue.size() != other.queue.size() || (queue.size() > 0 && queue.front() != other.queue.front());
        }
    };

    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    // DFSIterator class declaration
    class DFSIterator {
    private:
        stack<Node<T>*> stack;
    public:
        DFSIterator(Node<T>* root) {
            if (root) {
                stack.push(root);
            }
        }
        
        Node<T>* operator->() const {
            return stack.top();
        }
        Node<T>& operator*() const {
            return *stack.top();
        }

        DFSIterator& operator++() {
            Node<T>* current = stack.top();
            stack.pop();

            // Push children in reverse order (right to left) for DFS traversal
            for (size_t i = K - 1; i >= 0; --i) {
                if (current->children[i])
                    stack.push(current->children[i]);
            }

            return *this;
        }

        bool operator!=(const DFSIterator& other) const {
            return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
        }
    };

    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr);
    }

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
        HeapIterator(Node<T>* root) {
            if (root && K==2) {
                fillVector(root);
                heapify();
            }
        }

        Node<T>* operator->() const {
            return heap.front();
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

    };

    HeapIterator begin_heap() const {
        return HeapIterator(root);
    }

    HeapIterator end_heap() const {
        return HeapIterator(nullptr);
    }
};