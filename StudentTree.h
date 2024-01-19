// COP3530 -- Project1: GatorAVL Tree
// "Student.h" -- Created by: Madelyne Wirbel
// This file contains the class that creates the student (a node)
#pragma once
#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

class Tree{
private:

    struct Student{
        string name;
        string GatorID;
        int height;
        Student *left; // points to tree node to the left
        Student *right; // points to tree node to the right

        // --> FUNCTIONS <--
        Student(string name, string GatorID) { // constructor
            this->name = name;
            this->GatorID = GatorID;
            height = 1;

            left = nullptr;
            right = nullptr;
        }

        ~Student() = default; // destructor

    };

    Student* root; // holds the value of the root of the tree

    // --> INSERTION FUNCTIONS <--
// Function utilizes logic from powerpoints used in Professor Kapoor's Lecture
    Student* insertNode(Student* tempRoot, string name, string GatorID){ // creates the student node and inserts it within the tree class
        if (!foundID(GatorID, root)){ // double checks that GatorID in new node does not already exist in the tree
            if (tempRoot == nullptr) {
                tempRoot = new Student(name, GatorID); // this will become the root of the tree
            }
            else if (GatorID < tempRoot->GatorID) { // traverse left
                tempRoot->left = insertNode(tempRoot->left, name, GatorID);
                updateNodeHeight(tempRoot);
            }
            else { // traverse right
                tempRoot->right = insertNode(tempRoot->right, name, GatorID);
                updateNodeHeight(tempRoot);
            }

        }

        tempRoot = balanceTree(tempRoot);
        updateNodeHeight(tempRoot);
        root = tempRoot;
        return tempRoot;
    }

// Function utilizes logic from powerpoints used in Professor Kapoor's Lecture
    void updateNodeHeight(Student* tempRoot){ // recursively updates the height of all nodes in the tree
        if (tempRoot->left != nullptr && tempRoot->right != nullptr) { // checks to see that both left and right nodes are not empty
            tempRoot->height = 1 + max(tempRoot->left->height, tempRoot->right->height);
        }
        else if (tempRoot->left != nullptr || tempRoot->right != nullptr) { // checks to see that both left and right nodes are not empty
            if (tempRoot->left == nullptr){
                int lHeight = 0;
                tempRoot->height = 1 + max(lHeight, tempRoot->right->height);
            }
            else if (tempRoot->right == nullptr){
                int rHeight = 0;
                tempRoot->height = 1 + max(tempRoot->left->height, rHeight);
            }
        }
        else {
            tempRoot->height = 1;
        }

        // recursive calls
        if (tempRoot->right != nullptr){
            updateNodeHeight(tempRoot->right);
        }

        if (tempRoot->left != nullptr){
            updateNodeHeight(tempRoot->left);
        }
    }

    int getStudentHeight(Student* node){
        return node->height;
    }

    string getStudentName(Student* node){
        return node->name;
    }

    string getStudentID(Student* node){
        return node->GatorID;
    }

    void commaHelp(Student* node){ // determines whether or not a comma is needed when printing the trees
        if (node != nullptr){
            cout << ", ";
        }
    }

    // --> ROTATION FUNCTIONS <--
// For rotations Professor Kapoor's "Balanced Tree" slides were used as reference
// Only need left and right rotate functions because you can perform sequentially for dual cases
    Student* rotateLeft(Student* node){ // called when a right-right case is present
        Student* newParent = nullptr; // middle node becomes the root/ parent
        Student* grandChild = nullptr;
        if (node->right != nullptr){
            newParent = node->right; // original node will be less than the new parent
            grandChild = node->right->left;
            node->right = grandChild;
        }

        newParent->left = node;
        updateNodeHeight(node); // since the tree is rotated the heights must be updated
        return newParent;
    }

    Student* rotateRight(Student* node){ // called when a left-left case is present
        Student* newParent = nullptr; // middle node becomes the root/ parent
        Student* grandChild = nullptr;
        if (node->left != nullptr){
            newParent = node->left; // original node will be less than the new parent
            grandChild = node->left->right;
            node->left = grandChild;
        }

        newParent->right = node;
        updateNodeHeight(node); // since the tree is rotated the heights must be updated
        return newParent;
    }

    Student* rotateLeftRight(Student* node){
        Student* grandChild = node->left;
        Student* newChild = node->left->right; // node has to switch with the great grand child
        Student* greatGrandChild = node->left->right->left;

        node->left->right = greatGrandChild;
        node->left = newChild;
        newChild->left = grandChild;
        updateNodeHeight(node); // update the height

        Student* newParent = rotateRight(node);
        updateNodeHeight(node); // update the height after the second rotation
        return newParent;
    }

    Student* rotateRightLeft(Student* node){
        Student* grandChild = node->right;
        Student* newChild = node->right->left; // node has to switch with the great grand child
        Student* greatGrandChild = node->right->left->right;

        node->right->left = greatGrandChild;
        node->right = newChild;
        newChild->right = grandChild;
        updateNodeHeight(node); // update the height

        Student* newParent = rotateLeft(node);
        updateNodeHeight(node); // update the height after the second rotation
        return newParent;
    }

    // --> BALANCE FUNCTIONS <--
    int balanceFactor(Student* node){ // left - right
        int leftHeight;
        int rightHeight;
        if (node->left != nullptr){
            leftHeight = node->left->height;
        }
        else{
            leftHeight = 0;
        }

        if (node->right != nullptr){
            rightHeight = node->right->height;
        }
        else{
            rightHeight = 0;
        }

        return leftHeight - rightHeight;
    }

    Student* balanceTree(Student* node){
        int nodeBalanceFactor = balanceFactor(node);

        if (nodeBalanceFactor < -1){ // right imbalance
            if (balanceFactor(node->right) < 0){ // right-right case with one rotation
                node = rotateLeft(node);
            }
            else{ // right-left case with two rotations
                node = rotateRightLeft(node);
            }
        }

        if (nodeBalanceFactor > 1){ // left imbalance
            if (balanceFactor(node->left) > 0){
                node = rotateRight(node);
            }
            else{ // left-right case with two rotations
                node = rotateLeftRight(node);
            }
        }

        return node;
    }

    // --> SEARCH FUNCTIONS <--
    bool validGatorID(string GatorID){
        if (foundID(GatorID, root)){
            return false;
        }

        int digitCount = 0;

        for (char c : GatorID){
            if (isdigit(c)){
                digitCount += 1;
            }
            else if (c == '0'){
                digitCount += 1;
            }
            else{
                return false;
            }
        }

        if (digitCount == 8){ // length of a valid GatorID
            return true;
        }
        else{
            return false;
        }
    }

    bool validName(string name){ // using the AVL project breakdown video as reference
        for (char c : name){ // iterates through each character in the name
            if (!isalpha(c) && !isspace(c)) { // if the character is not in the alphabet OR a space (SPACES ALLOWED)
                return false;
            }
        }
        return true;
    }

    Student* foundID(string GatorID, Student* compNode){
        while (compNode != nullptr){
            if (compNode->GatorID == GatorID){
                return compNode;
            }
            else{
                Student* ID = foundID(GatorID, compNode->left);
                if (ID != nullptr){
                    return ID;
                }
                else{
                    Student* ID = foundID(GatorID, compNode->right);
                    return ID;
                }
            }
        }

        compNode = nullptr;
        return compNode;
    }

    void foundName(string name, Student* compNode, vector<Student*> &sameName){
        if (compNode == nullptr){ // base case
            return;
        }

        if (compNode->name == name){ // when the name you are searching for is in the node push_back to vector
            sameName.push_back(compNode);
        }

        // recursive calls
        foundName(name, compNode->left, sameName);
        foundName(name, compNode->right, sameName);
    }

    // --> ORDER FUNCTIONS <--
    void inorderHelper(Student* tempRoot){ // Left - Node - Right
        if (tempRoot != nullptr){
            inorderHelper(tempRoot->left);
            commaHelp(tempRoot->left); // need to check whether the comma should be printed-- use function

            cout << tempRoot->name;

            commaHelp(tempRoot->right);
            inorderHelper(tempRoot->right);
        }
    }

    void inorderVect(Student* tempRoot, vector<Student*> &studentVect){ // Left - Node - Right
        if (tempRoot != nullptr){
            inorderVect(tempRoot->left, studentVect);

            studentVect.push_back(tempRoot);

            inorderVect(tempRoot->right, studentVect);
        }
    }

    void inorderVectNames(Student* tempRoot, vector<string> &studentVect){ // Left - Node - Right
        if (tempRoot != nullptr){
            inorderVectNames(tempRoot->left, studentVect);

            studentVect.push_back(getStudentName(tempRoot));

            inorderVectNames(tempRoot->right, studentVect);
        }
    }

    Student* inorderSuccessor(Student* tempRoot){ // MUST PASS IN THE NODE TO THE RIGHT OF THE NODE TO DELETE
        if (tempRoot == nullptr){
            return nullptr;
        }

        while (tempRoot->left != nullptr){
            tempRoot = tempRoot->left;
        }
        return tempRoot;
    }

    void preorderHelper(Student* tempRoot){ // Node - Left - Right
        if (tempRoot != nullptr){
            cout << tempRoot->name;
            if (tempRoot->left){
                commaHelp(tempRoot->left);
            }
            else{
                commaHelp(tempRoot->right);
            }
            preorderHelper(tempRoot->left);

            // both a left and a right node must be present for a comma
            if (tempRoot->left && tempRoot->right){
                commaHelp(tempRoot->left);
            }
            preorderHelper(tempRoot->right);
        }
    }

    void preorderVectNames(Student* tempRoot, vector<string> &studentVect){ // Node - Left - Right
        if (tempRoot != nullptr){
            studentVect.push_back(getStudentName(tempRoot));

            preorderVectNames(tempRoot->left, studentVect);
            preorderVectNames(tempRoot->right, studentVect);
        }
    }

    void postorderHelper(Student* tempRoot){ // Left - Right - Node
        if (tempRoot != nullptr){
            postorderHelper(tempRoot->left);
            commaHelp(tempRoot->left);

            postorderHelper(tempRoot->right);
            commaHelp(tempRoot->right);

            cout << tempRoot->name;
        }
    }

    void postorderVectNames(Student* tempRoot, vector<string> &studentVect){ // Left - Right - Node
        if (tempRoot != nullptr){
            postorderVectNames(tempRoot->left, studentVect);
            postorderVectNames(tempRoot->right, studentVect);

            studentVect.push_back(getStudentName(tempRoot));
        }
    }

    // --> REMOVAL FUNCTIONS <--
    Student* parentOfDelete(Student* deleteNode, Student* compNode){
        //estasblish cases in which the function should return nullptr
        if (compNode == nullptr){
            return nullptr;
        }
        if (compNode->left == nullptr && compNode->right == nullptr){
            return nullptr;
        }

        // breakout case
        if (compNode->left == deleteNode || compNode->right == deleteNode){
            return compNode;
        }

        // recursive calls
        if (compNode->GatorID > deleteNode->GatorID){ // left traversal
            return parentOfDelete(deleteNode, compNode->left); // BE SURE TO RETURN THE RECURSIVE STATEMENTS OTHERWISE OVERRIDDEN
        }
        if (compNode->GatorID < deleteNode->GatorID) { // right traversal
            return parentOfDelete(deleteNode, compNode->right);
        }

    }

    string removeIDHelper(string GatorID){
        Student* deleteNode = foundID(GatorID, root);

        if (deleteNode != nullptr){
            Student* tempNode = nullptr; // need to create a temp node in order to reallocate pointers
            if (deleteNode == root){ // edge case
                tempNode = inorderSuccessor(deleteNode->right);

                if (tempNode == nullptr){ // if there is no in order successor
                    if (root->left != nullptr){ // if there is a node to the left of the root
                        root = root->left;
                    }
                    else{
                        root = nullptr;
                    }
                    delete deleteNode;
                    cout << "successful\n";
                    return "successful";
                }

                if (root->right != tempNode){ // if the successor is not directly to the right of the root
                    if (tempNode->right != nullptr){
                        Student* parentOfTemp = parentOfDelete(tempNode, deleteNode->right);
                        parentOfTemp->left = tempNode->right;
                        updateNodeHeight(parentOfTemp);
                    }
                    else{
                        Student* parentOfTemp = parentOfDelete(tempNode, deleteNode->right);
                        parentOfTemp->left = nullptr;
                        updateNodeHeight(parentOfTemp);
                    }
                    tempNode->left = root->left;
                    tempNode->right = root->right;
                }

                tempNode->left = root->left;
                root = tempNode;
                delete deleteNode;
                root->height = 0;
                updateNodeHeight(root);
                cout << "successful\n";
                return "successful";
            }
            // if the node to delete is not the node you need to know it's parent so you don't chop off the branch
            Student* parentDelete = parentOfDelete(deleteNode, root);
            // no children
            if (deleteNode->left == nullptr && deleteNode->right == nullptr){
                if (deleteNode == root){
                    root = nullptr;
                    delete deleteNode;
                }
                else{ // assigns the parent left/ right node pointer nullptr if pointing to the node to delete
                    if (parentDelete->left == deleteNode){
                        parentDelete->left = nullptr;
                    }
                    else if (parentDelete->right == deleteNode){
                        parentDelete->right = nullptr;
                    }
                    delete deleteNode;
                }
            }

            // one child
            if (deleteNode->left != nullptr && deleteNode->right == nullptr){ // the node to be deleted has a child to the left
                if (parentDelete->right == deleteNode){
                    parentDelete->right = deleteNode->left;
                }
                else if (parentDelete->left == deleteNode){
                    parentDelete->left = deleteNode->left; // only has a left child so the left child has to be reassigned
                }
                delete deleteNode;
            }

            if (deleteNode->left == nullptr && deleteNode->right != nullptr){ // the node to be deleted has a child to the right
                if (parentDelete->right == deleteNode){
                    parentDelete->right = deleteNode->right;
                }
                else if (parentDelete->left == deleteNode){
                    parentDelete->left = deleteNode->right; // only has a right child so the right child has to be reassigned
                }
                delete deleteNode;
            }

            // two children
            if (deleteNode->left != nullptr && deleteNode->right != nullptr){
                tempNode = inorderSuccessor(deleteNode->right);
                if (parentDelete->right == deleteNode){
                    parentDelete->right = tempNode;
                }
                else if (parentDelete->left == deleteNode){
                    parentDelete->left = tempNode;
                }
                tempNode->left = deleteNode->left;
                delete deleteNode;
            }

            updateNodeHeight(root);
            cout << "successful\n";
            return "successful";
        }
        else{
            cout << "unsuccessful\n";
            return "unsuccessful";
        }
    }

    string removeInorderHelper(int n){
        if (root == nullptr){
            cout << "unsuccessful\n";
            return "unsuccessful";
        }

        vector<Student*> studentVect;
        inorderVect(root, studentVect); // keeps the nodes in a vector inorder sort

        if (studentVect.size() - 1 >= n){
            Student* deleteNode = studentVect[n];
            Student* tempNode = nullptr; // need to create a temp node in order to reallocate pointers
            if (deleteNode == root){ // edge case
                tempNode = inorderSuccessor(deleteNode->right);

                if (tempNode == nullptr){ // if there is no successor
                    if (root->left != nullptr){ // if there is a node to the left of the root
                        root = root->left;
                    }
                    else{
                        root = nullptr;
                    }
                    delete deleteNode;
                    cout << "successful\n";
                    return "successful";
                }

                if (root->right != tempNode){ // if the successor is not directly to the right of the root
                    if (tempNode->right != nullptr){
                        Student* parentOfTemp = parentOfDelete(tempNode, deleteNode->right);
                        parentOfTemp->left = tempNode->right;
                        updateNodeHeight(parentOfTemp);
                    }
                    else{
                        Student* parentOfTemp = parentOfDelete(tempNode, deleteNode->right);
                        parentOfTemp->left = nullptr;
                        updateNodeHeight(parentOfTemp);
                    }
                    tempNode->left = root->left;
                    tempNode->right = root->right;
                }

                root = tempNode;
                delete deleteNode;
                root->height = 0; // must update the root height otherwise it will be off by one
                updateNodeHeight(root);
                cout << "successful\n";
                return "successful";
            }

            // if the node to delete is not the node you need to know it's parent so you don't chop off the branch
            Student* parentDelete = parentOfDelete(deleteNode, root);
            // no children
            if (deleteNode->left == nullptr && deleteNode->right == nullptr){
                if (deleteNode == root){
                    root = nullptr;
                    delete deleteNode;
                }
                else{ // assigns the parent left/ right node pointer nullptr if pointing to the node to delete
                    if (parentDelete->left == deleteNode){
                        parentDelete->left = nullptr;
                    }
                    else if (parentDelete->right == deleteNode){
                        parentDelete->right = nullptr;
                    }
                    delete deleteNode;
                }
            }

            // one child
            if (deleteNode->left != nullptr && deleteNode->right == nullptr){ // the node to be deleted has a child to the left
                if (parentDelete->right == deleteNode){
                    parentDelete->right = deleteNode->left;
                }
                else if (parentDelete->left == deleteNode){
                    parentDelete->left = deleteNode->left;
                }
                delete deleteNode;
            }

            if (deleteNode->left == nullptr && deleteNode->right != nullptr){ // the node to be deleted has a child to the left
                if (parentDelete->right == deleteNode){
                    parentDelete->right = deleteNode->right;
                }
                else if (parentDelete->left == deleteNode){
                    parentDelete->left = deleteNode->right;
                }
                delete deleteNode;
            }

            // two children
            if (deleteNode->left != nullptr && deleteNode->right != nullptr){
                tempNode = inorderSuccessor(deleteNode->right);
                if (parentDelete->right == deleteNode){
                    parentDelete->right = tempNode;
                }
                else if (parentDelete->left == deleteNode){
                    parentDelete->left = tempNode;
                }
                tempNode->left = deleteNode->left;
                delete deleteNode;
            }
            cout << "successful\n";
            updateNodeHeight(parentDelete);
            updateNodeHeight(root);
            return "successful";

        }
        cout << "unsuccessful\n";
        return "unsuccessful";
    }


public:
    // DO NOT directly access private members in public functions
    Tree(){ // constructor
        root = nullptr;
    }

    ~Tree()= default; // destructor

    string insert(string name, string GatorID){
        if (validGatorID(GatorID) && validName(name)){
            cout << "successful\n";
            root = insertNode(root, name, GatorID); // updates the root of the tree if needed
            return "successful";
        }
        else{
            cout << "unsuccessful\n";
            return "unsuccessful";
        }

    }

    vector<string> printPostorder(){
        postorderHelper(root);
        if (root != nullptr){
            cout << "\n";
        }
        vector<string> returnVect;
        postorderVectNames(root, returnVect);
        return returnVect;
    }

    vector<string> printPreorder(){
        preorderHelper(root);
        if (root != nullptr){
            cout << "\n";
        }
        vector<string> returnVect;
        preorderVectNames(root, returnVect);
        return returnVect;
    }

    vector<string> printInorder(){ // must return a value
        inorderHelper(root);
        if (root != nullptr){
            cout << "\n";
        }
        vector<string> returnVect;
        inorderVectNames(root, returnVect);
        return returnVect;
    }

    string searchID(string GatorID){
        Student* temp = foundID(GatorID, root);
        if (temp != nullptr){
            cout << getStudentName(temp) << "\n";
            return getStudentName(temp);
        }
        else{
            cout << "unsuccessful\n";
            return "unsuccessful";
        }
    }

    string searchName(string name){
        vector<Student*> nameNodes; // must push names to a vector in order to catch multiple names
        foundName(name, root, nameNodes);
        if (nameNodes.size() == 0){
            cout << "unsuccessful\n";
            return "unsuccessful";
        }
        string GatorIDString;
        for (int i = 0; i < nameNodes.size(); i++){
            cout << getStudentID(nameNodes[i]) << "\n";
            GatorIDString += getStudentID(nameNodes[i]);
        }
        return GatorIDString;
    }

    int printLevelCount(){
        if (root != nullptr){
            cout << getStudentHeight(root) << "\n";
            return getStudentHeight(root);
        }
        else{
            cout << "0\n";
            return 0;
        }
    }

    string removeID(string GatorID){ // will return a pointer to the node needed to connect
        return removeIDHelper(GatorID);
    }

    string removeInorder(int n){
        return removeInorderHelper(n);
    }


};
