/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <vector>

// Container - Node
template<typename T> 
class Node {
public:
    T value; // The value of the node
    std::vector<Node<T>*> children; // Vector of pointers to nodes = children

    Node(T val) : value(val) {} // constructor

    T get_value() const { // Generic get value function
        return value;
    }

    void add_child(Node<T>& child) { // Generic adding a child function
        children.push_back(&child);
    }
};

