// /*  ID: 212051007
//     Mail: mayrozen45@gmail.com
// */

// #include "doctest.h"
// #include "tree.hpp"
// #include <sstream>
// #include <string>

// template <typename T>
// std::string to_string(const T& num) {
//     std::stringstream ss;
//     ss << num;
//     return ss.str();
// }

// void deleteTree(Node<int>* node) {
//     for (auto child : node->children) {
//         deleteTree(child);
//     }
//     delete node;
// }

// // TEST_CASE("Test Tree Creation") {
// //     // Create a simple tree
// //     Node<int>* root = new Node<int>(10);
// //     root->children.push_back(new Node<int>(20));
// //     root->children.push_back(new Node<int>(30));

// //     CHECK(root->value == 10);
// //     CHECK(root->children.size() == 2);
// //     CHECK(root->children[0]->value == 20);
// //     CHECK(root->children[1]->value == 30);

// //     // Clean up
// //     deleteTree(root);
// // }

// // TEST_CASE("Test Add Child") {
// //     Node<int>* root = new Node<int>(1);
// //     auto child = Node<int>(2);
// //     root->add_child(child);

// //     CHECK(root->children.size() == 1);
// //     CHECK(root->children[0]->value == 2);

// //     // Clean up
// //     deleteTree(root);
// // }

// //---------------------------------PreOrderIterator---------------------------------
// // Define the templated test case
// template<typename T, int K>
// void testPreOrderIterator() {
//     Node<T> root = Node<T>(1);
//     Tree<T> tree;
//     tree.add_root(root);
//     Node<T> n1 = Node<T>(2);
//     Node<T> n2 = Node<T>(3);
//     tree.add_sub_node(root, n1);
//     tree.add_sub_node(root, n2);

//     std::stringstream ss;
//     for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
//     {
//         ss <<  to_string(node->get_value()) << " ";
//     }

//     CHECK(ss.str() == "1 2 3 ");
// }

// // Instantiate the templated test case with specific types
// TEST_CASE("Test PreOrderIterator with int and K=2") {
//     testPreOrderIterator<int, 2>();
// }

// // Add more test cases for different types and K values
// TEST_CASE("Test PreOrderIterator with double and K=3") {
//     testPreOrderIterator<double, 3>();
// }

// //---------------------------------PostOrderIterator---------------------------------
// template<typename T, int K>
// void testPostOrderIterator() {
//     Node<T> root = Node<T>(1);
//     Tree<T> tree;
//     tree.add_root(root);
//     Node<T> n1 = Node<T>(2);
//     Node<T> n2 = Node<T>(3);
//     tree.add_sub_node(root, n1);
//     tree.add_sub_node(root, n2);

//     std::stringstream ss;
//     for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
//     {
//         ss <<  to_string(node.get_root()->get_value()) << " ";
//     }

//     CHECK(ss.str() == "2 3 1 ");
// }

// // Instantiate the templated test case with specific types
// TEST_CASE("Test PostOrderIterator with int and K=2") {
//     testPostOrderIterator<int, 2>();
// }

// // Add more test cases for different types and K values
// TEST_CASE("Test PostOrderIterator with double and K=3") {
//     testPostOrderIterator<double, 3>();
// }

// //---------------------------------InOrderIterator---------------------------------
// template<typename T, int K>
// void testInOrderIterator() {
//     Node<T> root = Node<T>(1);
//     Tree<T> tree;
//     tree.add_root(root);
//     Node<T> n1 = Node<T>(2);
//     Node<T> n2 = Node<T>(3);
//     tree.add_sub_node(root, n1);
//     tree.add_sub_node(root, n2);

//     std::stringstream ss;
//     for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
//     {
//         ss <<  to_string(node->get_value()) << " ";
//     }

//     CHECK(ss.str() == "2 1 3 ");
// }

// // Instantiate the templated test case with specific types
// TEST_CASE("Test InOrderIterator with int and K=2") {
//     testInOrderIterator<int, 2>();
// }

// // Add more test cases for different types and K values
// TEST_CASE("Test InOrderIterator with double and K=3") {
//     testInOrderIterator<double, 3>();
// }

// //---------------------------------BFSIterator---------------------------------
// template<typename T, int K>
// void testBFSIterator() {
//     Node<T> root = Node<T>(1);
//     Tree<T> tree;
//     tree.add_root(root);
//     Node<T> n1 = Node<T>(2);
//     Node<T> n2 = Node<T>(3);
//     tree.add_sub_node(root, n1);
//     tree.add_sub_node(root, n2);

//     std::stringstream ss;
//     for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
//     {
//         ss <<  to_string(node->get_value()) << " ";
//     }

//     CHECK(ss.str() == "1 2 3 ");
// }

// // Instantiate the templated test case with specific types
// TEST_CASE("Test BFSIterator with int and K=2") {
//     testBFSIterator<int, 2>();
// }

// // Add more test cases for different types and K values
// TEST_CASE("Test BFSIterator with double and K=3") {
//     testBFSIterator<double, 3>();
// }

// //---------------------------------DFSIterator---------------------------------
// template<typename T, int K>
// void testDFSIterator() {
//     Node<T> root = Node<T>(1);
//     Tree<T> tree;
//     tree.add_root(root);
//     Node<T> n1 = Node<T>(2);
//     Node<T> n2 = Node<T>(3);
//     tree.add_sub_node(root, n1);
//     tree.add_sub_node(root, n2);

//     std::stringstream ss;
//     for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
//     {
//         ss <<  to_string(node->get_value()) << " ";
//     }

//     CHECK(ss.str() == "1 3 2 ");
// }

// // Instantiate the templated test case with specific types
// TEST_CASE("Test DFSIterator with int and K=2") {
//     testDFSIterator<int, 2>();
// }

// // Add more test cases for different types and K values
// TEST_CASE("Test DFSIterator with double and K=3") {
//     testDFSIterator<double, 3>();
// }
