#pragma once

#include <string>

#define BLACK 0
#define RED 1
#define SPACE_COUNT 10

struct RBNode
{
    // Attributes
    int _key;
    bool _color;

    typedef RBNode* RBRef;

    RBRef _parent;
    RBRef _left;
    RBRef _right;

    // Constructor 
    RBNode(int key, bool color,
    RBRef parent, RBRef left, RBRef right);
};

typedef RBNode* RBRef;

/* MAIN OPERATIONS */
    RBRef getNode(int key, int color);
    RBRef lookUp(RBRef pRoot, int key);
    void Insert(RBRef &pRoot, int key);
    void Remove(RBRef &pRoot, int key);
    int Height(RBRef pRoot);
    int BlackHeight(RBRef pRoot);
    RBRef createTree(int a[], int n);
    void removeTree(RBRef& pRoot);
    void print2D(RBRef pRoot);

/* SUPPORTING OPERATIONS */
    // Basic helpers
    void swapColor(RBRef &x);
    void rotateRight(RBRef &pRoot, RBRef subRoot);
    void rotateLeft(RBRef &pRoot, RBRef subRoot);

    // Insertion helpers
    void insert_BST(RBRef& rootParent, RBRef& pRoot, RBRef& insertee); 
    void AdjustLeft_insertion(RBRef &pRoot, RBRef &child);  
    void AdjustRight_insertion(RBRef &pRoot, RBRef &child);  
    void FixUp_insertion(RBRef &pRoot, RBRef &child);

    // Deletion helpers
    int countChildren(RBRef pNode);
    RBRef findLMS(RBRef pRoot);
    void findSubstituteAndTransfer
    (RBRef& pRoot, RBRef& removee, RBRef& substitute, RBRef& heir);
    void AdjustLeft_removal(RBRef &pRoot, RBRef &heir);  
    void AdjustRight_removal(RBRef &pRoot, RBRef &heir);  
    void FixUp_removal(RBRef pRoot, RBRef accused);

    // Other helpers
    std::string duplicate(std::string unit, int qtt);
    void internalPrint2D(RBRef pRoot, int spaceQtt);