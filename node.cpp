/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <vector>
#include <stack>
#include <memory>

// Container - Node
template<typename T> 
class Node {
public:
    T value;
    std::vector<Node<T>*> children; // Vector of pointers to nodes = children

    Node(T val) : value(val) {} // constructor

    T get_value() const { // Generic get value function
        return value;
    }

    void add_child(Node<T>& child) {
        children.push_back(&child);
    }
};

