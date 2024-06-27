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

    T get_child_value(std::size_t index) const {
        if (index < children.size()) {
            return children[index]->value;
        } 
        return -1;
    }
};

