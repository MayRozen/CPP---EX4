/*  ID: 212051007
    Mail: mayrozen45@gmail.com
*/

#include "doctest.h"
#include "tree.cpp"

TEST_CASE("Test PreOrderIterator") {
    // Create a tree structure
    Node<int>* root = new Node<int>(1);
    root->children.push_back(new Node<int>(2));
    root->children.push_back(new Node<int>(3));
    root->children[0]->children.push_back(new Node<int>(4));
    root->children[1]->children.push_back(new Node<int>(5));

    PreOrderIterator it = root->begin_pre_order();
    PreOrderIterator end = root->end_pre_order();

    std::stringstream ss;
    while (it != end) {
        ss << (*it)->value << " ";
        ++it;
    }
    
    // Check the output
    CHECK(ss.str() == "1 2 4 3 5 ");

    // Clean up
    deleteTree(root);
}

TEST_CASE("Test PostOrderIterator") {
    // Create a tree structure
    Node<int>* root = new Node<int>(1);
    root->children.push_back(new Node<int>(2));
    root->children.push_back(new Node<int>(3));
    root->children[0]->children.push_back(new Node<int>(4));
    root->children[1]->children.push_back(new Node<int>(5));

    PostOrderIterator it = root->begin_post_order();
    PostOrderIterator end = root->end_post_order();

    std::stringstream ss;
    while (it != end) {
        ss << (*it)->value << " ";
        ++it;
    }
    
    // Check the output
    CHECK(ss.str() == "4 2 5 3 1 ");

    // Clean up
    deleteTree(root);
}

TEST_CASE("Test InOrderIterator") {
    // Create a tree structure
    Node<int>* root = new Node<int>(1);
    root->children.push_back(new Node<int>(2));
    root->children.push_back(new Node<int>(3));
    root->children[0]->children.push_back(new Node<int>(4));
    root->children[1]->children.push_back(new Node<int>(5));

    InOrderIterator it = root->begin_in_order();
    InOrderIterator end = root->end_in_order();

    std::stringstream ss;
    while (it != end) {
        ss << (*it)->value << " ";
        ++it;
    }
    
    // Check the output
    CHECK(ss.str() == "4 2 1 3 5 ");

    // Clean up
    deleteTree(root);
}

TEST_CASE("Test BFSIterator") {
    // Create a tree structure
    Node<int>* root = new Node<int>(1);
    root->children.push_back(new Node<int>(2));
    root->children.push_back(new Node<int>(3));
    root->children[0]->children.push_back(new Node<int>(4));
    root->children[1]->children.push_back(new Node<int>(5));

    BFSIterator it = root->begin_bfs_scan();
    BFSIterator end = root->end_bfs_scan();

    std::stringstream ss;
    while (it != end) {
        ss << (*it)->value << " ";
        ++it;
    }
    
    // Check the output
    CHECK(ss.str() == "1 2 3 4 5 ");

    // Clean up
    deleteTree(root);
}

TEST_CASE("Test DFSIterator") {
    // Create a tree structure
    Node<int>* root = new Node<int>(1);
    root->children.push_back(new Node<int>(2));
    root->children.push_back(new Node<int>(3));
    root->children[0]->children.push_back(new Node<int>(4));
    root->children[1]->children.push_back(new Node<int>(5));

    DFSIterator it = root->begin_dfs_scan();
    DFSIterator end = root->end_dfs_scan();

    std::stringstream ss;
    while (it != end) {
        ss << (*it)->value << " ";
        ++it;
    }
    
    // Check the output
    CHECK(ss.str() == "1 3 5 2 4 ");

    // Clean up
    deleteTree(root);
}

TEST_CASE("Test HeapIterator") {
    // Create a tree structure
    Node<int>* root = new Node<int>(1);
    root->children.push_back(new Node<int>(2));
    root->children.push_back(new Node<int>(3));
    root->children[0]->children.push_back(new Node<int>(4));
    root->children[1]->children.push_back(new Node<int>(5));

    HeapIterator it = root->begin_heap();
    HeapIterator end = root->end_heap();

    std::stringstream ss;
    while (it != end) {
        ss << (*it)->value << " ";
        ++it;
    }
    
    // Check the output
    CHECK(ss.str() == "1 2 3 4 5 ");

    // Clean up
    deleteTree(root);
}
