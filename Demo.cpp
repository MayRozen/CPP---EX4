/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

/**
 * Demo app for Ex4
 */

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "tree.hpp"

using namespace std;

int main()
{

    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
   
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    cout<<"pre_order:"<<endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout<<"pre_order success!"<<endl;

    cout<<"post_order:"<<endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node.get_root()->get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout<<"post_order success!"<<endl;

    cout<<"in_order:"<<endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout<<"in_order success!"<<endl;

    cout<<"bfs_scan:"<<endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout<<"bfs_scan success!"<<endl;

    cout<<"dfs_scan:"<<endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1 1.2 1.4 1.5 1.3 1.6
    cout<<"dfs_scan success!"<<endl;

    cout << "Heap traversal:" << endl;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << "Heap traversal success!" << endl;

    tree.draw(); // Should print the graph using GUI.
    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    cout<<"first child"<<endl;
    three_ary_tree.add_sub_node(root_node, n2);
    cout<<"seconed child"<<endl;
    three_ary_tree.add_sub_node(root_node, n3);
    cout<<"third child"<<endl;
    three_ary_tree.add_sub_node(n1, n4);
    cout<<"n1 child"<<endl;
    three_ary_tree.add_sub_node(n2, n5);
    cout<<"n2 child"<<endl;

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    cout<<"Demo end!"<<endl;
    return 0;
}