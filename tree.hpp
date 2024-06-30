/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef TREE_HPP
#define TREE_HPP

#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>
#include <iostream>
#include "node.cpp"
#include "complex"

using namespace std;

template<typename T, int K = 2>
class Tree {
private:
    sf::Font font;

    void drawNode(sf::RenderWindow& window, Node<T>* node, sf::Vector2f position, float xOffset, float yOffset) {
        if (node == nullptr) return;

        sf::CircleShape circle(20);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(position);
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(node->value));
        text.setCharacterSize(15);
        text.setFillColor(sf::Color::White);
        text.setPosition(position.x + 10, position.y + 5);
        window.draw(text);

        float childXOffset = xOffset / K;
        float childYOffset = yOffset;

        for (size_t i = 0; i < node->children.size(); ++i) {
            sf::Vector2f childPosition(position.x + (i - (node->children.size() - 1) / 2.0f) * childXOffset, position.y + childYOffset);

            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(position.x + 20, position.y + 20)),
                sf::Vertex(sf::Vector2f(childPosition.x + 20, childPosition.y + 20))};
            window.draw(line, 2, sf::Lines);

            drawNode(window, node->children[i], childPosition, childXOffset, childYOffset);
        }
    }

    void delete_subtree(Node<T>* node) {
        if (node == nullptr) { // If there is no subtree
            return;
        }
        for (Node<T>* child : node->children) {
            delete_subtree(child); // Recursively delete children
        }
        delete node; // Delete the current node
    }
public:
    Node<T>* root;
    size_t max_children; // -> K

    Tree(size_t k=2) : root(nullptr) ,max_children(k) {} // Constructor

    ~Tree(){}
    void add_root(Node<T>& node) {
        root = &node; // Store the pointer to the node
    }

    void add_sub_node(Node<T>& parent, Node<T>& child) { // Adding a new node
        if (parent.children.size() <= K+1) { // If we have a "place" for the new kid
            parent.add_child(child);
        } else {
            throw runtime_error("Maximum number of children reached");
        }
    }

    void draw() {
        sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            drawNode(window, root, sf::Vector2f(400, 50), 200, 100);
            window.display();
        }
    }

//---------------------------------PreOrderIterator---------------------------------
    class PreOrderIterator {
    private:
        stack<Node<T>*> stack;
    public:
        PreOrderIterator(Node<T>* root) {
            if (root) {
                stack.push(root); // The root of the tree is the first value in the stack
            }
        }

        Node<T>* operator->() const {
            return stack.top(); // The first POINTER in the stack
        }

        Node<T>& operator*() const {
            return *stack.top(); // The first VALUE in the stack
        }
        
        PreOrderIterator& operator++() {
            if(K<=2){
                if (!stack.empty()) {
                    Node<T>* current = stack.top(); // The current node being processed in the traversal
                    stack.pop(); // Removes this node from the stack because it's being processed

                    // Iterate over these children in reverse order (from last to first)
                    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                        stack.push(*it);
                    }
                }
            } else{ // DFS
                if (!stack.empty()) {
                    Node<T>* current = stack.top();
                    stack.pop();

                    // Push children in reverse order (right to left) for DFS traversal
                    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                        stack.push(*it);
                    }
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

//---------------------------------PostOrderIterator---------------------------------
    class PostOrderIterator {
    private:
        Node<T>* root;
        stack<Node<T>*> stack;

        void init(Node<T>* node){
            if(node) { // If there is a node
                stack.push(node);
                for(auto it = node->children.rbegin(); it != node->children.rend(); ++it ){ // Run over all its children
                    init(*it); // Recrsive function
                }
            }
        }
        
    public:
        PostOrderIterator(Node<T>* r) : root(nullptr) {
            if (r) {
                init(r);
                root = stack.top();
            }
        }

        Node<T>* get_root() const { // Return the root of the tree
            return root;
        }

        Node<T>& operator->() const { // Return a refernce to the root of the tree
            return *root;
        }

        Node<T>& operator*() const {
            return *root;
        }
        
        PostOrderIterator& operator++() {
            if(K<=2){
                if (!stack.empty()) {
                    stack.pop(); // Removes this node from the stack because it's being processed
                    if (!stack.empty()) {
                        root = stack.top();
                    } else {
                        root = nullptr;
                    }
                } else {
                    root = nullptr;
                }
            } else{ // DFS
                if (!stack.empty()) {
                    Node<T>* current = stack.top();
                    stack.pop();

                    // Push children in reverse order (right to left) for DFS traversal
                    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                        stack.push(*it);
                    }
                }
            }

            return *this;
        }

        bool operator!=(const PostOrderIterator& other) const {
            return root != other.root;
        }

        bool operator==(const PostOrderIterator& other) const {
            return root == other.root;
        }
    };

    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root);
    }

    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr);
    }

//---------------------------------InOrderIterator---------------------------------
    class InOrderIterator {
    public:
        explicit InOrderIterator(Node<T>* root) {
            pushLeft(root);
        }

        Node<T>* operator->() const { // Return the first POINTER in the stack
            return nodes.top();
        }

        Node<T>& operator*() const { // Return the reference to the first value in the stack
            return *nodes.top();
        }

        InOrderIterator& operator++() {
            if(K<=2){
                if (!nodes.empty()) {
                    Node<T>* current = nodes.top();
                    nodes.pop();
                    if (!current->children.empty()) { // Run over all its children
                        pushLeft(current->children[1]); // Put it at the "left side" of the root
                    }
                }
            } else{ // DFS
                if (!nodes.empty()) {
                    Node<T>* current = nodes.top();
                    nodes.pop();

                    // Push children in reverse order (right to left) for DFS traversal
                    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                        nodes.push(*it);
                    }
                }
            }
            
            return *this;
        }

        bool operator!=(const InOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const InOrderIterator& other) const {
            return nodes == other.nodes;
        }

    private:
        stack<Node<T>*> nodes;

        void pushLeft(Node<T>* node) {
            while (node) {
                nodes.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                }
                else {
                    break;
                }
            }
        }
    };

    InOrderIterator begin_in_order() const {
        return InOrderIterator(root);
    }

    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr);
    }

//---------------------------------BFSIterator---------------------------------
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
            if (!queue.empty()) {
                Node<T>* current = queue.front();
                queue.pop();

                // Enqueue children in order (left to right) for BFS traversal
                for (auto& child : current->children) {
                    if (child) { // Check to ensure child is not nullptr
                        queue.push(child);
                    }
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

//---------------------------------DFSIterator---------------------------------
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
            if (!stack.empty()) {
                Node<T>* current = stack.top();
                stack.pop();

                // Push children in reverse order (right to left) for DFS traversal
                for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                    stack.push(*it);
                }
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

//---------------------------------HeapIterator---------------------------------
    class HeapIterator {
    private:
        vector<Node<T>*> heap;

        void heapify() {
            size_t n = heap.size();
            for (size_t i = n / 2; i > 0; --i) {
                siftDown(i - 1, n);
            }
        }


        void siftDown(size_t i, size_t n) {
            size_t smallest = i;
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;

            // Check if left child is within bounds and smaller than current smallest
            if (left < n && heap[left]!=nullptr && heap[left]->get_value() < heap[smallest]->get_value()) {
                smallest = left;
            }

            // Check if right child is within bounds and smaller than current smallest
            if (right < n && heap[right]!=nullptr && heap[right]->get_value() < heap[smallest]->get_value()) {
                smallest = right;
            }

            // If smallest has changed, swap elements and recursively sift down
            if (smallest != i) {
                std::swap(heap[i], heap[smallest]);
                siftDown(smallest, n); // Recursive call to siftDown
            }
        }

    void fillVector(Node<T>* node) {
        if (!node) return;
        heap.push_back(node);
        for (size_t i = 0; i < (size_t)K && i<node->children.size(); ++i) {
            fillVector(node->children[i]);
        }
    }

    public:
        HeapIterator(Node<T>* root) {
            if (root) {
                fillVector(root);
                heapify();
            }
        }

        Node<T>* operator->() const {
            if (!heap.empty()) {
                return heap.front();
            }
            return nullptr; // Handle empty heap case
        }

        Node<T>& operator*() const {
            if (!heap.empty()) {
                return *heap[0];
            }
            throw runtime_error("Dereferencing empty heap iterator"); // Handle empty heap case
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

#endif