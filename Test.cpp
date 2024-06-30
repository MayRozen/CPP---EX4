/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include "doctest.h"
#include "tree.hpp"
#include "Complex.cpp"
#include <sstream>
#include <string>
#include <type_traits> // Include for std::is_same

template <typename T>
std::string to_string(const T& num) {
    std::stringstream ss;
    ss << num;
    return ss.str();
}

void deleteTree(Node<int>* node) {
    for (auto child : node->children) {
        deleteTree(child);
    }
    delete node;
}

TEST_CASE("Test Tree Creation") {
    // Create a simple tree
    Node<int>* root = new Node<int>(10);
    root->children.push_back(new Node<int>(20));
    root->children.push_back(new Node<int>(30));

    CHECK(root->value == 10);
    CHECK(root->children.size() == 2);
    CHECK(root->children[0]->value == 20);
    CHECK(root->children[1]->value == 30);

    // Clean up
    deleteTree(root);
}

TEST_CASE("Test Tree Creation with 60 Children") {
    // Create a tree with a node having 6 children
    Node<int>* root = new Node<int>(10);
    for (size_t i = 0; i < 60; ++i) {
        root->children.push_back(new Node<int>(20 + i));
    }

    // Perform checks
    CHECK(root->value == 10);
    CHECK(root->children.size() == 60);
    for (size_t i = 0; i < 60; ++i) {
        CHECK(root->children[i]->value == 20 + i);
    }

    // Clean up
    deleteTree(root);
}

TEST_CASE("Test Add Child") {
    Node<int>* root = new Node<int>(1);
    Node<int>* child = new Node<int>(2);
    root->add_child(*child);

    CHECK(root->children.size() == 1);
    CHECK(root->children[0]->value == 2);

    // Clean up
    deleteTree(root);
}

//---------------------------------PreOrderIterator---------------------------------
// Define the templated test case
template<typename T, int K>
void testPreOrderIterator() {
    Node<T> root = Node<T>(1);
    Tree<T> tree;
    tree.add_root(root);
    Node<T> n1 = Node<T>(2);
    Node<T> n2 = Node<T>(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    std::stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        ss <<  to_string(node->get_value()) << " ";
    }

    // Convert expected result to a stringstream based on the type T
    std::stringstream expected_ss;
    if (std::is_same<T, int>::value) {
        expected_ss << "1 2 3 ";
    } else if (std::is_same<T, double>::value) {
        expected_ss << "1.000000 2.000000 3.000000 ";
    }

    CHECK(ss.str() == expected_ss.str());
}

// Instantiate the templated test case with specific types
TEST_CASE("Test PreOrderIterator with int and K=2") {
    testPreOrderIterator<int, 2>();
}

// Add more test cases for different types and K values
TEST_CASE("Test PreOrderIterator with double and K=3") {
    testPreOrderIterator<double, 3>();
}

//------------------------PreOrderIterator - using compelx------------------------
template<typename T, int K>
void testPreOrderIteratorComplex() {
    Node<T> root = Node<T>(1);
    Tree<T, K> tree;
    tree.add_root(root);
    Node<T> n1 = Node<T>(2);
    Node<T> n2 = Node<T>(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    std::stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        ss << node->get_value() << " ";
    }

    std::stringstream expected_ss;
    expected_ss << "1 + 0i 2 + 0i 3 + 0i ";

    CHECK(ss.str() == expected_ss.str());
}

TEST_CASE("Test PreOrderIterator with Complex and K=3") {
    testPreOrderIteratorComplex<Complex, 3>();
}

//---------------------------------PostOrderIterator---------------------------------
template<typename T, int K>
void testPostOrderIterator() {
    Node<T> root = Node<T>(1);
    Tree<T> tree;
    tree.add_root(root);
    Node<T> n1 = Node<T>(2);
    Node<T> n2 = Node<T>(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    std::stringstream ss;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        ss <<  to_string(node.get_root()->get_value()) << " ";
    }

    // Convert expected result to a stringstream based on the type T
    std::stringstream expected_ss;
    if (std::is_same<T, int>::value) {
        expected_ss << "2 3 1 ";
    } else if (std::is_same<T, double>::value) {
        expected_ss << "2.000000 3.000000 1.000000 ";
    }

    CHECK(ss.str() == expected_ss.str());
}

// Instantiate the templated test case with specific types
TEST_CASE("Test PostOrderIterator with int and K=2") {
    testPostOrderIterator<int, 2>();
}

// Add more test cases for different types and K values
TEST_CASE("Test PostOrderIterator with double and K=3") {
    testPostOrderIterator<double, 3>();
}

//---------------------------------InOrderIterator---------------------------------
template<typename T, int K>
void testInOrderIterator() {
    Node<T> root = Node<T>(1);
    Tree<T> tree;
    tree.add_root(root);
    Node<T> n1 = Node<T>(2);
    Node<T> n2 = Node<T>(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    std::stringstream ss;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        ss <<  to_string(node->get_value()) << " ";
    }

    // Convert expected result to a stringstream based on the type T
    std::stringstream expected_ss;
    if (std::is_same<T, int>::value) {
        expected_ss << "2 1 3 ";
    } else if (std::is_same<T, double>::value) {
        expected_ss << "2.000000 1.000000 3.000000 ";
    }

    CHECK(ss.str() == expected_ss.str());
}

// Instantiate the templated test case with specific types
TEST_CASE("Test InOrderIterator with int and K=2") {
    testInOrderIterator<int, 2>();
}

// Add more test cases for different types and K values
TEST_CASE("Test InOrderIterator with double and K=3") {
    testInOrderIterator<double, 3>();
}

//---------------------------------BFSIterator---------------------------------
template<typename T, int K>
void testBFSIterator() {
    Node<T> root = Node<T>(1);
    Tree<T> tree;
    tree.add_root(root);
    Node<T> n1 = Node<T>(2);
    Node<T> n2 = Node<T>(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    std::stringstream ss;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        ss <<  to_string(node->get_value()) << " ";
    }

    // Convert expected result to a stringstream based on the type T
    std::stringstream expected_ss;
    if (std::is_same<T, int>::value) {
        expected_ss << "1 2 3 ";
    } else if (std::is_same<T, double>::value) {
        expected_ss << "1.000000 2.000000 3.000000 ";
    }

    CHECK(ss.str() == expected_ss.str());
}

// Instantiate the templated test case with specific types
TEST_CASE("Test BFSIterator with int and K=2") {
    testBFSIterator<int, 2>();
}

// Add more test cases for different types and K values
TEST_CASE("Test BFSIterator with double and K=3") {
    testBFSIterator<double, 3>();
}

//---------------------------------DFSIterator---------------------------------
template<typename T, int K>
void testDFSIterator() {
    Node<T> root = Node<T>(1);
    Tree<T> tree;
    tree.add_root(root);
    Node<T> n1 = Node<T>(2);
    Node<T> n2 = Node<T>(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    std::stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        ss <<  to_string(node->get_value()) << " ";
    }

    // Convert expected result to a stringstream based on the type T
    std::stringstream expected_ss;
    if (std::is_same<T, int>::value) {
        expected_ss << "1 2 3 ";
    } else if (std::is_same<T, double>::value) {
        expected_ss << "1.000000 2.000000 3.000000 ";
    }

    CHECK(ss.str() == expected_ss.str());
}

// Instantiate the templated test case with specific types
TEST_CASE("Test DFSIterator with int and K=2") {
    testDFSIterator<int, 2>();
}

// Add more test cases for different types and K values
TEST_CASE("Test DFSIterator with double and K=3") {
    testDFSIterator<double, 3>();
}

//---------------------------------HeapIterator---------------------------------
template<typename T, int K>
void testHeapIterator() {
    Node<T> root = Node<T>(1);
    Tree<T> tree;
    tree.add_root(root);
    Node<T> n1 = Node<T>(2);
    Node<T> n2 = Node<T>(3);
    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    std::stringstream ss;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        ss << to_string(node->value) << " ";
    }

    // Convert expected result to a stringstream based on the type T
    std::stringstream expected_ss;
    if (std::is_same<T, int>::value) {
        expected_ss << "1 2 3 ";
    } else if (std::is_same<T, double>::value) {
        expected_ss << "1.000000 2.000000 3.000000 ";
    }

    CHECK(ss.str() == expected_ss.str());
}

// Instantiate the templated test case with specific types
TEST_CASE("Test HeapIterator with int and K=2") {
    testHeapIterator<int, 2>();
}

// Add more test cases for different types and K values
TEST_CASE("Test HeapIterator with double and K=3") {
    testHeapIterator<double, 3>();
}
