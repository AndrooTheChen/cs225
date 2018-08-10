/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node * subNode)
{
    if (subNode == NULL) { return; }
    mirror(subNode->left);
    mirror(subNode->right);

    // swap
    if (subNode->left == NULL && subNode->right == NULL) { return; }
    else if (subNode->left == NULL) {
        subNode->left = subNode->right;
        subNode->right = NULL;
    } else if (subNode->right == NULL) {
        subNode->right = subNode->left;
        subNode->left = NULL;
    } else {
        Node * temp = subNode->left;
        subNode->left = subNode->right;
        subNode->right = temp;
    }
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    return false;
}

template <typename T>
bool BinaryTree::isOrderedIterative(Node * subRoot) const
{
    std::vector<T> v;
    std::stack<Node *> s;
    Node * curr = subRoot;

    s.push(curr);
    curr = curr->left;
    while (curr != NULL && !s.empty()) {
        s.push(curr);
        curr = curr->left;
        while (curr == NULL && !s.empty()) {
            Node * temp = s.top();
            v.push_back(temp->elem);
            s.pop();
            curr = temp->right;
        }
    }

    int i = 0;
    for (int ctr = 0; ctr < v.size(); ctr++) {
        if (v[i++] > v[ctr]) { return false; }
    }

    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{

    // your code here
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree::isOrderedRecursive(Node * subRoot) const
{
    bool isOrdered = true;
    if (subRoot == NULL) { return true; }

    isOrdered = isOrderedRecursive(subRoot->left);

    if (subRoot->left == NULL && subRoot->right == NULL) { return true; }
    else if (subRoot->left == NULL) {
        return (subRoot->right.elem <= this->elem) { return false; }
    } else if (subRoot->right == NULL) {
        if (subRoot->left.elem >= this->elem) { return false; }
    } else {
        if (subRoot->left.elem >= this->elem) { return false; }
        if (subRoot->right.elem <= this->elem) { return false; }
    }
 
    isOrdered = isOrderedRecursive(subRoot->right);

    return isOrdered;
}

/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
    std::vector<T> v;
    findPaths(root, v, paths);
    int num = 0;
    for (vector<vector<T>::iterator i = paths.begin(); i != paths.end(); i++) {
        cout << "paths[" << num++ << "]: ";
        for (vector<T>::iterator j = v.begin(); j != v.end(); j++) {
            cout << paths[i][j] << " ";
        }
        cout << endl;
    }
    
}

template <typename T>
void BinaryTree<T>::findPaths(Node * subRoot, vector<T> &v, vector<vector<T>> &paths)
{
    //if (subRoot == NULL || subRoot->elem == -1) { return; }
    if (subRoot == NULL) { return; }
    v.push_back(subRoot->elem);
    findPaths(subRoot->left, v, paths);
    if (subRoot->left == NULL && subRoot->right == NULL) {
        v.push_back(subRoot->elem);
        //subRoot->elem = -1;
        paths.push_back(v);
        return;
    }
    findPaths(subRoot->right, v, paths);
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    int running_sum = 0;
    int static total_sum = 0;
    sumDistances(root, running_sum, total_sum);
    return total_sum;
}

template <typename T>
void BinaryTree<T>::sumDistances(Node * subRoot, int rsum, int static tsum)
{
    if (subRoot == NULL) { return; }
    tsum += rsum;
    if (subRoot->left != NULL) sumDistances(subRoot->left, rsum+1, tsum);
    if (subRoot->right != NULL) sumDistances(subRoot->right, rsum+1, tsum);
}

