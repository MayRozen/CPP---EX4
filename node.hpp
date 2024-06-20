/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include "complex"
using namespace std;

template<typename T>
class Node {
public:
    T value;
    vector<Node<T>*> children;

    Node(T val) : value(val) {}

    T get_value() const {
        return value;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }
};

#endif // NODE_HPP