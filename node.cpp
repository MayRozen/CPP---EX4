/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <vector>
#include <stack>

// Container - Node
template<typename T> 
class Node {
public:
    T value;
    std::vector<Node<T>*> children; // Vector of pointers to nodes = children

    Node(T val) : value(val) {} // constructor

    ~Node() {
        for (Node<T>* child : children) {
            delete child;  // Recursively delete children
        }
        children.clear();  // Clear the vector of children
    }

    T get_value() const { // Generic
        return value;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }

    // != operator for iterator comparison
    bool operator!=(const Node<T>& other) const {
        return !(*this == other);
    }

    // == operator for iterator comparison
    bool operator==(const Node<T>& other) const {
        if (node_stack.empty() && other.node_stack.empty()) {
            return true;
        }
        if (!node_stack.empty() && !other.node_stack.empty()) {
            return node_stack.top() == other.node_stack.top();
        }
        return false;
    }

    // Prefix increment operator
    Node<T>& operator++() {
        if (!node_stack.empty()) {
            Node<T>* current = node_stack.top();
            node_stack.pop();
            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                node_stack.push(*it);
            }
        }
        return *this;
    }
};

