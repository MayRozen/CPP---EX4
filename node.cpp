/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include <vector>
#include <stack>
#include <cstddef> // Include for size_t

template<typename T, size_t K = 2> // Default arity of 2
class Node {
public:
    T value;
    std::vector<Node<T>*> children;

    Node(T val) : value(val) {}

    ~Node() {
        for (Node<T>* child : children) {
            delete child;  // Recursively delete children
        }
        children.clear();  // Clear the vector of children
    }

    T get_value() const {
        return value;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }

    // Example iterator implementation (PreOrderIterator)
    class PreOrderIterator {
    private:
        std::stack<Node<T>*> stack;

    public:
        PreOrderIterator(Node<T>* root) {
            if (root){
                stack.push(root);
            }
        }

        Node<T>& operator*() const {
            return *stack.top();
        }

        PreOrderIterator& operator++() {
            Node<T>* current = stack.top();
            stack.pop();
            for (int i = current->children.size() - 1; i >= 0; --i) {
                stack.push(current->children[i]);
            }
            return *this;
        }

        bool operator!=(const PreOrderIterator& other) const {
            return stack.size() != other.stack.size() || (stack.size() > 0 && stack.top() != other.stack.top());
        }
    };
};

